//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_C23C1D9C_5C17_4760_88C9_F104F674FDC0)
#define FMP_C23C1D9C_5C17_4760_88C9_F104F674FDC0

#include <fmp/functor_fwd.hpp>
#include <fmp/foldmap.hpp>

namespace fmp {

template <typename F, typename T>
struct fmap {
  using type = map_t<F, T>;
};

template <typename F, typename T>
using fmap_t = typename fmap<F, T>::type;

} /* ns: fmp */

#endif /* if not defined 'FMP_C23C1D9C_5C17_4760_88C9_F104F674FDC0' */
