#include <cpp_utils/core.hpp>

#include <boost/ut/ut.hpp>

#include <type_traits>

using namespace ml::string;
using namespace boost::ut;
using namespace std::string_literals;
using namespace std::string_view_literals;

suite strings = [] {
  "view_from_u8"_test = [] {
    constexpr auto u8_literal{u8"'Hello World' in chinese: 世界您好"};
    expect(view_from_u8(u8_literal) == reinterpret_cast<const char *>(u8_literal));

    constexpr char8_t u8_buffer[]{u8"'Hello World' in chinese: 世界您好"};
    expect(view_from_u8(u8_buffer) == reinterpret_cast<const char *>(u8_buffer));

    constexpr std::u8string_view utf8sv{u8"'Hello World' in chinese: 世界您好"sv};
    expect(view_from_u8(utf8sv) == reinterpret_cast<const char *>(utf8sv.data()));
    expect(view_from_u8(u8"'Hello World' in chinese: 世界您好"sv) ==
      reinterpret_cast<const char *>(utf8sv.data()));

    const std::u8string utf8str{u8"'Hello World' in chinese: 世界您好"s};
    expect(view_from_u8(utf8str) == reinterpret_cast<const char *>(utf8str.c_str()));
  };

  "from_u8"_test = [] {
    constexpr auto u8_literal = u8"'Hello World' in chinese: 世界您好";
    const std::u8string str1{u8_literal};
    expect(from_u8(str1) == view_from_u8(u8_literal));
    expect(from_u8(u8_literal) == view_from_u8(u8_literal));
    expect(std::is_same_v<std::string, decltype(from_u8(std::declval<std::u8string>()))>);
    expect(std::is_same_v<std::string, decltype(from_u8(std::declval<std::u8string&>()))>);
  };
};
