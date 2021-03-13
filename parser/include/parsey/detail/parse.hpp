#pragma once

#include <concepts>
#include <utility>
#include <functional>

#include <parsey/detail/util.hpp>
#include <parsey/source.hpp>
#include <parsey/result.hpp>
#include <parsey/util.hpp>
#include <parsey/fwd/parse.hpp>

namespace parsey::detail {

struct ParserImpl {

};

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
        return [func = std::move(func), message]<parse_source Source>(
            Source
            & src) requires parse_trait<Func, Source> && std::predicate<Func,
            parse_source_input_value_t<Source>> {
            using ret_t = result<parse_source_input_value_t<Source>,
                parse_source_error_t<Source>>;
            auto const val{*src};

            if (val) {
                ++src;
                if (!std::invoke(func, *val))
                    return ret_t{parse_source_error_t<Source>{message}};
            }
            return val;
        };
    }
};
constexpr inline static liftPred_fn liftPredImpl{};

struct foldAll_fn {
    template <class Func, class Init, class ParserH, class... ParserT>
    constexpr auto operator()(Func func, Init init, char const* message,
        ParserH&& head, ParserT&&... prs) const {
        return [
            func_ = std::move(func), val = std::move(init), message,
            head_ = std::forward<ParserH>(head),
            ... prs_ = std::forward<ParserT>(prs)
        ]<parse_source Source>(
            Source & src) requires parser_with<ParserH, Source> && std::
            convertible_to<std::invoke_result_t<Func, Init,
                               parser_return_value_t<ParserH, Source>>,
                Init>
            &&(parser_with<ParserT, Source> && ...) {
            return opparen_impl(src, func_, val, message, head_, prs_...);
        };
    }

  private:
    template <parse_source Source, class Func>
    constexpr static inline auto opparen_impl(
        Source&, Func, auto val, char const*) {
        return make_parse_result<parse_source_error_t<Source>>(std::move(val));
    }
    template <parse_source Source, class Func, parser_with<Source> ParserHead,
        parser_with<Source>... ParserTail>
    constexpr static inline auto opparen_impl(Source& source, Func func,
        auto val, char const* message, ParserHead const& head,
        ParserTail const&... tail) requires std::invocable<Func, decltype(val),
        parser_return_value_t<ParserHead, Source>> {
        auto ret = std::invoke(head, source);
        using ret_t = std::invoke_result_t<Func, decltype(val),
            parser_return_value_t<ParserHead, Source>>;
        if (!ret)
            return make_parse_result<ret_t>(
                parse_source_error_t<Source>{message});

        return opparen_impl(source, func, func(val, *ret), message, tail...);
    }
};
constexpr inline static foldAll_fn foldAll{};

}  // namespace parsey::detail