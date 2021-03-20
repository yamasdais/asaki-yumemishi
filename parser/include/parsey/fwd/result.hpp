#pragma once

#include <concepts>

#include <parsey/util.hpp>
#include <parsey/fwd/error.hpp>

namespace parsey {

template <class T>
concept parse_result = requires(T val) {
    typename T::value_type;
    { static_cast<bool>(val) } -> std::same_as<bool>;
    { !val } -> std::same_as<bool>;
    { *val };
    { val.error() } -> parse_error;
};

template <class Func, class Arg>
concept parse_value_to_result =
    std::invocable<Func, Arg> && parse_result<std::invoke_result_t<Func, Arg>>;

template <parse_result Result>
using parse_result_value_t =
    std::remove_cvref_t<decltype(*std::declval<Result>())>;

template <parse_result Result>
using parse_result_error_t =
    std::remove_cvref_t<decltype(std::declval<Result>().error())>;

template <class Result, class Value, class Error>
concept parse_result_with = parse_result<Result>  // result
    &&(!parse_error<Value>)&&parse_error<Error>&& std::same_as<Value,
        parse_result_value_t<Result>>&& std::same_as<Error,
        parse_result_error_t<Result>>;

template <class T, parse_error Error>
requires(!parse_error<T>) struct result;

template <parse_error Error>
constexpr inline auto make_parse_result(auto value) requires(
    !parse_error<std::remove_cvref_t<decltype(value)>>);

template <class T>
requires(!parse_error<T>) constexpr inline auto make_parse_result(
    parse_error auto error);

template <class T, std::invocable<T> Conv>
struct result_value_handler;


}  // namespace parsey