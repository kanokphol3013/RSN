/**
 * @file utils.h
 * @brief Common utility functions
 */

#ifndef RSN_COMMON_UTILS_H_
#define RSN_COMMON_UTILS_H_

#include <string>
#include <cstdint>

namespace rsn {
namespace common {

/**
 * @brief Check if a directory exists
 */
bool DirectoryExists(const std::string& path);

/**
 * @brief Check if a path is writable
 */
bool IsWritable(const std::string& path);

/**
 * @brief Check if a file exists
 */
bool FileExists(const std::string& path);

/**
 * @brief Get file size in bytes
 */
uint64_t GetFileSize(const std::string& path);

/**
 * @brief Format bytes to human-readable string (KB, MB, GB)
 */
std::string FormatBytes(uint64_t bytes);

/**
 * @brief Convert string to uppercase
 */
std::string ToUpper(const std::string& str);

/**
 * @brief Convert string to lowercase
 */
std::string ToLower(const std::string& str);

}  // namespace common
}  // namespace rsn

#endif  // RSN_COMMON_UTILS_H_
