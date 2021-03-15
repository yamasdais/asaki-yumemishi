#pragma once

#include <ranges>
#include <concepts>
#include <iterator>
#include <variant>

#include <parsey/error.hpp>
#include <parsey/locator.hpp>
#include <parsey/result.hpp>

namespace parsey {

template <class Source>
concept parse_source = requires(Source& src) {
    typename Source::input_value_type;
    typename Source::error_type;
    typename Source::value_type;
    {*src} -> std::convertible_to<result<typename Source::input_value_type,
                typename Source::error_type>>;
    {++src};
}
&&std::forward_iterator<Source>&& parse_error<typename Source::error_type>;

template <parse_source T>
using parse_source_error_t = typename T::error_type;
template <parse_source T>
using parse_source_input_value_t = typename T::input_value_type;
template <parse_source T>
using parse_source_result_t = typename T::value_type;

template <std::ranges::forward_range Range,
    locator<std::iter_value_t<Range>> Locator =
        index_locator<std::iter_value_t<Range>>,
    parse_error Error = default_parser_error>
struct source {
    using range_type = Range;
    using input_value_type = std::iter_value_t<Range>;
    using value_type = result<input_value_type, Error>;
    using error_type = Error;
    using iterator_type = std::ranges::iterator_t<Range>;
    using sentinel_type = std::ranges::sentinel_t<Range>;
    using iterator_concept = std::forward_iterator_tag;
    //using range_iter_concept =
    //    typename std::iterator_traits<iterator_type>::iterator_concept;

    constexpr source() = default;
    constexpr source(source const& other) requires std::copyable<
        iterator_type> && std::copyable<sentinel_type> && std::copyable<Locator>
    = default;
    constexpr source(source&& other) = default;

    explicit constexpr source(Range const& range) noexcept(noexcept(
        std::ranges::begin(range)) && noexcept(std::ranges::end(range)))
        : current{std::ranges::begin(range)}
        , sentinel{std::ranges::end(range)}
        , locator{} {}

    source& operator=(source const& other) = default;
    source& operator=(source&& other) = default;

    // constexpr auto begin() const noexcept { return current; }
    // constexpr auto end() const noexcept { return sentinel; }

    constexpr operator bool() const noexcept { return current != sentinel; }
    constexpr bool operator!() const noexcept { return current == sentinel; }

    constexpr auto operator*() const noexcept(noexcept(*this->current)) {
        using ret_t = result<input_value_type, Error>;
        return (*this) ? ret_t{*current} : ret_t{Error{"out of range"}};
    }

    constexpr source operator++(int) {
        source ret{*this};
        next();
        return ret;
    }
    constexpr source& operator++() {
        next();
        return *this;
    }

    constexpr friend inline auto operator-(
        const source& l, const source& r) noexcept {
        return l.current - r.current;
    }

  private:
    constexpr void next() {
        locator.increment(*current);
        ++current;
    }
    iterator_type current;
    sentinel_type sentinel;
    Locator locator;
};

}  // namespace parsey