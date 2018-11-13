#include <boost/hana/assert.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/integral_constant.hpp>

#include <literal/basic_string.hpp>

#include <gtest/gtest.h>
#include <type_traits>

// bool test
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

// short hand
template <typename T0, typename T1>
using p = std::pair<T0, T1>;

using true_type = std::true_type;
using false_type = std::false_type;

namespace hana = boost::hana;

// construct macro
template <typename C>
auto macro_test_s1 = BOOST_HANA_BASIC_STRING(C, "");
template <typename C>
auto macro_test_s2 = BOOST_HANA_BASIC_STRING(C, "a");
template <typename C>
auto macro_test_s3 = BOOST_HANA_BASIC_STRING(C, "abcd");

template <typename C>
using MacroTarget = ::testing::Types<
  p<true_type, std::is_same<decltype(macro_test_s1<C>),
                            hana::basic_string<C>>>,
  p<true_type, std::is_same<decltype(macro_test_s2<C>),
                            hana::basic_string<C, (C)'a'>>>,
  p<true_type, std::is_same<decltype(macro_test_s3<C>),
                            hana::basic_string<C, (C)'a', (C)'b', (C)'c', (C)'d'>>>
  >;

INSTANTIATE_TYPED_TEST_CASE_P(BStrCharMacro, BoolTest,
                              MacroTarget<char>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrWCharMacro, BoolTest,
                              MacroTarget<wchar_t>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrChar16Macro, BoolTest,
                              MacroTarget<char16_t>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrChar32Macro, BoolTest,
                              MacroTarget<char32_t>);
// make
template <typename C>
using MakeTarget = ::testing::Types<
  p<true_type, decltype(hana::equal(hana::make<hana::basic_string_tag<C>>(),
                                    hana::basic_string_c<C>))>,
  p<true_type, decltype(hana::equal(hana::make<hana::basic_string_tag<C>>(
                                      hana::basic_char_c<C, (C)'a'>),
                                    hana::basic_string_c<C, (C)'a'>))>,
  p<true_type, decltype(hana::equal(hana::make<hana::basic_string_tag<C>>(
                                      hana::basic_char_c<C, (C)'a'>,
                                      hana::basic_char_c<C, (C)'b'>
                                    ),
                                    hana::basic_string_c<C, (C)'a', (C)'b'>))>,
  p<true_type, decltype(hana::equal(hana::make<hana::basic_string_tag<C>>(
                                      hana::basic_char_c<C, (C)'a'>,
                                      hana::basic_char_c<C, (C)'b'>,
                                      hana::basic_char_c<C, (C)'c'>
                                    ),
                                    hana::basic_string_c<C, (C)'a', (C)'b', (C)'c'>))>,
  p<true_type, decltype(hana::equal(hana::make<hana::basic_string_tag<C>>(
                                      hana::basic_char_c<C, (C)'a'>,
                                      hana::basic_char_c<C, (C)'b'>,
                                      hana::basic_char_c<C, (C)'c'>,
                                      hana::basic_char_c<C, (C)'d'>
                                    ),
                                    hana::basic_string_c<C, (C)'a', (C)'b', (C)'c', (C)'d'>))>,
  p<true_type, decltype(hana::equal(hana::make_basic_string<C>(
                                      hana::basic_char_c<C, (C)'a'>,
                                      hana::basic_char_c<C, (C)'b'>,
                                      hana::basic_char_c<C, (C)'c'>),
                                    hana::make<hana::basic_string_tag<C>>(
                                      hana::basic_char_c<C, (C)'a'>,
                                      hana::basic_char_c<C, (C)'b'>,
                                      hana::basic_char_c<C, (C)'c'>
                                    )))>
  >;

INSTANTIATE_TYPED_TEST_CASE_P(BStrCharMake, BoolTest,
                              MakeTarget<char>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrWCharMake, BoolTest,
                              MakeTarget<wchar_t>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrChar16Make, BoolTest,
                              MakeTarget<char16_t>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrChar32Make, BoolTest,
                              MakeTarget<char32_t>);
