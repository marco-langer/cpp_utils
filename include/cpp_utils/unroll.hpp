#ifndef CPP_UTILS_FIXED_UNROLL_HPP
#define CPP_UTILS_FIXED_UNROLL_HPP

#include <concepts>
#include <utility>

template <std::size_t N>
constexpr void
unroll(std::invocable auto f)
{
  [&f]<std::size_t... Is>(std::index_sequence<Is...>)
  {
    (..., (std::forward<Func>(f)(), void(Is)));
  }(std::make_index_sequence<N>{});
}

#endif