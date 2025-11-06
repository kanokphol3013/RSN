/**
 * @file file_carving.h
 * @brief File carving engine for signature-based recovery
 */

#ifndef RSN_CORE_FILE_CARVING_H_
#define RSN_CORE_FILE_CARVING_H_

#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>

namespace rsn {
namespace core {

/**
 * @brief File signature structure
 */
struct FileSignature {
  std::string file_type;              // e.g., "JPEG", "PNG", "PDF"
  std::string extension;              // e.g., ".jpg", ".png", ".pdf"
  std::vector<uint8_t> header;        // File header signature
  std::vector<uint8_t> footer;        // File footer signature (optional)
  size_t max_file_size;               // Maximum expected file size
  bool has_footer;                    // Whether footer signature exists
};

/**
 * @brief File carving engine
 *
 * Implements signature-based file carving for recovering files
 * without file system metadata.
 */
class FileCarvingEngine {
 public:
  FileCarvingEngine();
  ~FileCarvingEngine();

  /**
   * @brief Initialize the carving engine with signature database
   */
  bool Initialize();

  /**
   * @brief Carve files from a device/image
   * @param device_path Path to device or image file
   * @param output_dir Directory to save carved files
   * @return Number of files successfully carved
   */
  uint64_t CarveFiles(const std::string& device_path,
                      const std::string& output_dir);

  /**
   * @brief Add a custom file signature
   */
  void AddSignature(const FileSignature& signature);

  /**
   * @brief Get supported file types
   */
  std::vector<std::string> GetSupportedFileTypes() const;

  /**
   * @brief Set maximum scan size (in bytes)
   */
  void SetMaxScanSize(uint64_t size);

  /**
   * @brief Get carving statistics
   */
  struct CarvingStats {
    uint64_t bytes_scanned;
    uint64_t files_found;
    uint64_t files_carved;
    double scan_time_seconds;
  };
  CarvingStats GetStats() const;

 private:
  std::unordered_map<std::string, FileSignature> signatures_;
  CarvingStats stats_;
  uint64_t max_scan_size_;

  // Helper methods
  void LoadDefaultSignatures();
  bool MatchesSignature(const uint8_t* data, size_t size,
                       const std::vector<uint8_t>& signature);
  uint64_t FindFooter(const uint8_t* data, size_t start, size_t max_size,
                     const std::vector<uint8_t>& footer);
};

/**
 * @brief Common file signatures database
 */
namespace FileSignatures {

// Image formats
extern const FileSignature JPEG;
extern const FileSignature PNG;
extern const FileSignature GIF;
extern const FileSignature BMP;
extern const FileSignature TIFF;

// Document formats
extern const FileSignature PDF;
extern const FileSignature DOCX;
extern const FileSignature XLSX;
extern const FileSignature PPTX;

// Archive formats
extern const FileSignature ZIP;
extern const FileSignature RAR;
extern const FileSignature GZIP;
extern const FileSignature TAR;

// Video formats
extern const FileSignature MP4;
extern const FileSignature AVI;
extern const FileSignature MKV;

// Audio formats
extern const FileSignature MP3;
extern const FileSignature WAV;
extern const FileSignature FLAC;

}  // namespace FileSignatures

}  // namespace core
}  // namespace rsn

#endif  // RSN_CORE_FILE_CARVING_H_
