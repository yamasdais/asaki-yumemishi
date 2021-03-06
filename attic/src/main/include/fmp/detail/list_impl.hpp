//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_AAAA1AA4_2052_4A5F_ABC9_182D0CB9EA32)
#define FMP_AAAA1AA4_2052_4A5F_ABC9_182D0CB9EA32

#include <fmp/list_fwd.hpp>
#include <fmp/apply.hpp>
#include <fmp/foldmap.hpp>
#include <fmp/detail/monoid_impl.hpp>

namespace fmp {

namespace detail {

struct is_cons_impl {
  template <typename T>
  static auto check(typename T::car_type*, typename T::cdr_type* = nullptr)
    noexcept -> std::true_type;

  template <typename>
  static auto check(...) noexcept -> std::false_type;
};

template <>
struct monoid_unite_impl<cons> {
  template <typename A0, typename A1>
  using apply = foldr_t<curry<cons>, A1, A0>;
};

template <typename F,
          typename Acc,
          typename P>
struct cons_foldr_elem {
  using type = Acc;
};

template <typename F,
          typename Acc,
          typename Car, typename Cdr>
struct cons_foldr_elem<F, Acc, cons<Car,Cdr>> {
  using type = apply_t<F, Car,
                       typename cons_foldr_elem<F, Acc, Cdr>::type>;
};

template <typename F,
          typename Acc,
          typename P0, typename P1
          >
struct foldr_impl<F, Acc, cons<P0, P1>> {
  using type = typename cons_foldr_elem<F, Acc, cons<P0, P1>>::type;
};

template <typename F,
          typename C>
struct cons_map_elem {
  using type = C;
};

template <typename F,
          typename Car, typename Cdr>
struct cons_map_elem<F, cons<Car, Cdr>> {
  using type = cons<apply_t<F, Car>, typename cons_map_elem<F, Cdr>::type>;
};

template <typename F,
          typename Car, typename Cdr>
struct map_impl<F, cons<Car, Cdr>> {
  using type = typename cons_map_elem<F, cons<Car, Cdr>>::type;
};

} /* ns: fmp::detail */
} /* ns: fmp */

#endif /* if not defined 'FMP_AAAA1AA4_2052_4A5F_ABC9_182D0CB9EA32' */
