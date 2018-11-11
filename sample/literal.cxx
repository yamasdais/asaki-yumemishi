#include <iostream>
#include <type_traits>
#include <boost/type_index.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/string.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/type.hpp>
#include <boost/hana/transform.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/value.hpp>
#include <boost/hana/plus.hpp>
#include <boost/hana/fwd/count.hpp>


namespace literaltst {

struct CharLiteralChooser {
  wchar_t wchar_literal;
  char utf8_literal;
  char16_t char16_literal;
  char32_t char32_literal;

  constexpr CharLiteralChooser(
    wchar_t wchar_literal,
    char utf8_literal,
    char16_t char16_literal,
    char32_t char32_literal
  ) : wchar_literal(wchar_literal),
      utf8_literal(utf8_literal),
      char16_literal(char16_literal),
      char32_literal(char32_literal)
  {
  }
  template <typename Ch>
  constexpr Ch get() const noexcept;
};

template <>
constexpr char CharLiteralChooser::get() const noexcept {
  return utf8_literal;
}
template <>
constexpr wchar_t CharLiteralChooser::get() const noexcept {
  return wchar_literal;
}

#define CNV_CHTYPE(CH, PREFIX) (PREFIX ## CH)
#define CONVERT_CH(TYPE, CH) \
  literaltst::CharLiteralChooser{                                          \
    CNV_CHTYPE(CH,u8), CNV_CHTYPE(CH,L), CNV_CHTYPE(CH,u), CNV_CHTYPE(CH,U)\
    }.get<TYPE>()

template <typename To>
constexpr To convert(char ch) noexcept {
  return static_cast<To>(ch);
}

template <typename To, typename Str>
struct store;

template <
  typename To,
  template <char...> typename F,
  char... Ch
  >
struct store<To, const F<Ch...>> {
  constexpr static To const buffer[sizeof...(Ch)+1] = {
    static_cast<To>(Ch)..., static_cast<To>('\0')
  };
};
template <
  typename To,
  template <char...> typename F,
  char... Ch
  >
struct store<To, F<Ch...>> {
  constexpr static To const buffer[sizeof...(Ch)+1] = {
    static_cast<To>(Ch)..., static_cast<To>('\0')
  };
};

template <typename To>
struct trans {
  constexpr static auto hana_type = boost::hana::type_c<To>;

};

template <typename ChT>
struct string_t {
  template <ChT... C>
  using tuple_type = boost::hana::tuple<boost::hana::integral_constant<ChT, C>...>;
};

namespace detail {

template <typename ChT, typename S, std::size_t... N>
constexpr literaltst::string_t<ChT>::tuple_type<S::get()[N]...>
prepare_impl(S, std::index_sequence<N...>) { return {}; }

template <typename ChT, typename S>
constexpr decltype(auto)
prepare(S s) {
  return prepare_impl<ChT>(
    s,
    std::make_index_sequence<sizeof(S::get())/sizeof(ChT) - 1>{});
}

template <typename S>
using element_type = std::remove_const_t<std::remove_reference_t<S>>;

}

#define LITERAL_METASTRING(s) \
  (::literaltst::detail::prepare<::literaltst::detail::element_type<decltype(*s)>>([]{ \
      struct tmp { \
        static constexpr decltype(auto) get() { return s; }    \
      }; \
      return tmp{};                             \
    }()));

}

void test0()
{
  using boost::typeindex::type_id_with_cvr;
  constexpr auto c0 = literaltst::string_t<char>::tuple_type<'a', 'b', 'c'>{};
  auto c1 = BOOST_HANA_STRING("abc");
  const auto c2 = literaltst::store<wchar_t, decltype(c1)>::buffer;
  using c3 = literaltst::detail::element_type<decltype(*"abc")>;
  constexpr auto c4 = LITERAL_METASTRING(L"aabc");
  auto sum_str = [](auto str) {
    return boost::hana::fold_left(str, boost::hana::int_c<0>, [](auto sum, auto c) {
        constexpr int i = boost::hana::value(c) - 'a';
        return sum + boost::hana::int_c<i>;
      });
  };
  auto cat_str = [](auto str0, auto str1) {
    return str0 + str1;
  };
  auto c5 = cat_str(c1, c1);

  std::cout << "c0:" << type_id_with_cvr<decltype(c0)>().pretty_name() << std::endl;
  std::cout << "C1:" << type_id_with_cvr<decltype(c1)>().pretty_name() << std::endl;
  std::cout << "C2:" << type_id_with_cvr<decltype(c2)>().pretty_name() << std::endl;
  std::cout << "C3:" << type_id_with_cvr<c3>().pretty_name() << std::endl;
  std::cout << "C4:" << type_id_with_cvr<decltype(c4)>().pretty_name() << std::endl;
  std::cout << "C5:" << type_id_with_cvr<decltype(c5)>().pretty_name() << std::endl;
}



int main(int,char**)
{
  test0();
  
  return 0;
}
