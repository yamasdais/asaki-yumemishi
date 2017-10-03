#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <limits>

#include <fmp.hpp>
#include <fmp/incubation.hpp>
#include <fmp/operator.hpp>

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
  using val0 = fmp::val<int, 0>;
  static_assert(val0() == 0, "val0() == 0");
  std::cout << "val::value: " << val0::value << std::endl;

  using has_val0 = has_value<int>;
  using has_val1 = has_value<val0>;
  //std::cout << std::boolalpha;
  std::cout << "has_val0:" << has_val0() << std::endl;
  std::cout << "has_val1:" << has_val1() << std::endl;

  using b0 = fmp::boolean<std::true_type>;
  std::cout << "b0:" << b0() << std::endl;
  std::cout << "b(false):" << fmp::boolean<std::false_type>() << std::endl;

  using can_and_op = fmp::is_and_operatable<has_val0, has_val1>;
  using cant_and_op = fmp::is_and_operatable<has_val0, int>;
  std::cout << "and val0, val1: " << can_and_op() << std::endl;
  std::cout << "and val0, int: " << cant_and_op() << std::endl;

}

void test_monoid_et() {
  using et0 = fmp::et;

  std::cout << "MONOID et---" << std::endl;
  std::cout << "Unity: " << demangle<et0::unity>() << std::endl;
  std::cout << "et<true, false>:" << demangle<et0::op<std::true_type, std::false_type>>() << std::endl;
  std::cout << "et<false, false>:" << demangle<et0::op<std::false_type, std::false_type>>() << std::endl;
  std::cout << "et<false, true>:" << demangle<et0::op<std::false_type, std::true_type>>() << std::endl;
  std::cout << "et<true, true>:" << demangle<et0::op<std::true_type, std::true_type>>() << std::endl;
  std::cout << "et<true>:" << demangle<et0::op<std::true_type>>() << std::endl;
  std::cout << "et<false>:" << demangle<et0::op<std::false_type>>() << std::endl;
}

void test_monoid_uel() {
  using op0 = fmp::uel;

  std::cout << "MONOID uel---" << std::endl;
  std::cout << "Unity: " << demangle<op0::unity>() << std::endl;
  std::cout << "uel<true, false>:" << demangle<op0::op<std::true_type, std::false_type>>() << std::endl;
  std::cout << "uel<false, false>:" << demangle<op0::op<std::false_type, std::false_type>>() << std::endl;
  std::cout << "uel<false, true>:" << demangle<op0::op<std::false_type, std::true_type>>() << std::endl;
  std::cout << "uel<true, true>:" << demangle<op0::op<std::true_type, std::true_type>>() << std::endl;
  std::cout << "uel<true>:" << demangle<op0::op<std::true_type>>() << std::endl;
  std::cout << "uel<false>:" << demangle<op0::op<std::false_type>>() << std::endl;
}

// monoid test
#if 0
template <typename T0, typename T1>
struct type_size_comparator : public fmp::compare<fmp::type_size, T0, T1> {
};
#endif

#if 0
template <typename T0, typename T1>
using type_size_comparator = fmp::derived<fmp::compare<fmp::type_size, T0, T1>>;

template <typename T0, typename T1>
using cmp0 = fmp::derived<
  std::conditional_t<
    T0::template less_than<T1>::value,
    T1, T0
  >
>;

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
  std::cout << "monoid::op => " << demangle<max_monoid::op<char, long long>>()
            << std::endl;
//  std::cout << "tsc => " << demangle<type_size_comparator<int, long>::type::type>() << std::endl;
  using l0 = larger<fmp::type_size<char>, fmp::type_size<long>>;
  std::cout << "larger => " << demangle<l0::type>() << std::endl;
  using c0 = cmp0<fmp::type_size<char>, fmp::type_size<long>>;
  std::cout << "c0 => " << demangle<c0::type>() << std::endl;
}
#endif
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

//  static_assert(std::is_same<wider_monoid::op<int>, int>(),
//                "op with unity");
  std::cout << cmp_monoid::op<int>::value << std::endl;
  //auto dem = demangle<cmp_monoid>();
  std::cout << "demangle: " << demangle<cmp_monoid>() << std::endl;

  std::cout << "demangle obj: " << demangle(std::cout) << std::endl;
}
#endif
// order test
#if 0
void test_order() {
  std::cout << "sizeof min_type_size: "
            << fmp::type_size<fmp::type_size_min>::value << std::endl;
  std::cout << "sizeof max_type_size: "
            << fmp::type_size<fmp::type_size_max>::value << std::endl;
  std::cout << "LT: " << fmp::order_lt() << std::endl;
  std::cout << "EQ: " << fmp::type_size<fmp::type_size_max>::equals<fmp::type_size_max>()
            << std::endl;
  std::cout << "less_than: " << fmp::type_size<fmp::type_size_min>::less_than<fmp::type_size<int>>() << std::endl;
  std::cout << "greater_than: " << fmp::type_size<fmp::type_size_max>::greater_than<fmp::type_size<char>>() << std::endl;

  using c0 = fmp::cmp<fmp::type_size>::apply<fmp::type_size<int>, fmp::type_size<int>>;
  using c1 = fmp::compare<fmp::type_size, fmp::type_size<char>, fmp::type_size<int>>;
  std::cout << "compare: " << c1() << std::endl;

  using lt0 = fmp::less_than<fmp::type_size<char>, fmp::type_size<int>>;
}
#endif

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

