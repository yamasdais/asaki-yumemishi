#if !defined(FMP_9F9BE7D4_BB83_4900_9AC3_7BB8B33BC7F9)
#define FMP_9F9BE7D4_BB83_4900_9AC3_7BB8B33BC7F9

#include <fmp/primitive.hpp>

namespace fmp {

// forward declarations in 'operator.hpp'
template <typename T0, typename T1>
struct is_and_operatable;

template <typename T0, typename T1>
struct is_or_operatable;

template <typename T0, typename T1>
struct is_lt_operatable;

template <typename T0, typename T1>
struct is_eq_operatable;

template <typename T0, typename T1>
struct is_gt_operatable;

template <typename T0, typename T1>
struct lt;

template <typename T0, typename T1>
struct eq;

template <typename T0, typename T1>
struct gt;

namespace detail {

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

template <typename T0, typename T1>
struct op_and_impl : std::enable_if_t<
  is_and_operatable<T0, T1>::value,
  bool_type<T0::value && T1::value>
>
{
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
