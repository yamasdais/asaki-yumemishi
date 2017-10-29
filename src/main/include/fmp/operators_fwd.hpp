//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_75C387D6_1FA4_4127_8D87_1CE30C829668)
#define FMP_75C387D6_1FA4_4127_8D87_1CE30C829668

namespace fmp {

template <typename T0, typename T1>
struct is_and_operatable;

template <typename T0, typename T1>
struct is_or_operatable;

template <typename T0, typename T1>
struct is_lt_operatable;

template <typename T0, typename T1>
struct is_eq_operatable;

template <typename T0, typename T1>
struct is_gt_operatable;

template <typename T0, typename T1>
struct lt;

template <typename T0, typename T1>
struct eq;

template <typename T0, typename T1>
struct gt;


template <typename A0, typename A1>
struct append;

template <typename A0, typename A1>
using append_t = typename append<A0, A1>::type;

// monoid base
template <template <class...> typename Monoid>
struct monoid_trait;


template <template <class...> typename Monoid>
struct unity;

template <typename A0, typename A1>
struct unite;

template <typename Param>
struct all;

template <template <class> typename OP,
          typename A0, typename A1>
struct is_monoid;

template <template <class> typename OP,
          typename A0, typename A1>
using is_monoid_t = typename is_monoid<OP, A0, A1>::type;

} /* ns: fmp */

#endif /* FMP_75C387D6_1FA4_4127_8D87_1CE30C829668 */
