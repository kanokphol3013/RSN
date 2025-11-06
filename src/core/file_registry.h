/**
 * @file file_registry.h
 * @brief Registry for managing discovered files during recovery
 */

#ifndef RSN_CORE_FILE_REGISTRY_H_
#define RSN_CORE_FILE_REGISTRY_H_

#include <string>
#include <vector>
#include <cstdint>

namespace rsn {
namespace core {

/**
 * @brief Represents a recoverable file
 */
struct RecoverableFile {
  uint64_t id;
  std::string filename;
  std::string original_path;
  uint64_t size_bytes;
  std::string file_type;
  uint64_t sector_offset;
  bool is_deleted;
  bool is_fragmented;
  double recovery_confidence;  // 0.0 - 1.0
};

/**
 * @brief Registry for managing discovered files
 */
class FileRegistry {
 public:
  FileRegistry();
  ~FileRegistry();

  /**
   * @brief Add a file to the registry
   */
  void AddFile(const RecoverableFile& file);

  /**
   * @brief Get all files
   */
  const std::vector<RecoverableFile>& GetFiles() const;

  /**
   * @brief Get file by ID
   */
  const RecoverableFile* GetFileById(uint64_t id) const;

  /**
   * @brief Get total file count
   */
  size_t GetFileCount() const;

  /**
   * @brief Clear all files
   */
  void Clear();

 private:
  std::vector<RecoverableFile> files_;
};

}  // namespace core
}  // namespace rsn

#endif  // RSN_CORE_FILE_REGISTRY_H_
