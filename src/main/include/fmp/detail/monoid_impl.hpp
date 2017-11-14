//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_C9D45967_C2F8_45C5_9A79_E343AEC35685)
#define FMP_C9D45967_C2F8_45C5_9A79_E343AEC35685

#include <fmp/monoid_fwd.hpp>

namespace fmp {

namespace detail {

// operator
template <template <class> typename OP>
struct monoid_unite_impl;

template <
  template <class...> typename Monoid,
  typename Unity,
  template <class, class> typename Unite
>
struct monoid_default {
  using unity = Monoid<Unity>;

  template <typename A0, typename A1>
  using unite = typename Unite<A0, A1>::type;
};

// monoid unity
struct has_unity_impl {
  template <typename T>
  static auto check(typename T::unity*) -> std::true_type;

  template <typename T>
  static auto check(...) -> std::false_type;
};

// monoid unite
struct has_unite_impl {
  template <typename T>
  static auto check(typename T::template unite<
                    typename T::unity,
                    typename T::unity>*) -> std::true_type;

  template <typename T>
  static auto check(...) -> std::false_type;
};

// all
template <>
struct monoid_unite_impl<all> {
  template <typename A0, typename A1>
  using apply = typename bool_type<A0::type::value && A1::type::value>::type;

};

// endo
template <>
struct monoid_unite_impl<endo> {
  template <typename A0, typename A1>
  using apply = apply<compose<typename A0::type, typename A1::type>>;
};

} /* ns: detail */ } /* ns: fmp */

#endif /* if not defined 'FMP_C9D45967_C2F8_45C5_9A79_E343AEC35685' */
