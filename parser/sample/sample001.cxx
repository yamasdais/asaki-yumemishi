#include <iostream>

#include <parser.hpp>

constexpr static auto sv = std::string_view("abcdef");

namespace dp = dais::parse;

template <dp::parser_facade Facade>
struct printResult {
    using value_type = dp::source_value_t<dp::facade_source_t<Facade>>;
    void operator()(value_type const ch) const {
        std::cout << ch << "\n";
    }
    void operator()(std::basic_string<value_type> const& str) const {
        std::cout << str << "\n";
    }
    void operator()(dp::facade_error_t<Facade> const& err) const {
        std::cout << err.message << "\n";
    }
};

//template <class Source, dp::parser<Source> Parser>
template <dp::parser_facade Facade>
void parseTest(dp::parser<Facade> auto const& parser, dp::facade_source_t<Facade> const& source)
{
    auto itr = std::ranges::begin(source);
    auto result = parser(source, itr);
    //auto success = dp::parser_success(result);
    //TypeTracer<dp::parser_value_t<decltype(result)>> x;
    //std::cout << "parser success: " << success << std::endl;
    std::visit(printResult<Facade>{}, result);
}

void test_error() {
    static_assert(dp::parser_error<dp::default_parser_error>, "parser_error concept");
    dp::default_parser_error err{"test error"};
    std::cout << err.message << std::endl;
}

template <dp::parser_facade Facade>
constexpr auto to_parser_result(auto value) {
    return dp::parser_result_t<decltype(value), Facade>{value};
}

template <dp::parser_facade Facade>
void test_parser_result() {
    constexpr auto x0 = to_parser_result<Facade>(42);
    static_assert(dp::parser_success(x0), "parser success: x0");
    static_assert(dp::parser_result_with<decltype(x0), Facade>, "parser result: x0");
    static_assert(std::is_same_v<int, dp::parser_value_t<decltype(x0)>>, "parser result value: x0");
}

void test_facade() {
    auto v = std::string_view("0123abc");
    using ft = decltype(dp::make_parser_facade(v, dp::default_parser_error{}));
    //using ft = dp::parser_facade_t<decltype(src)>;

    static_assert(dp::parser_facade<ft>, "facade");

    using src_t = dp::facade_source_t<ft>;
    using err_t = dp::facade_error_t<ft>;
    //TypeTracer<src_t, decltype(src)> x;
    static_assert(std::is_same_v<src_t, decltype(v)>, "source type");
    static_assert(std::is_same_v<err_t, dp::default_parser_error>, "error type");
    //TypeTracer<snd> x;
    auto itr = std::ranges::begin(v);
    //TypeTracer<decltype(itr), dp::source_iter_t<decltype(src)>&> x;
    auto res = dp::peek<ft>(v, itr);
    test_parser_result<ft>();
}


int main(int, char**) {
    std::cout << std::boolalpha;

    test_error();
    test_facade();

    return 0;
}
