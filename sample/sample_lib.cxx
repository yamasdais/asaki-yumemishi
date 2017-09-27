#include "sample.hpp"

Demangler::Demangler(const std::type_info& info, int stat)
#if defined(HAVE_GCC_ABI_DEMANGLE)
  : name{abi::__cxa_demangle(info.name(), nullptr, nullptr, &stat)}
#endif
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

