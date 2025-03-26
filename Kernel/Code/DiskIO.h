#ifndef DISK_IO_H
#define DISK_IO_H

#include "Types.h"

// Reads sectors from disk into memory
bool ReadSectors(uint32_t lba, void* buffer, uint32_t sectorCount);

// Writes sectors from memory to disk
bool WriteSectors(uint32_t lba, const void* buffer, uint32_t sectorCount);

#endif // DISK_IO_H
