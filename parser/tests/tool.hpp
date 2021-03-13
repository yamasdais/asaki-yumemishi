#pragma once

#include <concepts>
#include <gtest/gtest.h>

namespace testutil {

template <class T>
concept from_testing = std::derived_from<T, ::testing::Test> && requires(T) {
    typename T::type;
};

template <from_testing T>
using get_param_t = typename T::type;

using TestCharTypes = ::testing::Types<char, char8_t, char16_t, char32_t, wchar_t>;

}  // namespace testutil