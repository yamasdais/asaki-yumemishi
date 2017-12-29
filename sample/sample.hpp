//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(UUID_29B974E6_2A8A_4B56_B0D5_6B885825F24A)
#define UUID_29B974E6_2A8A_4B56_B0D5_6B885825F24A

#if !defined(__cplusplus) or __cplusplus < 201103
#error This library designed for C++11 (or newer, hopefully).
#endif // c++ version check

#include <typeinfo>
#include <type_traits>
#include <memory>
#include <utility>
#include <cstdlib>

#include <boost/type_index.hpp>

template <typename T>
auto T_name() {
  return std::move(boost::typeindex::type_id_with_cvr<T>().pretty_name());
};

#endif /* UUID_29B974E6_2A8A_4B56_B0D5_6B885825F24A */
