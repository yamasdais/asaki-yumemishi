//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_920AB251_2A86_41EA_84BF_55360C70A3C2)
#define FMP_920AB251_2A86_41EA_84BF_55360C70A3C2

#include <fmp/primitive.hpp>

namespace fmp {

template <typename T, T V>
struct val : public std::integral_constant<T, V> {
  using type = val<T, V>;
  using value_type = T;

  template <typename CastTo>
  using cast = val<CastTo, static_cast<CastTo>(V)>;
};

template <typename T>
struct valtype {
  template <T V>
  using let = val<T, V>;
};

} /* ns: fmp */

#endif /* if not defined 'FMP_920AB251_2A86_41EA_84BF_55360C70A3C2' */
