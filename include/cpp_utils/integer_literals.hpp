#ifndef CPP_UTILS_INTEGER_LITERALS_HPP_INCLUDE
#define CPP_UTILS_INTEGER_LITERALS_HPP_INCLUDE

#include <cstdint>

namespace ml::integer_literals {

#ifdef __cpp_size_t_suffix
[[deprecated("use core language size_t literals instead")]]
#endif
consteval std::size_t
operator ""_uz(unsigned long long value) {
  return static_cast<std::size_t>(value);
}

#ifdef __cpp_size_t_suffix
[[deprecated("use core language ptrdiff_t literals instead")]]
#endif
consteval std::ptrdiff_t
operator ""_z(unsigned long long value) {
  return static_cast<std::ptrdiff_t>(value);
}

consteval std::uint8_t
operator ""_ui8(unsigned long long value) {
  return static_cast<std::uint8_t>(value);
}

consteval std::uint16_t
operator ""_ui16(unsigned long long value) {
  return static_cast<std::uint8_t>(value);
}

// Note: signed integer literals with a rank lower than int are not possible due to integer promotion

} // namespace ml::integer_literals

#endif