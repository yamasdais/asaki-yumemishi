//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <limits>

#include <boost/type_index.hpp>

#include <fmp.hpp>
#include <fmp/incubation.hpp>
#include <fmp/operator.hpp>
#include <fmp/monoid.hpp>
#include <fmp/foldmap.hpp>
#include <fmp/values.hpp>
#include <fmp/utils.hpp>
#include <fmp/maybe.hpp>
#include <fmp/functor.hpp>

#include "sample.hpp"

void test_quote() {
  using q0 = fmp::quote<int>;
  std::cout << "Quote::type: " << T_name<q0::type>() << std::endl;
  std::cout << "Unquote: " << T_name<q0::unquote>() << std::endl;
}

void test_derived() {
  using q0 = fmp::quote<int>;
  using d0 = fmp::derived<q0>;

  std::cout << "derived: " << T_name<d0::type>() << std::endl;
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


#if defined(__cpp_template_auto)
  using at1 = atval<0u>;
  using at0 = atval<0>;
  std::cout << "at1: " << T_name<at1>() << std::endl;
  std::cout << "at0: " << T_name<at0>() << std::endl;
#endif /* __cpp_template_auto */

}

void test_unity() {
  using namespace fmp;
#if 0
  using et0 = fmp::all;
  //using e0 = unity<int>; // ::type instantiation causes assertion error

  std::cout << "---Unity---" << std::endl;
  std::cout << "unity::type:" << T_name<unity<et0>::type>() << std::endl;
  std::cout << "unity_t:" << T_name<unity_t<et0>>() << std::endl;
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
            << T_name<unite_t<et0, std::true_type, std::false_type>>()
            << std::endl;
#endif
}

void test_monoid_et() {
  using et0 = fmp::all<std::true_type>;
  using ett0 = fmp::monoid_trait<fmp::all>;
  using et_u = fmp::unity_t<fmp::all>;
  using et_unite = fmp::unite_t<et0, et_u>;
  std::cout << "MONOID et---" << std::endl;
  std::cout << "et<true_type>=" << T_name<et0>() << std::endl;
  std::cout << "monoid_trait<et>=" << T_name<ett0>() << std::endl;
  std::cout << "monoid_trait<et>::unity=" << T_name<et_u>() << std::endl;
  std::cout << "unite<et0, unite>=" << T_name<et_unite>() << std::endl;
#if 0
  std::cout << "Unity: " << T_name<et0::unity>() << std::endl;
  std::cout << "et<true, false>:" << T_name<et0::unite_t<std::true_type, std::false_type>>() << std::endl;
  std::cout << "et<false, false>:" << T_name<et0::unite_t<std::false_type, std::false_type>>() << std::endl;
  std::cout << "et<false, true>:" << T_name<et0::unite_t<std::false_type, std::true_type>>() << std::endl;
  std::cout << "et<true, true>:" << T_name<et0::unite_t<std::true_type, std::true_type>>() << std::endl;
//  std::cout << "et<true>:" << T_name<et0::unite_t<std::true_type>>() << std::endl;
//  std::cout << "et<false>:" << T_name<et0::unite_t<std::false_type>>() << std::endl;
#endif
}

void test_monoid_uel() {
#if 0
  using op0 = fmp::uel;
  std::cout << "MONOID uel---" << std::endl;
  std::cout << "Unity: " << T_name<op0::unity>() << std::endl;
  std::cout << "uel<true, false>:" << T_name<op0::unite_t<std::true_type, std::false_type>>() << std::endl;
  std::cout << "uel<false, false>:" << T_name<op0::unite_t<std::false_type, std::false_type>>() << std::endl;
  std::cout << "uel<false, true>:" << T_name<op0::unite_t<std::false_type, std::true_type>>() << std::endl;
  std::cout << "uel<true, true>:" << T_name<op0::unite_t<std::true_type, std::true_type>>() << std::endl;
//  std::cout << "uel<true>:" << T_name<op0::unite_t<std::true_type>>() << std::endl;
//  std::cout << "uel<false>:" << T_name<op0::unite_t<std::false_type>>() << std::endl;
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
  std::cout << "c1:" << T_name<c1t>() << std::endl;
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
  std::cout << "LT: 0 < 1: " << T_name<op::type>() << std::endl;
  std::cout << "LT: 0 < 0: " << T_name<fmp::lt<int0, int0>::type>() << std::endl;
  std::cout << "LT: 1 < 0: " << T_name<fmp::lt<int1, int0>::type>() << std::endl;
  std::cout << "op_i: " << T_name<op_i::type>() << std::endl;
  std::cout << "op_i0: " << T_name<op_i0::type>() << std::endl;
  std::cout << "op_i1: " << T_name<op_i1::type>() << std::endl;
  std::cout << "op_i2: " << T_name<op_i2::type>() << std::endl;
}

