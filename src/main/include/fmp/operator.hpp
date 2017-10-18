//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_174E3523_C237_4B3A_87D4_E995AF774952)
#define FMP_174E3523_C237_4B3A_87D4_E995AF774952

#include <fmp/primitive.hpp>

#include <fmp/detail/operator_impl.hpp>

namespace fmp {

// monoid
template <template <class> typename Domain,
          template <class, class> typename Unite,
          typename Unity>
struct monoid {
  using unity = Unity;

  template <typename LType, typename RType>
  using unite = Unite<Domain<LType>, Domain<RType>>;

  template <typename LType, typename RType>
  using unite_t = typename unite<LType, RType>::type;
};


// monoid unity

template <typename T>
using has_unity = derived_t<
  decltype(detail::has_unity_impl::check<T>(nullptr))
>;

template <typename T>
struct unity {
  static_assert(has_unity<T>::value,
                "unity<T>: 'T' must have a typename 'unity' member");
  using type = typename T::unity;
};

template <typename T>
using unity_t = typename unity<T>::type;

// monoid unite
template <typename T>
using has_unite = derived_t<
  decltype(detail::has_unite_impl::check<T>(nullptr))
>;

template <typename T, typename L, typename R>
struct unite {
  static_assert(has_unite<T>::value,
                "unite<T,L,R>: 'T' must have a template 'unite<L, R>' member");

  using type = typename T::template unite_t<L, R>;
};

template <typename T, typename L, typename R>
using unite_t = typename unite<T, L, R>::type;

template <typename T0, typename T1>
struct is_and_operatable : public derived_t<
  decltype(detail::is_and_operatable_impl::check<T0, T1>(nullptr, nullptr))
>
{
};

template <typename T0, typename T1>
struct is_or_operatable : public derived_t<
  decltype(detail::is_or_operatable_impl::check<T0, T1>(nullptr, nullptr))
>
{
};

template <typename T0, typename T1>
struct is_lt_operatable : public derived_t<
  decltype(detail::is_lt_operatable_impl::check<T0, T1>(nullptr, nullptr))
>
{
};

template <typename T0, typename T1>
struct is_eq_operatable : public derived_t<
  decltype(detail::is_eq_operatable_impl::check<T0, T1>(nullptr, nullptr))
>
{
};

template <typename T0, typename T1>
struct is_gt_operatable : public derived_t<
  decltype(detail::is_gt_operatable_impl::check<T0, T1>(nullptr, nullptr))
>
{
};


/**
 * 'and' operator ('and' in latin. because of c++ reserved word)
 */
struct et : public monoid<
  boolean, detail::op_and_impl, std::true_type
>
{
};

/**
 * 'or' operator ('or' in latin. because of c++ reserved word)
 */
struct uel : public monoid<
  boolean, detail::op_or_impl, std::false_type
>
{
};

/**
 * 'less than' operator
 */
template <typename T0, typename T1>
struct lt : public detail::op_lt_impl<T0, T1> {
};

/**
 * 'equals' operator
 */
template <typename T0, typename T1>
struct eq : public detail::op_eq_impl<T0, T1> {
};

/**
 * 'greater than' operator
 */
template <typename T0, typename T1>
struct gt : public detail::op_gt_impl<T0, T1> {
};

/**
 * compare operator
 */
enum ordering {
  LT = -1,
  EQ = 0,
  GT = 1
};

struct order_lt
  : public std::integral_constant<ordering, ordering::LT> {
};
struct order_eq
  : public std::integral_constant<ordering, ordering::EQ> {
};
struct order_gt
  : public std::integral_constant<ordering, ordering::GT> {
};

template <typename T0, typename T1>
struct compare : public std::conditional_t<
  lt<T0, T1>::value, order_lt,
  std::conditional_t<eq<T0, T1>::value, order_eq,
                     order_gt>
>
{
};

template <template <class> typename Domain,
          typename Arg>
struct lt<Domain<infinity_lower>, Domain<Arg>> : public std::conditional_t<
  std::is_same<Arg, infinity_lower>::value,
  std::false_type, std::true_type
  >
{
};

template <template <class> typename Domain>
struct lt<Domain<infinity_lower>, Domain<infinity_upper>>
  : public std::true_type
{
};

template <template <class> typename Domain>
struct lt<Domain<infinity_upper>, Domain<infinity_lower>>
  : public std::false_type
{
};

template <template <class> typename Domain,
          typename Arg>
struct gt<Domain<infinity_lower>, Domain<Arg>> : public std::false_type
{
};

template <template <class> typename Domain,
          typename Arg>
struct lt<Domain<infinity_upper>, Domain<Arg>> : public std::false_type
{
};

template <template <class> typename Domain,
          typename Arg>
struct gt<Domain<Arg>, Domain<infinity_upper>> : public std::conditional_t<
  std::is_same<Arg, infinity_upper>::value,
  std::true_type, std::false_type
  >
{
};

template <template <class> typename Domain>
struct gt<Domain<infinity_lower>, Domain<infinity_upper>>
  : public std::false_type
{
};

template <template <class> typename Domain>
struct gt<Domain<infinity_upper>, Domain<infinity_lower>>
  : public std::true_type
{
};

template <template <class> typename Domain>
struct max : public monoid<
  Domain, detail::max_impl, infinity_lower
>
{
};

template <template <class> typename Domain>
struct min : public monoid<
  Domain, detail::min_impl, infinity_upper
>
{
};

}

#endif /* if not defined 'FMP_174E3523_C237_4B3A_87D4_E995AF774952' */
