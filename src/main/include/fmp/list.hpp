//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_2BC27905_2899_4653_A5E0_521DC13A65AB)
#define FMP_2BC27905_2899_4653_A5E0_521DC13A65AB

#include <fmp/operators_fwd.hpp>

namespace fmp {

template <typename A = nil_type, typename D = nil_type>
struct cons;

template <typename A, typename D>
struct cons {
  using type = cons<A, D>;
  using car_type = A;
  using cdr_type = D;
};

#if 0
template <>
struct unity<cons> {
  using type = cons<>;
};

template <typename A0_A, typename A0_D, typename A1_A, typename A1_D>
struct unite<cons<A0_A, A0_D>, cons<A1_A, A1_D>> {
  using type = cons<A0_A, cons<A1_A, A1_D>>;
};
#endif

#if 1
template <>
struct monoid_trait<cons> {
  using unity = cons<>;

  template <typename A0, typename A1>
  using unite = cons<typename A0::car_type, 
                     cons<typename A1::car_type, typename A1::cdr_type>>;
};
#endif

#if 0
template <typename A0_0, typename A0_1,
          typename A1_0, typename A1_1>
struct unite<cons<A0_0, A0_1>, cons<A1_0, A1_1>> {
  using type = cons<A0_0, cons<A1_0, A1_1>>;
};
#endif


} /* ns: fmp */

#endif /* if not defined 'FMP_2BC27905_2899_4653_A5E0_521DC13A65AB' */
