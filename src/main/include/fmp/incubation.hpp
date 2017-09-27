#if !defined(FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243)
#define FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243

#include <limits>

#include <fmp/primitive.hpp>

namespace fmp {

enum struct ordering {
  LT = -1,
  EQ = 0,
  GT = 1
};

using order_lt = std::integral_constant<ordering, ordering::LT>;
using order_eq = std::integral_constant<ordering, ordering::EQ>;
using order_gt = std::integral_constant<ordering, ordering::GT>;

template <typename T>
struct type_size {
  constexpr static size_t size = sizeof(T);

  template <typename A0>
  using equals = std::conditional_t<(sizeof(T) == sizeof(A0)), t_type, nil_type>;

  template <typename A0>
  using less_than = std::conditional_t<(sizeof(T) < sizeof(A0)), t_type, nil_type>;

  template <typename A0>
  using greater_than = std::conditional_t<(sizeof(T) > sizeof(A0)), t_type, nil_type>;
};

struct type_size_min {};
struct type_size_max {};

template <>
struct type_size<type_size_min> {
  constexpr static size_t size = 0ul;

  template <typename A0>
  using equals = std::conditional_t<std::is_same<type_size_min, A0>::value, t_type, nil_type>;

  template <typename A0>
  using less_than = t_type;

  template <typename A0>
  using greater_than = nil_type;
};

template <>
struct type_size<type_size_max> {
  constexpr static size_t size = std::numeric_limits<size_t>::max();

  template <typename A0>
  using equals = std::conditional_t<std::is_same<type_size_max, A0>::value, t_type, nil_type>;

  template <typename A0>
  using less_than = nil_type;

  template <typename A0>
  using greater_than = t_type;
};


namespace detail { // fmp::detail

template <template <class...> typename F,
          typename... A>
struct curried {
  using type = F<A...>;
};

template <template <class...> typename F>
struct curried<F> {
  using type = F<>;
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
};

}

#endif /* if not defined 'FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243' */
