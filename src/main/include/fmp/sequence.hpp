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

};

template <template <class...> typename F,
          typename... A0, typename... A1>
struct append<sequence<A0...>, F<A1...>> {
  using type = sequence<A0..., A1...>;
};

template <>
struct unity<sequence> {
  using type = sequence<>;
};

template <typename... A0, typename... A1>
struct unite<sequence<A0...>, sequence<A1...>> {
  using type = sequence<A0..., A1...>;
};

} /* ns: fmp */

#endif /* if not defined 'FMP_0FD7118A_1B28_4BDC_ADB1_DAFDBA2F2717' */
