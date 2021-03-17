#include <iostream>

#include <string_view>
#include <parser.hpp>

template <class... T>
struct TypeTracer;

constexpr static auto sv = std::string_view("abcdef");

namespace dp = parsey;

template <dp::parse_result Result>
struct print_result {
    std::string operator()(dp::parse_result_value_t<Result> const& val) const {
        return {val};
    }
    std::string operator()(dp::parse_result_error_t<Result> const& err) const {
        return {err.message};
    }
};

void test_paramType() {
    std::tuple<int const, std::string, double> ttup;
    using ttup_t = decltype(ttup);
    using t0 = typename dp::detail::GetParamTypeImpl<0, ttup_t>::type;
    using t1 = dp::get_tparam_t<ttup_t, 1>;
    using t2 = dp::get_tparam_t<ttup_t, 2>;
    static_assert(std::same_as<t0, int const>);
    static_assert(std::same_as<t1, std::string>);
    static_assert(std::same_as<t2, double>);
    static_assert(
        std::same_as<dp::get_tparam_t<std::string, 0>, char>);
}

template <template <class> class Trait, class L, class R>
struct CheckIterTraits {
    static_assert(std::same_as<Trait<L>, Trait<R>>);
};

void test_accumulator() {
    constexpr auto pfun = [](std::string acc, char v) {
        return std::move(acc.append(1, v));
    };
    constexpr auto pfun0 = [](std::string& acc, char v) {
        acc.append(1, v);
    };
    static_assert(
        std::invocable<decltype(pfun), std::string, char>, "invocable");
    static_assert(
        std::invocable<decltype(pfun0), std::string&, char>, "invocable");
    static_assert(
        std::same_as<std::invoke_result_t<decltype(pfun0), std::string&, char>,
            void>,
        "invoke_result_t");

    auto f = dp::make_accumulator<std::basic_string, char>(pfun0);
    f('a')('b');
    std::cout << "accumulator: " << *f << std::endl;
    auto fmpres = f.fmap<std::string>(std::identity{});
    std::cout << *fmpres << std::endl;
}
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
    std::cout << "test saved source: " << res.fmap(visitor) << std::endl;
    auto catchar = [](std::string init, char ch) {
        return init.append(1, ch);
    };
    std::cout << "catchar: " << catchar(std::string{"42"}, 'a') << std::endl;
    auto foo = dp::detail::foldAll(catchar, std::string{}, "cat chars",
        dp::pieces::lower, dp::pieces::lower);
    auto resf = foo(saved);
    std::cout << "test foldparser: "
              << resf.fmap(print_result<decltype(resf)>{}) << std::endl;

    static_assert(
        std::same_as<
            dp::parser_return_value_t<decltype(dp::pieces::lower), source_t>,
            char>,
        "parser_return_value_t");
    res = dp::pieces::upper(saved);
    std::cout << "test saved source: " << res.fmap(visitor) << std::endl;
}

int main(int, char**) {
    std::cout << std::boolalpha;

    test_accumulator();
    test_parse();

    return 0;
}
