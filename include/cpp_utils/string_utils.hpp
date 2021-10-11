#ifndef CPP_UTILS_STRING_HPP
#define CPP_UTILS_STRING_HPP

#include <string>

namespace ml::string {

std::string
from_u8(const std::u8string & str) {
  return std::string(str.cbegin(), str.cend());
}

} // namespace ml::string

#endif