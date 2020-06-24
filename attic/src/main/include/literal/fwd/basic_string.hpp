#if !defined(LITERAL_FA3FD9CE_BA2A_45BC_B1B7_DACA0864BBAA)
#define LITERAL_FA3FD9CE_BA2A_45BC_B1B7_DACA0864BBAA

#include <boost/hana/config.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/to.hpp>

BOOST_HANA_NAMESPACE_BEGIN

template <typename CharT, CharT ...s>
struct basic_string;

template <typename CharT, CharT c>
using basic_char_ = integral_constant<CharT, c>;

template <typename CharT, CharT c>
constexpr basic_char_<CharT, c> basic_char_c{};


template <typename CharT>
struct basic_string_tag { };

template <typename CharT>
constexpr auto make_basic_string = make<basic_string_tag<CharT>>;

template <typename CharT>
constexpr auto to_basic_string = to<basic_string_tag<CharT>>;

template <typename CharT, CharT ...s>
constexpr basic_string<CharT, s...> basic_string_c{};

#ifdef BOOST_HANA_CONFIG_ENABLE_STRING_UDL
namespace literals {
template <typename CharT, CharT ...s>
constexpr auto operator"" _s();

}

#endif

BOOST_HANA_NAMESPACE_END

#endif /* if not defined 'LITERAL_FA3FD9CE_BA2A_45BC_B1B7_DACA0864BBAA' */
