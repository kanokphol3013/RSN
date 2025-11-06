/**
 * @file ntfs_parser_test.cpp
 * @brief Unit tests for NTFS parser
 */

#include "filesystems/ntfs_parser.h"
#include <gtest/gtest.h>

using namespace rsn::filesystems;

class NTFSParserTest : public ::testing::Test {
 protected:
  void SetUp() override {
    parser_ = std::make_unique<NTFSParser>();
  }

  std::unique_ptr<NTFSParser> parser_;
};

TEST_F(NTFSParserTest, GetType_ReturnsNTFS) {
  EXPECT_EQ(parser_->GetType(), FileSystemType::NTFS);
}

TEST_F(NTFSParserTest, Initialize_ValidDevice_ReturnsTrue) {
  bool result = parser_->Initialize("/dev/sda1");
  EXPECT_TRUE(result);
  EXPECT_TRUE(parser_->IsValid());
}

TEST_F(NTFSParserTest, Parse_WithoutInitialize_ReturnsFalse) {
  bool result = parser_->Parse();
  EXPECT_FALSE(result);
}

TEST_F(NTFSParserTest, GetDiscoveredFiles_Initially_ReturnsEmpty) {
  auto files = parser_->GetDiscoveredFiles();
  EXPECT_TRUE(files.empty());
}
