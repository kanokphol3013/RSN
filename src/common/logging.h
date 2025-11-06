/**
 * @file logging.h
 * @brief Logging utilities for RecoverySoftNetz
 */

#ifndef RSN_COMMON_LOGGING_H_
#define RSN_COMMON_LOGGING_H_

#include <string>
#include <iostream>
#include <sstream>

namespace rsn {
namespace common {

/**
 * @brief Log level enumeration
 */
enum class LogLevel {
  DEBUG,
  INFO,
  WARNING,
  ERROR,
  CRITICAL
};

/**
 * @brief Simple logging function
 * @param level Log level
 * @param message Log message
 */
void Log(LogLevel level, const std::string& message);

/**
 * @brief Get current log level as string
 */
std::string LogLevelToString(LogLevel level);

}  // namespace common
}  // namespace rsn

#endif  // RSN_COMMON_LOGGING_H_
