#include "fenrir-core/model/coord.hpp"

#include <gtest/gtest.h>

using namespace fenrir::core;

TEST(Coord__Ctor, Default_Ctor_CreatesOutOfBoardCoordinate) {
  EXPECT_EQ(Coord{}, 0x88);
}

TEST(Coord__foreach, IteratesOverAllValidCoordinates) {
  u8 cnt[Coord::CNT] = {0};
  Coord::foreach ([&cnt](auto c) { ++cnt[c.idx()]; });

  for (usize i = 0; i < Coord::CNT; ++i) {
    if ((i & 0x88) == 0) {
      EXPECT_EQ(cnt[i], 1);
    } else {
      EXPECT_EQ(cnt[i], 0);
    }
  }
}

TEST(Coord__is_on_board, IsTrueForCoordinatesWithout0x88) {
  for (u8 i = 0; i < Coord::CNT; ++i) {
    Coord c{Coord::T{i}};
    if ((i & 0x88) == 0) {
      EXPECT_TRUE(c.is_on_board());
    } else {
      EXPECT_FALSE(c.is_on_board());
    }
  }
}

TEST(Coord__bool_conversion, IsOnlyTrueForCoordsOnTheBoard) {
  for (u8 i = 0; i < Coord::CNT; ++i) {
    if (Coord c{Coord::T{i}}) {
      EXPECT_TRUE(c.is_on_board());
    }
  }
}

TEST(Coord__bool_conversion, IsTrueForAllCoordsOnTheBoard) {
  usize cnt = 0;
  for (u8 i = 0; i < Coord::CNT; ++i) {
    if (Coord{Coord::T{i}}) {
      ++cnt;
    }
  }
  EXPECT_EQ(cnt, Coord::ON_BOARD_CNT);
}

TEST(Coord__rank, ReturnsTheRank) {
  EXPECT_EQ(Coord{Coord::A1}.rank(), 0);
  EXPECT_EQ(Coord{Coord::A2}.rank(), 1);
  EXPECT_EQ(Coord{Coord::B1}.rank(), 0);
  EXPECT_EQ(Coord{Coord::B2}.rank(), 1);
  EXPECT_EQ(Coord{Coord::F4}.rank(), 3);
  EXPECT_EQ(Coord{Coord::F5}.rank(), 4);
  EXPECT_EQ(Coord{Coord::H7}.rank(), 6);
  EXPECT_EQ(Coord{Coord::H8}.rank(), 7);
}

TEST(Coord__file, ReturnsTheFile) {
  EXPECT_EQ(Coord{Coord::A1}.file(), 0);
  EXPECT_EQ(Coord{Coord::A2}.file(), 0);
  EXPECT_EQ(Coord{Coord::B1}.file(), 1);
  EXPECT_EQ(Coord{Coord::B2}.file(), 1);
  EXPECT_EQ(Coord{Coord::F4}.file(), 5);
  EXPECT_EQ(Coord{Coord::G5}.file(), 6);
  EXPECT_EQ(Coord{Coord::G8}.file(), 6);
  EXPECT_EQ(Coord{Coord::H8}.file(), 7);
}

TEST(CoordDelta__operator_plus, AddsToTheDelta) {
  EXPECT_EQ(CoordDelta(0) + CoordDelta(0), 0);
  EXPECT_EQ(CoordDelta(1) + CoordDelta(1), 2);
  EXPECT_EQ(CoordDelta(3) + CoordDelta(7), 10);
  EXPECT_EQ(CoordDelta(1) + CoordDelta(100), 101);
}

TEST(CoordDelta__operator_minus, SubtractsFromTheDelta) {
  EXPECT_EQ(CoordDelta(0) - CoordDelta(0), 0);
  EXPECT_EQ(CoordDelta(1) - CoordDelta(1), 0);
  EXPECT_EQ(CoordDelta(7) - CoordDelta(3), 4);
  EXPECT_EQ(CoordDelta(100) - CoordDelta(1), 99);
}

