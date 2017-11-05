//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_AAAA1AA4_2052_4A5F_ABC9_182D0CB9EA32)
#define FMP_AAAA1AA4_2052_4A5F_ABC9_182D0CB9EA32

#include <fmp/list_fwd.hpp>

namespace fmp {
namespace detail {

struct is_cons_impl {
  template <typename T>
  static auto check(typename T::car_type*, typename T::cdr_type* = nullptr)
    noexcept -> std::true_type;

  template <typename>
  static auto check(...) noexcept -> std::false_type;
};

} /* ns: fmp::detail */
} /* ns: fmp */

#endif /* if not defined 'FMP_AAAA1AA4_2052_4A5F_ABC9_182D0CB9EA32' */
