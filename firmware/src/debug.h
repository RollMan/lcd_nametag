#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifndef __AVR_ARCH__
// Debugging utils especially for unit test on building host (--build)
#include <stdio.h>
// Print debug info especially for unit test on building host.
#define DEBUG_PRINTF(format, ...) printf(format, __VA_ARGS__)

// Print debug info common with --build and --host.
#define DEBUG_PRINT(message) fputs(message, stdout)

#define DEBUG_PRINTLN(message) puts(message)

#define DEBUG_PRINTHEX(hex) printf("%x", hex)

#else //__AVR_ARCH__
// Debugging units on target host (--host) where a binary runs.
#ifdef EBUG
// TODO:
#define DEBUG_PRINTF(format, ...)
#define DEBUG_PRINT(message)
#define DEBUG_PRINTLN(message)
#define DEBUG_PRINTHEX(hex)
#else // EBUG
#define DEBUG_PRINTF(format, ...)
#define DEBUG_PRINT(message)
#define DEBUG_PRINTLN(message)
#define DEBUG_PRINTHEX(hex)
#endif // EBUG
#endif //__AVR_ARCH__

#endif //__DEBUG_H__
