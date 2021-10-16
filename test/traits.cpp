#include <cpp_utils/core.hpp>

#include <boost/ut/ut.hpp>

using namespace ml;
using namespace boost::ut;

suite traits = [] {
  "dependent_false"_test = [] {
    expect(!dependent_false<void>);
  };

  "is_one_of"_test = [] {
    expect(!is_one_of_v<int>);
    expect(!is_one_of_v<int, double, bool>);
    expect(!is_one_of_v<int, double, const volatile int &>);
    expect(is_one_of_v<int, double, int>);
  };

  "is_standard_integer"_test = [] {
    expect(is_standard_integer_v<const int>);
    expect(!is_standard_integer_v<float>);
    expect(!is_standard_integer_v<bool>);
    expect(!is_standard_integer_v<char>);
  };

  "is_standard_arithmetic"_test = [] {
    expect(is_standard_arithmetic_v<const int>);
    expect(is_standard_arithmetic_v<float>);
    expect(!is_standard_arithmetic_v<bool>);
    expect(!is_standard_arithmetic_v<char>);
  };
};