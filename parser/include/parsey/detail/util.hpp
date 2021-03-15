#pragma once

#include <concepts>
#include <functional>

namespace parsey::detail {

// Getting parameter type with the parameter index.
// GetParametricType<type, index>
// ex [type: std::string, index: 0] => char, because string is basic_string<char>
template <class... Args>
struct TypeHolderImpl {};

template <std::size_t I, class T>
struct GetParamTypeImpl {};

template <template <class...> class T, class Head, class... Args>
struct GetParamTypeImpl<0u, T<Head, Args...>> {
    using type = Head;
};
template <template <class...> class T, class Head, class... Args>
struct GetParamTypeImpl<0u, T<Head const, Args...>> {
    using type = Head const;
};
template <std::size_t I, template <class...> class T, class Head, class... Args>
struct GetParamTypeImpl<I, T<Head, Args...>> {
    using type =
        typename GetParamTypeImpl<(I - 1u), TypeHolderImpl<Args...>>::type;
};

template <template <class...> class To, class From>
struct CopyParamTypesImpl;

template <template <class...> class To, template <class...> class From, class... Args>
struct CopyParamTypesImpl<To, From<Args...>> {
    using type = To<Args...>;
};

}  // namespace parsey::detail