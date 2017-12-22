//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_F16F016D_B014_4017_8E3E_2839D45D0114)
#define FMP_F16F016D_B014_4017_8E3E_2839D45D0114

#include <fmp/compose_fwd.hpp>
#include <fmp/curry.hpp>
#include <fmp/apply.hpp>

namespace fmp {

// forward declaration
#if 0
template <typename F, typename G>
struct compose;
#endif


} /* ns: fmp */

#include <fmp/detail/compose_impl.hpp>

namespace fmp {

template <typename F, typename G>
struct compose<F, G> {
  static_assert(has_apply<F>::value && is_curried_v<F>,
                "compose<F, G>: The F must have apply<A...> member typename");

  static_assert(has_apply<G>::value && is_curried_v<G>,
                "compose<F, G>: The G must have apply<A...> member typename");

  template <typename... A>
  using apply = detail::compose_apply_impl<F, apply_t<G, A...>>;
};

template <typename F, typename G, typename... H>
struct compose {
  template <typename... A>
  using apply = detail::compose_apply_impl<F, apply_t<compose<G, H...>, A...>>;
};

} /* ns: fmp */

#endif /* if not defined 'FMP_F16F016D_B014_4017_8E3E_2839D45D0114' */
