#include <iostream>
#include <utility>

#include <gtest/gtest.h>

#include <fmp/primitive.hpp>

#include <fmp_test.hpp>

template <typename T0, typename T1>
using p = std::pair<T0, T1>;

using true_type = std::true_type;
using false_type = std::false_type;

template <typename... A>
struct noarg;

template <>
struct noarg<> {
  constexpr static int value = 43;
  using type = std::true_type;
};

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

// CurryType
using CurryTypeTarget = ::testing::Types<
  // tests for no argument meta-function
  p<noarg<>, curry<noarg>::apply<>>,
  p<true_type, curry<noarg>::apply_t<>>,

  // tests for 1 argument meta-function
  p<false_type, curry<id, false_type>::apply_t<>>,
  p<false_type, curry<id>::apply_t<false_type>>,
  p<false_type, curry<id>::apply_t<>::apply_t<false_type>>,
  p<curry<id, false_type>, curry<id>::currying<false_type>>,

  // tests for 2 argument meta-function
  p<curry<std::is_same, int>, curry<std::is_same>::apply_t<int>>,
  p<std::is_same<int, long>, curry<std::is_same>::apply<int, long>>,
  p<false_type, curry<std::is_same>::apply_t<int, long>>,
  p<std::is_same<int, long>, curry<std::is_same>::currying<>::apply<int, long>>,
  p<std::is_same<int, long>, curry<std::is_same>::currying<int>::apply<long>>,
  p<std::is_same<int, long>,
    curry<std::is_same>::currying<int>::currying<long>::apply<>>,
  p<std::is_same<int, long>, curry<std::is_same>::currying<int, long>::apply<>>,
  p<std::is_same<int, long>, curry<std::is_same, int>::apply<long>>,
  p<std::is_same<int, long>, curry<std::is_same, int>::currying<long>::apply<>>,
  p<false_type, curry<std::is_same, int>::apply_t<long>>,
  p<false_type, curry<std::is_same, int, long>::apply_t<>>
>;

INSTANTIATE_TYPED_TEST_CASE_P(CurryType, TypeTest, CurryTypeTarget);

// ApplyType
using ApplyTypeTarget = ::testing::Types<
  p<true_type, apply_t<std::is_same, nothing, nothing>>
>;

INSTANTIATE_TYPED_TEST_CASE_P(ApplyType, TypeTest, ApplyTypeTarget);
