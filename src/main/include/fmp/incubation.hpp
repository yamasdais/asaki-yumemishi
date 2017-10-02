#if !defined(FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243)
#define FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243

#include <limits>

#include <fmp/primitive.hpp>
#include <fmp/operator.hpp>

namespace fmp {

namespace detail {


} // ns: detail


namespace detail {

}


template <typename T>
struct type_size {
  constexpr static size_t value = sizeof(T);

  template <typename Other>
  using equals = std::conditional_t<
    (value == Other::value),
    std::true_type, std::false_type>;

  template <typename Other>
  using less_than = std::conditional_t<
    (value < Other::value),
    std::true_type, std::false_type>;

  template <typename Other>
  using greater_than = std::conditional_t<
    (value > Other::value),
    std::true_type, std::false_type>;
};

struct type_size_min {};
struct type_size_max {};

template <>
struct type_size<type_size_min> {
  constexpr static size_t value = 0ul;

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
  constexpr static size_t value = std::numeric_limits<size_t>::max();

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

template <typename A0, typename A1>
struct less_than;

template <typename A0, typename A1>
struct less_than : public
  bool_type<(A0::value < A1::value)>
{
};

#if 0
template <template <class...> typename F,
          typename A0, typename A1>
struct compare : public fmp::derived<std::conditional_t<
  F<A0>::template less_than<A1>::value,
    order_lt,
    std::conditional_t<
      F<A0>::template equals<A1>::value,
      order_eq,
      order_gt
    >
  >
>
{
};
#endif

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
