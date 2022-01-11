#ifndef CPP_UTILS_FIXED_STRING_HPP
#define CPP_UTILS_FIXED_STRING_HPP

#include <algorithm>

// see https://stackoverflow.com/q/2033110/14290180

namespace ml {

template<std::size_t N>
struct fixed_string
{
  consteval fixed_string(const char (&str)[N])
  {
      std::copy_n(str, N, value);
  }
  
  consteval operator const char *() const noexcept { return value; }

  char value[N];
};

} // namespace ml

#endif