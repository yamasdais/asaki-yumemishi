//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_2BC27905_2899_4653_A5E0_521DC13A65AB)
#define FMP_2BC27905_2899_4653_A5E0_521DC13A65AB

#include <fmp/monoid.hpp>
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

template <>
struct monoid_trait<cons> : public detail::monoid_default<
  cons,
  detail::monoid_unite_impl<cons>::apply,
  nil_type, nil_type
  >
{
};

} /* ns: fmp */

#endif /* if not defined 'FMP_2BC27905_2899_4653_A5E0_521DC13A65AB' */
