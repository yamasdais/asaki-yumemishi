#include <iostream>
#include <utility>

#include <gtest/gtest.h>

#include <fmp/primitive.hpp>

#include <fmp_test.hpp>


using namespace fmp;

// HasValue
using HasValueTarget = ::testing::Types<
  p<true_type, has_value<val<int, 0>>>
>;

INSTANTIATE_TYPED_TEST_CASE_P(HasValue, BoolTest, HasValueTarget);

// HasType
using HasTypeTarget = ::testing::Types<
  p<false_type, has_type<int>>,
  p<true_type, has_type<fmp::id<int>>>
>;

INSTANTIATE_TYPED_TEST_CASE_P(HasType, BoolTest, HasTypeTarget);

// Value
using ValueTarget = ::testing::Types<
  v<int, 0, val<int, 0>>,
  v<char, ' ', val<int, 0x20>::cast<char>>
>;

INSTANTIATE_TYPED_TEST_CASE_P(Values, ValueTest, ValueTarget);
