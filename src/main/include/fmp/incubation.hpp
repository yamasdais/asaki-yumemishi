#if !defined(FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243)
#define FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243

#include <limits>

#include <fmp/primitive.hpp>

namespace fmp {

enum struct order: int {
  LT = -1,
  EQ = 0,
  GT = 1
};

template <typename T>
struct type_size {
  constexpr static size_t size = sizeof(T);
};

struct type_size_min {};
struct type_size_max {};

template <>
struct type_size<type_size_min> {
  constexpr static size_t size = 0ul;
};

template <>
struct type_size<type_size_max> {
  constexpr static size_t size = std::numeric_limits<size_t>::max();
};

}

#endif /* if not defined 'FMP_9A43C54B_27BD_4BB1_9404_B22FE8FBB243' */
