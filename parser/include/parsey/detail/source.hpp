#pragma once

#include <concepts>

#include <parsey/fwd/error.hpp>
#include <parsey/fwd/source.hpp>
#include <parsey/detail/result.hpp>

namespace parsey::detail {

template <class Func, parse_source Source,
            class InVal = parse_source_input_value_t<Source>,
            class Result = std::invoke_result_t<Func, InVal>>
    requires std::invocable<Func, parse_source_input_value_t<Source>>
        && parse_result<std::invoke_result_t<
                Func, parse_source_input_value_t<Source>>>
struct SourceResultVisitor
    : public ResultVisitorImpl<parse_result_value_t<Result>,
        std::remove_cvref_t<Func>, parse_source_error_t<Source>> {
    using err_t = parse_source_error_t<Source>;
    using base_t = ResultVisitorImpl<parse_result_value_t<Result>,
        std::remove_cvref_t<Func>, err_t>;
    constexpr SourceResultVisitor(Func const& func)
        : base_t{func} {}
    constexpr SourceResultVisitor(Func&& func)
        : base_t{std::forward<Func>(func)} {}

    using base_t::operator();
};

}