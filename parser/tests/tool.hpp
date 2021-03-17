#pragma once

#include <concepts>
#include <gtest/gtest.h>

#include <parsey/error.hpp>

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
		// disabled string comparison because pointer is not only C style string
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
		// I would expect these are the same address.
		return lv == rv;
#endif
	}
};

template <class T>
constexpr auto CheckEqualVal(T lv, T rv) {
	return IsEqualVal<T>{}(lv, rv);
}

// handle valid value
template <class T, parsey::parse_error Error = parsey::default_parser_error>
constexpr inline auto mk_result_pred = [](auto&& func) {
	using Func = std::remove_cvref_t<decltype(func)>;
	static_assert(std::predicate<Func, T>, "func must be a predicate");
	struct Pred {
		Func f;
		constexpr bool operator()(Error const& err) const {
			return false;
		}
		constexpr bool operator()(T v) const {
			return std::invoke(std::move(f), v);
		}
	};
	return Pred{std::forward<Func>(func)};
};

template <class...>
struct TTrace;

}  // namespace testutil