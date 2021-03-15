#pragma once

#include <functional>
#include <concepts>
#include <variant>

#include <parsey/error.hpp>

namespace parsey {

template <class T>
concept parse_result = requires(T val) {
    typename T::value_type;
    { static_cast<bool>(val) } -> std::same_as<bool>;
    { !val } -> std::same_as<bool>;
    { *val };
    { val.error() };
};

template <parse_result Result>
using parse_result_value_t =
    std::remove_cvref_t<decltype(*std::declval<Result>())>;

template <parse_result Result>
using parse_result_error_t =
    std::remove_cvref_t<decltype(std::declval<Result>().error())>;

// TODO: move to fwd/result.hpp
template <class T, parse_error Error>
struct result;

template <class RetT, parse_error Error, std::invocable<Error> ErrCnv>
struct result_error_handler {
    constexpr auto operator()(Error const&& err) const {
        return result<RetT, Error>{ErrCnv{}(std::forward<Error>(err))};
    }
};

template <class T, std::invocable<T> Func, parse_error Error,
    std::invocable<Error> ErrCnv = std::identity>
requires std::invocable<Func, T>
struct result_value_visitor
    : result_error_handler<std::invoke_result_t<Func, T>, Error, ErrCnv> {
    using ret_t = std::invoke_result_t<Func, T>;
    constexpr auto operator()(T v) const {
        return result<ret_t, Error>{std::invoke(Func{}, std::move(v))};
    }
    using result_error_handler<ret_t, Error, ErrCnv>::operator();
};

template <class T, parse_error Error>
constexpr auto make_result_visitor(std::invocable<T> auto&& func) requires
    std::invocable<std::remove_cvref_t<decltype(func)>, T> {
    return result_value_visitor<T, std::remove_cvref_t<decltype(func)>,
        Error>{};
}

template <class T, parse_error Error>
struct result {
    using value_type = T;
    using result_type = std::variant<T, Error>;

    constexpr explicit result(T v)
        : result_value{std::move(v)} {}

    constexpr explicit result(Error err)
        : result_value{std::move(err)} {}

    constexpr operator bool() const noexcept {
        return result_value.index() == 0u;
    }
    constexpr bool operator!() const noexcept { return !(bool)*this; }

    constexpr value_type operator*() const { return std::get<0>(result_value); }

    constexpr auto error() const { return std::get<1>(result_value); }

    template <class Func>
    requires std::invocable<Func, T const> && std::invocable<Func,
        Error const> && std::same_as<std::invoke_result_t<Func, T const>,
        std::invoke_result_t<Func, Error const>>
        && requires(Func f, result_type r) {
            {std::visit(f, r)}
                ->std::convertible_to<std::invoke_result_t<Func, T const>>;
        }
    constexpr auto fmap(Func&& func) const {
        return std::visit(std::forward<Func>(func), result_value);
    }

  private:
    result_type result_value;
};

template <parse_error Error>
constexpr inline auto make_parse_result(auto value) {
    return result<decltype(value), Error>(std::move(value));
}
template <class T>
constexpr inline auto make_parse_result(parse_error auto error) {
    return result<T, decltype(error)>(std::move(error));
}

}  // namespace parsey