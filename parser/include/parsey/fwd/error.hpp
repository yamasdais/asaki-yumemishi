#pragma once

#include <concepts>

#include <parsey/util.hpp>

namespace parsey {

enum class severity_t;

template <class Error>
concept parse_error = std::is_constructible_v<Error,
    char const*> && std::constructible_from<Error, char const*, severity_t>
    && requires (Error err) {
        {err.severity()} -> std::convertible_to<severity_t>;
    };

}