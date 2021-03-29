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
using ResValueTypes = decltype(sv);
using TestValueTypes = dp::copy_tparam_t<::testing::Types, ResValueTypes>;
using TestErrorType = dp::default_parser_error;

template <class T>
struct Parse0 : public ::testing::Test {
    using error_type = TestErrorType;
    using source_type = dp::source<T>;
    using range_type = T;
    using iterator_t = std::ranges::iterator_t<T>;
    constexpr inline static source_type make_source() {
        return source_type(std::get<range_type>(sv));
    }
    constexpr inline static auto make_source_upper() {
        return source_type(std::get<range_type>(sv_up));
    }
};

TYPED_TEST_SUITE(Parse0, TestValueTypes);

TYPED_TEST(Parse0, Any) {
    using ch_t = std::iter_value_t<typename TestFixture::iterator_t>;
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

TYPED_TEST(Parse0, Satisfy) {
    using ch_t = std::iter_value_t<typename TestFixture::iterator_t>;
    auto src = TestFixture::make_source();
    using source_t = decltype(src);
    ASSERT_TRUE(src);
    auto lower = dp::satisfy("lower", [](std::integral auto ch) {
        return dp::detail::isAlphaLower(ch);
    });
    static_assert(dp::parser_preparable_from<decltype(lower), source_t>, "preparable lower");
    constexpr auto upper = dp::satisfy("upper", [](std::integral auto ch) {
        return dp::detail::isAlphaUpper(ch);
    });
    static_assert(dp::parser_with<decltype(lower), source_t>, "lower parser with");
    static_assert(dp::parser_with<decltype(upper), source_t>, "upper parser with");
    auto res = lower(src);
    ASSERT_TRUE(res);
    ASSERT_EQ(static_cast<ch_t>('a'), *res);
    ASSERT_TRUE(src);
    res = upper(src);
    ASSERT_FALSE(res);
    ASSERT_EQ(dp::error_status_t::fail, res.error().status());
    ASSERT_TRUE(src);
    ASSERT_EQ(static_cast<ch_t>('b'), **src);
    res = lower(src);
    ASSERT_TRUE(res);
    ASSERT_EQ(static_cast<ch_t>('b'), *res);
    ASSERT_TRUE(src);
    ASSERT_EQ(static_cast<ch_t>('c'), **src);
    res = lower(src);
    ASSERT_TRUE(res);
    ASSERT_EQ(static_cast<ch_t>('c'), *res);
    ASSERT_FALSE(src);
}

TYPED_TEST(Parse0, PreparedSatisfy) {
    using ch_t = std::iter_value_t<typename TestFixture::iterator_t>;
    auto src = TestFixture::make_source();
    using source_t = decltype(src);
    ASSERT_TRUE(src);
    constexpr auto lower = dp::satisfy("low", [](dp::parse_source_input_value_t<source_t> ch) {
        return dp::detail::isAlphaLower(ch);
    }).template prepare<source_t>();
    constexpr auto upper = dp::prepare_possibly<source_t>(
        dp::satisfy("upper", [](dp::parse_source_input_value_t<source_t> ch) {
            return dp::detail::isAlphaUpper(ch);
        }));
    //constexpr auto o = lower.template prepare<source_t>();
    static_assert(dp::parser_with<decltype(lower), source_t>, "lower prepared parser with");
    auto res = lower(src);
    ASSERT_TRUE(res);
    ASSERT_EQ(static_cast<ch_t>('a'), *res);
    ASSERT_TRUE(src);
    res = upper(src);
    ASSERT_FALSE(res);
}

TYPED_TEST(Parse0, PreparedLower) {
    using ch_t = std::iter_value_t<typename TestFixture::iterator_t>;
    auto src = TestFixture::make_source();
    using source_t = decltype(src);
    ASSERT_TRUE(src);
    constexpr auto lower = dp::pieces::lower.template prepare<source_t>();
    auto res = lower(src);
    ASSERT_TRUE(res);
    ASSERT_EQ(static_cast<ch_t>('a'), *res);
    ASSERT_TRUE(src);
    ASSERT_EQ(static_cast<ch_t>('b'), **src);
}

TYPED_TEST(Parse0, PreparedUpper) {
    using ch_t = std::iter_value_t<typename TestFixture::iterator_t>;
    auto src = TestFixture::make_source_upper();
    using source_t = decltype(src);
    //ASSERT_TRUE(src);
    //constexpr auto lower = dp::pieces::lower.template prepare<source_t>();
    //auto res = lower(src);
    //ASSERT_TRUE(res);
}