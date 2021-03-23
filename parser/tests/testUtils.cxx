#include <gtest/gtest.h>

#include <string>
#include <string_view>
#include <tuple>
#include <concepts>
#include <type_traits>
#include <variant>
#include <ranges>
#include <numeric>

#include <parsey/util.hpp>

#include "tool.hpp"

namespace dp = parsey;

// must be empty
struct TestSample {};

constexpr inline TestSample testSample;
constexpr auto foostr = "foo";

constexpr inline std::tuple sample0{12, foostr, testSample};
using sample0_t = decltype(sample0);

TEST(ParseyUtil, GetTemplateParamIdx) {
    static_assert(
        std::same_as<int, dp::get_tparam_t<sample0_t, 0>>, "get_tparam(0)");
    static_assert(std::same_as<char const*, dp::get_tparam_t<sample0_t, 1>>,
        "get_tparam(1)");
    static_assert(std::same_as<TestSample, dp::get_tparam_t<sample0_t, 2>>,
        "get_tparam(2)");
    // constexpr bool testFail = std::same_as<int, dp::get_tparam_t<sample0_t,
    // 3>>; // compile error

    SUCCEED();
}

TEST(ParseyUtil, CopyTemplateParams) {
    using smplvar_t = dp::copy_tparam_t<std::variant, sample0_t>;
    static_assert(
        std::same_as<std::variant<int, char const*, TestSample>, smplvar_t>,
        "copy template parameters");

    SUCCEED();
}

constexpr inline auto testFunction(int) {
    return true;
}

TEST(ParseyUtil, NocaptureLambda) {
    int tval = 42;
    auto lmb = [tval](int v) {
        return v + tval;
    };
    auto lmbnocap = [](int v) {
        return v + 1;
    };
    static_assert(
        !dp::lambda_nocapture<decltype(testFunction), int>, "testFunction");
    static_assert(std::invocable<decltype(lmb), int>);
    static_assert(!dp::lambda_nocapture<decltype(lmb), int>, "lambda captured");
    static_assert(std::invocable<decltype(lmbnocap), int>);
    static_assert(
        dp::lambda_nocapture<decltype(lmbnocap), int>, "lamda nocapture");
    static_assert(
        dp::lambda_nocapture<decltype(lmbnocap) const, int>, "lamda nocapture");

    SUCCEED();
}

template <class C>
constexpr auto strAppender = [](std::basic_string<C>& str, C ch) {
    str.append(1, ch);
};

template <class T>
struct UtilAccumulator : public ::testing::Test {
    using value_type = T;
};
TYPED_TEST_SUITE(UtilAccumulator, testutil::TestCharTypes);

TYPED_TEST(UtilAccumulator, Char2Str) {
    using ch_t = typename TestFixture::value_type;
    constexpr ch_t chars[] = {'a', 'b', 'c'};
    // std::basic_string in libstdc++10 is not constexpr yet
    // auto appender = dp::make_accumulator<std::basic_string,
    // ch_t>(strAppender<ch_t>);
    auto appender =
        dp::make_accumulator<std::basic_string, ch_t>(strAppender<ch_t>);
    for (auto c : chars) {
        appender(c);
    }
    auto res = *appender;
    // clang++(and libstdc++-10) cannot compile this for statement
    // for (auto idx : std::views::iota(0ul, res.length())) {
    ASSERT_EQ(sizeof(chars) / sizeof(ch_t), res.length());
    for (decltype(res.length()) idx = 0ul, end = res.length(); idx != end;
         ++idx) {
        ASSERT_EQ(chars[idx], res[idx]);
    }
}

TEST(ParseyUtil, InvocableHolder) {
    int foo = 42;
    auto lmb = [foo]() {
        return foo;
    };
    auto nclmb = []() {
        return 42;
    };
    auto nclmb_i = [](int n) {
        return 42 + n;
    };
    auto nclmb_ci = [](int const& n) {
        return 42 + n;
    };
    auto nclmb_ri = [](int& n) {
        n += 42;
    };
    auto funcHold0 = dp::invocable_holder{lmb};
    ASSERT_EQ(foo, funcHold0());
    auto funcHold1 = dp::invocable_holder{nclmb};
    static_assert(sizeof(TestSample) != sizeof(decltype(funcHold0)), "capture func holder size");
    static_assert(sizeof(TestSample) == sizeof(decltype(funcHold1)), "nocapture func holder size");
    ASSERT_EQ(foo, funcHold1());
    auto funcHold2 = dp::invocable_holder{nclmb_i};
    ASSERT_EQ(foo + 3, funcHold2(3));
    auto funcHold3 = dp::invocable_holder{nclmb_ci};
    ASSERT_EQ(foo + 3, funcHold3(3));
    auto funcHold4 = dp::invocable_holder{nclmb_ri};
    int ri = 5;
    funcHold4(ri);
    ASSERT_EQ(foo + 5, ri);
}
