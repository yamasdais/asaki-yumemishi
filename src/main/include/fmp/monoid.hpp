//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_7D240F6E_E2FC_4A9D_AAAC_D40F96A23903)
#define FMP_7D240F6E_E2FC_4A9D_AAAC_D40F96A23903

#include <fmp/monoid_fwd.hpp>

namespace fmp {

// monoid unity
template <typename T>
using has_unity = derived_t<
  decltype(detail::has_unity_impl::check<T>(nullptr))
>;

template <
  template <class...> typename Monoid
>
struct unity {
  using type = typename monoid_trait<Monoid>::unity;
};

template <
  template <class...> typename Monoid
>
using unity_t = typename unity<Monoid>::type;


// monoid unite
template <
  template <class...> typename Monoid,
  typename A0, typename A1
>
struct unite<Monoid<A0>, Monoid<A1>> {
//  using type = typename A0::template unite_t<A1>;
  using type = Monoid<typename monoid_trait<Monoid>::template unite<Monoid<A0>, Monoid<A1>>>;
};


template <typename A0, typename A1>
using unite_t = typename unite<A0, A1>::type;

/**
 * 'and' operator ('and' in latin. because of c++ reserved word)
 */
template <typename Param>
struct all
{
  using type = typename boolean<Param>::type;
};

template <typename A0, typename A1>
struct is_monoid<all, A0, A1> : public derived_t<
  decltype(detail::is_bin_op_impl<all>::check<A0, A1>(nullptr, nullptr))
>
{
};

template <>
struct monoid_trait<all> : public detail::monoid_default<
  all,
  std::true_type,
  detail::monoid_unite_impl<all>::apply
> {
};


/**
 * Monoid endo
 */
template <typename T>
struct endo {
  //static_assert(is_curried_v<T>, "endo<T>: expected curry<F> as T");
  using type = T;
};

template <>
struct monoid_trait<endo> : public detail::monoid_default<
  endo,
  curry<id>,
  detail::monoid_unite_impl<endo>::apply
  >
{
};


} /* ns: fmp */

#endif /* if not defined 'FMP_7D240F6E_E2FC_4A9D_AAAC_D40F96A23903' */
