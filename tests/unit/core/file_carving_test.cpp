/**
 * @file file_carving_test.cpp
 * @brief Unit tests for file carving engine
 */

#include "core/file_carving.h"
#include <gtest/gtest.h>

using namespace rsn::core;

class FileCarvingEngineTest : public ::testing::Test {
 protected:
  void SetUp() override {
    engine_ = std::make_unique<FileCarvingEngine>();
  }

  std::unique_ptr<FileCarvingEngine> engine_;
};

TEST_F(FileCarvingEngineTest, Initialize_LoadsDefaultSignatures) {
  ASSERT_TRUE(engine_->Initialize());

  auto types = engine_->GetSupportedFileTypes();
  EXPECT_GT(types.size(), 0);

  // Check for common file types
  bool has_jpeg = false;
  bool has_pdf = false;
  for (const auto& type : types) {
    if (type.find("JPEG") != std::string::npos) has_jpeg = true;
    if (type.find("PDF") != std::string::npos) has_pdf = true;
  }

  EXPECT_TRUE(has_jpeg);
  EXPECT_TRUE(has_pdf);
}

TEST_F(FileCarvingEngineTest, GetSupportedFileTypes_ReturnsMultipleTypes) {
  engine_->Initialize();
  auto types = engine_->GetSupportedFileTypes();

  EXPECT_GE(types.size(), 5);  // At least 5 file types
}

TEST_F(FileCarvingEngineTest, AddSignature_IncreasesTypeCount) {
  engine_->Initialize();
  size_t initial_count = engine_->GetSupportedFileTypes().size();

  FileSignature custom_sig;
  custom_sig.file_type = "Custom Type";
  custom_sig.extension = ".cst";
  custom_sig.header = {0x43, 0x53, 0x54};
  custom_sig.max_file_size = 1024;
  custom_sig.has_footer = false;

  engine_->AddSignature(custom_sig);

  size_t new_count = engine_->GetSupportedFileTypes().size();
  EXPECT_GT(new_count, initial_count);
}

TEST_F(FileCarvingEngineTest, GetStats_InitiallyZero) {
  auto stats = engine_->GetStats();
  EXPECT_EQ(stats.bytes_scanned, 0);
  EXPECT_EQ(stats.files_found, 0);
  EXPECT_EQ(stats.files_carved, 0);
}

TEST_F(FileCarvingEngineTest, SetMaxScanSize_AcceptsValue) {
  EXPECT_NO_THROW(engine_->SetMaxScanSize(1024 * 1024 * 100));
}
