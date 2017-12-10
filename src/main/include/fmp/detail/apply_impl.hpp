//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#if !defined(FMP_1FFFCA1A_7C8B_4204_83CF_60372B9EC888)
#define FMP_1FFFCA1A_7C8B_4204_83CF_60372B9EC888

namespace fmp {
namespace detail {

struct apply_impl {
  template <typename T,
            typename... A>
  static auto get(typename T::template apply<A...>::type*) noexcept
    -> typename T::template apply<A...>::type;

  template <typename,
            typename... A>
  static auto get(...) noexcept
    -> nothing;
};

} /* ns: fmp::detail */
} /* ns: fmp */


#endif /* FMP_1FFFCA1A_7C8B_4204_83CF_60372B9EC888 */
