#include "include/traits.hpp"

int main() {
  static_assert(!cppu::always_false_v<void>);

  static_assert(cppu::is_standard_integer_v<const int>);
  static_assert(!cppu::is_standard_integer_v<float>);

  return 0;
}
