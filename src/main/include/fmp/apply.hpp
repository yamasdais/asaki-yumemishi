//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_F8907122_D4B7_450C_8476_597F69F19BFD)
#define FMP_F8907122_D4B7_450C_8476_597F69F19BFD

#include <fmp/curry.hpp>
#include <fmp/detail/apply_impl.hpp>

namespace fmp {

template <template <class...> typename F,
          typename... A>
struct apply : public id<
  decltype(detail::apply_impl::get<F, A...>(nullptr))
>
{
};

template <template <class...> typename F,
          typename... A>
using apply_t = typename apply<F, A...>::type;

} /* ns: fmp */

#endif /* FMP_F8907122_D4B7_450C_8476_597F69F19BFD */
