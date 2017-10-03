//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cxxabi.h>
#include "sample.hpp"

Demangler::Demangler(const std::type_info& info, int stat)
  : name{abi::__cxa_demangle(info.name(), nullptr, nullptr, &stat)}
{
  if (stat == -2) {
    throw std::invalid_argument(std::string("Invalid mangled name: '")
                                + info.name() + "'");
  }
  if (stat != 0) {
    throw std::runtime_error(std::string("Demangle failed with status: "
                                         + std::to_string(stat)));
  }
}

