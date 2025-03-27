#include "KeyboardRead.h"
#include "DiskIO.h"
#include "GDT.h"
#include "FAT32.h"
#include "Types.h"

// Define HEAP properties
#define HEAP_START  0x100000        // Start address of heap (1MB)
#define HEAP_MAX    0x100000000     // 4GB Max Heap
#define PAGE_SIZE   0x1000          // 4KB page size for alignment

// Ensure size_t is correctly defined
#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned long long size_t;  // Support large sizes for 64-bit
#endif

// Define FILE_WRITE flag if not already defined
#ifndef FILE_WRITE
#define FILE_WRITE 0x02  // Example write flag
#endif

// Custom implementation of strlen() (since standard libraries are unavailable)
size_t strlen(const char* str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// System call to write to a file (implemented elsewhere)
extern "C" int syscall_write_to_file(const char* filename, const void* data, size_t size, unsigned char accessFlags);

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
    size_t heapEnd;  // Track current heap boundary

public:
    MemoryManager() {
        freeList = (Block*)HEAP_START;
        freeList->size = PAGE_SIZE - sizeof(Block);
        freeList->free = true;
        freeList->next = nullptr;
        heapEnd = HEAP_START + PAGE_SIZE;
    }

    void* malloc(size_t size) {
        // Ensure alignment
        size = (size + 7) & ~7;  // Align to 8 bytes

        Block* current = freeList;

        while (current) {
            if (current->free && current->size >= size) {
                current->free = false;
                return (void*)(current + 1);
            }
            current = current->next;
        }

        // No available block, expand heap
        expandHeap(size);
        return malloc(size);  // Retry allocation after expanding
    }

    void free(void* ptr) {
        if (!ptr) return;

        Block* block = ((Block*)ptr) - 1;
        block->free = true;
    }

    void expandHeap(size_t size) {
        if (heapEnd + size > HEAP_MAX) {
            debug_log("Heap limit exceeded!");  // Log error
            return; // Prevent exceeding 4GB
        }

        Block* newBlock = (Block*)heapEnd;
        newBlock->size = size - sizeof(Block);
        newBlock->free = true;
        newBlock->next = nullptr;

        // Insert new block at the end of the free list
        Block* last = freeList;
        while (last->next) last = last->next;
        last->next = newBlock;

        heapEnd += size;
    }
};

// Global memory manager instance
MemoryManager memManager;

// Debug function to log messages
void debug_log(const char* message) {
    syscall_write_to_file("/log.txt", message, strlen(message), FILE_WRITE);
}

// Example usage: Writing a file
void Example_WriteFile() {
    const char* filename = "EXAMPLE.TXT";
    const char* data = "Hello, world! This is a test file.";
    size_t size = strlen(data);
    unsigned char accessFlags = FILE_WRITE;

    if (syscall_write_to_file(filename, data, size, accessFlags) == 0) {
        debug_log("Successfully wrote to file.");
    } else {
        debug_log("Failed to write to file.");
    }
}
