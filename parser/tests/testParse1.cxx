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
constexpr static auto sv_up = std::tuple{std::string_view{"ABC"},
    std::wstring_view{L"ABC"}, std::u8string_view{u8"ABC"}};
constexpr static auto sv_digit = std::tuple{std::string_view{"123"},
    std::wstring_view{L"123"}, std::u8string_view{u8"123"}};
using ResValueTypes = decltype(sv);
using TestValueTypes = dp::copy_tparam_t<::testing::Types, ResValueTypes>;
template <class V>
using TestErrorType = dp::default_parser_error<dp::index_locator<V>>;

template <class T>
struct Parse1 : public ::testing::Test {
    using error_type = TestErrorType<T>;
    using source_type = dp::source<T>;
    using range_type = T;
    using iterator_t = std::ranges::iterator_t<T>;
    constexpr inline static source_type make_source() {
        return source_type(std::get<range_type>(sv));
    }
    constexpr inline static auto make_source_upper() {
        return source_type(std::get<range_type>(sv_up));
    }
    constexpr inline static auto make_source_digit() {
        return source_type(std::get<range_type>(sv_digit));
    }
};

TYPED_TEST_SUITE(Parse1, TestValueTypes);

TYPED_TEST(Parse1, Choice) {
    using ch_t = std::iter_value_t<typename TestFixture::iterator_t>;
    using namespace dp::pieces;
    auto src = TestFixture::make_source();
    using source_t = decltype(src);
    ASSERT_TRUE(src);
    constexpr auto p = dp::prepare_parser<source_t>(choice(upper, lower));
    //static_assert(dp::parser_preparable_from<decltype(p), source_t>, "preparable");
    using ptype = decltype(p);
    static_assert(dp::parser_with<ptype, source_t>, "parser with source");
    auto res = p(src);
    ASSERT_TRUE(res);
    ASSERT_EQ(static_cast<ch_t>('a'), *res);
    res = p(src);
    ASSERT_TRUE(res);
    ASSERT_EQ(static_cast<ch_t>('b'), *res);
    res = p(src);
    ASSERT_TRUE(res);
    ASSERT_EQ(static_cast<ch_t>('c'), *res);
    ASSERT_FALSE(src);
    src = TestFixture::make_source_upper();
    ASSERT_TRUE(src);
    res = p(src);
    ASSERT_TRUE(res);
    ASSERT_EQ(static_cast<ch_t>('A'), *res);
    res = p(src);
    ASSERT_TRUE(res);
    ASSERT_EQ(static_cast<ch_t>('B'), *res);
    res = p(src);
    ASSERT_TRUE(res);
    ASSERT_EQ(static_cast<ch_t>('C'), *res);
    src = TestFixture::make_source_digit();
    ASSERT_TRUE(src);
    res = p(src);
    ASSERT_FALSE(res);
    ASSERT_TRUE(src);
    ASSERT_TRUE(*src);
    ASSERT_EQ(static_cast<ch_t>('1'), **src);
}