#include <cpp_utils/core.hpp>

#include <boost/ut/ut.hpp>

using namespace ml;
using namespace ml::integer_literals;
using namespace boost::ut;

suite integer_literals = [] {

  "operator_uz"_test = [] {
    constexpr auto value{42_uz};
    expect(value == 42_u);
    expect(std::is_same_v<std::size_t, decltype(42_uz)>);
  };

  "operator_z"_test = [] {
    constexpr auto value{42_z};
    expect(value == 42_i);
    expect(std::is_same_v<std::ptrdiff_t, decltype(42_z)>);
  };

  "operator_ui8"_test = [] {
    constexpr auto value{42_ui8};
    expect(value == 42_u);
    expect(std::is_same_v<std::uint8_t, decltype(42_ui8)>);
  };

  "operator_ui16"_test = [] {
    constexpr auto value{42_ui16};
    expect(value == 42_i);
    expect(std::is_same_v<std::uint16_t, decltype(42_ui16)>);
  };
};