#include "dot.hpp"
#include "gtest/gtest.h"

namespace {

TEST(DotOpTest, Constructor1) {
  DotOp d(32);
  std::pair<float, float> p(0., 0.);
  EXPECT_EQ(p, d.getResult());
}

TEST(DotOpTest, InvalidInputM1) {
  EXPECT_DEATH(DotOp d(10), "M mod 16 failed");
}
TEST(DotOpTest, InvalidInputM2) {
  EXPECT_DEATH(DotOp d(17), "M mod 16 failed");
}

} // namespace