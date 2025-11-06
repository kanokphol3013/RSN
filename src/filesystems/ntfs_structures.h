/**
 * @file ntfs_structures.h
 * @brief NTFS data structures and constants
 *
 * This file contains NTFS-specific data structures based on the
 * official NTFS specification from Microsoft.
 */

#ifndef RSN_FILESYSTEMS_NTFS_STRUCTURES_H_
#define RSN_FILESYSTEMS_NTFS_STRUCTURES_H_

#include <cstdint>

namespace rsn {
namespace filesystems {
namespace ntfs {

/**
 * @brief NTFS Boot Sector (512 bytes)
 */
#pragma pack(push, 1)
struct BootSector {
  uint8_t  jump[3];                    // Jump instruction
  char     oem_id[8];                  // "NTFS    "
  uint16_t bytes_per_sector;           // Usually 512
  uint8_t  sectors_per_cluster;        // Power of 2
  uint16_t reserved_sectors;           // 0
  uint8_t  zeros1[3];                  // Must be 0
  uint16_t unused1;                    // Not used
  uint8_t  media_descriptor;           // 0xF8 (hard disk)
  uint16_t zeros2;                     // Must be 0
  uint16_t sectors_per_track;          // Geometry
  uint16_t number_of_heads;            // Geometry
  uint32_t hidden_sectors;             // 0
  uint32_t unused2;                    // Not used
  uint32_t unused3;                    // Not used
  uint64_t total_sectors;              // Total volume size
  uint64_t mft_lcn;                    // MFT logical cluster number
  uint64_t mft_mirror_lcn;             // MFT mirror LCN
  int8_t   clusters_per_mft_record;    // Size of MFT record
  uint8_t  reserved1[3];               // Reserved
  int8_t   clusters_per_index_record;  // Size of index record
  uint8_t  reserved2[3];               // Reserved
  uint64_t volume_serial_number;       // Volume serial number
  uint32_t checksum;                   // Boot sector checksum
  uint8_t  bootstrap_code[426];        // Boot code
  uint16_t signature;                  // 0xAA55
};
#pragma pack(pop)

/**
 * @brief MFT Record Header (FILE record)
 */
#pragma pack(push, 1)
struct MFTRecordHeader {
  char     signature[4];               // "FILE"
  uint16_t update_sequence_offset;     // Offset to update sequence
  uint16_t update_sequence_size;       // Size in words
  uint64_t logfile_sequence_number;    // $LogFile sequence number
  uint16_t sequence_number;            // Sequence number
  uint16_t hard_link_count;            // Hard link count
  uint16_t first_attribute_offset;     // Offset to first attribute
  uint16_t flags;                      // Flags (in use, directory)
  uint32_t used_size;                  // Real size of FILE record
  uint32_t allocated_size;             // Allocated size of FILE record
  uint64_t base_record;                // Base FILE record
  uint16_t next_attribute_id;          // Next attribute ID
  uint16_t padding;                    // Alignment
  uint32_t mft_record_number;          // MFT record number
};
#pragma pack(pop)

/**
 * @brief MFT Record Flags
 */
enum MFTRecordFlags : uint16_t {
  MFT_RECORD_IN_USE = 0x0001,          // Record is in use
  MFT_RECORD_IS_DIRECTORY = 0x0002     // Record is a directory
};

/**
 * @brief Attribute Header (common to all attributes)
 */
#pragma pack(push, 1)
struct AttributeHeader {
  uint32_t attribute_type;             // Attribute type code
  uint32_t length;                     // Length of attribute
  uint8_t  non_resident_flag;          // 0 = resident, 1 = non-resident
  uint8_t  name_length;                // Length of name
  uint16_t name_offset;                // Offset to name
  uint16_t flags;                      // Flags
  uint16_t attribute_id;               // Unique ID
};
#pragma pack(pop)

/**
 * @brief Attribute Types
 */
enum AttributeType : uint32_t {
  ATTR_STANDARD_INFORMATION = 0x10,
  ATTR_ATTRIBUTE_LIST = 0x20,
  ATTR_FILE_NAME = 0x30,
  ATTR_OBJECT_ID = 0x40,
  ATTR_SECURITY_DESCRIPTOR = 0x50,
  ATTR_VOLUME_NAME = 0x60,
  ATTR_VOLUME_INFORMATION = 0x70,
  ATTR_DATA = 0x80,
  ATTR_INDEX_ROOT = 0x90,
  ATTR_INDEX_ALLOCATION = 0xA0,
  ATTR_BITMAP = 0xB0,
  ATTR_REPARSE_POINT = 0xC0,
  ATTR_EA_INFORMATION = 0xD0,
  ATTR_EA = 0xE0,
  ATTR_LOGGED_UTILITY_STREAM = 0x100,
  ATTR_END = 0xFFFFFFFF
};

/**
 * @brief $FILE_NAME Attribute (0x30)
 */
#pragma pack(push, 1)
struct FileNameAttribute {
  uint64_t parent_directory;           // Parent directory reference
  uint64_t creation_time;              // File creation time
  uint64_t modification_time;          // File modification time
  uint64_t mft_modification_time;      // MFT record change time
  uint64_t access_time;                // Last access time
  uint64_t allocated_size;             // Allocated size of file
  uint64_t real_size;                  // Real size of file
  uint32_t flags;                      // File attributes
  uint32_t reparse_value;              // Reparse point tag
  uint8_t  filename_length;            // Length of filename
  uint8_t  namespace_type;             // Namespace (DOS, Win32, etc.)
  // Followed by filename in Unicode (2 * filename_length bytes)
};
#pragma pack(pop)

/**
 * @brief $STANDARD_INFORMATION Attribute (0x10)
 */
#pragma pack(push, 1)
struct StandardInformation {
  uint64_t creation_time;              // File creation time
  uint64_t modification_time;          // File modification time
  uint64_t mft_modification_time;      // MFT record change time
  uint64_t access_time;                // Last access time
  uint32_t file_attributes;            // File attributes
  uint32_t max_versions;               // Maximum versions
  uint32_t version_number;             // Version number
  uint32_t class_id;                   // Class ID
};
#pragma pack(pop)

/**
 * @brief File Attributes Flags
 */
enum FileAttributes : uint32_t {
  FILE_ATTR_READONLY = 0x0001,
  FILE_ATTR_HIDDEN = 0x0002,
  FILE_ATTR_SYSTEM = 0x0004,
  FILE_ATTR_ARCHIVE = 0x0020,
  FILE_ATTR_DEVICE = 0x0040,
  FILE_ATTR_NORMAL = 0x0080,
  FILE_ATTR_TEMPORARY = 0x0100,
  FILE_ATTR_SPARSE_FILE = 0x0200,
  FILE_ATTR_REPARSE_POINT = 0x0400,
  FILE_ATTR_COMPRESSED = 0x0800,
  FILE_ATTR_OFFLINE = 0x1000,
  FILE_ATTR_NOT_CONTENT_INDEXED = 0x2000,
  FILE_ATTR_ENCRYPTED = 0x4000
};

/**
 * @brief Constants
 */
constexpr uint32_t NTFS_SIGNATURE = 0x5346544E;  // "NTFS" in little-endian
constexpr uint16_t BOOT_SIGNATURE = 0xAA55;
constexpr uint32_t FILE_SIGNATURE = 0x454C4946;  // "FILE" in little-endian
constexpr size_t MFT_RECORD_SIZE = 1024;         // Usually 1KB

}  // namespace ntfs
}  // namespace filesystems
}  // namespace rsn

#endif  // RSN_FILESYSTEMS_NTFS_STRUCTURES_H_
