//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_D6F7F80D_3E89_4F19_91F6_F26129FEB0F4)
#define FMP_D6F7F80D_3E89_4F19_91F6_F26129FEB0F4

#include <fmp/monoid.hpp>

namespace fmp {
namespace detail {

template <typename T>
struct just_impl {
  using type = just_impl<T>;
  using get = T;
};

struct nothing_impl {
  using type = nothing_impl;
};


template <typename A0, typename A1>
struct maybe_unite_impl;

template <>
struct maybe_unite_impl<maybe<nothing_impl>, maybe<nothing_impl>> {
  using type = maybe<nothing_impl>;
};

template <typename A>
struct maybe_unite_impl<maybe<nothing_impl>, maybe<just_impl<A>>> {
  using type = maybe<just_impl<A>>;
};

template <typename A>
struct maybe_unite_impl<maybe<just_impl<A>>, maybe<nothing_impl>> {
  using type = maybe<just_impl<A>>;
};

template <typename A0, typename A1>
struct maybe_unite_impl<maybe<just_impl<A0>>, maybe<just_impl<A1>>> {
  using type = maybe<just_impl<unite_t<A0, A1>>>;
};


} /* ns: fmp::detail */
} /* ns: fmp */

#endif /* if not defined 'FMP_D6F7F80D_3E89_4F19_91F6_F26129FEB0F4' */
