#pragma once

#include <concepts>
#include <utility>
#include <type_traits>
#include <ostream>

#include <parsey/fwd/locator.hpp>

namespace parsey {

template <class T>
concept printable_locator = incremental_locator<T, locator_value_t<T>> && requires(
    T const& l, std::ostream& out) {
    { out << l } -> std::same_as<std::ostream&>;
};

template <class T>
struct index_locator {
    constexpr explicit index_locator(size_t index = 0u) noexcept
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

    constexpr size_t position() const noexcept { return index; }

  private:
    size_t index;
};

struct locator_text {
    constexpr locator_text() = default;
};
}  // namespace parsey