void test_eq() {
  using int0 = fmp::val<int, 0>;
  using int1 = fmp::val<int, 1>;
  using op = fmp::eq<int0, int1>;
  using namespace fmp;
  std::cout << "EQ: 0 op 1: " << T_name<op::type>() << std::endl;
  std::cout << "EQ: 0 op 0: " << T_name<fmp::eq<int0, int0>>() << std::endl;
  std::cout << "EQ: 1 op 0: " << T_name<fmp::eq<int1, int0>::type>() << std::endl;
  std::cout << "gte: " << T_name<neg<gte<val<int, 0>, val<int, 0>>::type>>() << std::endl;
}

void test_gt() {
  using int0 = fmp::val<int, 0>;
  using int1 = fmp::val<int, 1>;
  using op = fmp::gt<int0, int1>;
  using op_i = fmp::gt<fmp::type_size<fmp::infinity_lower>, fmp::type_size<char>>;
  using op_i0 = fmp::gt<fmp::type_size<fmp::infinity_lower>, fmp::type_size<fmp::infinity_lower>>;
  using op_i1= fmp::gt<fmp::type_size<long>, fmp::type_size<fmp::infinity_lower>>;

  std::cout << "GT: 0 op 1: " << T_name<op::type>() << std::endl;
  std::cout << "GT: 0 op 0: " << T_name<fmp::gt<int0, int0>::type>() << std::endl;
  std::cout << "GT: 1 op 0: " << T_name<fmp::gt<int1, int0>::type>() << std::endl;
  std::cout << "op_i: " << T_name<op_i::type>() << std::endl;
  std::cout << "op_i0: " << T_name<op_i0::type>() << std::endl;
  std::cout << "op_i1: " << T_name<op_i1::type>() << std::endl;
}

void test_compare() {
  using int0 = fmp::val<int, 0>;
  using int1 = fmp::val<int, 1>;
  using op = fmp::compare<int0, int1>;

  std::cout << "CMP: 0 op 1: " << T_name<op::type>() << std::endl;
  std::cout << "CMP: 0 op 0: " << T_name<fmp::compare<int0, int0>::type>() << std::endl;
  std::cout << "CMP: 1 op 0: " << T_name<fmp::compare<int1, int0>::type>() << std::endl;
}


void test_max() {
#if 0
  using int0 = fmp::val<int, 0>;
  using maxop = fmp::max<fmp::type_size>;
  using max0 = maxop::unite_t<char, int>;
  using max1 = maxop::unite_t<int0, int0>;
//  using max2 = maxop::unite_t<char>;
  std::cout << "max0: " << T_name<max0::type>() << std::endl;
  std::cout << "max1: " << T_name<max1::type>() << std::endl;
//  std::cout << "max2: " << T_name<max2::type>() << std::endl;
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
  std::cout << "gt0: " << T_name<gt0::type>() << std::endl;
  std::cout << "min0: " << T_name<min0::type>() << std::endl;
  std::cout << "min1: " << T_name<min1::type>() << std::endl;
//  std::cout << "min2: " << T_name<min2::type>() << std::endl;
#endif
}

void test_foldl() {
  using namespace fmp;
//  using fold0 = foldl<cons, nil_type, int, long long>;

//  std::cout << "foldl0:" << T_name<fold0::type>() << std::endl;
}

