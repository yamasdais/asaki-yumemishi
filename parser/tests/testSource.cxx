#include <gtest/gtest.h>

#include <string>
#include <string_view>
#include <tuple>
#include <concepts>
#include <type_traits>
#include <variant>
#include <ranges>

#include <parsey/source.hpp>
#include <parsey/error.hpp>

#include "tool.hpp"

namespace dp = parsey;

constexpr static auto sv = std::tuple{std::string_view{"abc"},
    std::wstring_view{L"abc"}, std::u8string_view{u8"abc"}};
using ResValueTypes = decltype(sv);
using TestValueTypes = dp::copy_tparam_t<::testing::Types, ResValueTypes>;
using TestErrorType = dp::default_parser_error;

template <class T>
struct ParseSource : public ::testing::Test {
    using error_type = TestErrorType;
    using source_type = dp::source<T>;
};

TYPED_TEST_SUITE(ParseSource, TestValueTypes);

TYPED_TEST(ParseSource, CtorValue) {
    using source_t = typename TestFixture::source_type;
    using range_t = typename source_t::range_type;
    using value_t = dp::parse_source_input_value_t<source_t>;
    // check concepts
    static_assert(std::is_nothrow_default_constructible_v<source_t>,
        "nothrow default constructible");
    static_assert(std::is_nothrow_copy_constructible_v<source_t>,
        "nothrow copy constructible");
    static_assert(std::is_nothrow_move_constructible_v<source_t>,
        "nothrow move constructible");
    static_assert(std::forward_iterator<source_t>, "is forward");
    static_assert(dp::parse_source<source_t>, "is parse_source");

    constexpr source_t src{std::get<range_t>(sv)};
    using range_iter_t = std::ranges::iterator_t<range_t>;
    constexpr auto expect_val = static_cast<value_t>('a');
#ifndef _MSC_VER
    // skip if msvc. constexpr iterator comparison always fails.
    ASSERT_TRUE(src);
#endif
    constexpr auto v = *src;
    ASSERT_EQ(expect_val, *v);
    static_assert(expect_val == *v, "constexpr result value comparison");
    // visit()
    constexpr auto vis = testutil::mk_result_pred<value_t>(
        [expect_val](value_t sval) { return true; });
    static_assert(std::predicate<decltype(vis), value_t>, "predicate");
    static_assert(std::predicate<decltype(vis), TestErrorType>, "predicate");
    constexpr auto vis_res = visit(vis, v);
    ASSERT_TRUE(vis_res);
}

TYPED_TEST(ParseSource, Increment) {
    using source_t = typename TestFixture::source_type;
    using range_t = typename source_t::range_type;
    using value_t = dp::parse_source_input_value_t<source_t>;
    source_t src{std::get<range_t>(sv)};
    auto expect_val = static_cast<value_t>('a');
    auto vis = testutil::mk_result_pred<value_t>(
        [&expect_val](value_t sval) { return true; });
    ASSERT_TRUE(src);
    auto v = *src;
    ASSERT_EQ(expect_val, *v);
    ASSERT_TRUE(visit(vis, v));
    expect_val = static_cast<value_t>('b');
    v = *++src;
    ASSERT_EQ(expect_val, *v);
    ASSERT_TRUE(visit(vis, v));
    expect_val = static_cast<value_t>('c');
    v = *++src;
    ASSERT_EQ(expect_val, *v);
    ASSERT_TRUE(visit(vis, v));
    v = *++src;
    ASSERT_FALSE(src);
    ASSERT_FALSE(visit(vis, v));
    ASSERT_TRUE(v.error().severity() == dp::severity_t::end);
    ASSERT_THROW(++src, std::range_error);
}

TYPED_TEST(ParseSource, Backtrack) {
    using source_t = typename TestFixture::source_type;
    using range_t = typename source_t::range_type;
    using value_t = dp::parse_source_input_value_t<source_t>;
    source_t src{std::get<range_t>(sv)};
    auto expect_val = static_cast<value_t>('a');
    auto expect_val_2nd = static_cast<value_t>('b');
    source_t cp0 = src;
    ASSERT_TRUE(src == cp0);
    ++src;
    ASSERT_TRUE(src != cp0);
    auto sr = *src;
    auto cpr = *cp0;
    ASSERT_NE(expect_val, *sr);
    ASSERT_EQ(expect_val, *cpr);
    ASSERT_EQ(1, src - cp0);
    ASSERT_EQ(-1, cp0 - src);
    // revert src
    src = cp0;
    sr = *src;
    ASSERT_TRUE(src == cp0);
    ASSERT_EQ(expect_val, *sr);
    sr = *++src;
    ASSERT_TRUE(src != cp0);
    ASSERT_EQ(expect_val_2nd, *sr);
}