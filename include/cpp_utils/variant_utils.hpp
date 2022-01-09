#ifndef CPP_UTILS_VARIANT_HPP
#define CPP_UTILS_VARIANT_HPP

#include <variant>

template <typename... Ts>
struct overload : Ts ...
{
  overload(Ts && ... ts) : Ts{std::forward<Ts>(ts)}... {}
  using Ts::operator()...;
};

template <typename... Ts>
overload(Ts...) -> overload<Ts...>;

#endif