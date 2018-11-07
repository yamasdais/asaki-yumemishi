#include <iostream>
#include <boost/type_index.hpp>
#include <boost/hana/string.hpp>

namespace literal {

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
  literal::CharLiteralChooser{                                          \
    CNV_CHTYPE(CH,u8), CNV_CHTYPE(CH,L), CNV_CHTYPE(CH,u), CNV_CHTYPE(CH,U)\
    }.get<TYPE>()

template <typename To>
constexpr To convert(char ch) noexcept {
  return static_cast<To>(ch);
}

template <typename To, typename Str>
struct store;

template <typename To, char... Ch>
struct store<To, const boost::hana::string<Ch...>> {
  constexpr static To const buffer[sizeof...(Ch)+1] = {
    static_cast<To>(Ch)..., static_cast<To>('\0')
  };
};

}

void test0()
{
  using boost::typeindex::type_id_with_cvr;
  constexpr auto c0 = literal::convert<wchar_t>('a');
  constexpr auto c1 = BOOST_HANA_STRING("abc");
  auto c2 = literal::store<wchar_t, decltype(c1)>::buffer;
  std::cout << "c0:" << type_id_with_cvr<decltype(c0)>().pretty_name() << std::endl;
  std::cout << "C1:" << type_id_with_cvr<decltype(c1)>().pretty_name() << std::endl;
  std::cout << "C2:" << type_id_with_cvr<decltype(c2)>().pretty_name() << std::endl;
}



int main(int,char**)
{
  test0();
  
  return 0;
}
