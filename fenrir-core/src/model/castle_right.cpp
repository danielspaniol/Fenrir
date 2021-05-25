#include "fenrir-core/model/castle_right.hpp"

#include <iostream>

namespace fenrir::core {

auto operator<<(std::ostream &stream, CastleRight r) -> std::ostream & {
  static const cstr STR[] = {"none", "kingside", "queenside", "both"};
  return stream << STR[r];
}

auto CastleRight::dump() const -> void { std::cerr << *this << std::endl; }

} // namespace fenrir::core