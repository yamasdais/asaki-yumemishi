#include <boost/hana/assert.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/not.hpp>

#include <literal/basic_string.hpp>

#include <gtest/gtest.h>
#include <type_traits>

namespace hana = boost::hana;

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

// true test
template <typename T>
struct TrueTest : public ::testing::Test {
  // concept declarations of type T
  using actual_type = T;
  static_assert(std::is_same<typename actual_type::value_type, bool>::value,
                "type must be a bool");
};

TYPED_TEST_CASE_P(TrueTest);

template <typename T>
struct SameTest : public ::testing::Test {
  // concept declarations of type T
  using expected_type = typename T::first_type;
  using actual_type = typename T::second_type;
};

TYPED_TEST_CASE_P(SameTest);

template <typename Ex,
          typename T,
          template <T...> typename S,
          char... c>
struct AliasPair {
  using expected_type = Ex;
  using char_type = T;
  using str_type = S<static_cast<T>(c)...>;

  AliasPair() {
  }

  bool isExpected() const noexcept {
    return std::is_same<expected_type, str_type>::value;
  }
};


template <typename T>
struct AliasTest : public ::testing::Test {
};

TYPED_TEST_CASE_P(AliasTest);

TYPED_TEST_P(BoolTest, CheckBoolean) {
  bool actual = typename TypeParam::second_type();
  if (typename TypeParam::first_type()) {
    ASSERT_TRUE(actual);
  } else {
    ASSERT_FALSE(actual);
  }
}

TYPED_TEST_P(TrueTest, CheckTrue) {
  bool actual = typename TypeParam::type();
  ASSERT_TRUE(actual);
}

TYPED_TEST_P(SameTest, CheckSame) {
  auto r =std::is_same<
    typename TypeParam::first_type,
    typename TypeParam::second_type>::value;
  ASSERT_TRUE(r);
}

TYPED_TEST_P(AliasTest, AliasCheckSame) {
  ASSERT_TRUE(TypeParam().isExpected());
}

REGISTER_TYPED_TEST_CASE_P(BoolTest, CheckBoolean);
REGISTER_TYPED_TEST_CASE_P(TrueTest, CheckTrue);
REGISTER_TYPED_TEST_CASE_P(SameTest, CheckSame);
REGISTER_TYPED_TEST_CASE_P(AliasTest, AliasCheckSame);

// short hand
template <typename T0, typename T1>
using p = std::pair<T0, T1>;

template <typename Ex,
          typename T,
          template <T...> typename S,
          char... c>
using a = AliasPair<Ex, T, S, c...>;

using true_type = std::true_type;
using false_type = std::false_type;

// construct macro
template <typename C>
auto macro_test_s1 = BOOST_HANA_BASIC_STRING(C, "");
template <typename C>
auto macro_test_s2 = BOOST_HANA_BASIC_STRING(C, "a");
template <typename C>
auto macro_test_s3 = BOOST_HANA_BASIC_STRING(C, "abcd");
template <typename C>
auto macro_test_s4 = BOOST_HANA_BASIC_STRING(C, "\x80\xff\xa0");

#if 0
template <typename C>
using MacroTarget = ::testing::Types<
  p<true_type, std::is_same<decltype(macro_test_s1<C>),
                            hana::basic_string<C>>>,
  p<true_type, std::is_same<decltype(macro_test_s2<C>),
                            hana::basic_string<C, (C)'a'>>>,
  p<true_type, std::is_same<decltype(macro_test_s3<C>),
                            hana::basic_string<C, (C)'a', (C)'b', (C)'c', (C)'d'>>>
  >;
#endif
template <typename C>
using MacroTarget = ::testing::Types<
  p<decltype(macro_test_s1<C>),
    hana::basic_string<C>>,
  p<decltype(macro_test_s2<C>),
    hana::basic_string<C, (C)'a'>>,
  p<decltype(macro_test_s3<C>),
    hana::basic_string<C, (C)'a', (C)'b', (C)'c', (C)'d'>>,
  p<decltype(macro_test_s4<C>),
    hana::basic_string<C, (C)0x080, (C)0x0ff, (C)0x0a0>>
  >;

using AliasMacroTarget = ::testing::Types<
  a<decltype(macro_test_s1<char>), char, hana::string_b>,
  a<decltype(macro_test_s2<char>), char, hana::string_b, 'a'>,
  a<decltype(macro_test_s3<char>), char, hana::string_b, 'a', 'b', 'c', 'd'>,
  a<decltype(macro_test_s1<wchar_t>), wchar_t, hana::wstring>,
  a<decltype(macro_test_s2<wchar_t>), wchar_t, hana::wstring, 'a'>,
  a<decltype(macro_test_s3<wchar_t>), wchar_t, hana::wstring, 'a', 'b', 'c', 'd'>,
  a<decltype(macro_test_s1<char16_t>), char16_t, hana::u16string>,
  a<decltype(macro_test_s2<char16_t>), char16_t, hana::u16string, 'a'>,
  a<decltype(macro_test_s3<char16_t>), char16_t, hana::u16string, 'a', 'b', 'c', 'd'>,
  a<decltype(macro_test_s1<char32_t>), char32_t, hana::u32string>,
  a<decltype(macro_test_s2<char32_t>), char32_t, hana::u32string, 'a'>,
  a<decltype(macro_test_s3<char32_t>), char32_t, hana::u32string, 'a', 'b', 'c', 'd'>
  >;

