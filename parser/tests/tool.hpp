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

template <class T>
struct IsEqualVal {
	constexpr bool operator()(T const& lv, T const& rv) const {
		return lv == rv;
	}
};
template <class T>
struct IsEqualVal<T*> {
	constexpr bool operator()(T const* lv, T const* rv) const {
#if 0
		// pointer is not only C style string
        if (!v || !sample)
            return v == sample;
        while (*v++ == *sample++)
            if (*v == '\0')
                return true;
        return false;
#endif
		// Work around: visual studio C++ returns different address for constexpr object
#if defined(_MSC_VER)
		return *lv == *rv;
#else
		return lv == rv;
#endif
	}
};

template <class T>
constexpr auto CheckEqualVal(T lv, T rv) {
	return IsEqualVal<T>{}(lv, rv);
}

template <class...>
struct TTrace;

}  // namespace testutil