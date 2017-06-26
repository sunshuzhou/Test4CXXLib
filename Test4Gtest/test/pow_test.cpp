#include "include/pow.h"
#include "gtest/gtest.h"

TEST(POW_TEST_1, One) {
    EXPECT_EQ(1, pow(1, 1));
    EXPECT_EQ(1, pow(1, 1));
}

TEST(POW_TEST_2, Random) {
    EXPECT_EQ(32, pow(2, 5));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
}
