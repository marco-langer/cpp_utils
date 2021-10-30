#ifndef CPP_UTILS_STRING_HPP_INCLUDE
#define CPP_UTILS_STRING_HPP_INCLUDE

#include <string>
#include <string_view>
#include <type_traits>

namespace ml::string {

template <typename... Ts>
concept string_like = (... && std::is_constructible_v<std::string_view, Ts>);

inline std::string
from_u8(const std::u8string & str) {
  return std::string{str.cbegin(), str.cend()};
}

/* exclude r-value strings to prevent lifetime issues */
// TODO (1) is this correct for all edge cases ?
// TODO (2) can we simplify this ?
template <typename T>
requires(
  std::is_same_v<std::remove_cvref_t<T>, std::u8string_view>
  || !std::is_rvalue_reference_v<T&&>
)
std::string_view
view_from_u8(T && value) {
  if constexpr (std::is_same_v<std::remove_cvref_t<T>, std::u8string_view>) {
    return std::string_view{reinterpret_cast<const char *>(value.data()), value.size()};
  } else if constexpr (std::is_same_v<std::remove_cvref_t<T>, std::u8string>) {
    return std::string_view{reinterpret_cast<const char *>(value.c_str()), value.size()};
  } else {
    return std::string_view{reinterpret_cast<const char *>(value)};
  }
}

template <string_like... StringLike>
requires(sizeof...(StringLike) > 1)
std::string
concatenate(StringLike && ... args) {
  std::size_t length{};
  auto calc_length = [&](std::string_view el) { length += el.size(); };
  (..., calc_length(args));

  std::string result;
  result.reserve(length);
  auto append = [&](const auto & el) { result.append(el); };
  (..., append(args));

  return result;
}

} // namespace ml::string

#endif
