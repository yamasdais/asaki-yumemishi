//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_2BC27905_2899_4653_A5E0_521DC13A65AB)
#define FMP_2BC27905_2899_4653_A5E0_521DC13A65AB

#include <fmp/operators_fwd.hpp>
#include <fmp/detail/list_impl.hpp>

namespace fmp {

template <typename A, typename D>
struct cons {
  using type = cons<A, D>;
  using car_type = A;
  using cdr_type = D;
};

template <>
struct cons<nil_type, nil_type> {
  using type = nil_type;
  using car_type = nil_type;
  using cdr_type = nil_type;
};

template <typename A>
struct cons<A, cons<nil_type, nil_type>> {
  using type = cons<A, nil_type>;
  using car_type = A;
  using cdr_type = nil_type;
};

template <typename T>
using is_cons = derived_t<
  decltype(detail::is_cons_impl::check<T>(nullptr))
>;

template <typename T>
using car = id<std::enable_if_t<
                 is_cons<T>::value,
                 typename T::car_type>>;

template <typename T>
using car_t = typename car<T>::type;

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
