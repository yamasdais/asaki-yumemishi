#include <iostream>

#include <boost/type_index.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/greater.hpp>
#include <boost/hana/less.hpp>
#include <literal/basic_string.hpp>
#include <functional>

namespace hana = boost::hana;

void test0() {
  using boost::typeindex::type_id_with_cvr;
  constexpr auto c0 = BOOST_HANA_B_STRING("aabc");
  constexpr auto c0_1 = hana::basic_string_c<char, 'a', 'a', 'b', 'c'>;
  constexpr auto c0_2 = hana::basic_char_<char, 'a'>{};
  constexpr auto c0_3 = hana::basic_char_c<char, 'a'>;
  constexpr auto c0_4 = c0 == BOOST_HANA_B_STRING("bcd");
  constexpr auto c1 = BOOST_HANA_B_STRING(L"aabc");
  constexpr auto c1_0 = BOOST_HANA_WSTRING("aabc");
  constexpr auto c1_1 = c1 == c1_0;

  std::cout << "c0:" << type_id_with_cvr<decltype(c0)>().pretty_name() << std::endl;
  std::cout << "c0_1:" << type_id_with_cvr<decltype(c0_1)>().pretty_name() << std::endl;
  std::cout << "c0_2:" << type_id_with_cvr<decltype(c0_2)>().pretty_name() << std::endl;
  std::cout << "c0_3:" << type_id_with_cvr<decltype(c0_3)>().pretty_name() << std::endl;
  std::cout << "c0_4:" << type_id_with_cvr<decltype(c0_4)>().pretty_name() << std::endl;
  std::cout << "c0.c_str():" << c0.c_str() << std::endl;
  std::cout << "c1:" << type_id_with_cvr<decltype(c1)>().pretty_name() << std::endl;
  std::cout << "c1_0:" << type_id_with_cvr<decltype(c1_0)>().pretty_name() << std::endl;
  std::cout << "c1_1:" << type_id_with_cvr<decltype(c1_1)>().pretty_name() << std::endl;
}

template <typename S>
struct sig {};



void test1() {
  using boost::typeindex::type_id_with_cvr;

  std::cout << "hello" << std::endl;

  constexpr auto c0 = L'\xc0';
  std::cout << "c0:" << c0 << std::endl;

  using t0 = decltype(std::declval<decltype(*"abc")>());
  using t1 = std::decay_t<t0>;
  std::cout << "t0:" << type_id_with_cvr<t0>().pretty_name() << std::endl;
  std::cout << "t1:" << type_id_with_cvr<t1>().pretty_name() << std::endl;

  auto s0 = hana::equal(BOOST_HANA_BASIC_STRING(char, "abcd")[hana::size_c<2>],
                        hana::basic_char_c<char, 'c'>);
  std::cout << "s0:" << s0 << std::endl;
  std::cout << "s0t:" << type_id_with_cvr<decltype(s0)>().pretty_name() << std::endl;
  std::cout << "s0::type:" << decltype(s0)::value << std::endl;
}

int main(int, char**) {
  std::cout << std::hex;
  test1();
  
  return 0;
}
