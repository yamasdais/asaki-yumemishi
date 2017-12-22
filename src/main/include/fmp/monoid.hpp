//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_7D240F6E_E2FC_4A9D_AAAC_D40F96A23903)
#define FMP_7D240F6E_E2FC_4A9D_AAAC_D40F96A23903

#include <fmp/monoid_fwd.hpp>
#include <fmp/apply.hpp>
#include <fmp/compose.hpp>
#include <fmp/detail/monoid_impl.hpp>
#include <fmp/detail/operator_impl.hpp>
#include <fmp/check.hpp>

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
  typename... A0, typename... A1
>
struct unite<Monoid<A0...>, Monoid<A1...>> {
  using type = typename monoid_trait<Monoid>::template unite<
    Monoid<A0...>, Monoid<A1...>>;
};

template <typename A0, typename A1>
using unite_t = typename unite<A0, A1>::type;

// monoid concat
template <
  template <class...> typename Monoid,
  typename C
>
struct mconcat
{
  using type = apply_t<typename monoid_trait<Monoid>::concat, C>;

  using trace = typename monoid_trait<Monoid>::concat;
};

template <
  template <class...> typename Monoid,
  typename C
>
using mconcat_t = typename mconcat<Monoid, C>::type;

/**
 * 'and' operator
 */
template <typename Param>
struct all
{
  using get = typename boolean<Param>::type;
//  using type = typename boolean<Param>::type;
//  using type = all<typename boolean<Param>::type>;
  using type = all<get>;
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
  detail::monoid_unite_impl<all>::apply,
  std::true_type
> {
};


/**
 * Monoid endo
 */
template <typename T>
struct endo {
  static_assert(has_apply_v<T>, "endo<T>: expected type that has apply<>");

  using get = T;
  using type = endo<T>;

  template <typename... A0>
  using apply = id<apply_t<T, A0...>>;
};

template <>
struct monoid_trait<endo> : public detail::monoid_default<
  endo,
  detail::monoid_unite_impl<endo>::apply,
  curry<id>
  >
{
};

} /* ns: fmp */

#endif /* if not defined 'FMP_7D240F6E_E2FC_4A9D_AAAC_D40F96A23903' */
