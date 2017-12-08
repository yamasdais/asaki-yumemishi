//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_0C1960E6_F598_4F31_B57A_FEF339122B20)
#define FMP_0C1960E6_F598_4F31_B57A_FEF339122B20

#include <fmp/sequence_fwd.hpp>
#include <fmp/apply.hpp>
#include <fmp/detail/monoid_impl.hpp>
#include <fmp/detail/foldmap_impl.hpp>

namespace fmp { namespace detail {

template <typename... T>
struct head_impl;

template <typename Head, typename... Tail>
struct head_impl<Head, Tail...> {
  using apply = Head;
  template <template <class...> typename Holder>
  using tail = Holder<Tail...>;
};

template <>
struct head_impl<> {
  using apply = undefined_type;
};

template <typename F,
          typename Acc,
          typename... P
          >
struct sequence_foldr_elem;

template <typename F,
          typename Acc>
struct sequence_foldr_elem<F, Acc> {
  using type = Acc;
};

template <typename F,
          typename Acc,
          typename P0,
          typename... P
          >
struct sequence_foldr_elem<F, Acc, P0, P...> {
  using type = apply_t<F, P0,
                       typename sequence_foldr_elem<F, Acc, P...>::type>;
};

template <typename F,
          typename Acc,
          typename... P
          >
struct foldr_impl<F, Acc, sequence<P...>> {
#if 1
  using type = typename sequence_foldr_elem<F, Acc, P...>::type;
#else
  // for debug
  using type = sequence<F, Acc, P...>;
#endif
};

template <>
struct monoid_unite_impl<sequence> {
  template <typename A0, typename A1>
  using apply = append<A0, A1>;
};

template <typename F,
          typename ...A>
struct map_impl<F, sequence<A...>> {
  using type = sequence<apply_t<F, A>...>;
};


} /* namespace detail */ } /* namespace fmp */

#endif /* if not defined 'FMP_0C1960E6_F598_4F31_B57A_FEF339122B20' */