void test_foldr() {
  using namespace fmp;
  using f0 = foldr_t<curry<cons>, nil_type, sequence<int, long>>;
//  using fold0 = foldr<cons, nil_type, int, long long>;

  std::cout << "fold(f0): " << T_name<f0>() << std::endl;
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

  std::cout << "unity<cons>: " << T_name<c0>() << std::endl;
  std::cout << "cons<c1>: " << T_name<c1::type>() << std::endl;
  std::cout << "cons<c1>==cons?: " << is_cons_v<c0> << std::endl;
  std::cout << "cons<c1_0>: " << T_name<c1_0::type>() << std::endl;
  std::cout << "cons<c2>: " << T_name<c2>() << std::endl;
  std::cout << "car<c1>:=" << T_name<car<c1>>() << std::endl;
  std::cout << "car_t<c1>:=" << T_name<car_t<c1>>() << std::endl;
};

void test_list() {
  using l0 = fmp::list_t<char, int, float, double>;

  std::cout << "list<>: " << T_name<l0>() << std::endl;
}

void apply_sample() {
  using namespace fmp;
  using c0 = curry<std::is_same>;
  using a0 = apply<c0, int>::type;
  using a1 = apply_t<a0, char>;

  using t0 = has_apply<a1>;
  using e0 = apply<a1>; // cause assertion error if instantiate

  std::cout << "a0:" << T_name<a0>() << std::endl;
  std::cout << "a1:" << T_name<a1>() << std::endl;
  std::cout << "t0:" << T_name<t0>() << std::endl;
}

void compose_sample() {
  using namespace fmp;
  using f0 = curry<car>;
  using g0 = curry<cons>;
  using f1 = curry<std::add_const>;
  using f2 = curry<id>;

  using c0 = compose<f0, g0>;
  using r0 = apply_t<c0, int>;
  using r1 = apply_t<r0, int>;
  using c2 = compose<curry<id>, f0, g0>;
  using r2 = apply_t<c2, int, char>;

  //using ac0 = typename compose<f2, f1>::template apply<int>::type;
  //using ac0 = typename detail::compose_apply_impl<f2, apply_t<f1, int>>::type;
  using ac0 = apply_t<compose<f2, f1>, int>;

  std::cout << "hasapply:" << T_name<f0::template apply<cons<int, char>>>()
            << std::endl;
  std::cout << "f0 apply:" << T_name<apply_t<f0, cons<int, char>> >() << std::endl;
  std::cout << "car<cons2<int, char>>: "
            << T_name<car_t<cons<int, char>>>()<< std::endl;
  std::cout << "compose r0:" << T_name<apply_t<r0, nil_type>>() << std::endl;
  std::cout << "compose r1:" << T_name<apply_t<f0, cons<int, int>>>() << std::endl;
  std::cout << "compose c2:" << T_name<c2>() << std::endl;
  std::cout << "compose r2:" << T_name<r2>() << std::endl;
  std::cout << "compose ac0:" << T_name<ac0>() << std::endl;
  std::cout << "compose c0:" << T_name<r1>() << std::endl;
}

void test_valtype() {
  using namespace fmp;
  using vt0 = valtype<int>;
  using v0 = valtype<int>::template let<0>;
  using v1 = vt0::let<1>;
  using v2 = vt0::let<2>;

  std::cout << "--valtype--" << std::endl;
  std::cout << "v0: " << T_name<v0>() << std::endl;
  std::cout << "v1: " << T_name<v1>() << std::endl;
  std::cout << "v2: " << T_name<v2>() << std::endl;
}

void test_sequence() {
  using s0 = fmp::sequence<int, char>;
  using s1 = fmp::sequence<float, double>;
  using su = fmp::unity_t<fmp::sequence>;
  using sunite = fmp::unite_t<s0, s1>;

  using r0 = fmp::append_t<s0, s1>;
  std::cout << "--sequence--" << std::endl;
  std::cout << "r0:" << T_name<r0>() << std::endl;
  std::cout << "head<r0>: " << T_name<fmp::head_t<r0>>() << std::endl;
  std::cout << "unity<sequence>=" << T_name<su>() << std::endl;
  std::cout << "unite<s0, s1>=" << T_name<sunite>() << std::endl;
}

