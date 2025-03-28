#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "StdTypes.h"  // Ensures size_t and bool are defined

#define HEAP_START  0x100000        // 1MB Heap start address
#define HEAP_SIZE   0x100000000     // 4GB Heap size

// Memory block structure
struct Block {
    size_t size;
    bool free;
    Block* next;
};

// Memory Manager Class
class MemoryManager {
private:
    Block* freeList;

public:
    MemoryManager();
    void* malloc(size_t size);
    void free(void* ptr);
};

// Global memory manager instance
extern MemoryManager memManager;

#endif // MEMORY_MANAGER_H
