/**
 * @file filesystem_interface.h
 * @brief Abstract interface for file system parsers
 */

#ifndef RSN_FILESYSTEMS_FILESYSTEM_INTERFACE_H_
#define RSN_FILESYSTEMS_FILESYSTEM_INTERFACE_H_

#include <string>
#include <vector>
#include <memory>

namespace rsn {

// Forward declaration
namespace core {
struct RecoverableFile;
}

namespace filesystems {

/**
 * @brief File system type enumeration
 */
enum class FileSystemType {
  UNKNOWN,
  NTFS,      ///< Windows NTFS
  APFS,      ///< Apple File System
  EXT4,      ///< Linux ext4
  BTRFS,     ///< B-tree file system
  ZFS,       ///< Zettabyte file system
  EXFAT,     ///< Extended FAT
  FAT32,     ///< FAT32
  HFS_PLUS   ///< HFS+
};

/**
 * @brief Abstract base class for file system parsers
 *
 * All file system-specific parsers must inherit from this interface
 * and implement the required methods.
 */
class FileSystemInterface {
 public:
  virtual ~FileSystemInterface() = default;

  /**
   * @brief Get the file system type
   */
  virtual FileSystemType GetType() const = 0;

  /**
   * @brief Initialize the parser with a device
   * @param device_path Path to the device/image
   * @return true if successful, false otherwise
   */
  virtual bool Initialize(const std::string& device_path) = 0;

  /**
   * @brief Parse the file system and discover files
   * @return true if parsing succeeded, false otherwise
   */
  virtual bool Parse() = 0;

  /**
   * @brief Get discovered files
   */
  virtual std::vector<core::RecoverableFile> GetDiscoveredFiles() const = 0;

  /**
   * @brief Get last error message
   */
  virtual std::string GetLastError() const = 0;

  /**
   * @brief Check if file system is valid
   */
  virtual bool IsValid() const = 0;
};

}  // namespace filesystems
}  // namespace rsn

#endif  // RSN_FILESYSTEMS_FILESYSTEM_INTERFACE_H_
