#include "clock.hpp"
#include "gtest/gtest.h"
#include <chrono>
#include <thread>

namespace {

TEST(ClockTest, StartEnd) {
  Clock clk;
  clk.start();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  clk.end();
  EXPECT_GT(clk.duration(), 0.);
}

TEST(ClockTest, InvalidDuration1) {
  Clock clk;
  clk.start();
  EXPECT_DEATH(clk.duration(), "\\[ERROR\\] clock is still ticking...");
}

TEST(ClockTest, InvalidDuration2) {
  Clock clk;
  clk.start();
  clk.end();
  clk.start();
  EXPECT_DEATH(clk.duration(), "\\[ERROR\\] clock is still ticking...");
}

} // namespace