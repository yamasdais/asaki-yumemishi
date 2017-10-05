#include <gtest/gtest.h>
#include <iostream>

#include <fmp/primitive.hpp>

#include <fmp_test.hpp>

template <typename T>
void assert_true_bool()
{
  ASSERT_TRUE(T());
}

TEST(BasicTest, HasValue) {
  using namespace fmp;
  using exp0 = has_value<val<int, 0>>;
  ASSERT_TRUE(exp0());
}

TEST(BasicTest, HasType) {

  using f0 = fmp::has_type<int>;
  using t0 = fmp::has_type<fmp::id<int>>;
  ASSERT_FALSE(f0());
  ASSERT_TRUE(t0());
}
