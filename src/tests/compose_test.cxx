#include <utility>
#include <type_traits>

#include <gtest/gtest.h>

#include <fmp/primitive.hpp>
#include <fmp/values.hpp>

#include <fmp_test.hpp>

using namespace fmp;

using cr0 = curry<noarg>;
using cr1 = curry<id>;
using cr2 = curry<std::add_const>;

using ComposeTypeTarget = ::testing::Types<
  p<true_type, apply_t<compose<cr1, cr1>, true_type>>,
  p<true_type, apply_t<compose<cr1, cr1, cr1>, true_type>>,
  p<true_type, apply_t<compose<cr1, cr1, cr1, cr1>, true_type>>,
  p<const int, apply_t<compose<cr1, cr2>, int>>
  >;
INSTANTIATE_TYPED_TEST_CASE_P(ComposeType, TypeTest, ComposeTypeTarget);


// ComposeType
