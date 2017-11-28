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
#include <fmp/monoid.hpp>
#include <fmp/foldmap.hpp>
#include <fmp/values.hpp>
#include <fmp/utils.hpp>

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
#if 0
  using et0 = fmp::all;
  //using e0 = unity<int>; // ::type instantiation causes assertion error

  std::cout << "---Unity---" << std::endl;
  std::cout << "unity::type:" << demangle<unity<et0>::type>() << std::endl;
  std::cout << "unity_t:" << demangle<unity_t<et0>>() << std::endl;
#endif
};

void test_unite() {
  using namespace fmp;
  using et0 = fmp::all<std::true_type>;
  //using et1 = fmp::et<int>::type;

  std::cout << "---Unite---" << std::endl;
#if 0
  std::cout << "has_unite:" << has_unite<et0>::value << std::endl;
  std::cout << "unite<true, false>: "
            << demangle<unite_t<et0, std::true_type, std::false_type>>()
            << std::endl;
#endif
}

void test_monoid_et() {
  using et0 = fmp::all<std::true_type>;
  using ett0 = fmp::monoid_trait<fmp::all>;
  using et_u = fmp::unity_t<fmp::all>;
  using et_unite = fmp::unite_t<et0, et_u>;
  std::cout << "MONOID et---" << std::endl;
  std::cout << "et<true_type>=" << demangle<et0>() << std::endl;
  std::cout << "monoid_trait<et>=" << demangle<ett0>() << std::endl;
  std::cout << "monoid_trait<et>::unity=" << demangle<et_u>() << std::endl;
  std::cout << "unite<et0, unite>=" << demangle<et_unite>() << std::endl;
#if 0
  std::cout << "Unity: " << demangle<et0::unity>() << std::endl;
  std::cout << "et<true, false>:" << demangle<et0::unite_t<std::true_type, std::false_type>>() << std::endl;
  std::cout << "et<false, false>:" << demangle<et0::unite_t<std::false_type, std::false_type>>() << std::endl;
  std::cout << "et<false, true>:" << demangle<et0::unite_t<std::false_type, std::true_type>>() << std::endl;
  std::cout << "et<true, true>:" << demangle<et0::unite_t<std::true_type, std::true_type>>() << std::endl;
//  std::cout << "et<true>:" << demangle<et0::unite_t<std::true_type>>() << std::endl;
//  std::cout << "et<false>:" << demangle<et0::unite_t<std::false_type>>() << std::endl;
#endif
}

void test_monoid_uel() {
#if 0
  using op0 = fmp::uel;
  std::cout << "MONOID uel---" << std::endl;
  std::cout << "Unity: " << demangle<op0::unity>() << std::endl;
  std::cout << "uel<true, false>:" << demangle<op0::unite_t<std::true_type, std::false_type>>() << std::endl;
  std::cout << "uel<false, false>:" << demangle<op0::unite_t<std::false_type, std::false_type>>() << std::endl;
  std::cout << "uel<false, true>:" << demangle<op0::unite_t<std::false_type, std::true_type>>() << std::endl;
  std::cout << "uel<true, true>:" << demangle<op0::unite_t<std::true_type, std::true_type>>() << std::endl;
//  std::cout << "uel<true>:" << demangle<op0::unite_t<std::true_type>>() << std::endl;
//  std::cout << "uel<false>:" << demangle<op0::unite_t<std::false_type>>() << std::endl;
#endif
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
#if 0
  using int0 = fmp::val<int, 0>;
  using maxop = fmp::max<fmp::type_size>;
  using max0 = maxop::unite_t<char, int>;
  using max1 = maxop::unite_t<int0, int0>;
//  using max2 = maxop::unite_t<char>;
  std::cout << "max0: " << demangle<max0::type>() << std::endl;
  std::cout << "max1: " << demangle<max1::type>() << std::endl;
//  std::cout << "max2: " << demangle<max2::type>() << std::endl;
#endif
}

void test_min() {
  using int0 = fmp::val<int, 0>;
#if 0
  using minop = fmp::min<fmp::type_size>;
  using min0 = minop::unite_t<char, int>;
  using min1 = minop::unite_t<int0, int0>;
//  using min2 = minop::unite_t<char>;
  using gt0 = fmp::gt<fmp::type_size<char>, fmp::type_size<fmp::infinity_upper>>;
  std::cout << "gt0: " << demangle<gt0::type>() << std::endl;
  std::cout << "min0: " << demangle<min0::type>() << std::endl;
  std::cout << "min1: " << demangle<min1::type>() << std::endl;
//  std::cout << "min2: " << demangle<min2::type>() << std::endl;
#endif
}

void test_foldl() {
  using namespace fmp;
//  using fold0 = foldl<cons, nil_type, int, long long>;

//  std::cout << "foldl0:" << demangle<fold0::type>() << std::endl;
}

void test_foldr() {
  using namespace fmp;
  using f0 = foldr_t<curry<cons>, nil_type, sequence<int, long>>;
//  using fold0 = foldr<cons, nil_type, int, long long>;

  std::cout << "fold(f0): " << demangle<f0>() << std::endl;
}

