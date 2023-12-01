#include "arduAPI.h"
#include <gtest/gtest.h>

TEST(arduAPI, CfgParserInit) {
  arduAPI::CfgParser cfg;
  cfg.parse("50,50,50,50,100000000");
  EXPECT_EQ(cfg.isValid, true);
  EXPECT_EQ(cfg.motor0_rpm, 50);
  EXPECT_EQ(cfg.motor1_rpm, 50);
  EXPECT_EQ(cfg.motor2_rpm, 50);
  EXPECT_EQ(cfg.motor3_rpm, 50);
  EXPECT_EQ(cfg.duration,  100L * 1000L * 1000L);
}
