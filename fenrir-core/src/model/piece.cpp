#include "fenrir-core/model/piece.hpp"

#include <iostream>

namespace fenrir::core {

auto operator<<(std::ostream &stream, Piece p) -> std::ostream & {
  return stream << " PpNnBbRrQqKk"[p];
}

void Piece::dump() const { std::cerr << *this << std::endl; }

} // namespace fenrir::core