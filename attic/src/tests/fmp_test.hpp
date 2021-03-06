//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(UUID_29B974E6_2A8A_4B56_B0D5_6B885825F24A)
#define UUID_29B974E6_2A8A_4B56_B0D5_6B885825F24A

#if !defined(__cplusplus) or __cplusplus < 201103
#error This library designed for C++11 (or newer, hopefully).
#endif // c++ version check

#include <typeinfo>
#include <type_traits>
#include <memory>
#include <utility>
#include <cstdlib>

#include <gtest/gtest.h>

// gtest utilities

// Boolean test
template <typename T>
struct BoolTest : public ::testing::Test {
  // concept declarations of type T
  using expected_type = typename T::first_type;
  using actual_type = typename T::second_type;
  static_assert(std::is_same<typename expected_type::value_type, bool>::value,
                "first_type must be a bool");
  static_assert(std::is_same<typename actual_type::value_type, bool>::value,
                "second_type must be a bool");
};

TYPED_TEST_CASE_P(BoolTest);

TYPED_TEST_P(BoolTest, CheckBoolean) {
  bool actual = typename TypeParam::second_type();
  if (typename TypeParam::first_type()) {
    ASSERT_TRUE(actual);
  } else {
    ASSERT_FALSE(actual);
  }
}

REGISTER_TYPED_TEST_CASE_P(BoolTest, CheckBoolean);


// Type test
template <typename T>
struct TypeTest : public ::testing::Test {
  // concept declarations of type T
  using expected_type = typename T::first_type;
  using actual_type = typename T::second_type;
};

TYPED_TEST_CASE_P(TypeTest);

TYPED_TEST_P(TypeTest, CheckType) {
  bool is_same = std::is_same<
    typename TypeParam::first_type,
    typename TypeParam::second_type
    >::value;
  ASSERT_TRUE(is_same);
}

REGISTER_TYPED_TEST_CASE_P(TypeTest, CheckType);

// Value Test
template <typename T, T V, typename A>
struct value_test_param {
  using expected_type = T;
  constexpr static T value = V;
  using actual_type = A;
};

template <typename T>
struct ValueTest : public ::testing::Test {
  // concept declarations of type T
  using expected_type = typename T::expected_type;
  using actual_type = typename T::actual_type;
};

TYPED_TEST_CASE_P(ValueTest);

TYPED_TEST_P(ValueTest, CheckValue) {
  bool type_eq = std::is_same<
    typename TypeParam::expected_type,
    typename TypeParam::actual_type::value_type
    >::value;
  ASSERT_TRUE(type_eq) << "Type mismatched";

  auto expected = TypeParam::value;
  auto actual = TypeParam::actual_type::value;

  ASSERT_EQ(expected, actual) << "Value mismatched";
}

REGISTER_TYPED_TEST_CASE_P(ValueTest, CheckValue);

// short hand
template <typename T0, typename T1>
using p = std::pair<T0, T1>;

template <typename T, T V, typename A>
using v = value_test_param<T, V, A>;

using true_type = std::true_type;
using false_type = std::false_type;

// Class that takes template template parameter,
template <typename... A>
struct noarg;

// but without any argument only
template <>
struct noarg<> {
  constexpr static int value = 43;
  using type = std::true_type;
};

#endif /* UUID_29B974E6_2A8A_4B56_B0D5_6B885825F24A */
