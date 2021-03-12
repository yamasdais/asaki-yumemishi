
#pragma once

#include <concepts>
#include <functional>

#include <parsey/detail/util.hpp>

namespace parsey {

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
template <class X> struct tt;
    template <std::semiregular ResT, class ResFunc = Func>
    constexpr auto fmap(auto&& proj)
    requires std::convertible_to<std::invoke_result_t<decltype(proj), T>, ResT>
    {
        using ret_t = std::remove_cvref_t<std::invoke_result_t<decltype(proj), T>>;
        return accumulator<ret_t, ResFunc>{std::invoke((decltype(proj))proj, value)};
    }

  private:
    Func func;
    T value;
};

template <template <class...> class ParamT, class T>
auto make_accumulator = [](auto&& func)
requires std::invocable<decltype(func), ParamT<T>, T> || std::invocable<decltype(func), ParamT<T>&, T> {
    return accumulator(ParamT<T>{}, (decltype(func))func);
};

template <std::semiregular T, auto func>
struct associator0 {
    using function_type = decltype(func);
    constexpr explicit associator0() = default;
    constexpr explicit associator0(T&& v) noexcept
        : val{std::forward<T>(v)} {}

    template <class Arg>
    constexpr void operator()(Arg v) requires(
        std::invocable<function_type, T,
            Arg> || std::invocable<function_type, T&, Arg>) {
        if constexpr (std::invocable<function_type, T, Arg>) {
            static_assert(
                std::convertible_to<std::invoke_result_t<function_type, T, Arg>,
                    T>,
                "return type unmatch");
            val = std::move(std::invoke(func, std::move(val), v));
        } else {
            std::invoke(func, val, v);
        }
    }

    constexpr T& get() & noexcept { return val; }

    constexpr T const& get() const& noexcept { return val; }

    constexpr T get() && noexcept { return std::move(val); }

  private:
    T val;
};
}  // namespace parsey