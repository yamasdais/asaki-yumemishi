#include <gtest/gtest.h>

#include <string>
#include <tuple>
#include <concepts>
#include <type_traits>
#include <variant>

#include <parsey/result.hpp>
#include <parsey/error.hpp>
#include <parsey/util.hpp>

#include "tool.hpp"

namespace dp = parsey;

constexpr inline static auto samples = std::tuple('a', 42, (char const*)"foo");
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
#ifdef _MSC_VER
        return true;
#else
        return sample == v;
#endif
    }
};
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

TYPED_TEST(ParseResult, CtorValue) {
    using result_t = typename TestFixture::result_type;
    using value_t = dp::parse_result_value_t<result_t>;
    constexpr ResultVisitorImpl<value_t> visitor;
    constexpr result_t res = ctor_sample_result<result_t, value_t>();
    ASSERT_TRUE(res);
    auto resv = *res;
    ASSERT_TRUE(ParamVisitor<value_t>{}(resv));
    // visitor
    auto rvisited = res.fmap(visitor);
    static_assert(std::same_as<bool, decltype(rvisited)>, "visited result type");
    ASSERT_TRUE(rvisited);
    auto rv = dp::make_result_visitor<value_t, TestErrorType>(visitor);
    ASSERT_TRUE(rv(std::get<value_t>(samples)));

    constexpr result_t res0 = dp::make_parse_result<typename TestFixture::error_type>(*res);
    ASSERT_TRUE(res0);
#ifndef _MSC_VER
    ASSERT_EQ(*res, *res0);
#endif
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