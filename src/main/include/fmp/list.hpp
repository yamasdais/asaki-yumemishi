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

template <typename A, typename D>
struct cons2 {
  using type = cons<A, D>;
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

#if 0
template <typename T>
using is_cons = derived_t<
  decltype(detail::is_cons_impl::check<T>(nullptr))
>;
#endif
template <typename T>
struct is_cons : public std::false_type {
};

template <typename A0, typename A1>
struct is_cons<cons<A0, A1>> : public std::true_type {
};

template <typename T>
constexpr bool is_cons_v = is_cons<T>::value;

template <typename T>
struct car {
  static_assert(is_cons_v<T>, "car<T>: T must be a cons");
  using type = typename T::car_type;
};

template <typename T>
using car_t = typename car<T>::type;

template <typename T>
struct cdr {
  static_assert(is_cons_v<T>, "cdr<T>: T must be a cons");
  using type = typename T::cdr_type;
};

template <typename T>
using cdr_t = typename cdr<T>::type;

#if 1
template <>
struct monoid_trait<cons> {
  using unity = typename empty<cons>::type;

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
