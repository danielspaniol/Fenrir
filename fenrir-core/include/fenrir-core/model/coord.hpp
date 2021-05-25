#pragma once

#include "fenrir-core/prelude.hpp"

#include <functional>
#include <ostream>

namespace fenrir::core {

using Rank = u8;
using File = u8;

struct CoordDelta {
  constexpr CoordDelta(u8 data) : m_data{data} {}
  constexpr operator u8() const { return m_data; }

  constexpr auto operator+(CoordDelta d) const -> CoordDelta {
    return m_data + d.m_data;
  }
  constexpr auto operator-(CoordDelta d) const -> CoordDelta {
    return m_data - d.m_data;
  }

private:
  u8 m_data;
};

/// \brief 0x88 Coordinates
struct Coord {
  constexpr static usize FILE_CNT = 8;
  constexpr static usize RANK_CNT = 16;
  constexpr static usize CNT = FILE_CNT * RANK_CNT;

  constexpr static usize FILE_ON_BOARD_CNT = 8;
  constexpr static usize RANK_ON_BOARD_CNT = 8;
  constexpr static usize ON_BOARD_CNT = FILE_ON_BOARD_CNT * RANK_ON_BOARD_CNT;

  constexpr static usize RANK_MASK = 0b111;
  constexpr static usize RANK_SHIFT = 0;
  constexpr static usize FILE_MASK = 0b111;
  constexpr static usize FILE_SHIFT = 4;
  constexpr static usize MASK = 0x88; ///< Mask for invalid coordinates

  static auto foreach (const std::function<void(Coord)>) -> void;

  enum T : u8 {
    // clang-format off
    A1 = 0x00, A2, A3, A4, A5, A6, A7, A8,
    B1 = 0x10, B2, B3, B4, B5, B6, B7, B8,
    C1 = 0x20, C2, C3, C4, C5, C6, C7, C8,
    D1 = 0x30, D2, D3, D4, D5, D6, D7, D8,
    E1 = 0x40, E2, E3, E4, E5, E6, E7, E8,
    F1 = 0x50, F2, F3, F4, F5, F6, F7, F8,
    G1 = 0x60, G2, G3, G4, G5, G6, G7, G8,
    H1 = 0x70, H2, H3, H4, H5, H6, H7, H8,
    // clang-format on
  };

  /// \brief Creates an invalid coordinate
  constexpr Coord() : m_data{MASK} {}
  constexpr Coord(T t) : m_data{t} {}
  constexpr operator T() const { return m_data; }

  constexpr auto is_on_board() const -> bool { return (m_data & MASK) == 0; }
  constexpr operator bool() const { return is_on_board(); }

  constexpr auto rank() const -> Rank {
    return (m_data >> RANK_SHIFT) & RANK_MASK;
  }
  constexpr auto file() const -> File {
    return (m_data >> FILE_SHIFT) & FILE_MASK;
  }

  constexpr auto idx() const -> usize { return m_data; }

  constexpr auto operator+(CoordDelta delta) const -> Coord {
    return Coord::T{static_cast<u8>(m_data + delta)};
  }
  constexpr auto operator-(CoordDelta delta) const -> Coord {
    return Coord::T{static_cast<u8>(m_data - delta)};
  }

  constexpr auto operator==(Coord c) const -> bool {
    return m_data == c.m_data;
  }
  constexpr auto operator==(T val) const -> bool { return m_data == val; }
  constexpr auto operator==(int val) const -> bool { return m_data == val; }

  friend auto operator<<(std::ostream &stream, Coord c) -> std::ostream &;
  void dump() const;

private:
  T m_data;
};

constexpr inline auto operator""_rank(unsigned long long val) -> CoordDelta {
  assert(val < Coord::RANK_ON_BOARD_CNT);
  return val;
}
constexpr inline auto operator""_file(unsigned long long val) -> CoordDelta {
  assert(val < Coord::FILE_ON_BOARD_CNT);
  return val * Coord::RANK_CNT;
}

} // namespace fenrir::core