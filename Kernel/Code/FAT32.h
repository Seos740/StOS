#ifndef FAT32_H
#define FAT32_H

#include "Types.h"

// Structure representing a file entry in FAT32
struct FileEntry {
    char name[11];       // FAT32 8.3 filename
    uint8_t attributes;  // FAT32 file attributes
    uint32_t startCluster;
    uint32_t fileSize;
    uint8_t accessFlags; // Read/Write/Execute
    uint8_t ownerRing;   // Ring level of file
};

// Finds a file by name
bool FindFile(const char* filename, FileEntry* file);

// Reads clusters from FAT32
bool ReadClusters(uint32_t startCluster, void* buffer, uint32_t size);

// Writes clusters to FAT32
bool WriteClusters(uint32_t startCluster, const void* data, uint32_t size);

// Finds a free cluster for a new file
uint32_t FindFreeCluster();

// Updates the FAT32 table
void UpdateFATTable(uint32_t startCluster, uint32_t size);

#endif // FAT32_H
