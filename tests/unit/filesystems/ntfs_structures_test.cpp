/**
 * @file ntfs_structures_test.cpp
 * @brief Unit tests for NTFS structures
 */

#include "filesystems/ntfs_structures.h"
#include <gtest/gtest.h>
#include <cstring>

using namespace rsn::filesystems::ntfs;

TEST(NTFSStructuresTest, BootSectorSize_Is512Bytes) {
  EXPECT_EQ(sizeof(BootSector), 512);
}

TEST(NTFSStructuresTest, MFTRecordHeaderSize_IsCorrect) {
  // MFT record header should be 48 bytes
  EXPECT_EQ(sizeof(MFTRecordHeader), 48);
}

TEST(NTFSStructuresTest, AttributeHeaderSize_IsCorrect) {
  // Attribute header should be 16 bytes
  EXPECT_EQ(sizeof(AttributeHeader), 16);
}

TEST(NTFSStructuresTest, FileNameAttributeSize_IsCorrect) {
  // File name attribute should be 66 bytes (without actual filename)
  EXPECT_EQ(sizeof(FileNameAttribute), 66);
}

TEST(NTFSStructuresTest, StandardInformationSize_IsCorrect) {
  // Standard information should be 48 bytes
  EXPECT_EQ(sizeof(StandardInformation), 48);
}

TEST(NTFSStructuresTest, Constants_HaveCorrectValues) {
  EXPECT_EQ(BOOT_SIGNATURE, 0xAA55);
  EXPECT_EQ(MFT_RECORD_SIZE, 1024);
}

TEST(NTFSStructuresTest, AttributeTypes_AreUnique) {
  EXPECT_NE(ATTR_STANDARD_INFORMATION, ATTR_FILE_NAME);
  EXPECT_NE(ATTR_DATA, ATTR_INDEX_ROOT);
  EXPECT_EQ(ATTR_END, 0xFFFFFFFF);
}

TEST(NTFSStructuresTest, FileAttributes_ArePowersOfTwo) {
  // Flags should be individual bits
  EXPECT_EQ(FILE_ATTR_READONLY, 0x0001);
  EXPECT_EQ(FILE_ATTR_HIDDEN, 0x0002);
  EXPECT_EQ(FILE_ATTR_SYSTEM, 0x0004);
  EXPECT_EQ(FILE_ATTR_ARCHIVE, 0x0020);
}
