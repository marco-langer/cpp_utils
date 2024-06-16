#ifndef CPP_UTILS_UTILITY_HPP
#define CPP_UTILS_UTILITY_HPP

#include <utility>

namespace ml {

template <std::size_t I, std::size_t Offset = 0>
auto make_index_sequence()
{
    return []<std::size_t... Is>(std::index_sequence<Is...>)
    {
        return std::index_sequence<Offset + Is...>{};
    }(std::make_index_sequence<I>());
}

} // namespace ml

#endif
