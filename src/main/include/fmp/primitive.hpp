//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_2EAC0BFA_977A_4474_BCBE_66EF548CE53D)
#define FMP_2EAC0BFA_977A_4474_BCBE_66EF548CE53D

#include <type_traits>

#include <fmp/detail/check_impl.hpp>

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


// operator
template <bool Cond>
struct bool_type : public std::conditional_t<
  Cond, std::true_type, std::false_type
>
{
};

template <typename T>
struct boolean : public std::enable_if_t<
  has_value<T>::value,
  bool_type<T::value>
>
{
};


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

#include <fmp/curry.hpp>
#include <fmp/apply.hpp>
#include <fmp/compose.hpp>

#include <fmp/detail/sequence.hpp>
#include <fmp/detail/fold.hpp>
#include <fmp/detail/apply_impl.hpp>

namespace fmp {

template <typename A, typename D>
struct cons {
  using type = cons<A, D>;
  using car_type = A;
  using cdr_type = D;
};

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

template <typename T, T V>
struct val : public std::integral_constant<T, V> {
  using type = val<T, V>;
};

} /* ns: fmp */

#endif /* FMP_2EAC0BFA_977A_4474_BCBE_66EF548CE53D */

