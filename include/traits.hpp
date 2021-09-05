#ifndef CPP_UTILS_TRAITS_HPP
#define CPP_UTILS_TRAITS_HPP

#include <type_traits>

namespace cppu {

template <typename T, bool B>
using disable_if = std::enable_if<!B, T>;

template <typename T, bool B>
using disable_if_t = typename disable_if<T, B>::type;

template <typename T>
struct always_false : std::false_type {};

template <typename T>
inline constexpr bool always_false_v = always_false<T>::value;

template <typename T, typename ... Ts>
inline constexpr bool is_any_of_v = (... || std::is_same_v<T, Ts>);

template <typename T>
inline constexpr bool is_signed_integer_v = is_any_of_v<
  std::remove_cv_t<T>,
  signed char, signed short, signed, signed long, signed long long
>;

template <typename T>
inline constexpr bool is_unsigned_integer_v = is_any_of_v<
  std::remove_cv_t<T>,
  unsigned char, unsigned short, unsigned, unsigned long, unsigned long long
>;

template <typename T>
inline constexpr bool is_standard_integer_v =
  is_signed_integer_v<T> || is_unsigned_integer_v<T>;

template <typename T>
inline constexpr bool is_standard_arithmetic_v =
  is_standard_integer_v<T> || std::is_floating_point_v<T>;

}

#endif
