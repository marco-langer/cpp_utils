#ifndef CPP_UTILS_TRAITS_HPP_INCLUDE
#define CPP_UTILS_TRAITS_HPP_INCLUDE

#include <type_traits>

namespace ml {

template <bool B, typename T = void>
using disable_if = std::enable_if<!B, T>;

template <bool B, typename T = void>
using disable_if_t = typename disable_if<B, T>::type;

// see CppCon 2017 Arthur O'Dwyer SFINAE talk
template <bool B>
using bool_if_t = std::enable_if_t<B, bool>;

// see P1830
template <typename... T>
inline constexpr bool dependent_false = false;

template <typename T, typename ... Ts>
inline constexpr bool is_one_of_v = (... || std::is_same_v<T, Ts>);

template <typename T>
inline constexpr bool is_signed_integer_v = is_one_of_v<
  std::remove_cv_t<T>,
  signed char, signed short, signed, signed long, signed long long
>;

template <typename T>
inline constexpr bool is_unsigned_integer_v = is_one_of_v<
  std::remove_cv_t<T>,
  unsigned char, unsigned short, unsigned, unsigned long, unsigned long long
>;

template <typename T>
inline constexpr bool is_standard_integer_v =
  is_signed_integer_v<T> || is_unsigned_integer_v<T>;

template <typename T>
inline constexpr bool is_standard_arithmetic_v =
  is_standard_integer_v<T> || std::is_floating_point_v<T>;

template <typename T>
inline constexpr bool is_void_v = std::is_same_v<T, void>;

} // namespace ml

#endif
