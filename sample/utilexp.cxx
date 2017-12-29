//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <limits>
#include <tuple>
#include <boost/type_index.hpp>

#include <fmp.hpp>
#include <fmp/utils.hpp>
#include <fmp/maybe.hpp>

#include "sample.hpp"

template <typename T, typename... A>
struct apply0;

template <typename T, typename... A>
struct apply0 {
  using type = typename T::template apply<A...>::type;
};

void test_copy() {
  using namespace fmp;
  std::cout << "## " << __func__ << "() ##" << std::endl;

  auto t0 = std::make_tuple(1, 'x', "foo");
  using c0 = copy_t<decltype(t0), sequence>;
  using m0 = map_t<curry<std::add_const>, c0>;


  std::cout << T_name<decltype(t0)>() << std::endl;
  std::cout << T_name<c0>() << std::endl;
  std::cout << T_name<m0>() << std::endl;
};


void test_first() {
  using namespace fmp;
  std::cout << "## test_first() ##" << std::endl;

  using f0 = first_t<int, char, void>;

  std::cout << "f0: " << T_name<f0>() << std::endl;
}

void test_apply_args() {
  using namespace fmp;

  std::cout << "## test_apply_args() ##" << std::endl;
  using a0 = apply_args<int, char>;
  using r0 = apply_t<a0, curry<std::is_same>>;

  std::cout << "a0: " << T_name<a0>() << std::endl;
  std::cout << "r0: " << T_name<r0>() << std::endl;
}


int main(int, char**)
{
  test_first();
  test_apply_args();
  test_copy();
  return 0;
}
