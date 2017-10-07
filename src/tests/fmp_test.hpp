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

#include <gtest/gtest.h>

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


// gtest utilities

// Boolean test
template <typename T>
struct BoolTest : public ::testing::Test {
  // concept declarations of type T
  using expected_type = typename T::first_type;
  using actual_type = typename T::second_type;
  static_assert(std::is_same<typename expected_type::value_type, bool>::value,
                "first_type must be a bool");
  static_assert(std::is_same<typename actual_type::value_type, bool>::value,
                "second_type must be a bool");
};

TYPED_TEST_CASE_P(BoolTest);

TYPED_TEST_P(BoolTest, CheckBoolean) {
  bool actual = typename TypeParam::second_type();
  if (typename TypeParam::first_type()) {
    ASSERT_TRUE(actual);
  } else {
    ASSERT_FALSE(actual);
  }
}

REGISTER_TYPED_TEST_CASE_P(BoolTest, CheckBoolean);


// Type test
template <typename T>
struct TypeTest : public ::testing::Test {
  // concept declarations of type T
  using expected_type = typename T::first_type;
  using actual_type = typename T::second_type;
};

TYPED_TEST_CASE_P(TypeTest);

TYPED_TEST_P(TypeTest, CheckType) {
  bool is_same = std::is_same<
    typename TypeParam::first_type,
    typename TypeParam::second_type
    >::value;
  ASSERT_TRUE(is_same);
}

REGISTER_TYPED_TEST_CASE_P(TypeTest, CheckType);

#endif /* UUID_29B974E6_2A8A_4B56_B0D5_6B885825F24A */
