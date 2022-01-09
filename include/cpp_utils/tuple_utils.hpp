#ifndef CPP_UTILS_TUPLE_HPP_INCLUDE
#define CPP_UTILS_TUPLE_HPP_INCLUDE

#include <tuple>
#include <type_traits>

namespace ml {

template <typename T>
struct is_tuple : std::false_type {};

template <typename... Ts>
struct is_tuple<std::tuple<Ts...>> : std::true_type {};

template <typename T>
inline constexpr bool is_tuple_v = is_tuple<T>::value;

template <typename Tuple, typename Func>
void
tuple_for_each(Tuple && tp, Func && f)
{
  std::apply(
    [&](auto && ... args) {
      (std::forward<Func>(f)(std::forward<decltype(args)>(args)), ...);
    },
    std::forward<Tuple>(tp)
  );
}

} // namespace ml

#endif