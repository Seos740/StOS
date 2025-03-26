#ifndef GDT_H
#define GDT_H

#include "Types.h" // Ensure types like uint32_t are defined

// Loads the GDT (must be implemented in assembly)
extern "C" void LoadGDT();

// Retrieves the current ring level
extern "C" uint8_t GetCurrentRing();

#endif // GDT_H
