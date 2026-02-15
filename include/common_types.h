#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <stdint.h>

#ifdef _WIN32
    #define DLL_EXPORT extern "C" __declspec(dllexport)
    #define DLL_IMPORT extern "C" __declspec(dllimport)
#else
    #define DLL_EXPORT extern "C"
    #define DLL_IMPORT extern "C"
#endif

#endif // COMMON_TYPES_H