#include <gtest/gtest.h>

#include <concepts>

#include <parsey/locator.hpp>

#include "tool.hpp"

namespace dp = parsey;

template <class T>
struct IndexLocator : public ::testing::Test {
    using locator_type = dp::index_locator<T>;
};
TYPED_TEST_SUITE(IndexLocator, testutil::TestCharTypes);

TYPED_TEST(IndexLocator, Ctor) {
    using locator_t = typename TestFixture::locator_type;
    // concept assertion
    static_assert(std::is_nothrow_default_constructible_v<locator_t>, "default constructible");
    static_assert(std::semiregular<locator_t>, "semiregular");
    static_assert(dp::incremental_locator<locator_t, TypeParam>, "locator concept");
    static_assert(
        std::same_as<dp::locator_value_t<locator_t>, TypeParam>, "locator T");

    constexpr locator_t l;
    ASSERT_EQ(0, l.position());
}

TYPED_TEST(IndexLocator, Increment) {
    using locator_t = typename TestFixture::locator_type;
    using value_t = dp::locator_value_t<locator_t>;
    locator_t l;
    l.increment(static_cast<value_t>('a'));
    ASSERT_EQ(1, l.position());
    l.increment(static_cast<value_t>('a'));
    ASSERT_EQ(2, l.position());
    l.increment(static_cast<value_t>('b'));
    ASSERT_EQ(3, l.position());
}