//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243)
#define FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243

#include <fmp/primitive.hpp>
#include <fmp/operator.hpp>

namespace fmp {

namespace detail {

} // ns: detail

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


namespace detail {

template <template <class> typename F,
          typename... T>
struct map_impl;

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

//  using type = detail::curried<F, A...>;

  template <typename... P>
  using apply = typename detail::curried<F, A..., P...>::type;

  template <typename... Adds>
  using currying = curry<F, A..., Adds...>;
};


namespace detail {


struct apply_impl {
  template <template <class...> typename F,
            typename... A>
  static auto get(typename F<A...>::type*) noexcept -> typename F<A...>::type;

  template <template <class...> typename F,
            typename... A>
  static auto get(...) noexcept -> curry<F, A...>;

};

}

template <template <class...> typename F,
          typename... A>
struct apply : public derived<
  decltype(detail::apply_impl::get<F, A...>(nullptr))
>
{
};

template <template <class> typename F,
          template <class...> typename G,
          typename... A>
struct compose : public std::conditional_t<
  has_type<G<A...>>::value,
  derived<typename G<A...>::type>,
  curry<G, A...>
> {
};

template <template <class> typename F>
struct functor {
  template <typename T>
  using map = F<T>;
};

template <template <class> typename F,
          typename T>
struct map;

template <template <class> typename F,
          typename... A>
struct map<F, sequence<A...>> {
};

}

#endif /* if not defined 'FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243' */
