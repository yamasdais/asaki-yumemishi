//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243)
#define FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243

#include <fmp/primitive.hpp>
#include <fmp/operator.hpp>
#include <fmp/sequence.hpp>

namespace fmp {

namespace detail {

} // ns: detail

#if 0
template <template <class A0, class A1> typename F,
          typename Acc, typename... T>
struct foldl {
  using type = typename detail::foldl_elem<F, Acc, T...>::type;
};

template <template <class A0, class A1> typename F,
          typename Acc, typename... T>
struct foldr {
  using type = typename detail::foldr_elem<F, Acc, T...>::type;
};
#endif

namespace detail {

#if 0
template <template <class> typename F,
          typename... T>
struct map_impl;
#endif

}


template <typename T>
struct type_size {
  using type = T;
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


namespace detail { // fmp::detail

} // end of fmp::detail



namespace detail {


}

template <template <class> typename F>
struct functor {
  template <typename T>
  using map = F<T>;
};


namespace detail {


}

}

#endif /* if not defined 'FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243' */
