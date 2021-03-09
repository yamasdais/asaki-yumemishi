#pragma once

namespace parsey::detail {

// Getting parameter type with the parameter index.
// GetParametricType<type, index>
// ex [type: std::sting, index: 0] => char
template <class... Args>
struct TypeHolderImpl {};

template <std::size_t I, class T>
struct GetParamTypeImpl{};

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

#if 0
template <class T, std::size_t Idx>
using ttparam_get_t = typename GetParamTypeImpl<Idx, T>::type;

template <class>
struct TypeHolder;

template <template <class...> class T, class... Params>
struct TypeHolder<T<Params...>> {
    template <size_t I>
    constexpr static inline auto getParam() noexcept
        -> std::remove_cvref_t<decltype(
            std::get<I>(std::declval<std::tuple<Params...>>()))>;
};
#endif

template <class T, size_t I>
using GetParametricType =
    typename GetParamTypeImpl<I, T>::type;

}  // namespace parsey::detail