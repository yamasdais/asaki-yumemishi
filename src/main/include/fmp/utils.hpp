//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_34923AEE_9F31_49B2_AD8D_D975BE25512D)
#define FMP_34923AEE_9F31_49B2_AD8D_D975BE25512D

#include <fmp/apply.hpp>

namespace fmp {

template <typename F, typename A0, typename A1>
struct flip {
  using type = apply_t<F, A1, A0>;
};

template <template <class...> typename  C,
          typename... A>
using flipf = make_curried_hf<flip, C, A...>;

} /* ns: fmp */

#endif /* if not defined 'FMP_34923AEE_9F31_49B2_AD8D_D975BE25512D' */
