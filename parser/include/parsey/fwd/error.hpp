#pragma once

#include <concepts>

#include <parsey/util.hpp>

namespace parsey {

enum class error_status_t;

template <class Error>
concept parse_error = std::is_constructible_v<Error,
    char const*> && std::constructible_from<Error, char const*, error_status_t>
    && requires (Error err) {
        {err.status()} -> std::convertible_to<error_status_t>;
    };

}