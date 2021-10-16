#ifndef CPP_UTILS_CONCEPTS_HPP_INCLUDE
#define CPP_UTILS_CONCEPTS_HPP_INCLUDE

#include <cpp_utils/traits.hpp>

#include <concepts>
#include <iterator>

namespace ml {

template <typename T>
concept standard_integer = is_standard_integer_v<T>;

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template <typename T>
concept standard_arithmetic = is_standard_arithmetic_v<T>;

template <class ContainerT>
concept container = requires(ContainerT c) {
  requires std::regular<ContainerT>;
  requires std::swappable<ContainerT>;
  requires std::destructible<typename ContainerT::value_type>;
  requires std::same_as<typename ContainerT::reference, typename ContainerT::value_type &>;
  requires std::same_as<typename ContainerT::const_reference, const typename ContainerT::value_type &>;
  requires std::forward_iterator<typename ContainerT::iterator>;
  requires std::forward_iterator<typename ContainerT::const_iterator>;
  requires std::signed_integral<typename ContainerT::difference_type>;
  requires std::same_as<
    typename ContainerT::difference_type,
    typename std::iterator_traits<typename ContainerT::iterator>::difference_type
  >;
  requires std::same_as<
    typename ContainerT::difference_type,
    typename std::iterator_traits<typename ContainerT::const_iterator>::difference_type
  >;
  { c.begin() } -> std::same_as<typename ContainerT::iterator>;
  { c.end() } -> std::same_as<typename ContainerT::iterator>;
  { c.cbegin() } -> std::same_as<typename ContainerT::const_iterator>;
  { c.cend() } -> std::same_as<typename ContainerT::const_iterator>;
  { c.size() } -> std::same_as<typename ContainerT::size_type>;
  { c.max_size() } -> std::same_as<typename ContainerT::size_type>;
  { c.empty() } -> std::same_as<bool>;
};

} // namespace ml

#endif