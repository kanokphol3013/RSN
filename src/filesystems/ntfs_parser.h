/**
 * @file ntfs_parser.h
 * @brief NTFS file system parser
 */

#ifndef RSN_FILESYSTEMS_NTFS_PARSER_H_
#define RSN_FILESYSTEMS_NTFS_PARSER_H_

#include "filesystems/filesystem_interface.h"

namespace rsn {
namespace filesystems {

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

 private:
  std::string device_path_;
  std::vector<core::RecoverableFile> discovered_files_;
  std::string last_error_;
  bool is_valid_;
};

}  // namespace filesystems
}  // namespace rsn

#endif  // RSN_FILESYSTEMS_NTFS_PARSER_H_
