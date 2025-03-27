#ifndef STDTYPES_H
#define STDTYPES_H

// Define size_t as an unsigned integer type
typedef unsigned int size_t;

// Define bool, true, and false if not using stdbool.h
#ifndef __cplusplus
typedef enum { false, true } bool;
#endif

#endif // STDTYPES_H
