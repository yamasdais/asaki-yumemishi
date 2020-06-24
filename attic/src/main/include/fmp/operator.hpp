//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_174E3523_C237_4B3A_87D4_E995AF774952)
#define FMP_174E3523_C237_4B3A_87D4_E995AF774952

#include <fmp/primitive.hpp>
#include <fmp/operator_fwd.hpp>
#include <fmp/curry.hpp>
#include <fmp/compose.hpp>

#include <fmp/detail/operator_impl.hpp>

namespace fmp {

#if 0
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
#endif

#if 0
/**
 * 'or' operator ('or' in latin. because of c++ reserved word)
 */
struct uel : public monoid<
  boolean, detail::op_or_impl, std::false_type
>
{
};
#endif

/**
 * 'equals' operator
 */
template <typename V0, typename V1>
struct eq : public bool_type<V0::value == V1::value> {
};

template <typename V0, typename V1>
using eq_t = typename eq<V0, V1>::type;

/**
 * 'not equals' operator
 */
template <typename V0, typename V1>
struct ne : public bool_type<V0::value != V1::value> {
};

template <typename V0, typename V1>
using ne_t = typename ne<V0, V1>::type;

/**
 * 'less than' operator
 */
template <typename V0, typename V1>
struct lt : public bool_type<(V0::value < V1::value)> {
};

template <typename V0, typename V1>
using lt_t = typename lt<V0, V1>::type;

/**
 * 'less than or equal' operator
 */
template <typename V0, typename V1>
struct lte : public bool_type<(V0::value <= V1::value)> {
};

template <typename V0, typename V1>
using lte_t = typename lte<V0, V1>::type;

/**
 * 'greater than' operator
 */
template <typename V0, typename V1>
struct gt : public bool_type<(V0::value > V1::value)> {
};

template <typename V0, typename V1>
using gt_t = typename gt<V0, V1>::type;

/**
 * 'greater than or equals' operator
 */
template <typename V0, typename V1>
struct gte : public bool_type<(V0::value >= V1::value)> {
};

template <typename V0, typename V1>
using gte_t = typename gte<V0, V1>::type;

/**
 * 'negate' operator
 */
template <typename V>
struct neg : public bool_type<(!V::value)> {
};

template <typename V>
using neg_t = typename neg<V>::type;

/**
 * 'and' operator
 * et: 'and' in Latin.
 */
template <typename V0, typename V1>
struct et : public bool_type<(V0::value && V1::value)> {
};

template <typename V0, typename V1>
using et_t = typename et<V0, V1>::type;

/**
 * 'or' operator
 * uel: 'or' in Latin.
 */
template <typename V0, typename V1>
struct uel : public bool_type<(V0::value || V1::value)> {
};

template <typename V0, typename V1>
using uel_t = typename uel<V0, V1>::type;

/**
 * compare operator
 */
enum class ordering {
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

#if 0
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
#endif
}

#endif /* if not defined 'FMP_174E3523_C237_4B3A_87D4_E995AF774952' */
