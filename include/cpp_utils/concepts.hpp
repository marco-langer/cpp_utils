#ifndef CPP_UTILS_CONCEPTS_HPP
#define CPP_UTILS_CONCEPTS_HPP

#include "traits.hpp"

namespace ml {

template <typename T>
concept standard_integer = is_standard_integer_v<T>;

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template <typename T>
concept standard_arithmetic = is_standard_arithmetic_v<T>;

} // namespace ml

#endif