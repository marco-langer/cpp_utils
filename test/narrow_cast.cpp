#include <cpp_utils/core.hpp>

#include <boost/ut/ut.hpp>

#include <limits>
#include <type_traits>

using namespace ml;
using namespace boost::ut;

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