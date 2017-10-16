//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_F16F016D_B014_4017_8E3E_2839D45D0114)
#define FMP_F16F016D_B014_4017_8E3E_2839D45D0114

#include <fmp/curry.hpp>
#include <fmp/apply.hpp>

namespace fmp {

// forward declaration
template <typename F, typename G>
struct compose;

} /* ns: fmp */

#include <fmp/detail/compose_impl.hpp>

namespace fmp {

template <typename F, typename G>
struct compose {
  static_assert(has_apply<F>::value,
                "compose<F, G>: The F must have apply<A...> member typename");

  static_assert(has_apply<G>::value,
                "compose<F, G>: The G must have apply<A...> member typename");

  template <typename... A>
  using apply = detail::compose_apply_impl<F, apply_t<G, A...>>;

  template <typename... A>
  using apply_t = typename apply<A...>::type;
};

} /* ns: fmp */

#endif /* if not defined 'FMP_F16F016D_B014_4017_8E3E_2839D45D0114' */
