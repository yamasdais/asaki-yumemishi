#if !defined(FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243)
#define FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243

#include <limits>

#include <fmp/primitive.hpp>

namespace fmp {

template <typename T>
struct derived : public T {
  using type = T;
};

enum ordering {
  LT = -1,
  EQ = 0,
  GT = 1
};

struct order_lt
  : public std::integral_constant<ordering, ordering::LT> {
};
struct order_eq
  : public std::integral_constant<ordering, ordering::EQ> {
};
struct order_gt
  : public std::integral_constant<ordering, ordering::GT> {
};

template <typename T>
struct type_size {
  constexpr static size_t size = sizeof(T);

  template <typename A0>
  using equals = std::conditional_t<
    (sizeof(T) == sizeof(A0)),
    std::true_type, std::false_type>;

  template <typename A0>
  using less_than = std::conditional_t<
    (sizeof(T) < sizeof(A0)),
    std::true_type, std::false_type>;

  template <typename A0>
  using greater_than = std::conditional_t<
    (sizeof(T) > sizeof(A0)),
    std::true_type, std::false_type>;
};

struct type_size_min {};
struct type_size_max {};

template <>
struct type_size<type_size_min> {
  constexpr static size_t size = 0ul;

  template <typename A0>
  using equals = std::conditional_t<
    std::is_same<type_size_min, A0>::value,
    std::true_type, std::false_type>;

  template <typename A0>
  using less_than = std::true_type;

  template <typename A0>
  using greater_than = std::false_type;
};

template <>
struct type_size<type_size_max> {
  constexpr static size_t size = std::numeric_limits<size_t>::max();

  template <typename A0>
  using equals = std::conditional_t<
    std::is_same<type_size_max, A0>::value,
    std::true_type, std::false_type>;

  template <typename A0>
  using less_than = std::false_type;

  template <typename A0>
  using greater_than = std::true_type;
};

template <template <class...> typename F>
struct cmp {
  template <typename A0, typename A1>
  using apply = std::conditional_t<
    F<A0>::template less_than<A1>::value,
    order_lt,
    std::conditional_t<
      F<A0>::template equals<A1>::value,
      order_eq,
      order_gt
    >
  >;
};

template <template <class...> typename F,
          typename A0, typename A1>
struct compare : public std::conditional_t<
  F<A0>::template less_than<A1>::value,
    order_lt,
    std::conditional_t<
      F<A0>::template equals<A1>::value,
      order_eq,
      order_gt
    >
  >
{
};

namespace detail { // fmp::detail

template <template <class...> typename F,
          typename... A>
struct curried {
  using type = F<A...>;
};

} // end of fmp::detail


template <template <class...> typename F,
          typename... A>
struct curry {
  using args = sequence<A...>;
  constexpr static size_t value = sizeof...(A);

  using type = detail::curried<F, A...>;

  template <typename... P>
  using apply = typename detail::curried<F, A..., P...>::type;

  template <typename... Adds>
  using currying = curry<F, A..., Adds...>;
};

}

#endif /* if not defined 'FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243' */
