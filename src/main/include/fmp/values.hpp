//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_920AB251_2A86_41EA_84BF_55360C70A3C2)
#define FMP_920AB251_2A86_41EA_84BF_55360C70A3C2


namespace fmp {

template <typename T, T V>
struct val : public std::integral_constant<T, V> {
  using type = val<T, V>;
  using value_type = T;

  template <typename CastTo>
  using cast = val<CastTo, static_cast<CastTo>(V)>;
};

template <typename T>
struct valtype {
  template <T V>
  using let = val<T, V>;
};

#if defined(__cpp_template_auto)
template <auto V>
using atval = val<decltype(V), V>;

#endif /* __cpp_template_auto */


template <typename V0, typename V1>
struct add {
  using type = val<decltype(V0::value + V1::value), V0::value + V1::value>;
};

template <typename V0, typename V1>
using add_t = typename add<V0, V1>::type;

template <typename V0, typename V1>
struct sub {
  using type = val<decltype(V0::value - V1::value), V0::value - V1::value>;
};

template <typename V0, typename V1>
using sub_t = typename sub<V0, V1>::type;

template <typename V0, typename V1>
struct mul {
  using type = val<decltype(V0::value * V1::value), V0::value * V1::value>;
};

template <typename V0, typename V1>
using mul_t = typename mul<V0, V1>::type;

template <typename V0, typename V1>
struct div {
  using type = val<decltype(V0::value / V1::value), V0::value / V1::value>;
};

template <typename V0, typename V1>
using div_t = typename div<V0, V1>::type;

template <typename V0, typename V1>
struct mod {
  using type = val<decltype(V0::value % V1::value), V0::value % V1::value>;
};

template <typename V0, typename V1>
using mod_t = typename mod<V0, V1>::type;

} /* ns: fmp */

#endif /* if not defined 'FMP_920AB251_2A86_41EA_84BF_55360C70A3C2' */
