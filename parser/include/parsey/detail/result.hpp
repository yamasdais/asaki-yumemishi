#pragma once

#include <concepts>

#include <parsey/fwd/error.hpp>
#include <parsey/fwd/result.hpp>

namespace parsey::detail {

template <class ResT, parse_error SrcError, parse_error ResError = SrcError>
requires std::same_as<SrcError, ResError> || std::constructible_from<ResError,
    SrcError>
struct ResultErrorMerger {
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

template <class T, std::invocable<T> Func, parse_error InErr>
requires(!parse_error<T>)
    && parse_result<std::invoke_result_t<Func, T>> struct ResultVisitorImpl {
    using value_handler_t = result_value_handler<T, Func>;
    using result_t = std::invoke_result_t<Func, T>;
    using error_marger_t = ResultErrorMerger<parse_result_value_t<result_t>,
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
    constexpr auto operator()(T const& value) && {
        return std::invoke(std::move(value_handler), value);
    }
    constexpr auto operator()(T&& value) && {
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