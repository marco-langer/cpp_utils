#ifndef CPP_UTILS_ALGORITHM_HPP_INCLUDE
#define CPP_UTILS_ALGORITHM_HPP_INCLUDE

#include <type_traits>
#include <utility>

namespace ml {

template <typename Head0, typename Head1, typename... Tail>
constexpr auto
max(
        Head0     && head0,
        Head1     && head1,
        Tail      &&... tail) {

    auto result = head0 < head1 ? head1 : head0;
    auto max_helper = [&result](auto && el) {
      result = (el < result) ? result : el;
    };
    (..., max_helper(std::forward<Tail>(tail)));
    return result;
}

template <typename Head0, typename Head1, typename... Tail>
constexpr auto
min(
        Head0     && head0,
        Head1     && head1,
        Tail      &&... tail) {

    auto result = head0 < head1 ? head0 : head1;
    auto max_helper = [&result](auto && el) {
      result = (el < result) ? el : result;
    };
    (..., max_helper(std::forward<Tail>(tail)));
    return result;
}

} // namespace ml

#endif