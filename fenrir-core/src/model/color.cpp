#include "fenrir-core/model/color.hpp"

#include <iostream>

namespace fenrir::core {

auto operator<<(std::ostream &stream, Color c) -> std::ostream & {
  static const cstr STR[] = {"black", "white"};
  return stream << STR[c];
}

void Color::dump() const { std::cerr << *this << std::endl; }

} // namespace fenrir::core