//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243)
#define FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243

#include <type_traits>

#include <fmp/primitive.hpp>
#include <fmp/check.hpp>
#include <fmp/operator.hpp>
#include <fmp/sequence.hpp>

namespace fmp {

namespace detail {

} // ns: detail

template <typename T>
struct type_size {
  using type = T;
  constexpr static size_t value = sizeof(T);

  template <typename Other>
  using equals = std::conditional_t<
    (value == Other::value),
    std::true_type, std::false_type>;

  template <typename Other>
  using less_than = std::conditional_t<
    (value < Other::value),
    std::true_type, std::false_type>;

  template <typename Other>
  using greater_than = std::conditional_t<
    (value > Other::value),
    std::true_type, std::false_type>;
};

namespace detail {


}

} /* ns: fmp */

#endif /* if not defined 'FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243' */
