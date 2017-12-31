#include <iostream>
#include <utility>

#include <gtest/gtest.h>

#include <fmp/primitive.hpp>
#include <fmp/values.hpp>
#include <fmp/operator.hpp>

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

// Operators
using OperatorTarget = ::testing::Types<
  p<true_type, eq<val<int, 0>, val<int, 0>>>,
  p<false_type, eq<val<int, 1>, val<int, 0>>>,
  p<true_type, eq<val<int, 2>, val<unsigned int, 2u>>>,
  p<true_type, ne<val<int, 0>, val<int, 1>>>,
  p<false_type, ne<val<int, 1>, val<int, 1>>>,
  p<true_type, ne<val<int, 2>, val<unsigned int, 3u>>>,
  p<true_type, lt<val<int, -1>, val<int, 0>>>,
  p<false_type, lt<val<int, 0>, val<int, 0>>>,
  p<true_type, lt<val<int, 1>, val<unsigned int, 2u>>>,
  p<true_type, lte<val<int, -1>, val<int, 0>>>,
  p<true_type, lte<val<int, 0>, val<int, 0>>>,
  p<false_type, lte<val<int, 1>, val<int, 0>>>,
  p<true_type, lte<val<int, 1>, val<unsigned int, 2u>>>,
  p<true_type, gt<val<int, 1>, val<int, 0>>>,
  p<false_type, gt<val<int, 0>, val<int, 0>>>,
  p<true_type, gt<val<int, 3>, val<unsigned int, 2u>>>,
  p<true_type, gte<val<int, 1>, val<int, 0>>>,
  p<true_type, gte<val<int, 0>, val<int, 0>>>,
  p<false_type, gte<val<int, -1>, val<int, 0>>>,
  p<true_type, gte<val<int, 3>, val<unsigned int, 2u>>>
  >;

INSTANTIATE_TYPED_TEST_CASE_P(Operators, BoolTest, OperatorTarget);
