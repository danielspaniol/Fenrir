#pragma once

#include "fenrir-core/model/castle_right.hpp"
#include "fenrir-core/model/color.hpp"
#include "fenrir-core/model/coord.hpp"
#include "fenrir-core/model/piece.hpp"
#include "fenrir-core/prelude.hpp"

#include <array>
#include <ostream>

namespace fenrir::core {

using BoardData = std::array<Piece, Coord::CNT>;

struct BoardMeta {
  constexpr BoardMeta()
      : active_color{}, en_passent{}, white{}, black{}, halfmove_clock{},
        fullmove_counter{1} {}

  Color active_color;
  Coord en_passent;
  CastleRight white;
  CastleRight black;
  u32 halfmove_clock;
  u32 fullmove_counter;
};

struct Board {
  constexpr Board() = default;

  constexpr auto operator[](Coord c) const -> Piece { return m_data[c.idx()]; }
  auto operator[](Coord c) -> Piece & { return m_data[c.idx()]; }

  constexpr auto active_color() const -> Color { return m_meta.active_color; }
  auto set_active_color(Color c) -> void { m_meta.active_color = c; }
  auto flip_active_color() -> void {
    m_meta.active_color = m_meta.active_color.flipped();
  }

  constexpr auto en_passent() const -> Coord { return m_meta.en_passent; }
  auto set_en_passent(Coord c) -> void { m_meta.en_passent = c; }
  auto clear_en_passent() -> void { m_meta.en_passent = {}; }

  constexpr auto can_kingside_castle(Color c) -> bool {
    return c == Color::WHITE ? m_meta.white.can_kingside_castle()
                             : m_meta.black.can_kingside_castle();
  }
  auto set_can_kingside_castle(Color c, bool v) -> void {
    if (c == Color::WHITE) {
      m_meta.white = m_meta.white.with_can_kingside_castle(v);
    } else {
      m_meta.black = m_meta.black.with_can_kingside_castle(v);
    }
  }
  constexpr auto can_queenside_castle(Color c) -> bool {
    return c == Color::WHITE ? m_meta.white.can_queenside_castle()
                             : m_meta.black.can_queenside_castle();
  }
  auto set_can_queenside_castle(Color c, bool v) -> void {
    if (c == Color::WHITE) {
      m_meta.white = m_meta.white.with_can_queenside_castle(v);
    } else {
      m_meta.black = m_meta.black.with_can_queenside_castle(v);
    }
  }

  constexpr auto halfmove_clock() const -> u32 { return m_meta.halfmove_clock; }
  auto set_halfmove_clock(u32 i) -> void { m_meta.halfmove_clock = i; }
  auto inc_halfmove_clock() -> void { ++m_meta.halfmove_clock; }

  constexpr auto fullmove_counter() const -> u32 {
    return m_meta.fullmove_counter;
  }
  auto set_fullmove_counter(u32 i) -> void { m_meta.fullmove_counter = i; }
  auto inc_fullmove_counter() -> void { ++m_meta.fullmove_counter; }

private:
  BoardData m_data;
  BoardMeta m_meta;
};

} // namespace fenrir::core