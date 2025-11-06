/**
 * @file utils_test.cpp
 * @brief Unit tests for common utilities
 */

#include "common/utils.h"
#include <gtest/gtest.h>

using namespace rsn::common;

TEST(UtilsTest, FormatBytes_SmallSize_ReturnsBytes) {
  std::string result = FormatBytes(512);
  EXPECT_EQ(result, "512.00 B");
}

TEST(UtilsTest, FormatBytes_KilobyteSize_ReturnsKB) {
  std::string result = FormatBytes(2048);
  EXPECT_EQ(result, "2.00 KB");
}

TEST(UtilsTest, FormatBytes_MegabyteSize_ReturnsMB) {
  std::string result = FormatBytes(1048576);  // 1 MB
  EXPECT_EQ(result, "1.00 MB");
}

TEST(UtilsTest, ToUpper_LowercaseString_ReturnsUppercase) {
  std::string result = ToUpper("hello");
  EXPECT_EQ(result, "HELLO");
}

TEST(UtilsTest, ToLower_UppercaseString_ReturnsLowercase) {
  std::string result = ToLower("WORLD");
  EXPECT_EQ(result, "world");
}

TEST(UtilsTest, DirectoryExists_NonexistentPath_ReturnsFalse) {
  bool result = DirectoryExists("/nonexistent/directory/path");
  EXPECT_FALSE(result);
}

TEST(UtilsTest, FileExists_NonexistentFile_ReturnsFalse) {
  bool result = FileExists("/nonexistent/file.txt");
  EXPECT_FALSE(result);
}
