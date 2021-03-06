//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_382BA56B_E8C6_468A_B8F4_AB848AF0D3D2)
#define FMP_382BA56B_E8C6_468A_B8F4_AB848AF0D3D2

#include <fmp/primitive.hpp>

namespace fmp {

template <typename A, typename D>
struct cons;

template <>
struct empty<cons> {
  using type = cons<nil_type, nil_type>;
};

} /* ns: fmp */

#endif /* if not defined 'FMP_382BA56B_E8C6_468A_B8F4_AB848AF0D3D2' */
