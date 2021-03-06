//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_0FD7118A_1B28_4BDC_ADB1_DAFDBA2F2717)
#define FMP_0FD7118A_1B28_4BDC_ADB1_DAFDBA2F2717

#include <fmp/sequence_fwd.hpp>
#include <fmp/operator_fwd.hpp>
#include <fmp/utils_fwd.hpp>
#include <fmp/monoid.hpp>
#include <fmp/detail/sequence_impl.hpp>

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

#if 0
template <>
struct unity<sequence> {
  using type = sequence<>;
};

template <typename... A0, typename... A1>
struct unite<sequence<A0...>, sequence<A1...>> {
  using type = sequence<A0..., A1...>;
};
#endif

template <>
struct monoid_trait<sequence> : public detail::monoid_default<
  sequence,
  detail::monoid_unite_impl<sequence>::apply
  >
{
};

template <typename ...P>
struct head<sequence<P...>> {
  using type = typename detail::sequence_head_impl<P...>::type;
};

} /* ns: fmp */

#endif /* if not defined 'FMP_0FD7118A_1B28_4BDC_ADB1_DAFDBA2F2717' */
