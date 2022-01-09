#ifndef CPP_UTILS_STRING_HPP_INCLUDE
#define CPP_UTILS_STRING_HPP_INCLUDE

#include <cpp_utils/traits.hpp>

#include <string>
#include <string_view>

namespace ml::string {

template <typename T>
concept char_like = std::is_constructible_v<std::string_view, T>;

template <typename T>
concept char8_like = std::is_constructible_v<std::u8string_view, T>;

[[nodiscard]] inline std::string
from_u8(const std::u8string & str)
{
  return std::string{std::cbegin(str), std::cend(str)};
}

template <char8_like Char8Like>
requires(
  /* exclude r-value std::u8string to prevent lifetime issues for return value */
  std::is_same_v<std::remove_cvref_t<Char8Like>, std::u8string_view>
  || !std::is_rvalue_reference_v<Char8Like&&>
)
[[nodiscard]] std::string_view
view_from_u8(Char8Like && value)
{
  if constexpr (is_one_of_v<std::remove_cvref_t<Char8Like>, std::u8string_view, std::u8string>) {
    return std::string_view{reinterpret_cast<const char *>(value.data()), value.size()};
  } else {
    return std::string_view{reinterpret_cast<const char *>(value)};
  }
}

template <typename T, typename = void>
struct is_sizeable : std::false_type {};

template <typename T>
struct is_sizeable<T, std::void_t<decltype(std::size(std::declval<T>()))>> : std::true_type {};

template <typename T>
inline constexpr bool is_sizeable_v = is_sizeable<T>::value;

[[nodiscard]] std::string
concatenate(char_like auto && ... args)
{
  std::size_t length{};
  auto calc_length = [&]<char_like T>(T && el) { 
    if constexpr (is_sizeable_v<T>) {
      length += std::size(el);
    } else {
      length += std::string_view{el}.size();
    }
  };
  (..., calc_length(args));

  std::string result;
  result.reserve(length);
  auto append = [&](const auto & el) { result.append(el); };
  (..., append(args));

  return result;
}

} // namespace ml::string

#endif
