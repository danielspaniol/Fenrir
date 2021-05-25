#include "fenrir-core/model/coord.hpp"

#include <iostream>

namespace fenrir::core {

auto Coord::foreach (const std::function<void(Coord)> fn) -> void {
  for (u8 i = 0; i < Coord::CNT; ++i) {
    // If the coordinate gets invalid, the 4th bit is set.
    // To jump to the next valid coord, we need to add 0b1000.
    //  0b00000000 (valid)    +1
    //  ...
    //  0b00000111 (valid)    +1
    //  0b00001000 (invalid)  +8
    //  0b00010000 (valid)    +1
    //  ...
    //  0b00010111 (valid)    +1
    //  0b00011000 (invalid)  +8
    //  0b00100000 (valid)    +1
    //  ...
    if ((i & MASK) != 0) {
      i += 0x08;
    }

    fn(Coord::T{i});
  }
}

auto operator<<(std::ostream &stream, Coord c) -> std::ostream & {
  return stream << (char)c.file() + 'A' << (char)c.rank() + '1';
}

void Coord::dump() const { std::cerr << *this << std::endl; }

} // namespace fenrir::core