#include <utility>

#include <gtest/gtest.h>

#include <fmp/primitive.hpp>
#include <fmp/values.hpp>

#include <fmp_test.hpp>

using namespace fmp;

using cr0 = curry<noarg>;
using cr1 = curry<id>;

using ComposeTypeTarget = ::testing::Types<
  p<true_type, apply_t<compose<cr1, cr1>, true_type>>,
  p<true_type, apply_t<compose<cr1, cr1, cr1>, true_type>>,
  p<true_type, apply_t<compose<cr1, cr1, cr1, cr1>, true_type>>
  >;
INSTANTIATE_TYPED_TEST_CASE_P(ComposeType, TypeTest, ComposeTypeTarget);


// ComposeType
