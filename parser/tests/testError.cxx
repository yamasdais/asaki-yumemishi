#include <gtest/gtest.h>

#include <parsey/locator.hpp>
#include <parsey/error.hpp>

#include <sstream>

#include "tool.hpp"

namespace dp = parsey;

TEST(Error, Ctor) {
    static_assert(
        dp::parse_error<dp::default_parser_error<dp::index_locator<char>>>, "parser_error concept");
    constexpr char const* message = "test error";
    constexpr dp::default_parser_error<dp::index_locator<char>> err{message, dp::error_status_t::fail};

    std::stringstream str;
    str << err;
    ASSERT_TRUE(str.str() == message);
}

TEST(Error, Locatable) {
    using locate_t = dp::index_locator<char>;
    using error_t = dp::default_parser_error<locate_t>;
    static_assert(std::movable<error_t>, "error is movable");
    static_assert(dp::locatable_error<error_t>, "locatable error");
    static_assert(dp::locatable_error_with<error_t, locate_t>, "locatable with error");
    locate_t loc;
    auto err = dp::make_error<error_t>("test error", dp::error_status_t::fail, loc);

}