/**
 * @file ext4_parser.cpp
 * @brief Implementation of ext4 parser
 */

#include "filesystems/ext4_parser.h"
#include "core/file_registry.h"
#include "common/logging.h"

namespace rsn {
namespace filesystems {

Ext4Parser::Ext4Parser() : is_valid_(false) {}
Ext4Parser::~Ext4Parser() {}

FileSystemType Ext4Parser::GetType() const {
  return FileSystemType::EXT4;
}

bool Ext4Parser::Initialize(const std::string& device_path) {
  device_path_ = device_path;
  common::Log(common::LogLevel::INFO, "ext4 Parser initialized for: " + device_path);
  // TODO: Implement ext4 superblock validation
  is_valid_ = true;
  return true;
}

bool Ext4Parser::Parse() {
  if (!is_valid_) {
    last_error_ = "Parser not initialized";
    return false;
  }
  common::Log(common::LogLevel::INFO, "Parsing ext4 file system...");
  // TODO: Implement ext4 parsing
  return true;
}

std::vector<core::RecoverableFile> Ext4Parser::GetDiscoveredFiles() const {
  return discovered_files_;
}

std::string Ext4Parser::GetLastError() const {
  return last_error_;
}

bool Ext4Parser::IsValid() const {
  return is_valid_;
}

}  // namespace filesystems
}  // namespace rsn
