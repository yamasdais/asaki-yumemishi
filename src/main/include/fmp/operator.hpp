#if !defined(FMP_174E3523_C237_4B3A_87D4_E995AF774952)
#define FMP_174E3523_C237_4B3A_87D4_E995AF774952

#include <fmp/primitive.hpp>

#include <fmp/detail/operator_impl.hpp>

namespace fmp {

// monoid
template <template <class> typename Domain,
          template <class, class> typename Unite,
          typename Unity>
struct monoid {
  using unity = Unity;

  template <typename LType, typename RType = unity>
  using unite = typename Unite<Domain<LType>, Domain<RType>>::type;
};


template <typename T0, typename T1>
using is_and_operatable = derived_t<
  decltype(detail::is_and_operatable_impl::check<T0, T1>(nullptr, nullptr))
>;

/**
 * 'and' operator ('and' in latin. because of c++ reserved word)
 */
struct et : public monoid<
  boolean, detail::op_and_impl, std::true_type
>
{
};

/**
 * 'or' operator ('or' in latin. because of c++ reserved word)
 */
struct uel : public monoid<
  boolean, detail::op_or_impl, std::false_type
>
{
};

// tags
struct infinite_upper {
};

struct infinite_lower {
};

/**
 * 'less than' operator
 */
template <typename T0, typename T1>
struct lt : public detail::op_lt_impl<T0, T1> {
};

/**
 * 'equals' operator
 */
template <typename T0, typename T1>
struct eq : public detail::op_eq_impl<T0, T1> {
};

/**
 * 'greater than' operator
 */
template <typename T0, typename T1>
struct gt : public detail::op_gt_impl<T0, T1> {
};

/**
 * compare operator
 */
enum ordering {
  LT = -1,
  EQ = 0,
  GT = 1
};

struct order_lt
  : public std::integral_constant<ordering, ordering::LT> {
};
struct order_eq
  : public std::integral_constant<ordering, ordering::EQ> {
};
struct order_gt
  : public std::integral_constant<ordering, ordering::GT> {
};

template <typename T0, typename T1>
struct compare : public std::conditional_t<
  lt<T0, T1>::value, order_lt,
  std::conditional_t<eq<T0, T1>::value, order_eq,
                     order_gt>
>
{
};

template <template <class> typename Domain,
          typename Arg>
struct lt<Domain<infinite_lower>, Domain<Arg>> : public std::enable_if_t<
  !std::is_same<Arg, infinite_lower>::value,
  std::true_type
  >
{
};

template <template <class> typename Domain>
struct lt<Domain<infinite_lower>, Domain<infinite_lower>> : public std::false_type
{
};

template <template <class> typename Domain,
          typename Arg>
struct lt<Domain<Arg>, Domain<infinite_lower>> : public std::enable_if_t<
  !std::is_same<Arg, infinite_lower>::value,
  std::false_type
  >
{
};


}

#endif /* if not defined 'FMP_174E3523_C237_4B3A_87D4_E995AF774952' */