void test_flip() {
  using namespace fmp;

  std::cout << "flip: " << std::endl;
  using fl0 = curry<flip, curry<cons>>;
  using fl1 = flipf<cons, nil_type>;
  using snc0 = apply_t<fl0, nil_type, int>;

  using snc0 = apply_t<fl0, nil_type, int>;
  using snc1 = apply_t<fl1, int>;

  std::cout << "fl0: " << T_name<fl0>() << std::endl;
  std::cout << "snc0: " << T_name<snc0>()<< std::endl;
  std::cout << "snc1: " << T_name<snc1>() << std::endl;
}

void test_curried() {
  using namespace fmp;

  std::cout << "CURRIED-----" << std::endl;
  using c0 = curry<id, int>;
  using r0 = is_curried<c0>;

  std::cout << "fl0: " << T_name<r0::type>() << std::endl;
  std::cout << "is_curried_v<c0>: " << is_curried_v<c0> << std::endl;
  std::cout << "is_curried_v<int>: " << is_curried_v<int> << std::endl;
  std::cout << "is_curried_v<cons<int,nil>>: " << is_curried_v<cons<int,nil_type>> << std::endl;
}

void test_endo() {
  using namespace fmp;

  std::cout << "ENDO-----" << std::endl;
  using e0 = endo<curry<all>>;
  using ue0 = unite_t<endo<curry<get>>, e0>;

  std::cout << "unity<endo>:" << T_name<unity_t<endo>>() << std::endl;
  std::cout << "endo:" << T_name<e0>() << std::endl;
  std::cout << "apply:" << T_name<apply_t<e0, std::true_type>>() << std::endl;
  std::cout << "unite:" << T_name<apply_t<ue0, std::true_type>>() << std::endl;
}

void test_getmf() {
  using namespace fmp;

  using c0 = cons<int, char>;
  using r0 = get_mf<int>::type;
  using r1 = get_mf<c0>::template type<float, double>;

  std::cout << "-- GetMF-- " << std::endl;
  std::cout << "r0(int): " << T_name<r0>() << std::endl;
  std::cout << "r1(cons): " << T_name<r1>() << std::endl;
}

void test_mconcat() {
  using namespace fmp;

  std::cout << "## test_mconcat() ##" << std::endl;
  using e0 = compose<curry<id>, curry<unite>>;
  using u0 = unite_t<all<std::true_type>, all<std::false_type>>;
  using r0 = apply_t<e0, all<std::true_type>, all<std::false_type>>;
  using sq = sequence<all<std::true_type>, all<std::true_type>>;
  using f0 = foldr_t<e0, unity_t<all>, sq>;

  using mc0 = mconcat_t<all, sq>;
  using cc = curry<foldr, curry<unite>, unity_t<all>>;
  using mdet = monoid_trait<all>::concat;

  std::cout << "u0:" << T_name<u0::get>() << std::endl;
  std::cout << "e0:" << T_name<r0>() << std::endl;
  std::cout << "fold(f0): " << T_name<f0::get>() << std::endl;
  std::cout << "cc: " << T_name<cc>() << std::endl;
  std::cout << "mdet: " << T_name<apply<mdet, sq>::type>() << std::endl;
  std::cout << "mconcat: " << T_name<mc0>() << std::endl;
}

void test_map() {
  using namespace fmp;

  std::cout << "## test_map() ##" << std::endl;
  using c0 = list_t<int, char, double>;
  using s0 = sequence<int, char, double>;
  using p0 = curry<std::is_same, int>;
  using cr0 = map<p0, c0>;
  using sr0 = map<p0, s0>;

  std::cout << "c0: " << T_name<c0>() << std::endl;
  std::cout << "cr0: " << T_name<cr0::type>() << std::endl;
  std::cout << "sr0: " << T_name<sr0::type>() << std::endl;
}

