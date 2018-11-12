#include <iostream>

#include <boost/type_index.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/greater.hpp>
#include <boost/hana/less.hpp>
#include <literal/basic_string.hpp>

namespace hana = boost::hana;

void test0() {
  using boost::typeindex::type_id_with_cvr;
  constexpr auto c0 = BOOST_HANA_B_STRING("aabc");
  constexpr auto c0_1 = hana::basic_string_c<char, 'a', 'a', 'b', 'c'>;
  constexpr auto c0_2 = hana::basic_char_<char, 'a'>{};
  constexpr auto c0_3 = hana::basic_char_c<char, 'a'>;
  constexpr auto c0_4 = c0 == BOOST_HANA_B_STRING("bcd");
  constexpr auto c1 = BOOST_HANA_B_STRING(L"aabc");

  std::cout << "c0:" << type_id_with_cvr<decltype(c0)>().pretty_name() << std::endl;
  std::cout << "c0_1:" << type_id_with_cvr<decltype(c0_1)>().pretty_name() << std::endl;
  std::cout << "c0_2:" << type_id_with_cvr<decltype(c0_2)>().pretty_name() << std::endl;
  std::cout << "c0_3:" << type_id_with_cvr<decltype(c0_3)>().pretty_name() << std::endl;
  std::cout << "c0_4:" << type_id_with_cvr<decltype(c0_4)>().pretty_name() << std::endl;
  std::cout << "c0.c_str():" << c0.c_str() << std::endl;
  std::cout << "c1:" << type_id_with_cvr<decltype(c1)>().pretty_name() << std::endl;
}

int main(int, char**) {
  test0();
  
  return 0;
}
