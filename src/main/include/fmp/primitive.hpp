#if !defined(FMP_2EAC0BFA_977A_4474_BCBE_66EF548CE53D)
#define FMP_2EAC0BFA_977A_4474_BCBE_66EF548CE53D

#include <type_traits>

// tags
namespace fmp {

#if 0
struct t_type : public std::true_type {
};

struct nil_type : public std::false_type {
};
#endif

struct unit_type {
};

struct undefined_type {
};


// utility
template <typename T>
struct derived : public T {
  using type = T;
};

template <typename T>
using derived_t = typename derived<T>::type;

namespace detail {

struct has_value_impl {
  template <typename T>
  static auto check(T*) -> decltype(
    (T::value == T::value),
    std::true_type());

  template <typename T>
  static auto check(...) -> std::false_type;
};

}

template <typename T>
using has_value = derived_t<
  decltype(detail::has_value_impl::check<T>(nullptr))
>;


// operator
template <bool Cond>
struct bool_type : public std::conditional_t<
  Cond, std::true_type, std::false_type
>
{
};

template <typename T>
struct boolean : public std::enable_if_t<
  has_value<T>::value,
  bool_type<T::value>
>
{
};


template <typename, typename>
struct eq : public std::false_type {
};

template <typename T>
struct eq<T, T> : public std::true_type {
};

// simple type
template <typename T>
struct quote {
  using type = quote<T>;
  using unquote = T;
};

} // namespace fmp

#include <fmp/detail/sequence.hpp>

namespace fmp {

template <typename A, typename D>
struct cons {
  using type = cons<A, D>;
  using car_type = A;
  using cdr_type = D;
};

template <typename... T>
struct sequence {
  using type = sequence<T...>;
  constexpr static size_t size = sizeof...(T);

  using head = typename detail::head_impl<T...>::apply;
  using tail = typename detail::head_impl<T...>::template tail<sequence>;

  template <typename... A>
  using append = sequence<T..., A...>;

  template <typename... A>
  using prepend = sequence<A..., T...>;
};

template <typename T, T V>
struct val : public std::integral_constant<T, V> {
  using type = val<T, V>;
};

}

#endif /* FMP_2EAC0BFA_977A_4474_BCBE_66EF548CE53D */

