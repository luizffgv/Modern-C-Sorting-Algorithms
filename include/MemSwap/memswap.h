#ifndef MEMSWAP_H
#define MEMSWAP_H

#include <stddef.h>





/**
 * @brief Swaps contents of two memory locations.
 *
 * Should not be used if the locations overlap.
 *
 * @param sz Size of each memory location
 * @param first Address of first location
 * @param second Address of second location
 */
void MemSwap(size_t sz, void *first, void *second);

#endif // #ifndef MEMSWAP_H
