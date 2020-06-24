//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_F8907122_D4B7_450C_8476_597F69F19BFD)
#define FMP_F8907122_D4B7_450C_8476_597F69F19BFD

#include <fmp/curry.hpp>
#include <fmp/compose_fwd.hpp>
#include <fmp/detail/apply_impl.hpp>

namespace fmp {

template <typename T, typename... A>
struct apply {
  static_assert(has_apply<T>::value,
                "apply<T>: The T must have apply<A...> member typename");
//  using type = decltype(detail::apply_impl::get<T, A...>(nullptr));
  using type = typename T::template apply<A...>::type;
};

#if 0
template <template <class...> typename F,
          typename... P,
          typename... A>
struct apply<curry<F, P...>, A...> {
  using type = typename curry<F, P...>::template apply<A...>::type;
};
#endif

#if 0
template <typename F, typename G, typename... H,
          typename... A>
struct apply<compose<F, G, H...>, A...> {
  using type = typename compose<F, G, H...>::template apply<A...>::type;
};
#endif

template <typename T, typename... A>
using apply_t = typename apply<T, A...>::type;

template <template <class...> typename F,
          typename... A>
struct applyf : public apply<curry<F>, A...> {
};

template <template <class...> typename F,
          typename... A>
using applyf_t = typename applyf<F, A...>::type;

} /* ns: fmp */

#endif /* FMP_F8907122_D4B7_450C_8476_597F69F19BFD */
