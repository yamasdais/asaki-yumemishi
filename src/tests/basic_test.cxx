#include <gtest/gtest.h>
#include <iostream>

#include <fmp/primitive.hpp>

#include <fmp_test.hpp>

TEST(BasicTest, HasValue) {
  using namespace fmp;
  using exp0 = has_value<val<int, 0>>;
  ASSERT_TRUE(exp0());
}