INSTANTIATE_TYPED_TEST_CASE_P(BStrCharMacro, SameTest,
                              MacroTarget<char>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrWCharMacro, SameTest,
                              MacroTarget<wchar_t>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrChar16Macro, SameTest,
                              MacroTarget<char16_t>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrChar32Macro, SameTest,
                              MacroTarget<char32_t>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrAliasMacro, AliasTest,
                              AliasMacroTarget);

// make
template <typename C>
using MakeTarget = ::testing::Types<
  decltype(hana::equal(hana::make<hana::basic_string_tag<C>>(),
                       hana::basic_string_c<C>)),
  decltype(hana::equal(hana::make<hana::basic_string_tag<C>>(
                         hana::basic_char_c<C, (C)'a'>),
                       hana::basic_string_c<C, (C)'a'>)),
  decltype(hana::equal(hana::make<hana::basic_string_tag<C>>(
                         hana::basic_char_c<C, (C)'a'>,
                         hana::basic_char_c<C, (C)'b'>
                       ),
                       hana::basic_string_c<C, (C)'a', (C)'b'>)),
  decltype(hana::equal(hana::make<hana::basic_string_tag<C>>(
                         hana::basic_char_c<C, (C)'a'>,
                         hana::basic_char_c<C, (C)'b'>,
                         hana::basic_char_c<C, (C)'c'>
                       ),
                       hana::basic_string_c<C, (C)'a', (C)'b', (C)'c'>)),
  decltype(hana::equal(hana::make<hana::basic_string_tag<C>>(
                         hana::basic_char_c<C, (C)'a'>,
                         hana::basic_char_c<C, (C)'b'>,
                         hana::basic_char_c<C, (C)'c'>,
                         hana::basic_char_c<C, (C)'d'>
                       ),
                       hana::basic_string_c<C, (C)'a', (C)'b', (C)'c', (C)'d'>)),
  decltype(hana::equal(hana::make_basic_string<C>(
                         hana::basic_char_c<C, (C)'a'>,
                         hana::basic_char_c<C, (C)'b'>,
                         hana::basic_char_c<C, (C)'c'>),
                       hana::make<hana::basic_string_tag<C>>(
                         hana::basic_char_c<C, (C)'a'>,
                         hana::basic_char_c<C, (C)'b'>,
                         hana::basic_char_c<C, (C)'c'>
                       )))
  >;

INSTANTIATE_TYPED_TEST_CASE_P(BStrCharMake, TrueTest,
                              MakeTarget<char>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrWCharMake, TrueTest,
                              MakeTarget<wchar_t>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrChar16Make, TrueTest,
                              MakeTarget<char16_t>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrChar32Make, TrueTest,
                              MakeTarget<char32_t>);

// to
template <typename C>
using ToTarget0 = ::testing::Types<
  p<true_type, hana::is_convertible<hana::basic_string_tag<C>, C const*>>,
  p<false_type, hana::is_embedded<hana::basic_string_tag<C>, C const*>>
  >;

INSTANTIATE_TYPED_TEST_CASE_P(BStrCharTo, BoolTest,
                              ToTarget0<char>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrWCharTo, BoolTest,
                              ToTarget0<wchar_t>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrChar16To, BoolTest,
                              ToTarget0<char16_t>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrChar32To, BoolTest,
                              ToTarget0<char32_t>);

// any_of
template <typename C>
using AnyOfTarget = ::testing::Types<
  p<true_type, decltype(hana::any_of(
                          macro_test_s3<C>,
                          hana::equal.to(hana::basic_char_c<C, (C)'d'>)))>,
  p<true_type, decltype(hana::not_(hana::any_of(
                          macro_test_s1<C>,
                          hana::always(hana::true_c))))>,
  p<true_type, decltype(hana::not_(hana::any_of(
                          macro_test_s3<C>,
                          hana::equal.to(hana::basic_char_c<C, (C)'z'>))))>
  >;

INSTANTIATE_TYPED_TEST_CASE_P(BStrCharAnyOf, BoolTest,
                              AnyOfTarget<char>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrWCharAnyOf, BoolTest,
                              AnyOfTarget<wchar_t>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrChar16AnyOf, BoolTest,
                              AnyOfTarget<char16_t>);
INSTANTIATE_TYPED_TEST_CASE_P(BStrChar32AnyOf, BoolTest,
                              AnyOfTarget<char32_t>);