void test_maybe() {
  using namespace fmp;

  std::cout << "## test_maybe() ##" << std::endl;

  using j0 = just_t<all<std::true_type>>;
  using j1 = just_t<all<std::false_type>>;
  using n0 = nothing_t;

  using p0 = is_just_t<n0>;
  using p1 = is_nothing_t<j0>;

  using fj0 = from_just_t<j0>;
  using fm0 = from_maybe_t<j0, std::nullptr_t>;
  using fm1 = from_maybe_t<n0, std::nullptr_t>;
  using unit0 = unity_t<maybe>;
  using um0 = unite_t<j1, j1>;
  using cp0 = compose<curry<just>, curry<all>>;
  using amp0 = map_t<cp0,
                     sequence<std::true_type, std::true_type, std::true_type>>;
  using mcc0 = mconcat_t<maybe, amp0>;

  std::cout << "j0: " << T_name<j0>() << std::endl;
  std::cout << "n0: " << T_name<n0>() << std::endl;
  
  std::cout << "is_just<T>: " << T_name<is_just_t<j0>>() << std::endl;
  std::cout << "is_nothing<T>: " << T_name<is_nothing_t<n0>>() << std::endl;

  std::cout << "from_just<T>: " << T_name<from_just_t<j0>>() << std::endl;
  std::cout << "from_maybe<T>: " << T_name<fm0>() << std::endl;
  std::cout << "from_maybe<nothing>: " << T_name<fm1>() << std::endl;
  std::cout << "unity<>: " << T_name<unit0>() << std::endl;
  std::cout << "unite<A,B>: " << T_name<get_t<um0>>() << std::endl;
  std::cout << "all map: "<< T_name<amp0>() << std::endl;
  std::cout << "mconcat<maybe, map<...>>: " << T_name<from_maybe_t<mcc0, nothing>>() << std::endl;

}

void test_fmap()
{
  using namespace fmp;
  std::cout << "## " << __func__ << "() ##" << std::endl;

  using c0 = list_t<int, char, double>;
  using p0 = curry<std::is_same, int>;
  using cr0 = fmap_t<p0, c0>;

  using mp0 = fmap_t<curry<std::add_const>, just_t<int>>;
  using mp1 = fmap_t<curry<std::add_const>, nothing_t>;
  
  std::cout << "cr0: " << T_name<cr0>() << std::endl;

  std::cout << "fmap<just>: "<< T_name<mp0>() << std::endl;
  std::cout << "fmap<nothing>: "<< T_name<mp1>() << std::endl;
}

void test_add()
{
  using namespace fmp;
  std::cout << "## " << __func__ << "() ##" << std::endl;

  using vt = valtype<int>;
  using v1 = vt::let<1>;
  using v10 = vt::let<10>;
  using r11 = add<v1, v10>;

  std::cout << "add: " << T_name<r11::type>() << std::endl;
}

void test_div()
{
  using namespace fmp;
  std::cout << "## " << __func__ << "() ##" << std::endl;

  using vt = valtype<int>;
  using v1 = vt::let<12>;
  using v2 = vt::let<6>;
  using r0 = fmp::div_t<v1, v2>;

  std::cout << "div: " << T_name<r0>() << std::endl;
}

int main(int , char**)
{
  std::cout << std::boolalpha;
  //test_derived();
  //test_quote();
  //test_order();
  //test_monoid();
  test_curry();
  test_monoid_et();
  //test_monoid_uel();
  //test_lt();
  //test_gt();
  //test_compare();
  //test_max();
  //test_min();
  //test_foldl();
  //apply_sample();
  test_valtype();
  test_unity();
  test_unite();

  test_cons();
  //test_flip();
  //test_curried();
  test_getmf();
  test_foldr();
  test_list();
  test_mconcat();
  test_map();
  test_sequence();
  compose_sample();
  test_endo();
  test_maybe();
  test_fmap();
  test_value();
  test_add();
  test_eq();

  return 0;
}
