#pragma once

#include <ranges>
#include <concepts>
#include <iterator>
#include <variant>

#include <parsey/error.hpp>
#include <parsey/locator.hpp>
#include <parsey/result.hpp>

#include <parsey/detail/source.hpp>

namespace parsey {

template <std::ranges::forward_range Range,
    locator<std::iter_value_t<Range>> Locator =
        index_locator<std::iter_value_t<Range>>,
    parse_error Error = default_parser_error>
struct source {
    using range_type = Range;
    using iterator_type = std::ranges::iterator_t<Range>;
    using sentinel_type = std::ranges::sentinel_t<Range>;
    using input_value_type = std::iter_value_t<iterator_type>;
    using value_type = result<input_value_type, Error>;
    using error_type = Error;
    using iterator_concept = std::forward_iterator_tag;
    // using range_iter_concept =
    //     typename std::iterator_traits<iterator_type>::iterator_concept;

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
        return (*this) ? ret_t{*current}
                       : ret_t{Error{"end of range", error_status_t::end}};
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

    constexpr friend inline bool operator==(
        source const& l, source const& r) noexcept {
        return l.current == r.current;
    }
    constexpr friend inline bool operator!=(
        source const& l, source const& r) noexcept {
        return l.current != r.current;
    }
    constexpr friend inline auto operator-(
        source const& l, source const& r) noexcept {
        return l.current - r.current;
    }

    constexpr auto consume() {
        auto ret = *(*this);
        if (*this)
            next();
        return ret;
    }

    template <class Func>
    requires std::invocable<Func, input_value_type> && std::invocable<Func,
        error_type>
    constexpr auto visit(Func&& func) {
        if (current == sentinel)
            return std::invoke(std::forward<Func>(func), Error{"end of range", error_status_t::end});
        auto ret = std::invoke(std::forward<Func>(func), *current);
        if (ret)
            next();
        return ret;
    }

  private:
    constexpr void next() {
        if (current == sentinel) {
            if (std::is_constant_evaluated()) {
                static_assert([]() { return false; }, "out of range");
            } else {
                throw std::range_error("out of range: source::next()");
            }
        }
        locator.increment(*current);
        ++current;
    }
    iterator_type current;
    sentinel_type sentinel;
    Locator locator;
};

template <parse_source Source>
constexpr auto make_source_result_visitor(auto&& func)
    requires std::invocable<decltype(func),
            parse_source_input_value_t<Source>>
        && parse_result<std::invoke_result_t<decltype(func),
           parse_source_input_value_t<Source>>> {
    return detail::SourceResultVisitor<
        std::remove_cvref_t<decltype(func)>, Source>{(decltype(func))func};
}

}  // namespace parsey