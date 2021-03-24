#pragma once

#include <ostream>
#include <concepts>

#include <parsey/fwd/error.hpp>

namespace parsey {

enum class error_status_t {
    ignore, // success but the result has no value
    fail,  // just unmatched
    end,  // end of the source
    moderate,  // invalid but can be handled
    warning,
    error,
    fatal,
};

struct default_parser_error {
    using message_type = char const*;
    constexpr explicit default_parser_error(
        char const* message, error_status_t status = error_status_t::fail) noexcept
        : message{message}
        , status_{status} {}

    friend std::ostream& operator<<(
        std::ostream& out, default_parser_error const& err) {
        return out << err.message;
    }

    constexpr error_status_t status() const noexcept {
        return status_;
    }

    char const* message;
    error_status_t status_;
};

}  // namespace parsey