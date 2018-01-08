//          Copyright Yamashta, Daisuke 2017-2018
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_A6375D7A_31AC_4C84_B484_AB9791156620)
#define FMP_A6375D7A_31AC_4C84_B484_AB9791156620

#include <fmp/detail/eval_impl.hpp>

namespace fmp {

template <typename T>
struct eval : public detail::eval_impl<T, has_type<T>::value> {
};

template <typename T>
using eval_t = typename eval<T>::type;

}  /* ns: fmp */

#endif /* if not defined 'FMP_A6375D7A_31AC_4C84_B484_AB9791156620' */
