#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <limits>

#include <fmp.hpp>
#include <fmp/incubation.hpp>

#include "sample.hpp"

void test_quote() {
  using q0 = fmp::quote<int>;
  std::cout << "Quote::type: " << demangle<q0::type>() << std::endl;
  std::cout << "Unquote: " << demangle<q0::unquote>() << std::endl;
}

void test_derived() {
  using q0 = fmp::quote<int>;
  using d0 = fmp::derived<q0>;

  std::cout << "derived: " << demangle<d0::type>() << std::endl;
}

void test_value() {
  using namespace fmp;
  using val0 = fmp::value<int, 0>;
  static_assert(val0() == 0, "val0() == 0");
}


// monoid test
template <typename T0, typename T1>
struct type_size_comparator : public fmp::compare<fmp::type_size, T0, T1> {
};

template <typename T0, typename T1>
struct larger : public fmp::derived<std::conditional_t<
  (type_size_comparator<T0, T1>::value == fmp::order_lt::value),
  T1,
  T0
    >>
{
};

struct m_test0 : public fmp::monoid<
  fmp::type_size, larger, fmp::type_size_min
  >
{
};

void test_monoid() {
  /// simpler way to define concrete monoid
  using max_monoid = fmp::monoid<
    fmp::type_size, larger, fmp::type_size_min
    >;
  std::cout << "max_monoid: " << demangle<max_monoid>() << std::endl;
  std::cout << "monoid::op => " << demangle<max_monoid::unite<int, char>::type>()
            << std::endl;
}
#if 0
template <typename T0, typename T1>
struct type_size_wider0 {
  using apply = std::conditional_t<(sizeof(T0) < sizeof(T1)),
    T1, T0>;
};


struct mtest0 : public fmp::monoid<fmp::eq, fmp::value<int, 0>> {
};

void test_monoid() {
  /// simpler way to define concrete monoid
  using cmp_monoid = fmp::monoid<type_size_comparator, fmp::type_size_min>;

  static_assert(mtest0::unity() == 0, "mtest0::unity() == 0");
  static_assert(std::is_same<wider_type::apply, long>(),
                "wider");

//  static_assert(std::is_same<wider_monoid::unite<int>, int>(),
//                "unite with unity");
  std::cout << cmp_monoid::unite<int>::value << std::endl;
  //auto dem = demangle<cmp_monoid>();
  std::cout << "demangle: " << demangle<cmp_monoid>() << std::endl;

  std::cout << "demangle obj: " << demangle(std::cout) << std::endl;
}
#endif
// order test
void test_order() {
  std::cout << "sizeof min_type_size: "
            << fmp::type_size<fmp::type_size_min>::size << std::endl;
  std::cout << "sizeof max_type_size: "
            << fmp::type_size<fmp::type_size_max>::size << std::endl;
  std::cout << "LT: " << fmp::order_lt() << std::endl;
  std::cout << "EQ: " << fmp::type_size<fmp::type_size_max>::equals<fmp::type_size_max>()
            << std::endl;
  std::cout << "less_than: " << fmp::type_size<fmp::type_size_min>::less_than<int>() << std::endl;
  std::cout << "greater_than: " << fmp::type_size<fmp::type_size_max>::greater_than<char>() << std::endl;

  using c0 = fmp::cmp<fmp::type_size>::apply<int, int>;
  using c1 = fmp::compare<fmp::type_size, char, int>;
  std::cout << "compare: " << c1() << std::endl;
}

void test_eq() {
  using namespace fmp;
  static_assert(eq<int, int>::value,
                "eq<int, int> => true");
  static_assert(!eq<int, long>::value,
                "eq<int, long> => false");

}

template <typename... A>
struct noarg;

template <>
struct noarg<> {
  constexpr static int value = 43;
};

void test_curry() {
  using fmp::curry;
  using c0 = curry<std::is_same, int>;
  using c1 = c0::apply<int>;
  using c2 = c0::currying<long>;

  using n0 = curry<noarg>;
  
  std::cout << "c0 curried params:" << c0::value << std::endl;
  std::cout << "curry<is_same, int>::apply<int>:" << c1() << std::endl;
  std::cout << "c0::currying<long>: " << c2::apply<>() << std::endl;

  std::cout << "n0::value: " << n0::apply<>::value << std::endl;
}

int main(int , char**)
{
  test_derived();
  test_quote();
  test_eq();
  test_order();
  test_monoid();
  test_curry();
  
  return 0;
}
