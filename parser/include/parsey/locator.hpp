#pragma once

#include <concepts>
#include <utility>
#include <type_traits>
#include <ostream>

#include <parsey/detail/util.hpp>

namespace parsey {

template <class T, class V>
concept locator =
    std::is_default_constructible_v<T>&& std::is_copy_constructible_v<T>&&
        std::is_move_constructible_v<T>&& requires(T& l, V v) {
    l.increment(v);
};

template <class T>
//requires locator<T, typename T::value_type>
requires locator<T, detail::GetParametricType<T, 0>>
 using locator_value_t = detail::GetParametricType<T, 0>;

template <class T>
concept printable_locator = locator<T, locator_value_t<T>>&& requires(
    T const& l, std::ostream& out) {
    { out << l }
    ->std::same_as<std::ostream&>;
};


template <class T>
struct index_locator {
    constexpr index_locator() noexcept
        : index{0u} {}
    constexpr explicit index_locator(size_t index) noexcept
        : index{index} {}
    constexpr index_locator(index_locator const&) = default;
    constexpr index_locator(index_locator&&) = default;
    constexpr index_locator& operator=(index_locator const&) = default;
    constexpr index_locator& operator=(index_locator&&) = default;

    constexpr void increment(T) noexcept { ++index; }
    // for pure functional purpose
    constexpr index_locator next(T) const noexcept {
        return index_locator{index + 1u};
    }

    friend inline std::ostream& operator<<(
        std::ostream& o, index_locator const& locator) {
        return o << locator.index;
    }

  private:
    size_t index;
};

struct locator_text {
    constexpr locator_text() = default;
};
}  // namespace parsey