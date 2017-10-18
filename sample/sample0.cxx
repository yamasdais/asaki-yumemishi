//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

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

void test_unity() {
  using namespace fmp;
  using et0 = fmp::et;
  //using e0 = unity<int>; // ::type instantiation causes assertion error

  std::cout << "---Unity---" << std::endl;
  std::cout << "unity::type:" << demangle<unity<et0>::type>() << std::endl;
  std::cout << "unity_t:" << demangle<unity_t<et0>>() << std::endl;
};

void test_unite() {
  using namespace fmp;
  using et0 = fmp::et;

  std::cout << "---Unite---" << std::endl;
  std::cout << "has_unite:" << has_unite<et0>::value << std::endl;
  std::cout << "unite<true, false>: "
            << demangle<unite_t<et0, std::true_type, std::false_type>>()
            << std::endl;
}

void test_monoid_et() {
  using et0 = fmp::et;

  std::cout << "MONOID et---" << std::endl;
  std::cout << "Unity: " << demangle<et0::unity>() << std::endl;
  std::cout << "et<true, false>:" << demangle<et0::unite_t<std::true_type, std::false_type>>() << std::endl;
  std::cout << "et<false, false>:" << demangle<et0::unite_t<std::false_type, std::false_type>>() << std::endl;
  std::cout << "et<false, true>:" << demangle<et0::unite_t<std::false_type, std::true_type>>() << std::endl;
  std::cout << "et<true, true>:" << demangle<et0::unite_t<std::true_type, std::true_type>>() << std::endl;
//  std::cout << "et<true>:" << demangle<et0::unite_t<std::true_type>>() << std::endl;
//  std::cout << "et<false>:" << demangle<et0::unite_t<std::false_type>>() << std::endl;
}

void test_monoid_uel() {
  using op0 = fmp::uel;

  std::cout << "MONOID uel---" << std::endl;
  std::cout << "Unity: " << demangle<op0::unity>() << std::endl;
  std::cout << "uel<true, false>:" << demangle<op0::unite_t<std::true_type, std::false_type>>() << std::endl;
  std::cout << "uel<false, false>:" << demangle<op0::unite_t<std::false_type, std::false_type>>() << std::endl;
  std::cout << "uel<false, true>:" << demangle<op0::unite_t<std::false_type, std::true_type>>() << std::endl;
  std::cout << "uel<true, true>:" << demangle<op0::unite_t<std::true_type, std::true_type>>() << std::endl;
//  std::cout << "uel<true>:" << demangle<op0::unite_t<std::true_type>>() << std::endl;
//  std::cout << "uel<false>:" << demangle<op0::unite_t<std::false_type>>() << std::endl;
}

template <typename... A>
struct noarg;

template <>
struct noarg<> {
  constexpr static int value = 43;
  using type = std::true_type;
};

void test_curry() {
  using fmp::curry;
  using c0 = curry<std::is_same, int>;
  using c1 = c0::apply<int>;
  using c1t = c0::apply_t<int>;
  using c2 = c0::currying<long>;

  using n0 = curry<noarg>;

  std::cout << "c0 curried params:" << c0::value << std::endl;
  std::cout << "c1:" << demangle<c1t>() << std::endl;
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
  using max0 = maxop::unite_t<char, int>;
  using max1 = maxop::unite_t<int0, int0>;
//  using max2 = maxop::unite_t<char>;
  std::cout << "max0: " << demangle<max0::type>() << std::endl;
  std::cout << "max1: " << demangle<max1::type>() << std::endl;
//  std::cout << "max2: " << demangle<max2::type>() << std::endl;
}

void test_min() {
  using int0 = fmp::val<int, 0>;
  using minop = fmp::min<fmp::type_size>;
  using min0 = minop::unite_t<char, int>;
  using min1 = minop::unite_t<int0, int0>;
//  using min2 = minop::unite_t<char>;
  using gt0 = fmp::gt<fmp::type_size<char>, fmp::type_size<fmp::infinity_upper>>;
  std::cout << "gt0: " << demangle<gt0::type>() << std::endl;
  std::cout << "min0: " << demangle<min0::type>() << std::endl;
  std::cout << "min1: " << demangle<min1::type>() << std::endl;
//  std::cout << "min2: " << demangle<min2::type>() << std::endl;
}

void test_foldl() {
  using namespace fmp;
  using fold0 = foldl<cons, nil_type, int, long long>;

  std::cout << "foldl0:" << demangle<fold0::type>() << std::endl;
}

void test_foldr() {
  using namespace fmp;
  using fold0 = foldr<cons, nil_type, int, long long>;

  std::cout << "foldr0:" << demangle<fold0::type>() << std::endl;
}


void apply_sample() {
  using namespace fmp;
  using c0 = curry<std::is_same>;
  using a0 = apply<c0, int>::type;
  using a1 = apply_t<a0, char>;

  using t0 = has_apply<a1>;
  using e0 = apply<a1>; // cause assertion error if instantiate

  std::cout << "a0:" << demangle<a0>() << std::endl;
  std::cout << "a1:" << demangle<a1>() << std::endl;
  std::cout << "t0:" << demangle<t0>() << std::endl;
}

void compose_sample() {
  using namespace fmp;
  using f0 = curry<negate>;
  using g0 = curry<std::is_same>;

  using c0 = compose<f0, g0>;
  using r0 = c0::apply_t<int>;
  using r1 = apply_t<r0, int>;

  std::cout << "compose r0:" << demangle<r0>() << std::endl;
  std::cout << "compose r1:" << demangle<r1>() << std::endl;
}

void test_valtype() {
  using namespace fmp;
  using vt0 = valtype<int>;
  using v0 = valtype<int>::template let<0>;
  using v1 = vt0::let<1>;
  using v2 = vt0::let<2>;

  std::cout << "--valtype--" << std::endl;
  std::cout << "v0: " << demangle<v0>() << std::endl;
  std::cout << "v1: " << demangle<v1>() << std::endl;
  std::cout << "v2: " << demangle<v2>() << std::endl;
}

int main(int , char**)
{
  std::cout << std::boolalpha;
  //test_value();
  //test_derived();
  //test_quote();
  //test_order();
  //test_monoid();
  test_curry();
  //test_monoid_et();
  //test_monoid_uel();
  //test_lt();
  //test_eq();
  //test_gt();
  //test_compare();
  //test_max();
  //test_min();
  test_foldl();
  test_foldr();
  apply_sample();
  compose_sample();
  test_valtype();
  test_unity();
  test_unite();

  return 0;
}
