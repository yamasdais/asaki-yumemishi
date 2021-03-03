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
    auto itr = source.begin();
    auto result = parser(source, itr);
    auto success = dp::parser_success(result);
    //TypeTracer<dp::parser_value_t<decltype(result)>> x;
    std::cout << "parser success: " << success << std::endl;
    std::visit(printResult<Source>{}, result);
}

void test1() {
    auto v = std::string_view("0123abc");
    auto src = dp::make_source(v);
    auto digps = dp::detail::condLift_impl(dp::isDigitAscii, "digit");
    //TypeTracer<decltype(digps)> x;
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

    return 0;
}
