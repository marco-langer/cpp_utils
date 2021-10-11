#ifndef CPP_UTILS_STRING_HPP
#define CPP_UTILS_STRING_HPP

#include <string>
#include <string_view>
#include <type_traits>

namespace ml::string {

std::string
from_u8(const std::u8string & str) {
  return std::string{str.cbegin(), str.cend()};
}

/* exclude r-value strings to prevent lifetime issues */
// TODO is this correct for all edge cases?
template <typename T = std::u8string_view>
requires(
  std::is_same_v<T, std::u8string_view>
  || !std::is_rvalue_reference_v<T>
)
std::string_view
view_from_u8(std::u8string_view && value) {
  return std::string_view(reinterpret_cast<const char *>(value.data()), value.size());
}

} // namespace ml::string

#endif
