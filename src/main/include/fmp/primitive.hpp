#if !defined(UUID_2EAC0BFA_977A_4474_BCBE_66EF548CE53D)
#define UUID_2EAC0BFA_977A_4474_BCBE_66EF548CE53D

namespace fmp {

template <typename A, typename D>
struct cons {
  using type = cons<A, D>;
  using car_type = A;
  using cdr_type = D;
};

template <typename T, T V>
struct value : public std::integral_constant<T, V> {
  using type = value<T, V>;
};

template <typename T>
struct any {
  using type = any<T>;
  using value_type = T;
};


}

#endif /* UUID_2EAC0BFA_977A_4474_BCBE_66EF548CE53D */
#include <type_traits>

