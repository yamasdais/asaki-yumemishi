#pragma once

#include <functional>
#include <concepts>
#include <variant>

#include <parsey/error.hpp>
#include <parsey/util.hpp>
#include <parsey/detail/result.hpp>

namespace parsey {

template <class T, parse_error Error>
requires(!parse_error<T>) struct result {
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
    requires requires(Func f, result_type r) { {std::visit(f, r)}; }
    constexpr auto fmap(Func&& func) const {
        return std::visit(std::forward<Func>(func), result_value);
    }

    template <class Func>
    requires std::invocable<Func, T const> && std::invocable<Func, Error const>
    constexpr inline friend auto visit(Func&& func, result const& r) {
        return std::visit(std::forward<Func>(func), r.result_value);
    }

  private:
    result_type result_value;
};

template <parse_error Error>
constexpr inline auto make_parse_result(auto value) requires(
    !parse_error<std::remove_cvref_t<decltype(value)>>) {
    return result<decltype(value), Error>(std::move(value));
}
template <class T>
requires(!parse_error<T>) constexpr inline auto make_parse_result(
    parse_error auto error) {
    return result<T, decltype(error)>(std::move(error));
}

template <class T, std::invocable<T> Conv>
struct result_value_handler {
    constexpr result_value_handler(Conv const& converter)
        : converter{converter} {}
    constexpr result_value_handler(Conv&& converter)
        : converter{std::forward<Conv>(converter)} {}

    constexpr auto operator()(T const& v) const& {
        return std::invoke(converter, v);
    }
    constexpr auto operator()(T&& v) const& {
        return std::invoke(converter, std::move(v));
    }

    constexpr auto operator()(T const& v) const&& {
        return std::invoke(std::move(converter), v);
    }
    constexpr auto operator()(T&& v) const&& {
        return std::invoke(std::move(converter), std::move(v));
    }

  private:
    Conv converter;
};
template <class T, std::invocable<T> Conv>
requires lambda_nocapture<Conv, T>
struct result_value_handler<T, Conv> {
    constexpr result_value_handler(Conv const&) {}
    constexpr result_value_handler(Conv&&) {}
    constexpr auto operator()(T const& v) const {
        return std::invoke(Conv{}, v);
    }
    constexpr auto operator()(T&& v) const {
        return std::invoke(Conv{}, std::move(v));
    }
};

template <parse_result Result,
    std::invocable<parse_result_value_t<Result>> Func>
requires parse_result<std::invoke_result_t<Func, parse_result_value_t<Result>>>
constexpr auto make_result_visitor(Result const&, Func&& func) {
    return detail::ResultVisitorImpl<parse_result_value_t<Result>,
        std::remove_cvref_t<Func>, parse_result_error_t<Result>>{
        std::forward<Func>(func)};
}

}  // namespace parsey