void test_lt() {
  using int0 = fmp::val<int, 0>;
  using int1 = fmp::val<int, 1>;
  using op = fmp::lt<int0, int1>;
  using op_i = fmp::lt<fmp::type_size<fmp::infinity_lower>, fmp::type_size<char>>;
  using op_i0 = fmp::lt<fmp::type_size<fmp::infinity_lower>, fmp::type_size<fmp::infinity_lower>>;
  using op_i1= fmp::lt<fmp::type_size<long>, fmp::type_size<fmp::infinity_lower>>;
  using op_i2= fmp::lt<fmp::type_size<fmp::infinity_lower>, fmp::type_size<fmp::infinity_upper>>;
  std::cout << "LT: 0 < 1: " << demangle<op::type>() << std::endl;
  std::cout << "LT: 0 < 0: " << demangle<fmp::lt<int0, int0>::type>() << std::endl;
  std::cout << "LT: 1 < 0: " << demangle<fmp::lt<int1, int0>::type>() << std::endl;
  std::cout << "op_i: " << demangle<op_i::type>() << std::endl;
  std::cout << "op_i0: " << demangle<op_i0::type>() << std::endl;
  std::cout << "op_i1: " << demangle<op_i1::type>() << std::endl;
  std::cout << "op_i2: " << demangle<op_i2::type>() << std::endl;
}

void test_eq() {
  using int0 = fmp::val<int, 0>;
  using int1 = fmp::val<int, 1>;
  using op = fmp::eq<int0, int1>;
  std::cout << "EQ: 0 op 1: " << demangle<op::type>() << std::endl;
  std::cout << "EQ: 0 op 0: " << demangle<fmp::eq<int0, int0>::type>() << std::endl;
  std::cout << "EQ: 1 op 0: " << demangle<fmp::eq<int1, int0>::type>() << std::endl;
}

void test_gt() {
  using int0 = fmp::val<int, 0>;
  using int1 = fmp::val<int, 1>;
  using op = fmp::gt<int0, int1>;
  using op_i = fmp::gt<fmp::type_size<fmp::infinity_lower>, fmp::type_size<char>>;
  using op_i0 = fmp::gt<fmp::type_size<fmp::infinity_lower>, fmp::type_size<fmp::infinity_lower>>;
  using op_i1= fmp::gt<fmp::type_size<long>, fmp::type_size<fmp::infinity_lower>>;

  std::cout << "GT: 0 op 1: " << demangle<op::type>() << std::endl;
  std::cout << "GT: 0 op 0: " << demangle<fmp::gt<int0, int0>::type>() << std::endl;
  std::cout << "GT: 1 op 0: " << demangle<fmp::gt<int1, int0>::type>() << std::endl;
  std::cout << "op_i: " << demangle<op_i::type>() << std::endl;
  std::cout << "op_i0: " << demangle<op_i0::type>() << std::endl;
  std::cout << "op_i1: " << demangle<op_i1::type>() << std::endl;
}

void test_compare() {
  using int0 = fmp::val<int, 0>;
  using int1 = fmp::val<int, 1>;
  using op = fmp::compare<int0, int1>;

  std::cout << "CMP: 0 op 1: " << demangle<op::type>() << std::endl;
  std::cout << "CMP: 0 op 0: " << demangle<fmp::compare<int0, int0>::type>() << std::endl;
  std::cout << "CMP: 1 op 0: " << demangle<fmp::compare<int1, int0>::type>() << std::endl;
}


void test_max() {
  using int0 = fmp::val<int, 0>;
  using maxop = fmp::max<fmp::type_size>;
  using max0 = maxop::op<char, int>;
  using max1 = maxop::op<int0, int0>;
  using max2 = maxop::op<char>;
  std::cout << "max0: " << demangle<max0::type>() << std::endl;
  std::cout << "max1: " << demangle<max1::type>() << std::endl;
  std::cout << "max2: " << demangle<max2::type>() << std::endl;
}

void test_min() {
  using int0 = fmp::val<int, 0>;
  using minop = fmp::min<fmp::type_size>;
  using min0 = minop::op<char, int>;
  using min1 = minop::op<int0, int0>;
  using min2 = minop::op<char>;
  using gt0 = fmp::gt<fmp::type_size<char>, fmp::type_size<fmp::infinity_upper>>;
  std::cout << "gt0: " << demangle<gt0::type>() << std::endl;
  std::cout << "min0: " << demangle<min0::type>() << std::endl;
  std::cout << "min1: " << demangle<min1::type>() << std::endl;
  std::cout << "min2: " << demangle<min2::type>() << std::endl;
}

int main(int , char**)
{
  std::cout << std::boolalpha;
  //test_value();
  //test_derived();
  //test_quote();
  //test_order();
  //test_monoid();
  //test_curry();
  test_monoid_et();
  //test_monoid_uel();
  test_lt();
  test_eq();
  test_gt();
  test_compare();
  test_max();
  test_min();

  return 0;
}
