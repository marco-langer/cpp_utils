#include <cpp_utils/core.hpp>

#include <boost/ut/ut.hpp>

using namespace ml;
using namespace boost::ut;

suite algorithm = [] {
  "max"_test = [] {
    expect(max(3.14, -42.0, 123.45, 42.0) == 123.45_d);
  };

  "min"_test = [] {
    expect(min(3.14, -42.0, 123.45, 42.0) == -42.0_d);
  };
};