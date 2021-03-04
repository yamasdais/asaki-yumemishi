#include <iostream>

#include <parser.hpp>

constexpr static auto sv = std::string_view("abcdef");

namespace dp = dais::parse;

template <class Source>
struct printResult {
    void operator()(typename Source::value_type const ch) const {
        std::cout << ch << "\n";
    }
    void operator()(std::basic_string<typename Source::value_type> const& str) const {
        std::cout << str << "\n";
    }
    void operator()(typename Source::error_type const& err) const {
        std::cout << err.message << "\n";
    }
};

template <class Source, dp::parser<Source> Parser>
void parseTest(Parser const& parser, Source const& source)
{
    auto itr = std::ranges::begin(source);
    auto result = parser(source, itr);
    auto success = dp::parser_success(result);
    //TypeTracer<dp::parser_value_t<decltype(result)>> x;
    std::cout << "parser success: " << success << std::endl;
    std::visit(printResult<Source>{}, result);
}

void test_error() {
    static_assert(dp::parser_error<dp::default_parser_error>, "parser_error concept");
    dp::default_parser_error err{"test error"};
    std::cout << err.message << std::endl;
}

void test_facade() {
    auto v = std::string_view("0123abc");
    auto src = dp::make_source(v);
    using ft = decltype(dp::make_parser_facade(src, dp::default_parser_error{}));
    //using ft = dp::parser_facade_t<decltype(src)>;

    static_assert(dp::parser_facade<ft>, "facade");

    using src_t = dp::facade_source_t<ft>;
    using err_t = dp::facade_error_t<ft>;
    //TypeTracer<src_t, decltype(src)> x;
    static_assert(std::is_same_v<src_t, decltype(src)>, "source type");
    static_assert(std::is_same_v<err_t, dp::default_parser_error>, "error type");
    //TypeTracer<snd> x;
    auto itr = std::ranges::begin(src);
    //TypeTracer<decltype(itr), dp::source_iter_t<decltype(src)>&> x;
    auto res = dp::peek<ft>(src, itr);
    TypeTracer<decltype(res)> x;
}

void test1() {
    auto v = std::string_view("0123abc");
    auto src = dp::make_source(v);
    using itr_t = dp::source_iter_t<decltype(src)>;
    static_assert(std::is_same_v<std::ranges::iterator_t<decltype(v)>, itr_t>);
    using itr_vt = dp::source_value_t<decltype(src)>;
    static_assert(std::is_same_v<std::iter_value_t<decltype(v)>, itr_vt>);
    //TypeTracer<itr_vt> x;
    auto digps = dp::detail::condLift_impl(dp::isDigitAscii, "digit");
    constexpr auto zero = dp::character('0');
    parseTest(digps, src);
    parseTest(dp::lower, src);
    parseTest(zero, src);
}

void test0() {
    //constexpr auto rv = std::ranges::ref_view(sv);
    //constexpr dais::parse::source src{rv};
    constexpr auto src = dp::make_source(sv);
    using source_type = decltype(src);
    auto isRange = std::ranges::forward_range<source_type>;
    std::cout << "isForwardRange: " << isRange << "\n";
    std::cout << "sizeof source: " << sizeof(src) << std::endl;
    //TypeTracer<typename decltype(src)::value_type> x;
    for (auto const ch : src) {
        std::cout << ch << " ";
    }
    std::cout << std::endl;
    auto itr = src.begin();
    constexpr auto citr = src.begin();
    ++itr;
    auto ch1 = src.peek(itr);
    constexpr auto cch1 = src.peek(citr);
    constexpr auto succeeded = source_type::result_success(cch1);
    std::cout << "Success: " << succeeded << ", ch: " << std::get<typename source_type::value_type>(ch1) << std::endl;

    //using rtt = dp::parser_return_type_t<decltype(dp::anyChar), source_type>;
    auto pfc = dp::parse_function<decltype(dp::isDigitAscii), source_type>;
    std::cout << "parse_function: " << pfc << std::endl;
    
    parseTest(dp::anyChar, src);
}

int main(int, char**) {
    std::cout << std::boolalpha;
    test0();
    test1();

    test_error();

    return 0;
}
