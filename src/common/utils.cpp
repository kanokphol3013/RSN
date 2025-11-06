/**
 * @file utils.cpp
 * @brief Implementation of common utilities
 */

#include "common/utils.h"
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>
#include <sstream>
#include <iomanip>

namespace rsn {
namespace common {

bool DirectoryExists(const std::string& path) {
  struct stat info;
  if (stat(path.c_str(), &info) != 0) {
    return false;
  }
  return (info.st_mode & S_IFDIR) != 0;
}

bool IsWritable(const std::string& path) {
  return access(path.c_str(), W_OK) == 0;
}

bool FileExists(const std::string& path) {
  struct stat info;
  return stat(path.c_str(), &info) == 0;
}

uint64_t GetFileSize(const std::string& path) {
  struct stat info;
  if (stat(path.c_str(), &info) != 0) {
    return 0;
  }
  return static_cast<uint64_t>(info.st_size);
}

std::string FormatBytes(uint64_t bytes) {
  const char* units[] = {"B", "KB", "MB", "GB", "TB"};
  int unit_index = 0;
  double size = static_cast<double>(bytes);

  while (size >= 1024.0 && unit_index < 4) {
    size /= 1024.0;
    unit_index++;
  }

  std::ostringstream oss;
  oss << std::fixed << std::setprecision(2) << size << " " << units[unit_index];
  return oss.str();
}

std::string ToUpper(const std::string& str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::toupper);
  return result;
}

std::string ToLower(const std::string& str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

}  // namespace common
}  // namespace rsn
