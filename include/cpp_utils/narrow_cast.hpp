#ifndef CPP_UTILS_NARROW_CAST_HPP
#define CPP_UTILS_NARROW_CAST_HPP

#include <cstdint>
#include <concepts>
#include <exception>
#include <limits>

/* inspired by Microsoft's gls library, but with a different implementation:
 *
 *   - narrow_cast_s   throws on narrowing error
 *   - narrow_cast     throws in debug build on narrowing error, and falls back to 
 *                     unchecked static_cast in release build.
 */

namespace ml {

/* TODO maybe some more meta info here what went wrong?
 * (not trivial, because we need a constexpr int-to-string conversion to use this
 *  exception in consteval context.)
 */
struct narrowing_error : public std::exception
{
    const char* what() const noexcept(true) override { return "narrowing_error"; }
};

template <std::integral T, std::integral U>
[[nodiscard]] constexpr 
T
narrow_cast_s(U u) noexcept(false)
{
  constexpr const bool is_different_signedness =
    (std::numeric_limits<T>::is_signed != std::numeric_limits<U>::is_signed);

  const T t = static_cast<T>(u);
  if (static_cast<U>(t) != u || (is_different_signedness && ((t < T{}) != (u < U{}))))
  {
    throw narrowing_error{};
  }
  return t;
}

template <std::integral T, std::integral U>
[[nodiscard]] constexpr 
T
narrow_cast(U u) noexcept(false)
{
  // TODO maybe a different, dedicated narrowing define ?
#ifndef NDEBUG
  return narrow_cast_s<T>(u);
#else
  return static_cast<T>(u);
#endif
}

} // namespace ml

#endif