void test_cons() {
  using namespace fmp;

  using c0 = unity_t<cons>;
  using c1 = cons<int, nil_type>;
  using ac0 = curry<cons, int>;
  using c1_0 = apply_t<ac0, empty<cons>::type>;
  //using c2_0 = detail::monoid_unite_impl<cons>::template apply<cons<char, double>, c1>;
  using c2 = unite_t<c1, cons<char, cons<float, nil_type> > >;
  using car_0t = car_t<c1>;

  std::cout << "unity<cons>: " << demangle<c0>() << std::endl;
  std::cout << "cons<c1>: " << demangle<c1::type>() << std::endl;
  std::cout << "cons<c1>==cons?: " << is_cons_v<c0> << std::endl;
  std::cout << "cons<c1_0>: " << demangle<c1_0::type>() << std::endl;
  std::cout << "cons<c2>: " << demangle<c2>() << std::endl;
  std::cout << "car<c1>:=" << demangle<car<c1>>() << std::endl;
  std::cout << "car_t<c1>:=" << demangle<car_t<c1>>() << std::endl;
};

void test_list() {
  using l0 = fmp::list_t<char, int, float, double>;

  std::cout << "list<>: " << demangle<l0>() << std::endl;
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
  using f0 = curry<car>;
  using g0 = curry<cons>;

  using c0 = compose<f0, g0>;
  using r0 = apply_t<c0, int>;
  using r1 = apply_t<r0, int>;

  std::cout << "hasapply:" << demangle<f0::template apply<cons<int, char>>>()
            << std::endl;
  std::cout << "f0 apply:" << demangle<apply_t<f0, cons<int, char>> >() << std::endl;
  std::cout << "car<cons2<int, char>>: "
            << demangle<car_t<cons<int, char>>>()<< std::endl;
  std::cout << "compose r0:" << demangle<r0>() << std::endl;
  std::cout << "compose r1:" << demangle<apply_t<f0, cons<int, int>>>() << std::endl;
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

void test_sequence() {
  using s0 = fmp::sequence<int, char>;
  using s1 = fmp::sequence<float, double>;
  using su = fmp::unity_t<fmp::sequence>;
  using sunite = fmp::unite_t<s0, s1>;

  using r0 = fmp::append_t<s0, s1>;
  std::cout << "--sequence--" << std::endl;
  std::cout << "r0:" << demangle<r0>() << std::endl;
  std::cout << "unity<sequence>=" << demangle<su>() << std::endl;
  std::cout << "unite<s0, s1>=" << demangle<sunite>() << std::endl;
}

void test_is_operatable() {
  using namespace fmp;

  using ett = all<std::true_type>;
  using etf = all<std::false_type>;
  using can_op = is_monoid_t<all, ett, int>;
  using et_op = detail::monoid_unite_impl<all>::apply<ett, etf>;

  std::cout << "pred: " << demangle<can_op>() << std::endl;
  std::cout << "op: " << demangle<et_op>() << std::endl;
}

void test_flip() {
  using namespace fmp;

  std::cout << "flip: " << std::endl;
  using fl0 = curry<flip, curry<cons>>;
  using fl1 = flipf<cons, nil_type>;
  using snc0 = apply_t<fl0, nil_type, int>;

  using snc0 = apply_t<fl0, nil_type, int>;
  using snc1 = apply_t<fl1, int>;

  std::cout << "fl0: " << demangle<fl0>() << std::endl;
  std::cout << "snc0: " << demangle<snc0>()<< std::endl;
  std::cout << "snc1: " << demangle<snc1>() << std::endl;
}

void test_curried() {
  using namespace fmp;

  std::cout << "CURRIED-----" << std::endl;
  using c0 = curry<id, int>;
  using r0 = is_curried<c0>;

  std::cout << "fl0: " << demangle<r0::type>() << std::endl;
  std::cout << "is_curried_v<c0>: " << is_curried_v<c0> << std::endl;
  std::cout << "is_curried_v<int>: " << is_curried_v<int> << std::endl;
  std::cout << "is_curried_v<cons<int,nil>>: " << is_curried_v<cons<int,nil_type>> << std::endl;
}

void test_endo() {
  using namespace fmp;

  std::cout << "ENDO-----" << std::endl;
  using e0 = endo<curry<all>>;
  using ue0 = unite_t<endo<curry<negate>>, e0>;
  using re0 = apply_t<ue0, std::true_type>;

  std::cout << "unity<endo>:" << demangle<unity_t<endo>>() << std::endl;
  std::cout << "endo:" << demangle<e0>() << std::endl;
  std::cout << "apply:" << demangle<apply_t<e0, std::true_type>>() << std::endl;
  std::cout << "unite:" << demangle<ue0>() << std::endl;
  std::cout << "apply compose:" << demangle<re0>() << std::endl;
}

void test_getmf() {
  using namespace fmp;

  using c0 = cons<int, char>;
  using r0 = get_mf<int>::type;
  using r1 = get_mf<c0>::template type<float, double>;

  std::cout << "-- GetMF-- " << std::endl;
  std::cout << "r0(int): " << demangle<r0>() << std::endl;
  std::cout << "r1(cons): " << demangle<r1>() << std::endl;
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
  test_monoid_et();
  //test_monoid_uel();
  //test_lt();
  //test_eq();
  //test_gt();
  //test_compare();
  //test_max();
  //test_min();
  //test_foldl();
  //apply_sample();
  compose_sample();
  test_valtype();
  test_unity();
  test_unite();

  //test_is_operatable();
  //test_sequence();
  test_cons();
  //test_flip();
  //test_curried();
  test_endo();
  test_getmf();
  test_foldr();
  test_list();

  return 0;
}
