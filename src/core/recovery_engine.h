/**
 * @file recovery_engine.h
 * @brief Core recovery engine for RecoverySoftNetz
 *
 * This file contains the main recovery engine class that orchestrates
 * file system parsing, pattern matching, and file recovery operations.
 *
 * @author RecoverySoftNetz Team
 * @date 2025-11-06
 * @version 0.1.0
 */

#ifndef RSN_CORE_RECOVERY_ENGINE_H_
#define RSN_CORE_RECOVERY_ENGINE_H_

#include <string>
#include <vector>
#include <memory>
#include <cstdint>

namespace rsn {
namespace core {

// Forward declarations
class FileSystemInterface;
class FileRegistry;

/**
 * @brief Recovery statistics
 */
struct RecoveryStats {
  uint64_t total_files_found;
  uint64_t files_recovered;
  uint64_t bytes_scanned;
  uint64_t bytes_recovered;
  double scan_time_seconds;
  double recovery_rate_percent;
};

/**
 * @brief Main recovery engine class
 *
 * The RecoveryEngine is the central component that coordinates all recovery
 * operations including device scanning, file system parsing, and file recovery.
 *
 * @example
 * @code
 * RecoveryEngine engine;
 * engine.SetDevice("/dev/sda1");
 * engine.SetOutputPath("/recovery/output");
 *
 * if (engine.StartScan()) {
 *   while (engine.IsScanning()) {
 *     RecoveryStats stats = engine.GetStats();
 *     std::cout << "Progress: " << stats.recovery_rate_percent << "%" << std::endl;
 *   }
 *   engine.RecoverAllFiles();
 * }
 * @endcode
 */
class RecoveryEngine {
 public:
  /**
   * @brief Recovery mode enumeration
   */
  enum class RecoveryMode {
    METADATA_ONLY,      ///< Metadata-based recovery (fastest)
    FILE_CARVING,       ///< File signature-based carving
    DEEP_SCAN,          ///< Deep scan with AI-assisted recovery
    RAID_RECONSTRUCT    ///< RAID array reconstruction
  };

  /**
   * @brief Constructor
   */
  RecoveryEngine();

  /**
   * @brief Destructor
   */
  ~RecoveryEngine();

  // Prevent copying
  RecoveryEngine(const RecoveryEngine&) = delete;
  RecoveryEngine& operator=(const RecoveryEngine&) = delete;

  /**
   * @brief Set the device to scan
   * @param device_path Path to the device (e.g., "/dev/sda1")
   * @return true if device is valid and accessible, false otherwise
   */
  bool SetDevice(const std::string& device_path);

  /**
   * @brief Set the output path for recovered files
   * @param output_path Directory path for recovery output
   * @return true if path is valid and writable, false otherwise
   */
  bool SetOutputPath(const std::string& output_path);

  /**
   * @brief Set the recovery mode
   * @param mode Recovery mode to use
   */
  void SetRecoveryMode(RecoveryMode mode);

  /**
   * @brief Start the scan operation
   * @return true if scan started successfully, false otherwise
   */
  bool StartScan();

  /**
   * @brief Stop the current scan operation
   */
  void StopScan();

  /**
   * @brief Check if scan is currently running
   * @return true if scanning, false otherwise
   */
  bool IsScanning() const;

  /**
   * @brief Get current recovery statistics
   * @return RecoveryStats structure with current stats
   */
  RecoveryStats GetStats() const;

  /**
   * @brief Recover all found files
   * @return Number of files successfully recovered
   */
  uint64_t RecoverAllFiles();

  /**
   * @brief Recover specific files by index
   * @param file_indices Indices of files to recover
   * @return Number of files successfully recovered
   */
  uint64_t RecoverFiles(const std::vector<uint64_t>& file_indices);

  /**
   * @brief Get file registry (list of found files)
   * @return Shared pointer to file registry
   */
  std::shared_ptr<FileRegistry> GetFileRegistry() const;

  /**
   * @brief Get last error message
   * @return Error message string
   */
  std::string GetLastError() const;

 private:
  class Impl;  // PIMPL idiom for implementation details
  std::unique_ptr<Impl> pimpl_;

  // Private helper methods
  bool ValidateDevice(const std::string& device_path);
  bool DetectFileSystem();
  void InitializeParser();
};

}  // namespace core
}  // namespace rsn

#endif  // RSN_CORE_RECOVERY_ENGINE_H_
