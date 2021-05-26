#include "fenrir-core/model/board.hpp"

#include <iostream>

namespace fenrir::core {

auto operator<<(std::ostream &stream, const Board &board) -> std::ostream & {
  stream << board.active_color() << " to move\n";
  stream << "White castle rights: " << board.m_meta.white << '\n';
  stream << "Black castle rights: " << board.m_meta.black << '\n';
  stream << "Move: " << board.fullmove_counter()
         << "; Halfmove: " << board.halfmove_clock() << '\n';

  stream << '\n';
  Coord::foreach ([&stream, &board](auto c) {
    stream << board[c];
    if (c.rank() == Coord::RANK_ON_BOARD_CNT - 1) {
      stream << '\n';
    }
  });

  return stream;
}

auto Board::dump() const -> void { std::cerr << *this << std::endl; }

} // namespace fenrir::core