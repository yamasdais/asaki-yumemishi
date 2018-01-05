#include <utility>

#include <gtest/gtest.h>

#include <fmp/primitive.hpp>
#include <fmp/values.hpp>

#include <fmp_test.hpp>

using namespace fmp;

// Value
using ValueTarget = ::testing::Types<
  v<int, 0, val<int, 0>>,
  v<unsigned int, 0u, val<unsigned int, 0u>>,
#if defined(__cpp_template_auto)
  v<int, 0, atval<0>>,
  v<char, 'a', atval<'a'>>,
  v<bool, true, atval<true>>,
//  v<unsigned int, 0u, atval<0u>::type>,  // gcc 7.2.0 fails. disabled till 8.0
#endif /* __cpp_template_auto */
  v<char, ' ', val<int, 0x20>::cast<char>>,
// add
  v<int, 11, add_t<val<int, 1>, val<int, 10>>>,
  v<long, 42, add_t<val<int, 2>, val<long, 40l>>>,
// sub
  v<int, 5, sub_t<val<int, 8>, val<int, 3>>>,
  v<long, 12, sub_t<val<int, 23>, val<long, 11>>>,
// mul
  v<int, 12, mul_t<val<int, 3>, val<int, 4>>>,
  v<long, 24, mul_t<val<int, 6>, val<long, 4>>>,
// div
  v<int, 6, fmp::div_t<val<int, 24>, val<int, 4>>>,
  v<long, 4, fmp::div_t<val<int, 12>, val<long, 3>>>,
// mod
  v<int, 3, mod_t<val<int, 8>, val<int, 5>>>,
  v<long, 5, mod_t<val<int, 11>, val<long, 6>>>,
// b_not
  v<int, ~1, b_not_t<val<int, 1>>>,
  v<unsigned int, ~0xe5e5e5e5, b_not_t<val<unsigned int, 0xe5e5e5e5>>>,
// b_and
  v<int, 35 & 42, b_and_t<val<int, 35>, val<int, 42>>>,
  v<int, 0xe00a, b_and_t<val<short, 0xef4a>, val<int, 0xe00a>>>,
  v<int, 0xe00a, b_and_t<val<unsigned short, 0xef4a>, val<int, 0xefe00a>>>,
// b_or
  v<int, 35 | 42, b_or_t<val<int, 35>, val<int, 42>>>,
  v<int, 0xef6a, b_or_t<val<short, 0x0f4a>, val<int, 0xe02a>>>,
// b_xor
  v<int, 35 ^ 42, b_xor_t<val<int, 35>, val<int, 42>>>,
  v<int, 0xe797, b_xor_t<val<int, 0xf57c>, val<int, 0x12eb>>>,
// b_shl
  v<int, 8, b_shl_t<val<int, 1>, val<int, 3>>>,
// b_shr
  v<int, 1, b_shr_t<val<int, 15>, val<int, 3>>>
>;

INSTANTIATE_TYPED_TEST_CASE_P(Values, ValueTest, ValueTarget);
