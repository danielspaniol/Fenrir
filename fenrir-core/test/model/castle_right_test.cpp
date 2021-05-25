#include "fenrir-core/model/castle_right.hpp"

#include <gtest/gtest.h>

using namespace fenrir::core;

TEST(CastleRight, default_ctor) {
  CastleRight r;
  EXPECT_FALSE(r.can_kingside_castle());
  EXPECT_FALSE(r.can_queenside_castle());
}

TEST(CastleRight, can_kingside_castle) {
  EXPECT_FALSE(CastleRight(CastleRight::NONE).can_kingside_castle());
  EXPECT_TRUE(CastleRight(CastleRight::KINGSIDE).can_kingside_castle());
  EXPECT_FALSE(CastleRight(CastleRight::QUEENSIDE).can_kingside_castle());
  EXPECT_TRUE(CastleRight(CastleRight::BOTH).can_kingside_castle());
}

TEST(CastleRight, can_queenside_castle) {
  EXPECT_FALSE(CastleRight(CastleRight::NONE).can_queenside_castle());
  EXPECT_FALSE(CastleRight(CastleRight::KINGSIDE).can_queenside_castle());
  EXPECT_TRUE(CastleRight(CastleRight::QUEENSIDE).can_queenside_castle());
  EXPECT_TRUE(CastleRight(CastleRight::BOTH).can_queenside_castle());
}

TEST(CastleRight, set_can_kingside_castle) {
  EXPECT_EQ(CastleRight(CastleRight::NONE).with_can_kingside_castle(true),
            CastleRight::KINGSIDE);
  EXPECT_EQ(CastleRight(CastleRight::KINGSIDE).with_can_kingside_castle(true),
            CastleRight::KINGSIDE);
  EXPECT_EQ(CastleRight(CastleRight::QUEENSIDE).with_can_kingside_castle(true),
            CastleRight::BOTH);
  EXPECT_EQ(CastleRight(CastleRight::BOTH).with_can_kingside_castle(true),
            CastleRight::BOTH);
  EXPECT_EQ(CastleRight(CastleRight::NONE).with_can_kingside_castle(false),
            CastleRight::NONE);
  EXPECT_EQ(CastleRight(CastleRight::KINGSIDE).with_can_kingside_castle(false),
            CastleRight::NONE);
  EXPECT_EQ(CastleRight(CastleRight::QUEENSIDE).with_can_kingside_castle(false),
            CastleRight::QUEENSIDE);
  EXPECT_EQ(CastleRight(CastleRight::BOTH).with_can_kingside_castle(false),
            CastleRight::QUEENSIDE);
}

TEST(CastleRight, set_can_queenside_castle) {
  EXPECT_EQ(CastleRight(CastleRight::NONE).with_can_queenside_castle(true),
            CastleRight::QUEENSIDE);
  EXPECT_EQ(CastleRight(CastleRight::KINGSIDE).with_can_queenside_castle(true),
            CastleRight::BOTH);
  EXPECT_EQ(CastleRight(CastleRight::QUEENSIDE).with_can_queenside_castle(true),
            CastleRight::QUEENSIDE);
  EXPECT_EQ(CastleRight(CastleRight::BOTH).with_can_queenside_castle(true),
            CastleRight::BOTH);
  EXPECT_EQ(CastleRight(CastleRight::NONE).with_can_queenside_castle(false),
            CastleRight::NONE);
  EXPECT_EQ(CastleRight(CastleRight::KINGSIDE).with_can_queenside_castle(false),
            CastleRight::KINGSIDE);
  EXPECT_EQ(
      CastleRight(CastleRight::QUEENSIDE).with_can_queenside_castle(false),
      CastleRight::NONE);
  EXPECT_EQ(CastleRight(CastleRight::BOTH).with_can_queenside_castle(false),
            CastleRight::KINGSIDE);
}