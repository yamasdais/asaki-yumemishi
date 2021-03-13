#include <gtest/gtest.h>

#include <parsey/error.hpp>

#include <sstream>

namespace dp = parsey;

TEST(Error, Ctor) {
    static_assert(
        dp::parse_error<dp::default_parser_error>, "parser_error concept");
    constexpr char const* message = "test error";
    constexpr dp::default_parser_error err{message};

    std::stringstream str;
    str << err;
    ASSERT_TRUE(str.str() == message);
}