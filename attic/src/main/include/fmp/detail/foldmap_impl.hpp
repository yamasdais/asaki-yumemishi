//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_A147BBB6_0D59_439B_AEA1_0B6D65E8A9C8)
#define FMP_A147BBB6_0D59_439B_AEA1_0B6D65E8A9C8

namespace fmp {

namespace detail {

template <template <class A0, class A1> typename F,
          typename Acc, typename...>
struct foldl_elem0;

template <template <class, class> typename F,
          typename Acc>
struct foldl_elem0<F, Acc> {
  using type = Acc;
};

template <template <class, class> typename F,
          typename Acc, typename T0, typename... Tail>
struct foldl_elem0<F, Acc, T0, Tail...> {
  using type = typename foldl_elem0<
    F, typename F<Acc, T0>::type, Tail...
  >::type;
};

template <template <class, class...> typename F,
          typename Acc, typename...>
struct foldr_elem0;

template <template <class, class...> typename F,
          typename Acc>
struct foldr_elem0<F,Acc> {
  using type = Acc;
};

template <template <class, class...> typename F,
          typename Acc,
          typename T0,
          typename... Tail>
struct foldr_elem0<F, Acc, T0, Tail...> {
  using type = typename F<
    T0, typename foldr_elem0<F, Acc, Tail...>::type
  >::type;
};

template <typename F,
          typename Acc,
          typename C
          >
struct foldr_impl;


template <typename F,
          typename C
          >
struct map_impl;

struct is_foldable {
};

} /* ns: fmp::detail */

} /* ns: fmp */

#endif /* if not defined 'FMP_A147BBB6_0D59_439B_AEA1_0B6D65E8A9C8' */
