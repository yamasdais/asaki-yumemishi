//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_CAB7B197_B0AD_4C4C_BEA9_2334826A3E89)
#define FMP_CAB7B197_B0AD_4C4C_BEA9_2334826A3E89

#include <fmp/primitive.hpp>
#include <fmp/monoid.hpp>
#include <fmp/maybe_fwd.hpp>
#include <fmp/functor_fwd.hpp>
#include <fmp/detail/maybe_impl.hpp>

namespace fmp {

template <typename T>
struct maybe<detail::just_tag<T>> {
  using get = T;
  using type = maybe<detail::just_tag<T>>;
};

template <>
struct maybe<detail::nothing_tag> {
  using get = detail::nothing_tag;
  using type = maybe<get>;
};

struct nothing {
  using type = maybe<detail::nothing_tag>;
};

using nothing_t = typename nothing::type;

template <typename T>
struct just {
  using type = maybe<detail::just_tag<T>>;
};

template <typename T>
using just_t = typename just<T>::type;


// is_just
template <typename T>
struct is_just : public std::false_type {
};

template <typename T>
struct is_just<maybe<detail::just_tag<T>>> : public std::true_type {
};

template <typename T>
using is_just_t = typename is_just<T>::type;

// is_nothing
template <typename T>
struct is_nothing : public std::false_type {
};

template <>
struct is_nothing<maybe<detail::nothing_tag>> : public std::true_type {
};

template <typename T>
using is_nothing_t = typename is_nothing<T>::type;

// from just
template <typename T>
struct from_just;

template <typename T>
struct from_just<maybe<detail::just_tag<T>>> {
  using type = T;
};

template <typename T>
using from_just_t = typename from_just<T>::type;

// from maybe
template <typename T, typename D>
struct from_maybe;

template <typename T, typename D>
struct from_maybe<maybe<detail::just_tag<T>>, D> {
  using type = T;
};

template <typename D>
struct from_maybe<maybe<detail::nothing_tag>, D> {
  using type = D;
};

template <typename T, typename D>
using from_maybe_t = typename from_maybe<T, D>::type;

// as monoid
template <>
struct monoid_trait<maybe> : public detail::monoid_default<
  maybe,
  detail::maybe_unite_impl,
  detail::nothing_tag
  > {
};


} /* ns: fmp */

#endif /* if not defined 'FMP_CAB7B197_B0AD_4C4C_BEA9_2334826A3E89' */
