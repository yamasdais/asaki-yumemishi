#include <iostream>
#include <utility>

#include <gtest/gtest.h>

#include <fmp/primitive.hpp>

#include <fmp_test.hpp>

template <typename T0, typename T1>
using p = std::pair<T0, T1>;

using true_type = std::true_type;
using false_type = std::false_type;

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

// ApplyType
using ApplyTypeTarget = ::testing::Types<
  p<true_type, apply<std::is_same, nothing, nothing>>
>;

INSTANTIATE_TYPED_TEST_CASE_P(ApplyType, TypeTest, ApplyTypeTarget);
