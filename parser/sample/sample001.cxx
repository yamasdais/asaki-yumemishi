#include <iostream>

#include <string_view>
#include <parser.hpp>

template <class... T>
struct TypeTracer;

constexpr static auto sv = std::string_view("abcdef");

namespace dp = parsey;

#if 0
template <dp::parser_facade Facade>
struct printResult {
    using value_type = dp::source_value_t<dp::facade_source_t<Facade>>;
    void operator()(value_type const ch) const { std::cout << ch << "\n"; }
    void operator()(std::basic_string<value_type> const& str) const {
        std::cout << str << "\n";
    }
    void operator()(dp::facade_error_t<Facade> const& err) const {
        std::cout << err.message << "\n";
    }
};

// template <class Source, dp::parser<Source> Parser>
template <dp::parser_facade Facade>
void parseTest(dp::parser<Facade> auto const& parser,
    dp::facade_source_t<Facade> const& source) {
    auto itr = std::ranges::begin(source);
    auto result = parser(source, itr);
    // auto success = dp::parser_success(result);
    // TypeTracer<dp::parser_value_t<decltype(result)>> x;
    // std::cout << "parser success: " << success << std::endl;
    std::visit(printResult<Facade>{}, result);
}

template <dp::parser_facade Facade>
constexpr auto to_parser_result(auto value) {
    return dp::parser_result_t<decltype(value), Facade>{value};
}

#endif
template <dp::parse_result Result>
struct print_result {
    std::string operator()(dp::parse_result_value_t<Result> const& val) const {
        return {val};
    }
    std::string operator()(dp::parse_result_error_t<Result> const& err) const {
        return {err.message};
    }
};

void test_error() {
    static_assert(
        dp::parse_error<dp::default_parser_error>, "parser_error concept");
    constexpr dp::default_parser_error err{"test error"};
    std::cout << err << std::endl;
}

void test_paramType() {
    std::tuple<int const, std::string, double> ttup;
    using ttup_t = decltype(ttup);
    using t0 = typename dp::detail::GetParamTypeImpl<0, ttup_t>::type;
    using t1 = dp::detail::GetParametricType<ttup_t, 1>;
    using t2 = dp::detail::GetParametricType<ttup_t, 2>;
    static_assert(std::same_as<t0, int const>);
    static_assert(std::same_as<t1, std::string>);
    static_assert(std::same_as<t2, double>);
    static_assert(
        std::same_as<dp::detail::GetParametricType<std::string, 0>, char>);
}

void test_locator() {
    constexpr dp::index_locator<char> c_locator;
    // TypeTracer<lvt> x;
    auto loc = c_locator;
    using lvt = dp::locator_value_t<decltype(loc)>;
    static_assert(std::same_as<lvt, char>);
    auto is_printable = dp::printable_locator<decltype(loc)>;
    loc.increment('a');
    static_assert(dp::locator<decltype(loc), char>, "locator");
    std::cout << "locator index: " << loc << std::endl;
    std::cout << "next: " << loc.next('b') << std::endl;
    std::cout << "is printable: " << is_printable << std::endl;
}

template <template <class> class Trait, class L, class R>
struct CheckIterTraits {
    static_assert(std::same_as<Trait<L>, Trait<R>>);
};
void test_source() {
    using source_t = dp::source<std::string_view>;
    constexpr source_t orig{sv};
    source_t source(orig);
    static_assert(std::is_nothrow_default_constructible_v<source_t>,
        "nothrow default constructible");
    static_assert(std::is_nothrow_copy_constructible_v<source_t>,
        "nothrow copy constructible");
    static_assert(std::is_nothrow_move_constructible_v<source_t>,
        "nothrow move constructible");
    // constexpr source_t def;
    using sv_iter_t = std::ranges::iterator_t<decltype(sv)>;
    // static_assert(std::same_as<std::iter_difference_t<source_t>,
    // std::iter_difference_t<sv_iter_t>>, "iter_difference_t"); using
    // sv_value_t = std::iter_value_t<sv_iter_t>;
    CheckIterTraits<std::iter_difference_t, source_t, sv_iter_t>{};
    static_assert(std::same_as<std::iter_value_t<sv_iter_t>,
                      std::iter_value_t<sv_iter_t>>,
        "iter_value_t");
    // CheckIterTraits<std::iter_reference_t, source_t, sv_iter_t>{};
    // CheckIterTraits<std::iter_rvalue_reference_t, source_t, sv_iter_t>{};
    static_assert(std::forward_iterator<source_t>, "is forward");
    // static_assert(std::same_as<std::iter_value_t<source_t>,
    // std::iter_value_t<std::string_view>>, "iter_value_t");
    std::cout << "Is source: "
              << dp::parse_source<decltype(source)> << std::endl;

    std::cout << "operator**: " << **source << std::endl;
    source_t saved = source;
    ++source;
    ++source;
    std::cout << "operator**(+2): " << **source << std::endl;
    std::cout << "operator**(saved): " << **saved << std::endl;
    std::cout << "source - saved:" << (source - saved) << std::endl;
}

