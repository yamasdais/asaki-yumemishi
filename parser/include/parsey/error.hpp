#pragma once

#include <ostream>
#include <concepts>

#include <parsey/fwd/error.hpp>

namespace parsey {

enum class severity_t {
    fail,  // just unmatched
    end,  // end of the source
    moderate,  // invalid but can be handled
    warning,
    error,
    fatal,
};

struct default_parser_error {
    using message_type = char const*;
    // work around: vscode intellisense(perhaps) claims the parser_error
    // constraint violation without this constructor
    constexpr explicit default_parser_error(
        char const* message, severity_t severity = severity_t::fail) noexcept
        : message{message}
        , severity_{severity} {}

    friend std::ostream& operator<<(
        std::ostream& out, default_parser_error const& err) {
        return out << err.message;
    }

    constexpr severity_t severity() const {
        return severity_;
    }

    char const* message;
    severity_t severity_;
};

}  // namespace parsey