#include "fenrir-core/model/board.hpp"
#include "fenrir-core/model/color.hpp"

#include <gtest/gtest.h>

#include <vector>

using namespace fenrir::core;

TEST(BoardMeta, default_ctor) {
  BoardMeta m;

  EXPECT_EQ(m.active_color, Color::WHITE);
  EXPECT_FALSE(Coord(m.en_passent).is_on_board());
  EXPECT_EQ(m.white, CastleRight::NONE);
  EXPECT_EQ(m.black, CastleRight::NONE);
  EXPECT_EQ(m.halfmove_clock, 0);
  EXPECT_EQ(m.fullmove_counter, 1);
}

TEST(Board, default_ctor) {
  Board b;

  Coord::foreach ([&b](auto c) { EXPECT_EQ(b[c], Piece::EMPTY); });
  EXPECT_EQ(b.active_color(), Color::WHITE);
  EXPECT_FALSE(b.en_passent());
  EXPECT_FALSE(b.can_kingside_castle(Color::WHITE));
  EXPECT_FALSE(b.can_kingside_castle(Color::BLACK));
  EXPECT_FALSE(b.can_queenside_castle(Color::WHITE));
  EXPECT_FALSE(b.can_queenside_castle(Color::BLACK));
  EXPECT_EQ(b.halfmove_clock(), 0);
  EXPECT_EQ(b.fullmove_counter(), 1);
}

TEST(Board, operator_index) {
  static Piece PIECES[] = {
      Piece::WHITE_KING, Piece::WHITE_PAWN, Piece::WHITE_KNIGHT,
      Piece::EMPTY,      Piece::EMPTY,      Piece::BLACK_KNIGHT,
      Piece::BLACK_PAWN, Piece::BLACK_KING,
  };

  Board b;
  Coord::foreach ([&b](auto c) { b[c] = PIECES[c.rank()]; });
  Coord::foreach ([&b](auto c) { EXPECT_EQ(b[c], PIECES[c.rank()]); });
}
TEST(Board, operator_index__ForConstObject) {
  static Piece PIECES[] = {
      Piece::WHITE_KING, Piece::WHITE_PAWN, Piece::WHITE_KNIGHT,
      Piece::EMPTY,      Piece::EMPTY,      Piece::BLACK_KNIGHT,
      Piece::BLACK_PAWN, Piece::BLACK_KING,
  };

  Board b;
  Coord::foreach ([&b](auto c) { b[c] = PIECES[c.rank()]; });
  const Board &const_b = b;
  Coord::foreach ([b = const_b](auto c) { EXPECT_EQ(b[c], PIECES[c.rank()]); });
}

TEST(Board, set_active_color) {
  Board b;
  b.set_active_color(Color::BLACK);
  EXPECT_EQ(b.active_color(), Color::BLACK);
  b.set_active_color(Color::WHITE);
  EXPECT_EQ(b.active_color(), Color::WHITE);
}

TEST(Board, flip_active_color) {
  Board b;
  b.set_active_color(Color::BLACK);

  b.flip_active_color();
  EXPECT_EQ(b.active_color(), Color::WHITE);
  b.flip_active_color();
  EXPECT_EQ(b.active_color(), Color::BLACK);
}

TEST(Board, set_en_passent) {
  Board b;

  static std::vector<Coord> COORDS{Coord::A1, Coord::B7, Coord{},  Coord::G8,
                                   Coord::C2, Coord{},   Coord::A1};
  for (auto c : COORDS) {
    b.set_en_passent(c);
    EXPECT_EQ(b.en_passent(), c);
  }
}

TEST(Board, clear_en_passent) {
  Board b;
  b.set_en_passent(Coord::C5);

  b.clear_en_passent();
  EXPECT_FALSE(b.en_passent());
}

TEST(Board, set_can_kingside_castle) {
  Board b;

  b.set_can_kingside_castle(Color::WHITE, true);
  EXPECT_TRUE(b.can_kingside_castle(Color::WHITE));
  b.set_can_kingside_castle(Color::WHITE, false);
  EXPECT_FALSE(b.can_kingside_castle(Color::WHITE));
  b.set_can_kingside_castle(Color::BLACK, true);
  EXPECT_TRUE(b.can_kingside_castle(Color::BLACK));
  b.set_can_kingside_castle(Color::BLACK, false);
  EXPECT_FALSE(b.can_kingside_castle(Color::BLACK));
}

TEST(Board, set_can_queenside_castle) {
  Board b;

  b.set_can_queenside_castle(Color::WHITE, true);
  EXPECT_TRUE(b.can_queenside_castle(Color::WHITE));
  b.set_can_queenside_castle(Color::WHITE, false);
  EXPECT_FALSE(b.can_queenside_castle(Color::WHITE));
  b.set_can_queenside_castle(Color::BLACK, true);
  EXPECT_TRUE(b.can_queenside_castle(Color::BLACK));
  b.set_can_queenside_castle(Color::BLACK, false);
  EXPECT_FALSE(b.can_queenside_castle(Color::BLACK));
}

TEST(Board, set_halfmove_clock) {
  Board b;

  b.set_halfmove_clock(42);
  EXPECT_EQ(b.halfmove_clock(), 42);
  b.set_halfmove_clock(69);
  EXPECT_EQ(b.halfmove_clock(), 69);
}

TEST(Board, inc_halfmove_clock) {
  Board b;
  b.set_halfmove_clock(42);

  b.inc_halfmove_clock();
  EXPECT_EQ(b.halfmove_clock(), 43);
  b.inc_halfmove_clock();
  EXPECT_EQ(b.halfmove_clock(), 44);
}

TEST(Board, set_fullmove_counter) {
  Board b;

  b.set_fullmove_counter(42);
  EXPECT_EQ(b.fullmove_counter(), 42);
  b.set_fullmove_counter(69);
  EXPECT_EQ(b.fullmove_counter(), 69);
}

TEST(Board, inc_fullmove_counter) {
  Board b;
  b.set_fullmove_counter(42);

  b.inc_fullmove_counter();
  EXPECT_EQ(b.fullmove_counter(), 43);
  b.inc_fullmove_counter();
  EXPECT_EQ(b.fullmove_counter(), 44);
}