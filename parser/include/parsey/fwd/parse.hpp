#pragma once

#include <concepts>

#include <parsey/util.hpp>
#include <parsey/fwd/result.hpp>
#include <parsey/fwd/source.hpp>

namespace parsey {

struct parser_tag {};
struct scan_source_parser_tag : public parser_tag {};

template <class Result, class T, class Source>
concept parse_result_from =
    parse_source<Source>&& std::convertible_to<parse_result_value_t<Result>,
        T>&& std::same_as<parse_result_error_t<Result>,
        parse_source_error_t<Source>>;


template <class Parse, class Source>
concept parser_with = parse_source<Source>&& std::invocable<Parse, Source&>;

template <class Func, class Source>
concept parse_trait = parse_source<Source>&&
    std::invocable<Func, parse_source_input_value_t<Source>>;

template <class Parser, parse_source Source>
requires parser_with<Parser, Source> using parser_return_value_t =
    parse_result_value_t<std::invoke_result_t<Parser, Source&>>;

}