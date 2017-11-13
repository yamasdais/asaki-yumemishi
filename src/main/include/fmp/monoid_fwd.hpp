//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_C261D76F_312D_4D18_9C20_9304AEBBF61C)
#define FMP_C261D76F_312D_4D18_9C20_9304AEBBF61C

namespace fmp {

// monoid base
template <template <class...> typename Monoid>
struct monoid_trait;


template <template <class...> typename Monoid>
struct unity;

template <typename A0, typename A1>
struct unite;

template <typename Param>
struct all;

template <typename T>
struct endo;

template <template <class> typename OP,
          typename A0, typename A1>
struct is_monoid;

template <template <class> typename OP,
          typename A0, typename A1>
using is_monoid_t = typename is_monoid<OP, A0, A1>::type;

} /* ns: fmp */

#endif /* if not defined 'FMP_C261D76F_312D_4D18_9C20_9304AEBBF61C' */
