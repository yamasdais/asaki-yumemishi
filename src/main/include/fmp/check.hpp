//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_7F01D58B_9578_452E_9552_DF92574AFA5D)
#define FMP_7F01D58B_9578_452E_9552_DF92574AFA5D

#include <fmp/detail/check_impl.hpp>

namespace fmp {

template <typename T>
using has_value = derived_t<
  decltype(detail::has_value_impl::check<T>(nullptr))
>;

template <typename T>
using has_type = derived_t<
  decltype(detail::has_type_impl::check<T>(nullptr))
>;

template <template <class...> typename F,
          typename... A>
using can_apply = derived_t<
  decltype(detail::can_apply_impl::check<F, A...>(nullptr))
>;

template <typename T>
using has_apply = derived_t<
  decltype(detail::has_apply_impl::check<T>(nullptr))
>;

} /* ns: fmp */

#endif /* if not defined 'FMP_7F01D58B_9578_452E_9552_DF92574AFA5D' */
