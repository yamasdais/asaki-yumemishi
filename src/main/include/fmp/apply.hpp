//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_F8907122_D4B7_450C_8476_597F69F19BFD)
#define FMP_F8907122_D4B7_450C_8476_597F69F19BFD

#include <fmp/curry.hpp>
#include <fmp/detail/apply_impl.hpp>

namespace fmp {

template <typename T, typename... A>
struct apply {
  using type = decltype(detail::apply_impl::get<T, A...>(nullptr));

};

template <typename T, typename... A>
using apply_t = typename apply<T, A...>::type;

} /* ns: fmp */

#endif /* FMP_F8907122_D4B7_450C_8476_597F69F19BFD */
