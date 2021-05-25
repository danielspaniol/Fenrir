#include "fenrir-core/model/piece.hpp"

#include <gtest/gtest.h>

using namespace fenrir::core;

TEST(Piece__color, ReturnsTheColor) {
  EXPECT_FALSE(Piece(Piece::EMPTY).color());
  EXPECT_EQ(Piece(Piece::WHITE_PAWN).color(), Color::WHITE);
  EXPECT_EQ(Piece(Piece::BLACK_PAWN).color(), Color::BLACK);
  EXPECT_EQ(Piece(Piece::WHITE_KNIGHT).color(), Color::WHITE);
  EXPECT_EQ(Piece(Piece::BLACK_KNIGHT).color(), Color::BLACK);
  EXPECT_EQ(Piece(Piece::WHITE_BISHOP).color(), Color::WHITE);
  EXPECT_EQ(Piece(Piece::BLACK_BISHOP).color(), Color::BLACK);
  EXPECT_EQ(Piece(Piece::WHITE_ROOK).color(), Color::WHITE);
  EXPECT_EQ(Piece(Piece::BLACK_ROOK).color(), Color::BLACK);
  EXPECT_EQ(Piece(Piece::WHITE_QUEEN).color(), Color::WHITE);
  EXPECT_EQ(Piece(Piece::BLACK_QUEEN).color(), Color::BLACK);
  EXPECT_EQ(Piece(Piece::WHITE_KING).color(), Color::WHITE);
  EXPECT_EQ(Piece(Piece::BLACK_KING).color(), Color::BLACK);
}