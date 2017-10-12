#include <utility>

#include <gtest/gtest.h>

#include <fmp/primitive.hpp>

#include <fmp_test.hpp>

using namespace fmp;

// ApplyType

using ap0 = curry<noarg>;
using ap1 = curry<id>;
using ap2 = curry<std::is_same>;
using v0 = val<int, 0>;

using ApplyTypeTarget = ::testing::Types<
  // no arg
  p<true_type, apply<ap0>::type>,
  p<true_type, apply_t<ap0>>,

  // 1 arg
  p<curry<id>, apply_t<ap1>>,
  p<v0, apply_t<apply_t<ap1>, v0>>,
  p<v0, apply_t<ap1, v0>>,

  // 2 args
  p<curry<std::is_same>, apply_t<ap2>>,
  p<curry<std::is_same, nothing>, apply_t<apply_t<ap2>, nothing>>,
  p<curry<std::is_same, nothing>, apply_t<ap2, nothing>>,
  p<true_type, apply_t<ap2, nothing, nothing>>,
  p<false_type, apply_t<ap2, nothing, int>>,
  p<true_type, apply_t<apply_t<ap2, nothing>, nothing>>,
  p<false_type, apply_t<apply_t<ap2, nothing>, int>>,
  p<true_type, apply_t<curry<std::is_same, nothing>, nothing>>
>;

INSTANTIATE_TYPED_TEST_CASE_P(ApplyType, TypeTest, ApplyTypeTarget);
