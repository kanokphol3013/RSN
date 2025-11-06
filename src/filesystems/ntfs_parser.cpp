/**
 * @file ntfs_parser.cpp
 * @brief Implementation of NTFS parser
 */

#include "filesystems/ntfs_parser.h"
#include "filesystems/ntfs_structures.h"
#include "core/file_registry.h"
#include "common/logging.h"
#include <cstring>

namespace rsn {
namespace filesystems {

NTFSParser::NTFSParser()
  : is_valid_(false), next_file_id_(0) {
  volume_info_ = {0, 0, 0, 0, 0};
}

NTFSParser::~NTFSParser() {}

FileSystemType NTFSParser::GetType() const {
  return FileSystemType::NTFS;
}

bool NTFSParser::Initialize(const std::string& device_path) {
  device_path_ = device_path;
  common::Log(common::LogLevel::INFO, "NTFS Parser initialized for: " + device_path);

  // Read and validate boot sector
  if (!ReadBootSector()) {
    last_error_ = "Failed to read NTFS boot sector";
    return false;
  }

  if (!ValidateBootSector()) {
    last_error_ = "Invalid NTFS boot sector";
    return false;
  }

  is_valid_ = true;
  common::Log(common::LogLevel::INFO, "NTFS volume validated successfully");
  return true;
}

bool NTFSParser::Parse() {
  if (!is_valid_) {
    last_error_ = "Parser not initialized";
    return false;
  }

  common::Log(common::LogLevel::INFO, "Parsing NTFS file system...");

  // Parse MFT (Master File Table)
  if (!ParseMFT()) {
    last_error_ = "Failed to parse MFT";
    return false;
  }

  common::Log(common::LogLevel::INFO,
              "NTFS parsing complete. Found " +
              std::to_string(discovered_files_.size()) + " files");

  return true;
}

std::vector<core::RecoverableFile> NTFSParser::GetDiscoveredFiles() const {
  return discovered_files_;
}

std::string NTFSParser::GetLastError() const {
  return last_error_;
}

bool NTFSParser::IsValid() const {
  return is_valid_;
}

NTFSParser::VolumeInfo NTFSParser::GetVolumeInfo() const {
  return volume_info_;
}

bool NTFSParser::ReadBootSector() {
  // TODO: Implement actual boot sector reading from device
  // For now, create a mock boot sector for demonstration

  boot_sector_ = std::make_unique<ntfs::BootSector>();
  std::memset(boot_sector_.get(), 0, sizeof(ntfs::BootSector));

  // Set mock values (in real implementation, read from device)
  std::memcpy(boot_sector_->oem_id, "NTFS    ", 8);
  boot_sector_->bytes_per_sector = 512;
  boot_sector_->sectors_per_cluster = 8;
  boot_sector_->total_sectors = 1000000;  // Mock value
  boot_sector_->mft_lcn = 1000;           // Mock MFT location
  boot_sector_->signature = ntfs::BOOT_SIGNATURE;

  // Populate volume info
  volume_info_.bytes_per_sector = boot_sector_->bytes_per_sector;
  volume_info_.sectors_per_cluster = boot_sector_->sectors_per_cluster;
  volume_info_.total_sectors = boot_sector_->total_sectors;
  volume_info_.mft_location = boot_sector_->mft_lcn;
  volume_info_.volume_serial = boot_sector_->volume_serial_number;

  return true;
}

bool NTFSParser::ValidateBootSector() {
  if (!boot_sector_) {
    return false;
  }

  // Check OEM ID
  if (std::memcmp(boot_sector_->oem_id, "NTFS    ", 8) != 0) {
    common::Log(common::LogLevel::ERROR, "Invalid NTFS OEM ID");
    return false;
  }

  // Check boot signature
  if (boot_sector_->signature != ntfs::BOOT_SIGNATURE) {
    common::Log(common::LogLevel::ERROR, "Invalid boot signature");
    return false;
  }

  // Validate sector size (should be power of 2, typically 512)
  if (boot_sector_->bytes_per_sector == 0 ||
      (boot_sector_->bytes_per_sector & (boot_sector_->bytes_per_sector - 1)) != 0) {
    common::Log(common::LogLevel::ERROR, "Invalid bytes per sector");
    return false;
  }

  common::Log(common::LogLevel::DEBUG,
              "NTFS boot sector validated: " +
              std::to_string(boot_sector_->bytes_per_sector) + " bytes/sector, " +
              std::to_string(boot_sector_->sectors_per_cluster) + " sectors/cluster");

  return true;
}

bool NTFSParser::ParseMFT() {
  common::Log(common::LogLevel::INFO,
              "Parsing MFT at cluster " + std::to_string(volume_info_.mft_location));

  // TODO: Implement actual MFT parsing
  // 1. Calculate MFT physical offset
  // 2. Read MFT entries
  // 3. Parse each FILE record
  // 4. Extract file metadata
  // 5. Identify deleted files

  // For demonstration, create some mock discovered files
  core::RecoverableFile mock_file1;
  mock_file1.id = next_file_id_++;
  mock_file1.filename = "deleted_document.docx";
  mock_file1.original_path = "C:\\Users\\User\\Documents\\deleted_document.docx";
  mock_file1.size_bytes = 1024 * 50;  // 50 KB
  mock_file1.file_type = "Microsoft Word Document";
  mock_file1.sector_offset = 12345;
  mock_file1.is_deleted = true;
  mock_file1.is_fragmented = false;
  mock_file1.recovery_confidence = 0.95;

  discovered_files_.push_back(mock_file1);

  core::RecoverableFile mock_file2;
  mock_file2.id = next_file_id_++;
  mock_file2.filename = "photo.jpg";
  mock_file2.original_path = "C:\\Users\\User\\Pictures\\photo.jpg";
  mock_file2.size_bytes = 1024 * 1024 * 2;  // 2 MB
  mock_file2.file_type = "JPEG Image";
  mock_file2.sector_offset = 67890;
  mock_file2.is_deleted = true;
  mock_file2.is_fragmented = true;
  mock_file2.recovery_confidence = 0.75;

  discovered_files_.push_back(mock_file2);

  common::Log(common::LogLevel::DEBUG,
              "Mock MFT parsing: created " +
              std::to_string(discovered_files_.size()) + " sample files");

  return true;
}

bool NTFSParser::ParseMFTRecord(uint64_t record_number) {
  // TODO: Implement actual MFT record parsing
  // 1. Read MFT record from disk
  // 2. Validate FILE signature
  // 3. Parse attributes ($FILE_NAME, $DATA, etc.)
  // 4. Extract file metadata
  // 5. Check if deleted

  return true;
}

std::string NTFSParser::ExtractFileName(const uint8_t* attribute_data,
                                        size_t size) {
  // TODO: Implement Unicode filename extraction from $FILE_NAME attribute
  return "extracted_filename.txt";
}

bool NTFSParser::IsDeletedFile(uint16_t flags) {
  // Check if MFT_RECORD_IN_USE flag is NOT set
  return (flags & ntfs::MFT_RECORD_IN_USE) == 0;
}

}  // namespace filesystems
}  // namespace rsn
