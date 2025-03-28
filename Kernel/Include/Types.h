#pragma once

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

#ifdef __UINT64_TYPE__  // Check if the compiler already defines it
typedef __UINT64_TYPE__ uint64_t;
#else
typedef unsigned long long uint64_t;  // Define it manually if needed
#endif
