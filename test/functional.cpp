#include <cpp_utils/core.hpp>

#include <boost/ut/ut.hpp>

#include <algorithm>
#include <vector>

using namespace ml;
using namespace boost::ut;

suite functional = [] {
  "in_range"_test = [] {
    auto predicate = in_range(3, 42);
    expect(predicate(11));
    expect(!predicate(1));
    expect(!predicate(50));
    expect(!predicate(3));
    expect(!predicate(42));
  };

  "in_range collection true"_test = [] {
    std::vector<double> vec{4.0, 11.2, 27.3};
    expect(std::all_of(vec.cbegin(), vec.cend(), in_range<double>{3.14, 42.0}));
  };

  "in_range collection false"_test = [] {
    std::vector<double> vec{4.0, 111.2, 27.3};
    expect(!std::all_of(vec.cbegin(), vec.cend(), in_range<double>{3.14, 42.0}));
  };

  "in_range_min_inclusive"_test = [] {
    auto predicate = in_range_min_inclusive(3, 42);
    expect(predicate(11));
    expect(!predicate(1));
    expect(!predicate(50));
    expect(predicate(3));
    expect(!predicate(42));
  };

  "in_range_min_inclusive collection true"_test = [] {
    std::vector<double> vec{3.14, 11.2, 27.3};
    expect(std::all_of(vec.cbegin(), vec.cend(), in_range_min_inclusive<double>{3.14, 42.0}));
  };

  "in_range_min_inclusive collection false"_test = [] {
    std::vector<double> vec{4.0, 111.2, 27.3};
    expect(!std::all_of(vec.cbegin(), vec.cend(), in_range_min_inclusive<double>{3.14, 42.0}));
  };
};