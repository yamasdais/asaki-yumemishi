#if !defined(FMP_0C1960E6_F598_4F31_B57A_FEF339122B20)
#define FMP_0C1960E6_F598_4F31_B57A_FEF339122B20

#if defined(__cpp_nested_namespace_definitions)
namespace fmp::detail {
#else
namespace fmp { namespace detail {
#endif

template <typename... T>
struct head_impl;

template <typename Head, typename... Tail>
struct head_impl<Head, Tail...> {
  using apply = Head;
  template <template <class...> typename Holder>
  using tail = Holder<Tail...>;
};

template <>
struct head_impl<> {
  using apply = nil_type;
};

#if defined(__cpp_nested_namespace_definitions)
} /* namespace fmp::detail */
#else
} /* namespace detail */ } /* namespace fmp */
#endif

#endif /* if not defined 'FMP_0C1960E6_F598_4F31_B57A_FEF339122B20' */
