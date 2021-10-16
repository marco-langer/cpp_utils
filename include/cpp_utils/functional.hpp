#ifndef CPP_UTILS_FUNCTIONAL_HPP_INCLUDE
#define CPP_UTILS_FUNCTIONAL_HPP_INCLUDE

#include <concepts>
#include <utility>

namespace ml {

template <std::totally_ordered T>
struct in_range
{
  in_range() = delete;

  in_range(const T & lower_bound, const T & upper_bound)
      : lower_bound_(lower_bound), upper_bound_(upper_bound)
  {}

  in_range(T && lower_bound, T && upper_bound)
      : lower_bound_(std::move(lower_bound)), upper_bound_(std::move(upper_bound))
  {}

  [[nodiscard]] bool
  operator()(const T & el) const
  {
    return el > lower_bound_ && el < upper_bound_;
  }

  T lower_bound_;
  T upper_bound_;
};

template <std::totally_ordered T>
struct in_range_min_inclusive
{
  in_range_min_inclusive() = delete;

  in_range_min_inclusive(const T & lower_bound, const T & upper_bound)
      : lower_bound_(lower_bound), upper_bound_(upper_bound)
  {}

  in_range_min_inclusive(T && lower_bound, T && upper_bound)
      : lower_bound_(std::move(lower_bound)), upper_bound_(std::move(upper_bound))
  {}

  [[nodiscard]] bool
  operator()(const T & el) const
  {
    return el >= lower_bound_ && el < upper_bound_;
  }

  T lower_bound_;
  T upper_bound_;
};


} // namespace ml

#endif
