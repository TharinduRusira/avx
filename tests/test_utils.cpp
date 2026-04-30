#include "utils.h"
#include "gtest/gtest.h"

namespace {

TEST(UtilTest, UtilTest_pow2_0_Test) { EXPECT_EQ(ceil_pow_of_2(0), 1); }
TEST(UtilTest, UtilTest_pow2_1_Test) { EXPECT_EQ(ceil_pow_of_2(1), 1); }
TEST(UtilTest, UtilTest_pow2_4_Test) { EXPECT_EQ(ceil_pow_of_2(4), 4); }
TEST(UtilTest, UtilTest_pow2_17_Test) { EXPECT_EQ(ceil_pow_of_2(17), 32); }
TEST(UtilTest, UtilTest_pow2_32_Test) { EXPECT_EQ(ceil_pow_of_2(32), 32); }
TEST(UtilTest, UtilTest_pow2_INTMAX__Test) {
  EXPECT_EQ(ceil_pow_of_2(2147483648 - 1), 2147483648);
}
TEST(UtilTest, UtilTest_pow2_neg1_Test) { EXPECT_EQ(ceil_pow_of_2(-1), 0); }
TEST(UtilTest, UtilTest_pow2_neg10_Test) { EXPECT_EQ(ceil_pow_of_2(-10), 0); }

} // namespace