TEST(CoordDelta__rank_literal, CreatesTheDelta) {
  EXPECT_EQ(0_rank, 0x00);
  EXPECT_EQ(1_rank, 0x01);
  EXPECT_EQ(2_rank, 0x02);
  EXPECT_EQ(3_rank, 0x03);
  EXPECT_EQ(4_rank, 0x04);
  EXPECT_EQ(5_rank, 0x05);
  EXPECT_EQ(6_rank, 0x06);
  EXPECT_EQ(7_rank, 0x07);
}

TEST(CoordDelta__rank_literal, FailsForInvalidRankDeltas) {
  EXPECT_DEATH(8_rank, "Assertion");
  EXPECT_DEATH(9_rank, "Assertion");
  EXPECT_DEATH(10_rank, "Assertion");
}

TEST(CoordDelta__file_literal, CreatesTheDelta) {
  EXPECT_EQ(0_file, 0x00);
  EXPECT_EQ(1_file, 0x10);
  EXPECT_EQ(2_file, 0x20);
  EXPECT_EQ(3_file, 0x30);
  EXPECT_EQ(4_file, 0x40);
  EXPECT_EQ(5_file, 0x50);
  EXPECT_EQ(6_file, 0x60);
  EXPECT_EQ(7_file, 0x70);
}

TEST(CoordDelta__file_literal, FailsForInvalidFileDeltas) {
  EXPECT_DEATH(8_file, "Assertion");
  EXPECT_DEATH(9_file, "Assertion");
  EXPECT_DEATH(10_file, "Assertion");
}

TEST(Coord__operator_plus, AddsTheDeltaIfTheResultIsValid) {
  // Directly on the values
  EXPECT_EQ(Coord::A1 + 0_rank + 0_file, Coord::A1);
  EXPECT_EQ(Coord::A1 + 1_rank + 0_file, Coord::A2);
  EXPECT_EQ(Coord::A1 + 0_rank + 1_file, Coord::B1);
  EXPECT_EQ(Coord::A1 + 1_rank + 1_file, Coord::B2);
  EXPECT_EQ(Coord::C3 + 2_rank + 4_file, Coord::G5);
  // On the wrapper struct
  EXPECT_EQ(Coord{Coord::A1} + 0_rank + 0_file, Coord::A1);
  EXPECT_EQ(Coord{Coord::A1} + 1_rank + 0_file, Coord::A2);
  EXPECT_EQ(Coord{Coord::A1} + 0_rank + 1_file, Coord::B1);
  EXPECT_EQ(Coord{Coord::A1} + 1_rank + 1_file, Coord::B2);
  EXPECT_EQ(Coord{Coord::C3} + 2_rank + 4_file, Coord::G5);
}

TEST(Coord__operator_plus, ReturnsFalseyValueIfTheResultIsInvalid) {
  EXPECT_FALSE(Coord{Coord::A8} + 1_rank);
  EXPECT_FALSE(Coord{Coord::A2} + 7_rank);
  EXPECT_FALSE(Coord{Coord::B3} + 7_rank);
  EXPECT_FALSE(Coord{Coord::G5} + 6_rank);
  EXPECT_FALSE(Coord{Coord::B8} + 7_file);
  EXPECT_FALSE(Coord{Coord::D2} + 7_file);
  EXPECT_FALSE(Coord{Coord::H3} + 1_file);
  EXPECT_FALSE(Coord{Coord::G5} + 6_file);
}
TEST(Coord__operator_plus, Associativity) {
  // Directly on the values
  EXPECT_EQ((Coord::A1 + 0_rank) + 0_file, Coord::A1 + (0_rank + 0_file));
  EXPECT_EQ((Coord::A1 + 1_rank) + 0_file, Coord::A1 + (1_rank + 0_file));
  EXPECT_EQ((Coord::A1 + 0_rank) + 1_file, Coord::A1 + (0_rank + 1_file));
  EXPECT_EQ((Coord::A1 + 1_rank) + 1_file, Coord::A1 + (1_rank + 1_file));
  EXPECT_EQ((Coord::C3 + 2_rank) + 4_file, Coord::C3 + (2_rank + 4_file));
  // On the wrapper struct
  EXPECT_EQ((Coord{Coord::A1} + 0_rank) + 0_file,
            Coord{Coord::A1} + (0_rank + 0_file));
  EXPECT_EQ((Coord{Coord::A1} + 1_rank) + 0_file,
            Coord{Coord::A1} + (1_rank + 0_file));
  EXPECT_EQ((Coord{Coord::A1} + 0_rank) + 1_file,
            Coord{Coord::A1} + (0_rank + 1_file));
  EXPECT_EQ((Coord{Coord::A1} + 1_rank) + 1_file,
            Coord{Coord::A1} + (1_rank + 1_file));
  EXPECT_EQ((Coord{Coord::C3} + 2_rank) + 4_file,
            Coord{Coord::C3} + (2_rank + 4_file));
}

