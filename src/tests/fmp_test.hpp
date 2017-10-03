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

class Demangler {
 public:

  struct Deleter {
    inline void operator()(void* p) {
      std::free(p);
    }
  };
 private:
  std::unique_ptr<char[], Deleter> name;

  Demangler(const std::type_info& info, int stat);

 public:
  inline explicit Demangler(const std::type_info& info)
    : Demangler{info, 0}
  {
  }

#if 0
  inline Demangler(Demangler&& other) noexcept
  {
    *this = std::move(other);
  }

  inline Demangler& operator=(Demangler&& other) noexcept {
    if (this != &other) {
      this->name = std::move(other.name);
    }
    return *this;
  }
#endif

  inline operator const char*() const noexcept {
    return name.get();
  }
};


template <typename Ty>
inline auto demangle() {
  return std::move(Demangler{typeid(Ty)});
}

template <typename Ty>
inline auto demangle(const Ty& obj) {
  return std::move(Demangler{typeid(obj)});
}

#endif /* UUID_29B974E6_2A8A_4B56_B0D5_6B885825F24A */
