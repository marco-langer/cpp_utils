#ifndef CPP_UTILS_OPERATOR_UZ_HPP
#define CPP_UTILS_OPERATOR_UZ_HPP

#include <cstdint>

namespace ml::literals {

#ifdef __cpp_size_t_suffix
[[deprecated("use core language size_t literals instead")]]
#endif
consteval std::size_t
operator ""_uz(unsigned long long value) {
  return static_cast<std::size_t>(value);
}

} // namespace ml::literals

#endif