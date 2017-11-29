//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_FE8B755E_F036_42E8_BCEA_2CF8653318E8)
#define FMP_FE8B755E_F036_42E8_BCEA_2CF8653318E8

#include <fmp/apply.hpp>

namespace fmp {
namespace detail {

template <typename F, typename G>
struct compose_apply_impl {
  using type = apply_t<F, G>;
};

template <typename F,
          template <class...> typename G,
          typename... A>
struct compose_apply_impl<F, curry<G, A...>> {
  using type = compose<F, curry<G, A...>>;
};

} /* ns: fmp::detail */
} /* ns: fmp */

#endif /* if not defined 'FMP_FE8B755E_F036_42E8_BCEA_2CF8653318E8' */
