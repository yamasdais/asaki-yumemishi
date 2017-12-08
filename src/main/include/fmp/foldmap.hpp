//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_5DD22950_26D7_4713_821B_82530AF2A776)
#define FMP_5DD22950_26D7_4713_821B_82530AF2A776

#include <fmp/detail/foldmap_impl.hpp>

namespace fmp {

template <typename F,
          typename Acc,
          typename C
          >
struct foldr {
  using type = typename detail::foldr_impl<F, Acc, C>::type;
};

template <typename F,
          typename Acc,
          typename C>
using foldr_t = typename foldr<F, Acc,C>::type;


template <typename F,
          typename C>
struct map {
  using type = typename detail::map_impl<F, C>::type;
};

} /* ns: fmp */

#endif /* if not defined 'FMP_5DD22950_26D7_4713_821B_82530AF2A776' */
