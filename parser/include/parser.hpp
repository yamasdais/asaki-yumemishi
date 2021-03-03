#pragma once

#include <concepts>
#include <ranges>
#include <iterator>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>

template <class T>
struct TypeTracer;

namespace dais::parse {
    struct locator;

    template <class Mesg>
    struct error {
        using message_type = Mesg;
        Mesg message;
    };

    // source will be depricated, then replaced with concept
    template <std::ranges::forward_range Range, class MessageT = char const*>
    struct source {
        using view_type = std::ranges::views::all_t<Range>;
        using iterator_type = decltype(std::ranges::cbegin(std::declval<view_type>()));
        using sentinel_type = decltype(std::ranges::cend(std::declval<view_type>()));
        using value_type = std::iter_value_t<iterator_type>;
        using error_type = error<MessageT>;
        using result_type = std::variant<value_type, error_type>;

        explicit constexpr source(view_type range)
            noexcept(noexcept(std::is_nothrow_move_constructible_v<view_type>))
            : view(std::move(range))
        {}

        constexpr iterator_type begin() const noexcept {
            return std::ranges::cbegin(view);
        }
        constexpr sentinel_type end() const noexcept {
            return std::ranges::cend(view);
        }
        constexpr void next(iterator_type& itr) const {
            ++itr;
        }
        constexpr result_type peek(iterator_type const& current) const noexcept(noexcept(*current)) {
            return current != end()
                ? result_type{value_type(*current)}
                : result_type{error_type("out of range")};
        }

        // static
        constexpr static inline bool result_success(result_type const& result) noexcept {
            return std::holds_alternative<value_type>(result);
        }

      private:
        view_type view;
    };

    template <std::ranges::forward_range Range>
    constexpr source<Range> make_source(Range& range) {
        return source<Range>(std::ranges::views::all_t<Range>(range));
    }

    template <class Source>
    concept sourceable = requires (Source const& src) {
        typename Source::value_type;
        typename Source::result_type;
        typename Source::error_type;
        typename Source::iterator_type;
        {src.peek(std::declval<typename Source::iterator_type>())}
            -> std::convertible_to<typename Source::result_type>;
    } && std::ranges::forward_range<Source>;

    template <class T, sourceable Source>
    using parser_result_t = std::variant<T, typename Source::error_type>;

    template <class Result>
        requires requires (Result const& result) {
            {result.index()} -> std::convertible_to<size_t>;
        }
    constexpr static inline bool parser_success(Result const& result) noexcept {
        return result.index() == 0;
    }

    template <class Result>
    using parser_value_decl_t = decltype(std::get<0>(std::declval<Result>()));
    template <class Result>
    using parser_value_t = std::remove_reference_t<parser_value_decl_t<Result>>;

    template <class Func, sourceable Source>
        requires std::is_invocable_v<Func, Source const&, typename Source::iterator_type&>
    struct parser_return_type {
        using type = std::invoke_result_t<Func, Source const&, typename Source::iterator_type&>;
    };
    template <class Func, sourceable Source>
    using parser_return_type_t = typename parser_return_type<Func, Source>::type;

    template <class Func, class Source, class... Args>
    concept parse_function = sourceable<Source>
        && std::invocable<Func, typename Source::value_type, Args...>;

    template <class Parser, class Source>
    concept parser = sourceable<Source>
        && std::is_invocable_v<Parser, Source const&, typename Source::iterator_type&>;

    // parse functions
    constexpr static inline auto isDigitAscii = [](std::integral auto ch) noexcept -> bool
    {
        return '0' <= ch && ch <= '9';
    };

    // parsers
    namespace detail {
        struct anyChar_fn {
            template <sourceable Source>
            constexpr auto operator()(Source const& src, typename Source::iterator_type& cur)
                const noexcept {
                auto ret{src.peek(cur)};
                if (Source::result_success(ret)) {
                    src.next(cur);
                }
                return ret;
            }
        };

        struct condLift_fn {
            template <class Func, class Mesg, class... Args>
            constexpr auto operator()(Func func, Mesg message, Args... args) const noexcept {
                return [func=std::move(func),message,...args=args]
                    <sourceable Source>(Source const& src, typename Source::iterator_type& cur)
                    -> parser_result_t<typename Source::value_type, Source>
               requires parse_function<Func, Source, Args...>
                   && std::convertible_to<Mesg, typename Source::error_type::message_type>
                   && std::predicate<Func, typename Source::value_type, Args...>
               {
                    auto ret{src.peek(cur)};
                    if (!Source::result_success(ret))
                        return {std::get<1>(ret)};
                    if (!func(std::get<0>(ret), args...))
                        return {typename Source::error_type{message}};
                    src.next(cur);
                    return {std::get<0>(ret)};
                };
            }
        };

        constexpr static inline condLift_fn condLift_impl{};
    }

    constexpr static inline detail::anyChar_fn anyChar{};

    constexpr auto character(std::integral auto ch) noexcept {
        return detail::condLift_impl([](std::integral auto c, std::integral auto reqCh) noexcept {
                return c == reqCh;
                }, "character", ch);
    }
    constexpr auto between(std::integral auto low, std::integral auto high) noexcept {
        return detail::condLift_impl([](std::integral auto c, std::integral auto l, std::integral auto h) noexcept {
                return l <= c && c <= h;
                }, "between", low, high);
    }

    template <auto func, auto mesg>
    constexpr static inline auto condLift = detail::condLift_impl(func, mesg());

    constexpr static inline auto lower = condLift<[](std::integral auto c) noexcept {
        return 'a' <= c && c <= 'z';
    }, []() noexcept { return "lower alphabet"; }>;

}
