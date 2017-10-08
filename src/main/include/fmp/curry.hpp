//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_1541E847_B530_48E2_848F_C8CC210691B6)
#define FMP_1541E847_B530_48E2_848F_C8CC210691B6

#include <fmp/detail/curry_impl.hpp>

namespace fmp {

template <template <class...> typename F,
          typename... A>
struct curry {
//  using args = sequence<A...>;
  constexpr static size_t value = sizeof...(A);

//  using type = detail::curried<F, A...>;

  template <typename... P>
  using apply = typename detail::curried<F, A..., P...>::type;

  template <typename... P>
  using apply_t = typename apply<P...>::type;

  template <typename... Adds>
  using currying = curry<F, A..., Adds...>;
};

} /* ns: fmp */

#endif /* FMP_1541E847_B530_48E2_848F_C8CC210691B6 */
