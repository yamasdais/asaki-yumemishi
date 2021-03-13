#include <gtest/gtest.h>

#include <parsey/locator.hpp>

#include "tool.hpp"

namespace dp = parsey;

template <class T>
struct IndexLocator : public ::testing::Test {
    using locator_type = dp::index_locator<T>;
};
TYPED_TEST_SUITE(IndexLocator, testutil::TestCharTypes);

TYPED_TEST(IndexLocator, Ctor) {
    using locator = typename TestFixture::locator_type;
    // concept assertion
    static_assert(dp::locator<locator, TypeParam>, "is locator");
    static_assert(
        std::same_as<dp::locator_value_t<locator>, TypeParam>, "locator T");

    constexpr locator l;
    ASSERT_EQ(0, l.position());
}