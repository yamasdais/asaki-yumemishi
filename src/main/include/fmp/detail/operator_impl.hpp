#if !defined(FMP_9F9BE7D4_BB83_4900_9AC3_7BB8B33BC7F9)
#define FMP_9F9BE7D4_BB83_4900_9AC3_7BB8B33BC7F9

#include <fmp/primitive.hpp>

namespace fmp { namespace detail {

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
  decltype(is_and_operatable_impl::check<T0, T1>(nullptr, nullptr))::value,
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
struct op_or_impl : std::enable_if_t<
  decltype(is_or_operatable_impl::check<T0, T1>(nullptr, nullptr))::value,
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
struct op_lt_impl : std::enable_if_t<
  decltype(is_lt_operatable_impl::check<T0, T1>(nullptr, nullptr))::value,
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
struct op_eq_impl : std::enable_if_t<
  decltype(is_eq_operatable_impl::check<T0, T1>(nullptr, nullptr))::value,
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
struct op_gt_impl : std::enable_if_t<
  decltype(is_gt_operatable_impl::check<T0, T1>(nullptr, nullptr))::value,
  bool_type<(T0::value > T1::value)>
>
{
};


} /* ns: detail */ } /* ns: fmp */

#endif /* if not defined 'FMP_9F9BE7D4_BB83_4900_9AC3_7BB8B33BC7F9' */
