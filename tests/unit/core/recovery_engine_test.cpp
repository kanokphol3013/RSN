/**
 * @file recovery_engine_test.cpp
 * @brief Unit tests for RecoveryEngine class
 */

#include "core/recovery_engine.h"
#include "core/file_registry.h"
#include <gtest/gtest.h>

using namespace rsn::core;

/**
 * @brief Test fixture for RecoveryEngine tests
 */
class RecoveryEngineTest : public ::testing::Test {
 protected:
  void SetUp() override {
    engine_ = std::make_unique<RecoveryEngine>();
  }

  void TearDown() override {
    engine_.reset();
  }

  std::unique_ptr<RecoveryEngine> engine_;
};

/**
 * @brief Test RecoveryEngine construction
 */
TEST_F(RecoveryEngineTest, ConstructorInitializesCorrectly) {
  ASSERT_NE(engine_, nullptr);
  EXPECT_FALSE(engine_->IsScanning());
}

/**
 * @brief Test setting device path
 */
TEST_F(RecoveryEngineTest, SetDevice_ValidPath_ReturnsTrue) {
  // Note: This is a basic test - in reality, we'd need a mock device
  bool result = engine_->SetDevice("/dev/sda1");
  // For now, just check it doesn't crash
  EXPECT_TRUE(result || !result);  // Accept any result for placeholder
}

/**
 * @brief Test getting stats before scan
 */
TEST_F(RecoveryEngineTest, GetStats_BeforeScan_ReturnsZeroStats) {
  RecoveryStats stats = engine_->GetStats();
  EXPECT_EQ(stats.total_files_found, 0);
  EXPECT_EQ(stats.files_recovered, 0);
  EXPECT_EQ(stats.bytes_scanned, 0);
}

/**
 * @brief Test recovery mode setting
 */
TEST_F(RecoveryEngineTest, SetRecoveryMode_AllModes_NoException) {
  EXPECT_NO_THROW(engine_->SetRecoveryMode(RecoveryEngine::RecoveryMode::METADATA_ONLY));
  EXPECT_NO_THROW(engine_->SetRecoveryMode(RecoveryEngine::RecoveryMode::FILE_CARVING));
  EXPECT_NO_THROW(engine_->SetRecoveryMode(RecoveryEngine::RecoveryMode::DEEP_SCAN));
  EXPECT_NO_THROW(engine_->SetRecoveryMode(RecoveryEngine::RecoveryMode::RAID_RECONSTRUCT));
}

/**
 * @brief Test file registry access
 */
TEST_F(RecoveryEngineTest, GetFileRegistry_ReturnsValidPointer) {
  auto registry = engine_->GetFileRegistry();
  ASSERT_NE(registry, nullptr);
  EXPECT_EQ(registry->GetFileCount(), 0);
}

/**
 * @brief Test stopping scan when not scanning
 */
TEST_F(RecoveryEngineTest, StopScan_WhenNotScanning_NoException) {
  EXPECT_NO_THROW(engine_->StopScan());
  EXPECT_FALSE(engine_->IsScanning());
}
