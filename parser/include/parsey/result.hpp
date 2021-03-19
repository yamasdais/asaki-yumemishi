#pragma once

#include <functional>
#include <concepts>
#include <variant>

#include <parsey/fwd/result.hpp>
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

template <class ResT, parse_error SrcError, parse_error ResError = SrcError>
requires std::same_as<SrcError, ResError> || std::constructible_from<ResError,
    SrcError>
struct result_error_merger {
    constexpr auto operator()(SrcError const& err) const {
        if constexpr (std::same_as<SrcError, ResError>) {
            return make_parse_result<ResT>(err);
        } else {
            return make_parse_result<ResT>(ResError(err));
        }
    }
    constexpr auto operator()(SrcError&& err) const {
        if constexpr (std::same_as<SrcError, ResError>) {
            return make_parse_result<ResT>(std::move(err));
        } else {
            return make_parse_result<ResT>(ResError(std::move(err)));
        }
    }
};

}  // namespace parsey

namespace parsey::detail {

template <class T, std::invocable<T> Func, parse_error InErr>
requires(!parse_error<T>)
    && parse_result<std::invoke_result_t<Func, T>> struct ResultVisitorImpl {
    using value_handler_t = result_value_handler<T, Func>;
    using result_t = std::invoke_result_t<Func, T>;
    using error_marger_t = result_error_merger<parse_result_value_t<result_t>,
        InErr, parse_result_error_t<result_t>>;

    constexpr ResultVisitorImpl(Func const& func) noexcept
        : value_handler{func} {}

    constexpr ResultVisitorImpl(Func&& func) noexcept
        : value_handler{std::move(func)} {}

    constexpr auto operator()(T const& value) const& {
        return std::invoke(value_handler, value);
    }
    constexpr auto operator()(T&& value) const& {
        return std::invoke(value_handler, std::move(value));
    }
    constexpr auto operator()(T const& value) const&& {
        return std::invoke(std::move(value_handler), value);
    }
    constexpr auto operator()(T&& value) const&& {
        return std::invoke(std::move(value_handler), std::move(value));
    }

    constexpr auto operator()(InErr const& err) const {
        return std::invoke(error_marger_t{}, err);
    }
    constexpr auto operator()(InErr&& err) const {
        return std::invoke(error_marger_t{}, std::move(err));
    }

    [[no_unique_address]] value_handler_t value_handler;
};

}  // namespace parsey::detail

namespace parsey {

template <parse_result Result,
    std::invocable<parse_result_value_t<Result>> Func>
requires parse_result<std::invoke_result_t<Func, parse_result_value_t<Result>>>
constexpr auto make_result_visitor(Result const&, Func&& func) {
    return detail::ResultVisitorImpl<parse_result_value_t<Result>,
        std::remove_cvref_t<Func>, parse_result_error_t<Result>>{
        std::forward<Func>(func)};
}

}  // namespace parsey