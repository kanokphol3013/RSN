/**
 * @file logging.cpp
 * @brief Implementation of logging utilities
 */

#include "common/logging.h"
#include <chrono>
#include <iomanip>
#include <ctime>

namespace rsn {
namespace common {

std::string LogLevelToString(LogLevel level) {
  switch (level) {
    case LogLevel::DEBUG:    return "DEBUG";
    case LogLevel::INFO:     return "INFO";
    case LogLevel::WARNING:  return "WARNING";
    case LogLevel::ERROR:    return "ERROR";
    case LogLevel::CRITICAL: return "CRITICAL";
    default:                 return "UNKNOWN";
  }
}

void Log(LogLevel level, const std::string& message) {
  // Get current timestamp
  auto now = std::chrono::system_clock::now();
  auto now_c = std::chrono::system_clock::to_time_t(now);

  std::ostringstream oss;
  oss << "[" << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << "] "
      << "[" << LogLevelToString(level) << "] "
      << message;

  // Output to stderr for WARNING/ERROR/CRITICAL, stdout otherwise
  if (level >= LogLevel::WARNING) {
    std::cerr << oss.str() << std::endl;
  } else {
    std::cout << oss.str() << std::endl;
  }
}

}  // namespace common
}  // namespace rsn
