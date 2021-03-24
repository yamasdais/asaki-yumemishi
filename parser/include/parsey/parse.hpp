#pragma once

#include <concepts>
#include <variant>

#include <parsey/detail/util.hpp>
#include <parsey/source.hpp>
#include <parsey/result.hpp>

#include <parsey/fwd/parse.hpp>
#include <parsey/detail/parse.hpp>

namespace parsey {

constexpr inline static detail::satisfy_fn satisfy{};

namespace pieces {

constexpr inline static detail::any_fn any{};

constexpr inline static auto lower = satisfy("lower alphabet",
    [](std::integral auto ch) { return detail::isAlphaLower(ch); });

constexpr inline static auto upper = satisfy("upper alphabet",
    [](std::integral auto ch) { return detail::isAlphaUpper(ch); });

constexpr inline static auto char1 = [](std::integral auto a_ch) {
    return satisfy("single character", [a_ch](std::integral auto ch) {
        return ch == a_ch;
    });
};

// combinators

}  // namespace pieces

}  // namespace parsey