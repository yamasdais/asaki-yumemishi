#pragma once

#include <concepts>
#include <ostream>

#include <parsey/util.hpp>

namespace parsey {

template <class Locator>
concept locator = std::semiregular<std::remove_cvref_t<Locator>>
&& requires (Locator l) {
    std::as_const(l).position();
};

template <class Locator, class V>
concept incremental_locator = locator<Locator> && requires(Locator& l, V v) {
    l.increment(v);
};

template <class T>
requires incremental_locator<T, get_tparam_t<T, 0>>
using locator_value_t = get_tparam_t<T, 0>;

template <class T, class V>
concept printable_locator = locator<T> && requires(
    T const& l, std::basic_ostream<V>& out) {
    { out << l } -> std::same_as<std::basic_ostream<V>&>;
};

}
