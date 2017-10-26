//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_0FD7118A_1B28_4BDC_ADB1_DAFDBA2F2717)
#define FMP_0FD7118A_1B28_4BDC_ADB1_DAFDBA2F2717

#include <fmp/operators_fwd.hpp>
#include <fmp/detail/sequence.hpp>

namespace fmp {

template <typename... T>
struct sequence {
  using type = sequence<T...>;
  constexpr static size_t size = sizeof...(T);

#if 0
  using head = std::enable_if_t<(size > 0),
    typename detail::head_impl<T...>::apply>;
  using tail = typename detail::head_impl<T...>::template tail<sequence>;
#endif

#if 0
  template <typename... A>
  using append = sequence<T..., A...>;
#endif

  template <typename... A>
  using prepend = sequence<A..., T...>;

};

template <template <class...> typename F,
          typename... A0, typename... A1>
struct append<sequence<A0...>, F<A1...>> {
  using type = sequence<A0..., A1...>;
};

#if 0
template <typename... A>
struct unity<sequence<A...>> : public derived<sequence<>> {
};
#endif

} /* ns: fmp */

#endif /* if not defined 'FMP_0FD7118A_1B28_4BDC_ADB1_DAFDBA2F2717' */
