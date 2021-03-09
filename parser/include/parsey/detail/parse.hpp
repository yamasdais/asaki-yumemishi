#pragma once

#include <concepts>

#include <parsey/detail/util.hpp>
#include <parsey/source.hpp>
#include <parsey/result.hpp>
#include <parsey/fwd/parse.hpp>

namespace parsey::detail {

constexpr bool isAlphaLower(std::integral auto ch) noexcept {
    return 'a' <= ch && ch <= 'z';
}
constexpr bool isAlphaUpper(std::integral auto ch) noexcept {
    return 'A' <= ch && ch <= 'Z';
}

struct any_fn {
    template <parse_source Source>
    constexpr auto operator()(Source& src) const {
        auto const val{*src};
        if (val)
            ++src;
        return val;
    }
};

struct liftPred_fn {
    template <class Func>
    constexpr auto operator()(Func func, char const* message) const noexcept {
        return
            [func = std::move(func), message]<parse_source Source>(
                Source & src) requires parse_trait<Func,
                Source> && std::predicate<Func, parse_source_input_value_t<Source>> {
            using ret_t = result<parse_source_input_value_t<Source>,
                parse_source_error_t<Source>>;
            auto const val{*src};

            if (val) {
                ++src;
                if (!func(*val))
                    return ret_t{parse_source_error_t<Source>{message}};
            }
            return val;
        };
    }
};

constexpr inline static liftPred_fn liftPredImpl{};

struct foldAll_fn {
    template <class Func, class Init, class... Parser>
    constexpr auto operator()(
        Func func, Init init, char const* message, Parser... prs) const {
        return [
            func = std::move(func), val = std::move(init), message, ... prs =
            prs
        ]<parse_source Source>(
            Source & src) requires(parser<Parser, Source> && ...) {
            return opparen_impl(src, func, val, message, prs...);
        };
    }

  private:
    template <parse_source Source, class Func>
    constexpr static inline auto opparen_impl(
        Source&, Func, auto val, char const*) {
        return make_parse_result<parse_source_error_t<Source>>(std::move(val));
    }
    template <parse_source Source, class Func, parser<Source> ParserHead,
        parser<Source>... ParserTail>
    constexpr static inline auto opparen_impl(Source& source, Func func,
        auto val, char const* message, ParserHead head,
        ParserTail... tail) requires std::invocable<Func, decltype(val),
        parser_return_value_t<ParserHead, Source>> {
        auto ret = head(source);
        using ret_t = std::invoke_result_t<Func, decltype(val),
            parser_return_value_t<ParserHead, Source>>;
        if (!ret)
            return make_parse_result<ret_t>(
                parse_source_error_t<Source>{"foldAll"});

        return opparen_impl(source, func, func(val, *ret), message, tail...);
    }
};
constexpr inline static foldAll_fn foldAll{};

}  // namespace parsey::detail