void test_source_result() {
    using source_t = dp::source<std::string_view>;
    source_t const source(sv);
    auto res = *source;

    using res_t = decltype(res);
    static_assert(dp::parse_result<res_t>, "parse result");
    static_assert(std::same_as<dp::parse_result_value_t<res_t>, char>,
        "parse_result_value_t");
    static_assert(std::same_as<dp::parse_result_error_t<res_t>,
                      dp::parse_source_error_t<source_t>>,
        "parse_result_error_t");

    std::cout << *res << std::endl;
}

#if 0
template <dp::parse_facade Facade>
void test_parser_result() {
    auto res = dp::make_parse_result<dp::facade_error_t<Facade>>(42);
    std::cout << "parser result(" << (bool)res << "): " << *res << std::endl;
    auto const err = dp::make_parse_result<int>(
        dp::default_parser_error("test parser result"));
    std::cout << "parser error(" << (bool)err << "): " << err.error()
              << std::endl;
    static_assert(
        dp::parse_result_from<decltype(res), int, dp::facade_source_t<Facade>>,
        "parse result from");
}

void test_facade() {
    using source_t = dp::source<std::string_view>;
    source_t src(sv);
    dp::parser_facade_t<source_t> facade;
    using src_t = dp::facade_source_t<decltype(facade)>;
    using err_t = dp::facade_error_t<decltype(facade)>;
    static_assert(std::same_as<src_t, source_t>, "facade_source_t");
    static_assert(
        std::same_as<err_t, dp::default_parser_error>, "facade_erro_t");

    test_parser_result<decltype(facade)>();
}
#endif

void test_parse() {
    using source_t = dp::source<std::string_view>;
    source_t src(sv);
    source_t saved(sv);

    auto res = dp::pieces::any(src);
    std::cout << "test parse(): " << *res << std::endl;
    std::cout << "test parse(): " << *dp::pieces::any(src);
    while (src) {
        std::cout << ' ' << *dp::pieces::lower(src);
    }
    std::cout << std::endl;

    auto visitor = print_result<decltype(res)>{};
    res = dp::pieces::lower(saved);
    std::cout << "test saved source: " << *res << std::endl;
    res = dp::pieces::letter('b')(saved);
    std::cout << "test saved source: " << res.visit(visitor) << std::endl;
    auto catchar = [](std::string init, char ch) {
        return init.append(1, ch);
    };
    std::cout << "catchar: " << catchar(std::string{"42"}, 'a') << std::endl;
    auto foo = dp::detail::foldAll(catchar, std::string{}, "cat chars",
        dp::pieces::lower, dp::pieces::lower);
    auto resf = foo(saved);
    std::cout << "test foldparser: "
              << resf.visit(print_result<decltype(resf)>{}) << std::endl;

    static_assert(
        std::same_as<
            dp::parser_return_value_t<decltype(dp::pieces::lower), source_t>,
            char>,
        "parser_return_value_t");
    res = dp::pieces::upper(saved);
    std::cout << "test saved source: " << res.visit(visitor) << std::endl;
}

#if 0
template <dp::parser_facade Facade>
void test_parser_result() {
    constexpr auto x0 = to_parser_result<Facade>(42);
    static_assert(dp::parser_success(x0), "parser success: x0");
    static_assert(
        dp::parser_result_with<decltype(x0), Facade>, "parser result: x0");
    static_assert(std::is_same_v<int, dp::parser_value_t<decltype(x0)>>,
        "parser result value: x0");
}

void test_facade() {
    auto v = std::string_view("0123abc");
    using ft = decltype(dp::make_parser_facade(v, dp::default_parser_error{}));
    // using ft = dp::parser_facade_t<decltype(src)>;

    static_assert(dp::parser_facade<ft>, "facade");

    using src_t = dp::facade_source_t<ft>;
    using err_t = dp::facade_error_t<ft>;
    // TypeTracer<src_t, decltype(src)> x;
    static_assert(std::is_same_v<src_t, decltype(v)>, "source type");
    static_assert(
        std::is_same_v<err_t, dp::default_parser_error>, "error type");
    // TypeTracer<snd> x;
    auto itr = std::ranges::begin(v);
    // TypeTracer<decltype(itr), dp::source_iter_t<decltype(src)>&> x;
    auto res = dp::peek<ft>(v, itr);
    test_parser_result<ft>();
}
#endif

int main(int, char**) {
    std::cout << std::boolalpha;

    test_locator();
    test_error();
    test_source();
    test_source_result();
    test_parse();

    return 0;
}
