#pragma once

// unused. will remove
#include <concepts>

#include <parsey/util.hpp>
#include <parsey/error.hpp>
#include <parsey/source.hpp>

namespace parsey {

template <class T>
concept parse_facade = parse_source<get_tparam_t<T, 0>>&&
    parse_error<get_tparam_t<T, 1>>;

template <parse_facade Facade>
using facade_source_t = detail::GetParametricType<Facade, 0>;

template <parse_facade Facade>
using facade_error_t = detail::GetParametricType<Facade, 1>;

//template <parse_source Source, parse_error Error = default_parser_error>
//struct parser_facade_t {};

}