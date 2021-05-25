#include "fenrir-core/model/color.hpp"

#include <gtest/gtest.h>

using namespace fenrir::core;

TEST(Color, flip) {
  EXPECT_EQ(Color(Color::WHITE).flipped(), Color::BLACK);
  EXPECT_EQ(Color(Color::BLACK).flipped(), Color::WHITE);
}