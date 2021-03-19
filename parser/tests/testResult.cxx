#include <gtest/gtest.h>

#include <string>
#include <tuple>
#include <concepts>
#include <type_traits>
#include <variant>
#include <ranges>
#include <algorithm>

#include <parsey/result.hpp>
#include <parsey/error.hpp>
#include <parsey/util.hpp>

#include "tool.hpp"

namespace dp = parsey;

constexpr static auto samples = std::tuple('a', 42, (char const*)"foo");
using ResValueTypes = decltype(samples);
using TestValueTypes = dp::copy_tparam_t<::testing::Types, ResValueTypes>;
using TestErrorType = dp::default_parser_error;

template <class T>
constexpr auto get_sample_value() {
    return std::get<T>(samples);
}
template <class Res, class Val>
constexpr auto ctor_sample_result() {
    auto sample = get_sample_value<Val>();
    static_assert(std::same_as<Val, decltype(sample)>, "result value type");
    return Res{sample};
}

template <class T>
struct ParamVisitor {
    constexpr bool operator()(T const& v) const {
        auto sample = get_sample_value<T>();
        static_assert(std::same_as<T, decltype(sample)>, "result value type");
        // work around for Visual studio bug.
        // return sample == v;
        return testutil::CheckEqualVal(sample, v);
    }
};

template <class T>
struct AsIsVisitor {};

template <class... T>
struct ResultVisitorImpl : public ParamVisitor<T>... {
    using ParamVisitor<T>::operator()...;
    constexpr bool operator()(TestErrorType const& error) const {
        return false;
    }
};
using ResultVisitor = dp::copy_tparam_t<ResultVisitorImpl, ResValueTypes>;

template <class T>
struct ParseResult : public ::testing::Test {
    using error_type = TestErrorType;
    using result_type = dp::result<T, error_type>;
};

TYPED_TEST_SUITE(ParseResult, TestValueTypes);

TYPED_TEST(ParseResult, Utils) {
    using result_t = typename TestFixture::result_type;
    using value_t = dp::parse_result_value_t<result_t>;
    using err_t = dp::parse_result_error_t<result_t>;
    value_t sample_val = std::get<value_t>(samples);
    auto v2r = [](value_t v) {
        return dp::make_parse_result<err_t>(v);
    };
    auto e2r = [](err_t&& err) {
        return dp::make_parse_result<value_t>(std::forward<err_t>(err));
    };
    auto e2rc = [](err_t const& err) {
        return dp::make_parse_result<value_t>(err);
    };
    static_assert(dp::parse_value_to_result<decltype(v2r), value_t>,
        "parse_value_to_result");
    static_assert(dp::parse_value_to_result<decltype(e2r), err_t&&>,
        "parse_value_to_result");
    static_assert(dp::parse_value_to_result<decltype(e2rc), err_t const&>,
        "parse_value_to_result");
}

TYPED_TEST(ParseResult, CtorValue) {
    using result_t = typename TestFixture::result_type;
    using value_t = dp::parse_result_value_t<result_t>;
    value_t sample_val = std::get<value_t>(samples);
    constexpr ResultVisitorImpl<value_t> visitor;
    auto err = dp::default_parser_error{"foo error"};
    // testutil::TTrace<decltype(altvis_ret), decltype(visitor)> x;
    constexpr result_t res = ctor_sample_result<result_t, value_t>();
    ASSERT_TRUE(res);
    auto resv = *res;
    ASSERT_TRUE(ParamVisitor<value_t>{}(resv));
    // visitor
    constexpr auto rvisited = res.fmap(visitor);
    static_assert(std::same_as<bool, std::remove_cvref_t<decltype(rvisited)>>,
        "visited result type");
    ASSERT_TRUE(rvisited);
    // visit with std::identity
    auto genvisit = visit([](auto const& v) { return result_t{v}; }, res);
    // auto rv = dp::make_result_visitor<value_t, TestErrorType>(visitor);
    // ASSERT_TRUE(rv(sample_val));

    constexpr result_t res0 =
        dp::make_parse_result<typename TestFixture::error_type>(*res);
    ASSERT_TRUE(res0);
    ASSERT_TRUE(testutil::CheckEqualVal(*res, *res0));
}

