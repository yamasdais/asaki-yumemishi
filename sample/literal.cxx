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


struct LiteralChooser {
  char const* char_literal;
  wchar_t const* wchar_literal;
  char16_t const* char16_literal;
  char32_t const* char32_literal;

  constexpr LiteralChooser(
    char const* char_literal,
    wchar_t const* wchar_literal,
    char16_t const* char16_literal,
    char32_t const* char32_literal
  ) : char_literal(char_literal),
    wchar_literal(wchar_literal),
    char16_literal(char16_literal),
    char32_literal(char32_literal)
  {
  }
  template <typename Ch>
  constexpr operator Ch const *() const noexcept;
};

template <>
constexpr LiteralChooser::operator char const*()
  const noexcept {
  return char_literal;
}

template <>
constexpr LiteralChooser::operator wchar_t const*()
  const noexcept {
  return wchar_literal;
}

template <>
constexpr LiteralChooser::operator char16_t const*()
  const noexcept {
  return char16_literal;
}

template <>
constexpr LiteralChooser::operator char32_t const*()
  const noexcept {
  return char32_literal;
}

#define CNV_CHTYPE(CH, PREFIX) (PREFIX ## CH)
#if 0
#define CONVERT_CH(TYPE, CH) \
  CharLiteralChooser{                                          \
    CH, CNV_CHTYPE(CH,L), CNV_CHTYPE(CH,u), CNV_CHTYPE(CH,U)\
    }.get<TYPE>()
#endif
#define CONVERT_CH(TYPE, CH) \
  LiteralChooser{ CH, CNV_CHTYPE(CH,L), CNV_CHTYPE(CH,u), CNV_CHTYPE(CH,U) }

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
  constexpr static auto length = sizeof...(Ch);
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
constexpr string_t<ChT>::tuple_type<S::get()[N]...>
prepare_impl(S, std::index_sequence<N...>) { return {}; }

template <typename ChT, typename S>
constexpr decltype(auto)
prepare(S s) {
  return prepare_impl<ChT>(
    s,
    std::make_index_sequence<sizeof(S::get())/sizeof(ChT) - 1>{});
}


}

#define LITERAL_METASTRING(str) \
  (::detail::prepare<std::decay_t<decltype(*str)>>([]{ \
      struct tmp { \
        static constexpr decltype(auto) get() { return str; }    \
      }; \
      return tmp{};                             \
    }()));

void test0()
{
  using boost::typeindex::type_id_with_cvr;
  constexpr auto c0 = string_t<char>::tuple_type<'a', 'b', 'c'>{};
  auto c1 = BOOST_HANA_STRING("abc");
  using c2 = store<wchar_t, decltype(c1)>;
  using c3 = std::decay_t<decltype(*"abc")>;
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
  auto c6 = c2::length;

  std::cout << "c0:" << type_id_with_cvr<decltype(c0)>().pretty_name() << std::endl;
  std::cout << "C1:" << type_id_with_cvr<decltype(c1)>().pretty_name() << std::endl;
  std::cout << "C2:" << type_id_with_cvr<decltype(c2::buffer)>().pretty_name() << std::endl;
  std::cout << "C3:" << type_id_with_cvr<c3>().pretty_name() << std::endl;
  std::cout << "C4:" << type_id_with_cvr<decltype(c4)>().pretty_name() << std::endl;
  std::cout << "C5:" << type_id_with_cvr<decltype(c5)>().pretty_name() << std::endl;
  std::cout << "C6:" << c6 << std::endl;
}

void test1() {
  using boost::typeindex::type_id_with_cvr;
  constexpr char32_t const* cc = LiteralChooser("abc", L"abc", u"abc", U"abc");

  std::cout << "cc:" << type_id_with_cvr<decltype(cc)>().pretty_name() << std::endl;
}

int basic_strcmp(char const* l, char const* r) {
  for (; *l != '\0'; l++, r++) {
    if (*l != *r) {
      return *l < *r ? -1 : 1;
    }
  }
  return *r == '\0' ? 0 : -1;
}
void test2() {
  auto res = basic_strcmp("a", "ab");
  std::cout << "res: " << res << std::endl;
}

int main(int,char**)
{
  test2();
  
  return 0;
}
