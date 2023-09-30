#ifndef CPP_UTILS_ALGORITHM_HPP_INCLUDE
#define CPP_UTILS_ALGORITHM_HPP_INCLUDE

#include <algorithm>
#include <iterator>
#include <concepts>
#include <ranges>
#include <type_traits>
#include <utility>

namespace ml {

// TODO constraints

template <typename Head0, typename Head1, typename... Tail>
constexpr auto
max(Head0 && head0, Head1 && head1, Tail &&... tail)
{
  auto result = head0 < head1 ? head1 : head0;
  auto max_helper = [&result](auto && el) {
    result = (el < result) ? result : el;
  };
  (..., max_helper(std::forward<Tail>(tail)));
  return result;
}

template <typename Head0, typename Head1, typename... Tail>
constexpr auto
min(Head0 && head0, Head1 && head1, Tail &&... tail)
{
  auto result = head0 < head1 ? head0 : head1;
  auto max_helper = [&result](auto && el) {
    result = (el < result) ? el : result;
  };
  (..., max_helper(std::forward<Tail>(tail)));
  return result;
}

template <typename C>
concept Container = requires
{
    std::ranges::range<C> && !std::ranges::view<C>;
};

template <typename C>
    requires std::random_access_iterator<typename C::iterator>
[[nodiscard]] C set_difference(const C & first, const C & second)
{
    C sortedFirst{ first };
    C sortedSecond{ second };
    std::ranges::sort(sortedFirst);
    std::ranges::sort(sortedSecond);

    C result;
    std::ranges::set_difference(sortedFirst, sortedSecond, std::back_inserter(result));
    return result;
}

template <typename C>
[[nodiscard]] C set_difference(const C & first, const C & second)
{
    C result;
    for (auto && element : first) {
        if (!second.contains(element)) {
            result.insert(element);
        }
    }

    return result;
}

namespace detail {

template <typename C>
auto make_inserter(C & container)
{
    if constexpr (requires { C{}.push_back(typename C::value_type{}); } ) {
        return std::back_inserter(container);
    }
    else {
        return std::inserter(container, container.begin());
    }
}

} // namespace detail


template <typename C>
struct PartitionResult
{
    C first;
    C second;
};


namespace detail {

template <Container Cont, std::indirect_unary_predicate<typename Cont::iterator> Predicate>
[[nodiscard]] PartitionResult<Cont> partition_split_set_difference(const Cont & data, Predicate predicate)
{
    PartitionResult<Cont> result;
    std::ranges::copy_if(data, make_inserter(result.first), std::move(predicate));
    result.second = set_difference(data, result.first);
    return result;
}

template <Container Cont, std::indirect_unary_predicate<std::ranges::iterator_t<Cont>> UnaryPredicate>
[[nodiscard]] auto partition_split_impl(Cont && container, UnaryPredicate predicate)
{
    using Container = std::remove_cvref_t<Cont>;
    PartitionResult<Container> result{ .first = std::forward<Cont>(container) };
    auto partition = std::ranges::partition(
        result.first,
        std::move(predicate)
    );
    result.second = Container(partition.begin(), partition.end());
    result.first.erase(partition.begin(), partition.end());
    return result;
}

} // namespace detail

template
<
    Container Container,
    std::indirect_unary_predicate<std::ranges::iterator_t<Container>> UnaryPredicate
>
[[nodiscard]] auto partition_split(Container && container, UnaryPredicate predicate)
    -> PartitionResult<std::remove_cvref_t<Container>>
{
    if constexpr (std::permutable<std::ranges::iterator_t<std::remove_cvref_t<Container>>>) {
        return detail::partition_split_impl(std::forward<Container>(container), std::move(predicate));
    }
    else {
        return detail::partition_split_set_difference(container, std::move(predicate));
    }
}

} // namespace ml

#endif