
#include <gtest/gtest.h>

#include <string>
#include <string_view>
#include <tuple>
#include <concepts>
#include <type_traits>
#include <variant>
#include <ranges>

#include <parsey/parse.hpp>

#include "tool.hpp"

namespace dp = parsey;

constexpr static auto sv = std::tuple{std::string_view{"abc"},
    std::wstring_view{L"abc"}, std::u8string_view{u8"abc"}};
using ResValueTypes = decltype(sv);
using TestValueTypes = dp::copy_tparam_t<::testing::Types, ResValueTypes>;
using TestErrorType = dp::default_parser_error;

template <class T>
struct Parse0 : public ::testing::Test {
    using error_type = TestErrorType;
    using source_type = dp::source<T>;
    using range_type = T;
    constexpr inline static source_type make_source() {
        return source_type(std::get<range_type>(sv));
    }
};

TYPED_TEST_SUITE(Parse0, TestValueTypes);

TYPED_TEST(Parse0, Any) {
    using ch_t = std::iter_value_t<typename TestFixture::range_type>;
    using namespace dp::pieces;
    auto src = TestFixture::make_source();
    ASSERT_TRUE(src);
    auto srcret = *src;
    ASSERT_TRUE(srcret);
    ASSERT_EQ(static_cast<ch_t>('a'), *srcret);
    auto r0 = any(src);
    ASSERT_TRUE(r0);
    ASSERT_EQ(static_cast<ch_t>('a'), *r0);
    srcret = *src;
    ASSERT_TRUE(srcret);
    ASSERT_EQ(static_cast<ch_t>('b'), *srcret);
}