#pragma once

#include <ostream>
#include <concepts>

#include <parsey/fwd/error.hpp>
#include <parsey/fwd/locator.hpp>

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

template <parse_error Error>
constexpr auto make_error(char const* message, error_status_t state, locator auto const& loc) {
    using locator_t = std::remove_cvref_t<decltype(loc)>;
    if constexpr (locatable_error_with<Error, locator_t>) {
        return Error{message, state, loc};
    } else {
        return Error{message, state};
    }
}

template <locator Locator>
struct default_parser_error {
    using message_type = char const*;
    constexpr explicit default_parser_error(
        char const* message, error_status_t status) noexcept
        : message{message}
        , status_{status} {}
    constexpr explicit default_parser_error(
        char const* message, error_status_t status, Locator const& loc) noexcept
        : message{message}
        , status_{status}
        , locator_{loc} {}

    friend std::ostream& operator<<(
        std::ostream& out, default_parser_error const& err) {
        return out << err.message;
    }

    constexpr error_status_t status() const noexcept {
        return status_;
    }
    constexpr Locator const& locate() const {
        return locator_;
    }

    constexpr void setLocator(Locator const& loc) {
        locator_ = loc;
    }

    char const* message;
    error_status_t status_;
    Locator locator_;
};

}  // namespace parsey