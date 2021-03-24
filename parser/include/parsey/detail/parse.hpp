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

template <parse_source Source, class Visitor>
requires std::invocable<Visitor, parse_source_input_value_t<Source>>
&& parse_result<std::invoke_result_t<Visitor, parse_source_input_value_t<Source>>>
&& std::invocable<Visitor, parse_source_error_t<Source>>
&& parse_result<std::invoke_result_t<Visitor, parse_source_error_t<Source>>>
struct PreparedSourceParser {
    constexpr PreparedSourceParser(Visitor const& visitor)
        : visitor{visitor} {}
    constexpr PreparedSourceParser(Visitor&& visitor)
        : visitor{std::forward<Visitor>(visitor)} {}

    constexpr auto operator()(Source& source) const& {
        return source.fmap(visitor);
    }
    constexpr auto operator()(Source& source) && {
        return source.fmap(std::move(visitor));
    }
  protected:
    Visitor visitor;
};
template <parse_source Source>
constexpr auto MakePreparedSourceParser(auto&& func)
requires std::invocable<decltype(func), parse_source_input_value_t<Source>> {
    return PreparedSourceParser<Source, std::remove_cvref_t<decltype(func)>>(
        (decltype(func))func);
}

constexpr bool isAlphaLower(std::integral auto ch) noexcept {
    return 'a' <= ch && ch <= 'z';
}
constexpr bool isAlphaUpper(std::integral auto ch) noexcept {
    return 'A' <= ch && ch <= 'Z';
}

struct any_fn {
    using parser_trait = scan_source_parser_tag;
    template <parse_source Source>
    constexpr auto operator()(Source& src) const {
        return src.consume();
    }
};

struct satisfy_fn {
    template <parse_source Source>
    constexpr auto prepare(
        char const* message, auto&& func) const requires parse_trait<decltype(func),
        Source> && std::predicate<decltype(func), parse_source_input_value_t<Source>>
    {
        using ret_t = result<parse_source_input_value_t<Source>,
            parse_source_error_t<Source>>;
        return MakePreparedSourceParser<Source>(make_source_result_visitor<Source>(
            [=](parse_source_input_value_t<Source> const& val) {
                return std::invoke((decltype(func))func, val)
                ? ret_t{val}
                : ret_t{parse_source_error_t<Source>{message, error_status_t::fail}};
            }
        ));
    }
    template <class Predic>
    struct SatisfyImpl {
        constexpr SatisfyImpl(char const* name, Predic const& predic)
        : name{name}, predic{predic} {}
        constexpr SatisfyImpl(char const* name, Predic&& predic)
        : name{name}, predic{std::forward<Predic>(predic)} {}

        template <parse_source Source>
        requires parse_trait<Predic, Source> && std::predicate<Predic, parse_source_input_value_t<Source>>
        constexpr auto prepare() const {
            using ret_t = result<parse_source_input_value_t<Source>,
                parse_source_error_t<Source>>;
            return MakePreparedSourceParser<Source>(make_source_result_visitor<
                Source>([name=this->name,predic=this->predic](parse_source_input_value_t<Source> const& val) {
                return std::invoke(predic, val)
                ? ret_t{val}
                : ret_t{parse_source_error_t<Source>{name, error_status_t::fail}};
            }));
        }
        template <parse_source Source>
        requires parse_trait<Predic, Source> && std::predicate<Predic, parse_source_input_value_t<Source>>
        constexpr auto operator()(Source& source) const {
            return prepare<Source>()(source);
        }

      private:
        char const* name;
        Predic predic;
    };
    template <class Func>
    constexpr auto operator()(char const* message, Func&& func) const {
        return SatisfyImpl(message, std::forward<Func>(func));
        #if 0
        return [this, message, func = std::forward<Func>(func)]<parse_source Source>(
            Source & src) requires parse_trait<Func, Source> && std::predicate<Func,
            parse_source_input_value_t<Source>> {
            return this->prepare<Source>(message, func)(src);
        };
        #endif
    }
};

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
                Init> &&(parser_with<ParserT, Source> && ...) {
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