//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_0FD7118A_1B28_4BDC_ADB1_DAFDBA2F2717)
#define FMP_0FD7118A_1B28_4BDC_ADB1_DAFDBA2F2717

#include <fmp/detail/sequence.hpp>

namespace fmp {

template <typename... T>
struct sequence {
  using type = sequence<T...>;
  constexpr static size_t size = sizeof...(T);

  using head = typename detail::head_impl<T...>::apply;
  using tail = typename detail::head_impl<T...>::template tail<sequence>;

  template <typename... A>
  using append = sequence<T..., A...>;

  template <typename... A>
  using prepend = sequence<A..., T...>;

};

} /* ns: fmp */

#endif /* if not defined 'FMP_0FD7118A_1B28_4BDC_ADB1_DAFDBA2F2717' */
