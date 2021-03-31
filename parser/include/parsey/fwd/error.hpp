#pragma once

#include <concepts>

#include <parsey/util.hpp>
#include <parsey/fwd/locator.hpp>

namespace parsey {

enum class error_status_t;

template <class Error>
concept parse_error =
    std::constructible_from<std::remove_cvref_t<Error>, char const*, error_status_t>
    && requires(Error err) {
    { err.status() } -> std::convertible_to<error_status_t>;
};

template <class Error>
concept locatable_error = parse_error<Error>
    && requires(Error err) {
    { err.locate() };
};

template <class Error, class Locator>
concept locatable_error_with = locatable_error<Error>
    && locator<Locator>
    && std::constructible_from<Error, char const*, error_status_t, Locator>
    && requires(Error err) {
    {err.locate()} -> std::convertible_to<Locator>;
    {err.setLocator(std::declval<Locator>())};
};

}