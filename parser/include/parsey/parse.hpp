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

#if 1
constexpr inline static auto lower = detail::liftPredImpl(
    [](std::integral auto ch) { return detail::isAlphaLower(ch); },
    "lower alphabet");
#else
constexpr inline static auto lower = satisfy(
    "lower alphabet", [](std::integral auto ch) {
        return detail::isAlphaLower(ch);
    });
#endif


constexpr inline static auto upper = detail::liftPredImpl(
    [](std::integral auto ch) { return detail::isAlphaUpper(ch); },
    "upper alphabet");

constexpr auto letter(std::integral auto refCh) noexcept {
    return detail::liftPredImpl(
        [refCh](std::integral auto ch) { return ch == refCh; }, "letter");
}

// combinators

}  // namespace pieces

}  // namespace parsey