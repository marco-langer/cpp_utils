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

suite strings = [] {
  using namespace ml::string;

  "from_u8"_test = [] {
    constexpr auto u8_literal = u8"Hello World on chinese: 世界您好";
    const std::u8string str1{u8_literal};
    expect(from_u8(str1) == reinterpret_cast<const char *>(u8_literal));
    expect(from_u8(u8_literal) == reinterpret_cast<const char *>(u8_literal));
    expect(std::is_same_v<std::string, decltype(from_u8(std::declval<std::u8string>()))>);
    expect(std::is_same_v<std::string, decltype(from_u8(std::declval<std::u8string&>()))>);
  };
};

int main() {}
