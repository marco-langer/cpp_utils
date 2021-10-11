#include <cpp_utils/core.hpp>

#include <boost/ut/ut.hpp>

#include <climits>

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
    constexpr auto u8_literal = u8"'Hello World' in chinese: 世界您好";
    const std::u8string str1{u8_literal};
    expect(from_u8(str1) == reinterpret_cast<const char *>(u8_literal));
    expect(from_u8(u8_literal) == reinterpret_cast<const char *>(u8_literal));
    expect(std::is_same_v<std::string, decltype(from_u8(std::declval<std::u8string>()))>);
    expect(std::is_same_v<std::string, decltype(from_u8(std::declval<std::u8string&>()))>);
  };
};

suite literals = [] {
  using namespace ml::literals;

  "operator_uz"_test = [] {
    constexpr auto value = 42_uz;
    expect(value == 42_u);
    expect(std::is_same_v<std::size_t, decltype(42_uz)>);
  };
};

suite narrow_cast = [] {
  "narrow_cast_s"_test = [] {
    expect(narrow_cast_s<std::uint8_t>(42) == 42_u);
    expect(std::is_same_v<std::uint8_t, decltype(narrow_cast_s<std::uint8_t>(42))>);
  };

  "narrow_cast_s throws"_test = [] {
    expect(throws<narrowing_error>([] {
      [[maybe_unused]] const auto x = narrow_cast_s<int>(std::numeric_limits<std::size_t>::max());
    }));

    expect(throws<narrowing_error>([] {
      [[maybe_unused]] const auto x = narrow_cast_s<std::uint8_t>(std::numeric_limits<std::int16_t>::max());
    }));
  };
};

int main() {}