TYPED_TEST(ParseResult, CtorError) {
    using result_t = typename TestFixture::result_type;
    using value_t = dp::parse_result_value_t<result_t>;
    using error_t = dp::parse_result_error_t<result_t>;
    constexpr char const* msg = "test error message";
    constexpr result_t res{error_t{msg}};
    constexpr ResultVisitorImpl<value_t> visitor;
    ASSERT_FALSE(res);
    auto rvisited = res.fmap(visitor);
    ASSERT_FALSE(rvisited);
    constexpr result_t res0 = dp::make_parse_result<value_t>(error_t{msg});
    ASSERT_FALSE(res0);
}

TYPED_TEST(ParseResult, VisitorValue) {
    using result_t = typename TestFixture::result_type;
    using value_t = dp::parse_result_value_t<result_t>;
    using error_t = dp::parse_result_error_t<result_t>;
    constexpr value_t sample_val = std::get<value_t>(samples);
    constexpr result_t res = ctor_sample_result<result_t, value_t>();
    // attempt captured lambda
    constexpr auto handler = [sample_val](value_t val) {
        return dp::result<bool, error_t>{
            testutil::CheckEqualVal(sample_val, val)
        };
    };
    constexpr auto visitor = dp::make_result_visitor(res, handler);
    using vis_t = std::remove_cvref_t<decltype(visitor)>;
    static_assert(dp::parse_value_to_result<vis_t, value_t>,
        "function returns parse_result");
    static_assert(std::invocable<vis_t, value_t>, "visit value");
    static_assert(std::invocable<vis_t, error_t>, "visit error");
    static_assert(std::invocable<vis_t, value_t&>, "visit value");
    static_assert(std::invocable<vis_t, error_t&>, "visit error");
    static_assert(std::invocable<vis_t, value_t&&>, "visit value");
    static_assert(std::invocable<vis_t, error_t&&>, "visit error");
    static_assert(std::invocable<vis_t, value_t const&>, "visit value");
    static_assert(std::invocable<vis_t, error_t const&>, "visit error");
    using vis_r_t = std::invoke_result_t<vis_t, value_t>;
    static_assert(
        dp::parse_result_with<vis_r_t, dp::parse_result_value_t<vis_r_t>,
            dp::parse_result_error_t<vis_r_t>>,
        "visited result type");
    ASSERT_TRUE(res);
    auto visited_r = res.fmap(visitor);
    ASSERT_TRUE(*visited_r);

    constexpr auto nocap_handler = [](value_t const&) {
        return dp::result<bool, error_t>{true};
    };
    constexpr auto nocap_visitor = dp::make_result_visitor(res, nocap_handler);
    using nocap_vis_t = std::remove_cvref_t<decltype(nocap_visitor)>;
    struct TMP {};
    static_assert(sizeof(TMP) == sizeof(nocap_vis_t), "nocapture visitor object size");
    static_assert(dp::parse_value_to_result<nocap_vis_t, value_t>,
        "function returns parse_result");
    static_assert(std::invocable<nocap_vis_t, value_t>, "visit value");
    static_assert(std::invocable<nocap_vis_t, error_t>, "visit error");
    static_assert(std::invocable<nocap_vis_t, value_t const&>, "visit value");
    static_assert(std::invocable<nocap_vis_t, error_t const&>, "visit error");
    auto nocap_visited_r = res.fmap(nocap_visitor);
    ASSERT_TRUE(*nocap_visited_r);
}

TYPED_TEST(ParseResult, VisitorError) {
    using result_t = typename TestFixture::result_type;
    using value_t = dp::parse_result_value_t<result_t>;
    using error_t = dp::parse_result_error_t<result_t>;
    constexpr char const* msg = "test error message";
    constexpr result_t res{error_t{msg}};
    constexpr auto nocap_handler = [](value_t const&) {
        return dp::result<bool, error_t>{true};
    };
    constexpr auto nocap_visitor = dp::make_result_visitor(res, nocap_handler);
    using nocap_vis_t = std::remove_cvref_t<decltype(nocap_visitor)>;
    static_assert(dp::parse_value_to_result<nocap_vis_t, error_t>,
        "function returns parse_result");
    ASSERT_FALSE(res);
    static_assert(std::invocable<nocap_vis_t, value_t>, "visit value");
    static_assert(std::invocable<nocap_vis_t, error_t>, "visit error");
    static_assert(std::invocable<nocap_vis_t, value_t const&>, "visit value");
    static_assert(std::invocable<nocap_vis_t, error_t const&>, "visit error");

    auto visited = res.fmap(nocap_visitor);
    ASSERT_FALSE(visited);
}