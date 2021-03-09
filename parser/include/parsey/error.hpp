#pragma once

#include <ostream>
#include <concepts>

namespace parsey {

template <class Error>
concept parse_error = std::is_nothrow_constructible_v<Error, char const*>;

struct default_parser_error {
    using message_type = char const*;
    char const* message;
    // work around: vscode intellisense(perhaps) claims the parser_error
    // constraint violation without this constructor
    constexpr default_parser_error(char const* message) noexcept
        : message{message} {}

    friend std::ostream& operator<<(
        std::ostream& out, default_parser_error const& err) {
        return out << err.message;
    }
};

}  // namespace parsey