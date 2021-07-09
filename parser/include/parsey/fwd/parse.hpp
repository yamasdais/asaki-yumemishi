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
    requires parser_with<Parser, Source>
using parser_return_value_t =
    parse_result_value_t<std::invoke_result_t<Parser, Source&>>;

template <class Parse, class Source>
concept parser_preparable_from = parser_with<Parse, Source>
&& requires (Parse p, Source) {
    {p.template prepare<Source>()} -> parser_with<Source>;
};

template <parse_source Source>
constexpr auto prepare_parser(auto&& parser)
requires parser_preparable_from<std::remove_cvref_t<decltype(parser)>, Source>
{
    return std::forward<decltype(parser)>(parser).template prepare<Source>();
}

template <parse_source Source>
constexpr auto prepare_possibly(auto&& parser) {
    using Parser = std::remove_cvref_t<decltype(parser)>;
    static_assert(parser_with<Parser, Source>, "Invalid Parser with Source");
    if constexpr (parser_preparable_from<Source, Parser>) {
        return parepare_parser<Source>(std::forward<Parser>(parser));
    } else {
        return std::forward<Parser>(parser);
    }
}

}  // namespace parsey
