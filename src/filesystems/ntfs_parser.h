/**
 * @file ntfs_parser.h
 * @brief NTFS file system parser
 */

#ifndef RSN_FILESYSTEMS_NTFS_PARSER_H_
#define RSN_FILESYSTEMS_NTFS_PARSER_H_

#include "filesystems/filesystem_interface.h"
#include <memory>

namespace rsn {
namespace filesystems {

// Forward declarations
namespace ntfs {
struct BootSector;
struct MFTRecordHeader;
}

/**
 * @brief NTFS file system parser
 */
class NTFSParser : public FileSystemInterface {
 public:
  NTFSParser();
  ~NTFSParser() override;

  FileSystemType GetType() const override;
  bool Initialize(const std::string& device_path) override;
  bool Parse() override;
  std::vector<core::RecoverableFile> GetDiscoveredFiles() const override;
  std::string GetLastError() const override;
  bool IsValid() const override;

  /**
   * @brief Get NTFS volume information
   */
  struct VolumeInfo {
    uint64_t total_sectors;
    uint64_t mft_location;
    uint32_t bytes_per_sector;
    uint32_t sectors_per_cluster;
    uint64_t volume_serial;
  };
  VolumeInfo GetVolumeInfo() const;

 private:
  std::string device_path_;
  std::vector<core::RecoverableFile> discovered_files_;
  std::string last_error_;
  bool is_valid_;

  // NTFS specific data
  std::unique_ptr<ntfs::BootSector> boot_sector_;
  VolumeInfo volume_info_;
  uint64_t next_file_id_;

  // Helper methods
  bool ReadBootSector();
  bool ValidateBootSector();
  bool ParseMFT();
  bool ParseMFTRecord(uint64_t record_number);
  std::string ExtractFileName(const uint8_t* attribute_data, size_t size);
  bool IsDeletedFile(uint16_t flags);
};

}  // namespace filesystems
}  // namespace rsn

#endif  // RSN_FILESYSTEMS_NTFS_PARSER_H_
