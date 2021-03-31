#pragma once

#include <concepts>

#include <parsey/util.hpp>
#include <parsey/fwd/locator.hpp>
#include <parsey/fwd/error.hpp>
#include <parsey/fwd/result.hpp>

namespace parsey {

template <class Source>
concept parse_source = requires(Source& src) {
    typename Source::input_value_type;
    typename Source::error_type;
    typename Source::value_type;
    { *src } -> parse_result_with<typename Source::input_value_type,
                    typename Source::error_type>;
    { ++src };
    { src.consume() } -> parse_result_with<
        typename Source::input_value_type,
        typename Source::error_type>;
    { std::as_const(src).locate() } -> locator;
}
&&std::forward_iterator<std::remove_cvref_t<Source>>&& parse_error<typename Source::error_type>;

template <parse_source T>
using parse_source_error_t = typename T::error_type;
template <parse_source T>
using parse_source_input_value_t = typename T::input_value_type;
template <parse_source T>
using parse_source_result_t = typename T::value_type;

}