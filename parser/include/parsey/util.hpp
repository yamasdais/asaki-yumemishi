
#pragma once

#include <concepts>
#include <type_traits>
#include <functional>

#include <parsey/detail/util.hpp>

namespace parsey {

// Category: meta programming


template <class T, std::size_t I>
using get_tparam_t = typename detail::GetParamTypeImpl<I, std::remove_cvref_t<T>>::type;

template <template <class...> class To, class From>
using copy_tparam_t = typename detail::CopyParamTypesImpl<To, std::remove_cvref_t<From>>::type;

template <class Func, class... Args>
concept lambda_nocapture = std::invocable<Func, Args...>
&& std::is_class_v<Func> && std::default_initializable<Func>;

template <class Func>
struct invocable_holder {
    constexpr invocable_holder(Func const& func)
    : func{func} {}
    constexpr invocable_holder(Func&& func)
    : func{std::forward<Func>(func)} {}

    template <class... Args>
    requires std::invocable<Func, Args...>
    constexpr auto operator()(Args&& ...args) const & {
        return std::invoke(func, std::forward<Args>(args)...);
    }

    template <class... Args>
    constexpr auto operator()(Args&& ...args) && {
        return std::invoke(std::move(func), std::forward<Args>(args)...);
    }
  private:
    Func func;
};
template <class Func>
requires std::is_class_v<Func> && std::default_initializable<Func>
struct invocable_holder<Func> {
    constexpr invocable_holder(Func const&) {}
    constexpr invocable_holder(Func&&) {}

    template <class... Args>
    requires std::invocable<Func, Args...>
    constexpr auto operator()(Args&& ...args) const {
        return std::invoke(Func{}, std::forward<Args>(args)...);
    }
};

template <std::semiregular T, class Func>
struct accumulator {
    using value_type = T;
    constexpr explicit accumulator(T value = T{}, Func func = Func{}) noexcept(
        noexcept(std::is_nothrow_default_constructible_v<T>))
        : func{std::move(func)}
        , value{std::move(value)} {}

    constexpr T& operator*() & noexcept { return value; }
    constexpr T const& operator*() const& noexcept { return value; }
    constexpr T operator*() && noexcept { return std::move(value); }

    template <class V>
    constexpr accumulator& operator()(V v) requires
        std::invocable<Func, T, V> || std::invocable<Func, T&, V> {
        if constexpr (std::invocable<Func, T, V>) {
            static_assert(
                std::convertible_to<std::invoke_result_t<Func, T, V>, T>,
                "return value unmatched");
            value = std::move(std::invoke(
                std::forward<Func>(func), std::move(value), std::move(v)));
        } else {
            std::invoke(std::forward<Func>(func), value, std::move(v));
        }
        return *this;
    }

    template <std::semiregular ResT, class ResFunc = Func>
    constexpr auto fmap(auto&& proj) requires
        std::convertible_to<std::invoke_result_t<decltype(proj), T>, ResT> {
        using ret_t =
            std::remove_cvref_t<std::invoke_result_t<decltype(proj), T>>;
        return accumulator<ret_t, ResFunc>{
            std::invoke((decltype(proj))proj, value)};
    }

  private:
    Func func;
    T value;
};

template <template <class...> class ParamT, class T>
constexpr auto make_accumulator = [](auto&&func) requires std::invocable<decltype(func),
                            ParamT<T>, T> || std::invocable < decltype(func),
     ParamT<T>
&, T > {
    return accumulator(ParamT<T>{}, (decltype(func))func);
};

}  // namespace parsey