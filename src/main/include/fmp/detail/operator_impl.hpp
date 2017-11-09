//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_9F9BE7D4_BB83_4900_9AC3_7BB8B33BC7F9)
#define FMP_9F9BE7D4_BB83_4900_9AC3_7BB8B33BC7F9

#include <fmp/primitive.hpp>
#include <fmp/apply.hpp>
#include <fmp/operators_fwd.hpp>

namespace fmp {

namespace detail {

template <
  template <class...> typename Monoid,
  typename Unity,
  template <class, class> typename Unite
>
struct monoid_default {
  using unity = Monoid<Unity>;

  template <typename A0, typename A1>
  using unite = typename Unite<A0, A1>::type;
  // using unite = apply_t
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

// operator and
struct is_and_operatable_impl {
  template <typename T0, typename T1>
  static auto check(T0*, T1*) -> decltype(
    (T0::value && T1::value),
    std::true_type()
  );

  template <typename T0, typename T1>
  static auto check(...) -> std::false_type;
};

#if 0
template <typename T0, typename T1>
struct op_and_impl : std::enable_if_t<
  is_and_operatable<T0, T1>::value,
  bool_type<T0::value && T1::value>
>
{
};
#endif

template <typename T0, typename T1>
struct op_and_impl0 : public derived<
  bool_type<T0::type::value && T1::type::value>
>
{
};

// operator
template <template <class> typename OP>
struct monoid_unite_impl;


// operatable?
template <template <class> typename T>
struct is_bin_op_impl;

// all
template <>
struct is_bin_op_impl<all> {
  template <typename T0, typename T1>
  static auto check(all<T0>*, all<T1>*) -> decltype(
    (T0::type::value && T1::type::value),
    std::true_type()
  );

  template <typename T0, typename T1>
  static auto check(...) -> std::false_type;
};

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

template <typename A0, typename A1>
struct endo_unite_impl {
  using type = A0;
};

// operator or
struct is_or_operatable_impl {
  template <typename T0, typename T1>
  static auto check(T0*, T1*) -> decltype(
    (T0::value || T1::value),
    std::true_type()
  );

  template <typename T0, typename T1>
  static auto check(...) -> std::false_type;
};

template <typename T0, typename T1>
struct op_or_impl : public std::enable_if_t<
  is_or_operatable<T0, T1>::value,
  bool_type<T0::value || T1::value>
>
{
};

// operator compare
struct is_lt_operatable_impl {
  template <typename T0, typename T1>
  static auto check(T0*, T1*) -> decltype(
    (T0::value < T1::value),
    std::true_type()
  );

  template <typename T0, typename T1>
  static auto check(...) -> std::false_type;
};

template <typename T0, typename T1>
struct op_lt_impl : public std::enable_if_t<
  is_lt_operatable<T0, T1>::value,
  bool_type<(T0::value < T1::value)>
>
{
};

struct is_eq_operatable_impl {
  template <typename T0, typename T1>
  static auto check(T0*, T1*) -> decltype(
    (T0::value == T1::value),
    std::true_type()
  );

  template <typename T0, typename T1>
  static auto check(...) -> std::false_type;
};

template <typename T0, typename T1>
struct op_eq_impl : public std::enable_if_t<
  is_eq_operatable<T0, T1>::value,
  bool_type<(T0::value == T1::value)>
>
{
};

struct is_gt_operatable_impl {
  template <typename T0, typename T1>
  static auto check(T0*, T1*) -> decltype(
    (T0::value > T1::value),
    std::true_type()
  );

  template <typename T0, typename T1>
  static auto check(...) -> std::false_type;
};

template <typename T0, typename T1>
struct op_gt_impl : public std::enable_if_t<
  is_gt_operatable<T0, T1>::value,
  bool_type<(T0::value > T1::value)>
>
{
};

// max implementation
template <typename T0, typename T1>
struct max_impl : public std::enable_if_t<
  is_lt_operatable<T0, T1>::value,
  derived<std::conditional_t<lt<T0, T1>::value, T1, T0>>
>
{
};

// min implementation
template <typename T0, typename T1>
struct min_impl : public std::enable_if_t<
  is_gt_operatable<T0, T1>::value,
  derived<std::conditional_t<gt<T0, T1>::value, T1, T0>>
>
{
};

} /* ns: detail */ } /* ns: fmp */

#endif /* if not defined 'FMP_9F9BE7D4_BB83_4900_9AC3_7BB8B33BC7F9' */
