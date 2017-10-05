//          Copyright Yamashta, Daisuke 2017
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(FMP_C9476D80_F8A2_4A97_80CA_65948D41B619)
#define FMP_C9476D80_F8A2_4A97_80CA_65948D41B619

namespace fmp {
namespace detail {

struct has_value_impl {
  template <typename T>
  static auto check(T*) noexcept -> decltype(
    (T::value == T::value),
    std::true_type());

  template <typename T>
  static auto check(...) noexcept -> std::false_type;
};

struct has_type_impl {
  template <typename T>
  static auto check(typename T::type*) noexcept -> std::true_type;

  template <typename T>
  static auto check(...) noexcept -> std::false_type;
};

} /* ns: fmp::detail */

} /* ns: fmp */

#endif /* if not defined 'FMP_C9476D80_F8A2_4A97_80CA_65948D41B619' */
