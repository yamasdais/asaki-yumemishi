//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_34923AEE_9F31_49B2_AD8D_D975BE25512D)
#define FMP_34923AEE_9F31_49B2_AD8D_D975BE25512D

#include <fmp/primitive.hpp>
#include <fmp/utils_fwd.hpp>
#include <fmp/apply.hpp>
#include <fmp/sequence.hpp>

namespace fmp {

template <typename T>
using head_t = typename head<T>::type;

template <typename F>
struct get_mf {
  using type = undefined_type;
};

template <template <class...> typename F,
          typename... A>
struct get_mf<F<A...>> {
  template <typename... P>
  using type = F<P...>;
};

template <typename F, typename A0, typename A1>
struct flip {
  using type = apply_t<F, A1, A0>;
};

template <template <class...> typename  C,
          typename... A>
using flipf = make_curried_hf<flip, C, A...>;

template <typename... T>
struct first {
  using type = head_t<sequence<T...>>;
};

template <typename... T>
using first_t = typename first<T...>::type;

template <typename... Args>
struct apply_args {
  template <typename... F>
  using apply = id<apply_t<first_t<F...>, Args...>>;
};

template <template <class...> typename Src,
          template <class...> typename Dest,
          typename... P>
struct copy<Src<P...>, Dest> {
  using type = Dest<P...>;
};

template <typename Src,
          template <class...> typename Dest
          >
using copy_t = typename copy<Src, Dest>::type;

} /* ns: fmp */

#endif /* if not defined 'FMP_34923AEE_9F31_49B2_AD8D_D975BE25512D' */
