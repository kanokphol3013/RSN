/**
 * @file file_registry.cpp
 * @brief Implementation of FileRegistry class
 */

#include "core/file_registry.h"

namespace rsn {
namespace core {

FileRegistry::FileRegistry() {}

FileRegistry::~FileRegistry() {}

void FileRegistry::AddFile(const RecoverableFile& file) {
  files_.push_back(file);
}

const std::vector<RecoverableFile>& FileRegistry::GetFiles() const {
  return files_;
}

const RecoverableFile* FileRegistry::GetFileById(uint64_t id) const {
  for (const auto& file : files_) {
    if (file.id == id) {
      return &file;
    }
  }
  return nullptr;
}

size_t FileRegistry::GetFileCount() const {
  return files_.size();
}

void FileRegistry::Clear() {
  files_.clear();
}

}  // namespace core
}  // namespace rsn
