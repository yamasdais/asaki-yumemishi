#include <iostream>
#include <type_traits>
#include <limits>

#include <fmp.hpp>
#include <fmp/incubation.hpp>

struct mtest0 : public fmp::monoid<fmp::eq, fmp::value<int, 0>> {
};

template <typename T0, typename T1>
struct type_size_wider {
  using apply = std::conditional_t<(sizeof(T0) < sizeof(T1)),
    T1, T0>;
};

//typedef char max_size_type[std::numeric_limits<size_t>::max()];
//using max_size_type = char[std::numeric_limits<size_t>::max()];

struct fofo : public fmp::monoid<type_size_wider, fmp::type_size_min> {
};

void test_value() {
  using namespace fmp;
  using val0 = fmp::value<int, 0>;
  static_assert(val0() == 0, "val0() == 0");
}

void test_monoid() {
  using wider_type = type_size_wider<char, long>;

  /// simpler way to define concrete monoid
  using wider_monoid = fmp::monoid<type_size_wider, fmp::type_size_min>;

  static_assert(mtest0::unity() == 0, "mtest0::unity() == 0");
  static_assert(std::is_same<wider_type::apply, long>(),
                "wider");
  static_assert(std::is_same<fofo::unite<long>, long>(),
                "unite<long> with unity");

  static_assert(std::is_same<wider_monoid::unite<int>, int>(),
                "unite with unity");
}

void test_order() {
  std::cout << "sizeof min_type_size: "
            << fmp::type_size<fmp::type_size_min>::size << std::endl;
  std::cout << "sizeof max_type_size: "
            << fmp::type_size<fmp::type_size_max>::size << std::endl;
  std::cout << "LT: " << (int)fmp::order_lt::value << std::endl;
  std::cout << "EQ: " << fmp::type_size<fmp::type_size_max>::equals<fmp::type_size_max>()
            << std::endl;
  std::cout << "less_than: " << fmp::type_size<fmp::type_size_min>::less_than<int>() << std::endl;
  std::cout << "greater_than: " << fmp::type_size<fmp::type_size_max>::greater_than<char>() << std::endl;
}

void test_eq() {
  using namespace fmp;
  static_assert(eq<int, int>::value,
                "eq<int, int> => true");
  static_assert(!eq<int, long>::value,
                "eq<int, long> => false");

}


void test_curry() {
  using fmp::curry;
  using c0 = curry<std::is_same, int>;
  using c1 = c0::apply<int>;
  std::cout << "c0 curried params:" << c0::value << std::endl;
  std::cout << "curry<is_same, int>::apply<int>:" << c1() << std::endl;
}

int main(int , char**)
{
  test_eq();
  test_order();
  test_monoid();
  test_curry();
  
  return 0;
}
