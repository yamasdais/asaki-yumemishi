#include <iostream>
#include <utility>

#include <gtest/gtest.h>

#include <fmp/primitive.hpp>

#include <fmp_test.hpp>

using HasValueTarget = ::testing::Types<
  std::pair<std::true_type, fmp::has_value<fmp::val<int, 0>>>
>;

INSTANTIATE_TYPED_TEST_CASE_P(HasValue, BoolTest, HasValueTarget);

using HasTypeTarget = ::testing::Types<
  std::pair<std::false_type, fmp::has_type<int>>,
  std::pair<std::true_type, fmp::has_type<fmp::id<int>>>
>;

INSTANTIATE_TYPED_TEST_CASE_P(HasType, BoolTest, HasTypeTarget);
