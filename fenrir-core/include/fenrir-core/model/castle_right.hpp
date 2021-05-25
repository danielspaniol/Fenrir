#pragma once

#include "fenrir-core/prelude.hpp"

#include <ostream>

namespace fenrir::core {

struct CastleRight {
  constexpr static usize KINGMASK = 0b01;
  constexpr static usize QUEENMASK = 0b10;

  enum T : u8 { NONE, KINGSIDE, QUEENSIDE, BOTH };

  constexpr CastleRight() : m_data{NONE} {}
  constexpr CastleRight(T t) : m_data{t} {}
  constexpr operator T() const { return m_data; }

  constexpr auto can_kingside_castle() const -> bool { return m_data % 2 == 1; }
  constexpr auto can_queenside_castle() const -> bool { return m_data > 1; }

  constexpr auto with_can_kingside_castle(bool val) const -> CastleRight {
    return val ? T{static_cast<u8>(m_data | KINGMASK)}
               : T{static_cast<u8>(m_data & ~KINGMASK)};
  }
  constexpr auto with_can_queenside_castle(bool val) const -> CastleRight {
    return val ? T{static_cast<u8>(m_data | QUEENMASK)}
               : T{static_cast<u8>(m_data & ~QUEENMASK)};
  }

  friend auto operator<<(std::ostream &stream, CastleRight r) -> std::ostream &;
  auto dump() const -> void;

private:
  T m_data;
};

} // namespace fenrir::core