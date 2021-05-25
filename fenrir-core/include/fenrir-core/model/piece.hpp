#pragma once

#include "fenrir-core/model/color.hpp"
#include "fenrir-core/prelude.hpp"

#include <optional>
#include <ostream>

namespace fenrir::core {

struct Piece {
  enum T : u8 {
    EMPTY,
    WHITE_PAWN,
    BLACK_PAWN,
    WHITE_KNIGHT,
    BLACK_KNIGHT,
    WHITE_BISHOP,
    BLACK_BISHOP,
    WHITE_ROOK,
    BLACK_ROOK,
    WHITE_QUEEN,
    BLACK_QUEEN,
    WHITE_KING,
    BLACK_KING
  };

  constexpr Piece(T t) : m_data{t} {}
  constexpr operator T() const { return m_data; }

  constexpr auto color() const -> std::optional<Color> {
    if (m_data == EMPTY) {
      return {};
    }
    return Color::T{static_cast<u8>(m_data % 2)};
  }

  friend auto operator<<(std::ostream &stream, Piece p) -> std::ostream &;
  void dump() const;

private:
  T m_data;
};

} // namespace fenrir::core