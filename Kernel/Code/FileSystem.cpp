#define RING_0_LIMIT 0x20000000 // 512MB
#define RING_1_LIMIT 0x40000000 // 1GB
#define RING_2_LIMIT 0x60000000 // 1.5GB
#define RING_3_LIMIT 0xFFFFFFFF // Full addressable space

// File access flags
#define FILE_READ  0x01
#define FILE_WRITE 0x02
#define FILE_EXEC  0x04
#define FILE_HIDDEN 0x08

struct FileEntry {
    char name[11];       // FAT32 8.3 filename
    unsigned char attributes;  // FAT32 file attributes
    unsigned int startCluster;
    unsigned int fileSize;
    unsigned char accessFlags; // Read/Write/Execute
    unsigned char ownerRing;   // Ring level of file
};

unsigned char GetCurrentRing();
bool FindFile(const char* filename, FileEntry* file);
void ReadClusters(unsigned int startCluster, void* buffer, unsigned int size);
void WriteClusters(unsigned int startCluster, const void* data, unsigned int size);
unsigned int FindFreeCluster();
void UpdateFATTable(unsigned int startCluster, unsigned int size);

bool CheckRingAccess(unsigned char requiredRing) {
    unsigned char currentRing = GetCurrentRing();
    return currentRing <= requiredRing;
}

bool ReadFile(const char* filename, void* buffer, unsigned int size) {
    FileEntry file;
    if (!FindFile(filename, &file)) return false;
    
    if (!CheckRingAccess(file.ownerRing)) return false;
    
    ReadClusters(file.startCluster, buffer, size);
    return true;
}

bool WriteFile(const char* filename, const void* data, unsigned int size, unsigned char accessFlags) {
    FileEntry file;
    if (FindFile(filename, &file)) {
        if (!CheckRingAccess(file.ownerRing)) return false;
    } else {
        file.startCluster = FindFreeCluster();
        file.fileSize = size;
        file.accessFlags = accessFlags;
        file.ownerRing = GetCurrentRing();
    }
    
    WriteClusters(file.startCluster, data, size);
    UpdateFATTable(file.startCluster, size);
    return true;
}

bool ModifyFilePermissions(const char* filename, unsigned char newFlags) {
    FileEntry file;
    if (!FindFile(filename, &file)) return false;
    if (!CheckRingAccess(file.ownerRing)) return false;
    
    file.accessFlags = newFlags;
    return true;
}

bool DeleteFile(const char* filename) {
    FileEntry file;
    if (!FindFile(filename, &file)) return false;
    if (!CheckRingAccess(file.ownerRing)) return false;
    
    UpdateFATTable(file.startCluster, 0);
    return true;
}
