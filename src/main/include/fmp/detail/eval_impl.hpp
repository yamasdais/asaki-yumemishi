//          Copyright Yamashta, Daisuke 2017-2018
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_F1777EF5_3241_421E_ACD0_65998A0A7706)
#define FMP_F1777EF5_3241_421E_ACD0_65998A0A7706

#include <fmp/eval_fwd.hpp>
#include <fmp/check.hpp>

namespace fmp {
namespace detail {

template <typename T, bool>
struct eval_impl;

template <typename T>
struct eval_impl<T, true> {
  using type = typename T::type;
};

template <typename T>
struct eval_impl<T, false> {
  using type = T;
};

template <typename T, int Level, bool>
struct evalL_impl;

template <typename T, int Level>
struct evalL_impl<T, Level, true> {
  using type = typename evalL_impl<typename T::type,
                                   Level - 1,
                                   has_type<typename T::type>::value
                                   && (Level > 0)>::type;
};

template <typename T, int Level>
struct evalL_impl<T, Level, false> {
  using type = T;
};

}  /* ns: detail */
}  /* ns: fmp */

#endif /* if not defined 'FMP_F1777EF5_3241_421E_ACD0_65998A0A7706' */
