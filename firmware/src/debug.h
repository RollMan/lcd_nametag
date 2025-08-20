#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifndef __AVR_ARCH__
// Debugging utils especially for unit test on building host (--build)
#include <stdio.h>
// Print debug info especially for unit test on building host.
#define DEBUG_PRINTF(...) \
    { printf(__VA_ARGS__); }

// Print debug info common with --build and --host.
#define DEBUG_PRINT(...) \
    { printf(__VA_ARGS__); }
#define DEBUG_PRINTLN(...) \
    { printf(__VA_ARGS__); printf("\n");}

#else //__AVR_ARCH__
// Debugging units on target host (--host) where a binary runs.
    #ifdef EBUG
    // TODO:
    #define DEBUG_PRINTF(...)
    #define DEBUG_PRINT(...)
    #define DEBUG_PRINTLN(...)
    #else //EBUG
    #define DEBUG_PRINTF(...)
    #define DEBUG_PRINT(...)
    #define DEBUG_PRINTLN(...)
    #endif // EBUG
#endif //__AVR_ARCH__

#endif //__DEBUG_H__