TEST(Coord__operator_minus, SubtractsTheDeltaIfTheResultIsValid) {
  // Directly on the values
  EXPECT_EQ(Coord::A1 - 0_rank - 0_file, Coord::A1);
  EXPECT_EQ(Coord::A2 - 1_rank - 0_file, Coord::A1);
  EXPECT_EQ(Coord::B1 - 0_rank - 1_file, Coord::A1);
  EXPECT_EQ(Coord::B2 - 1_rank - 1_file, Coord::A1);
  EXPECT_EQ(Coord::G5 - 2_rank - 4_file, Coord::C3);
  // On the wrapper struct
  EXPECT_EQ(Coord{Coord::A1} - 0_rank - 0_file, Coord::A1);
  EXPECT_EQ(Coord{Coord::A2} - 1_rank - 0_file, Coord::A1);
  EXPECT_EQ(Coord{Coord::B1} - 0_rank - 1_file, Coord::A1);
  EXPECT_EQ(Coord{Coord::B2} - 1_rank - 1_file, Coord::A1);
  EXPECT_EQ(Coord{Coord::G5} - 2_rank - 4_file, Coord::C3);
}

TEST(Coord__operator_minus, ReturnsFalseyValueIfTheResultIsInvalid) {
  EXPECT_FALSE(Coord{Coord::A1} - 1_rank);
  EXPECT_FALSE(Coord{Coord::A2} - 7_rank);
  EXPECT_FALSE(Coord{Coord::B3} - 7_rank);
  EXPECT_FALSE(Coord{Coord::G5} - 6_rank);
  EXPECT_FALSE(Coord{Coord::B8} - 7_file);
  EXPECT_FALSE(Coord{Coord::D2} - 7_file);
  EXPECT_FALSE(Coord{Coord::A3} - 1_file);
  EXPECT_FALSE(Coord{Coord::A5} - 7_file);
}

TEST(Coord__operator_minus, Distributivity) {
  // Directly on the values
  EXPECT_EQ((Coord::A1 - 0_rank) - 0_file, Coord::A1 - (0_rank + 0_file));
  EXPECT_EQ((Coord::A2 - 1_rank) - 0_file, Coord::A2 - (1_rank + 0_file));
  EXPECT_EQ((Coord::B1 - 0_rank) - 1_file, Coord::B1 - (0_rank + 1_file));
  EXPECT_EQ((Coord::B2 - 1_rank) - 1_file, Coord::B2 - (1_rank + 1_file));
  EXPECT_EQ((Coord::G5 - 2_rank) - 4_file, Coord::G5 - (2_rank + 4_file));
  // On the wrapper struct
  EXPECT_EQ((Coord{Coord::A1} - 0_rank) - 0_file,
            Coord{Coord::A1} - (0_rank + 0_file));
  EXPECT_EQ((Coord{Coord::A2} - 1_rank) - 0_file,
            Coord{Coord::A2} - (1_rank + 0_file));
  EXPECT_EQ((Coord{Coord::B1} - 0_rank) - 1_file,
            Coord{Coord::B1} - (0_rank + 1_file));
  EXPECT_EQ((Coord{Coord::B2} - 1_rank) - 1_file,
            Coord{Coord::B2} - (1_rank + 1_file));
  EXPECT_EQ((Coord{Coord::G5} - 2_rank) - 4_file,
            Coord{Coord::G5} - (2_rank + 4_file));
}