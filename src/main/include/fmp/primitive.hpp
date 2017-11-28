//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_2EAC0BFA_977A_4474_BCBE_66EF548CE53D)
#define FMP_2EAC0BFA_977A_4474_BCBE_66EF548CE53D

#include <utility>
#include <type_traits>

// tags
namespace fmp {

#if 0
struct t_type : public std::true_type {
};

#endif
struct nil_type : public std::false_type {
};

struct unit_type {
};

struct undefined_type {
};

struct nothing {
};

template <template <class...> typename T>
struct empty {
};

/**
 * tag for upper infinity +∞ (U+221E)
 */
struct infinity_upper {
};

/**
 * tag for lower infinity -∞ (U+221E)
 */
struct infinity_lower {
};

// utility
template <typename T>
struct id {
  using type = T;
};

template <typename T>
struct derived : public T {
  using type = T;
};

template <typename T>
using derived_t = typename derived<T>::type;

template <bool Cond>
struct bool_type : public std::conditional_t<
  Cond, std::true_type, std::false_type
>
{
};

template <typename T>
struct boolean;

// simple type
template <typename T>
struct quote {
  using type = quote<T>;
  using unquote = T;
};

template <typename T>
struct negate;

template <>
struct negate<std::true_type> : public std::false_type {
};

template <>
struct negate<std::false_type> : public std::true_type {
};

} // namespace fmp

#include <fmp/check.hpp>

#include <fmp/curry.hpp>
#include <fmp/apply.hpp>
#include <fmp/compose.hpp>

#include <fmp/list.hpp>

#include <fmp/detail/apply_impl.hpp>

namespace fmp {

template <typename T>
struct boolean : public std::enable_if_t<
  has_value<T>::value,
  bool_type<T::value>
>
{
};

} /* ns: fmp */

#endif /* FMP_2EAC0BFA_977A_4474_BCBE_66EF548CE53D */
