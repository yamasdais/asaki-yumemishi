#if !defined(FMP_2EAC0BFA_977A_4474_BCBE_66EF548CE53D)
#define FMP_2EAC0BFA_977A_4474_BCBE_66EF548CE53D

#include <type_traits>

// tags
namespace fmp {

struct t_type : public std::true_type {
};

struct nil_type : public std::false_type {
};

struct unit_type {
};

struct undefined_type {
};



// operator
template <typename, typename>
struct eq : public nil_type {
  using apply = nil_type;
};

template <typename T>
struct eq<T, T> : public t_type {
  using apply = t_type;
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
struct value : public std::integral_constant<T, V> {
  using type = value<T, V>;
};

// monoid
template <template <class, class> typename Unite,
          typename Unity>
struct monoid {
  using unity = Unity;

  template <typename LType, typename RType = unity>
  using unite = Unite<LType, RType>;
};

}

#endif /* FMP_2EAC0BFA_977A_4474_BCBE_66EF548CE53D */

