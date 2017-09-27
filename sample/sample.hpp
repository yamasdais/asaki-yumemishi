#if !defined(UUID_29B974E6_2A8A_4B56_B0D5_6B885825F24A)
#define UUID_29B974E6_2A8A_4B56_B0D5_6B885825F24A

#if !defined(__cplusplus) or __cplusplus < 201103
#error This library designed for C++11 (or newer, hopefully).
#endif // c++ version check

#include <typeinfo>
#include <memory>
#include <utility>
#include <cstdlib>

template <typename Ty>
auto demangle(Ty);

class Demangler {
 public:

  template <typename Ty>
  struct Deleter {
    inline void operator()(void* p) {
      std::free(p);
    }
  };
 private:
  std::unique_ptr<char[], Deleter<char[]> > name;

  Demangler(const std::type_info& info, int stat);

 public:
  inline explicit Demangler(const std::type_info& info)
    : Demangler{info, 0}
  {
  }

  template <typename Ty>
  inline Demangler(Ty val)
    : Demangler{typeid(val), 0}
  {
  }

  inline operator const char*() const noexcept {
    return name.get();
  }

  template <typename Ty>
  friend auto demangle(Ty);
};


template <typename Ty>
inline auto demangle(Ty obj) {
  return std::move(Demangler{obj}.name);
}

#endif /* UUID_29B974E6_2A8A_4B56_B0D5_6B885825F24A */