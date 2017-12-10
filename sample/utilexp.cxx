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
#include <fmp/utils.hpp>

#define Demangle(T) boost::typeindex::type_id_with_cvr<T>().pretty_name()


void test_first() {
  using namespace fmp;
  std::cout << "## test_first() ##" << std::endl;

  using f0 = first_t<int, char, void>;

  std::cout << "f0: " << Demangle(f0) << std::endl;
}

void test_apply_args() {
  using namespace fmp;

  std::cout << "## test_apply_args() ##" << std::endl;
  using a0 = apply_args<int, char>;
  using r0 = apply_t<a0, curry<std::is_same>>;

  std::cout << "a0: " << Demangle(a0) << std::endl;
  std::cout << "r0: " << Demangle(r0) << std::endl;
}


int main(int, char**)
{
  test_first();
  test_apply_args();
  return 0;
}
