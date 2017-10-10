//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_2ECC40D7_DB96_4BC2_BD50_F6ADD548A8F2)
#define FMP_2ECC40D7_DB96_4BC2_BD50_F6ADD548A8F2

namespace fmp {
namespace detail {

struct curry_apply_impl {
  template <template <class...> typename F,
            typename... A>
  static auto get(typename F<A...>::type*) noexcept
    -> F<A...>;

  template <template <class...> typename F,
            typename... A>
  static auto get(...) noexcept
    -> derived<curry<F, A...>>;
};

} /* ns: fmp::detail */
} /* ns: fmp */

#endif /* FMP_2ECC40D7_DB96_4BC2_BD50_F6ADD548A8F2 */
