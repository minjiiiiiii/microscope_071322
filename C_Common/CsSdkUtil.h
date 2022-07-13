#ifndef __CS_SDK_UTIL_H__
#define __CS_SDK_UTIL_H__

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "CsTypes.h"

#include <CsAppSupport.h>

#ifdef __cplusplus
extern "C"{
#endif

 #ifndef MIN			
 #define MIN(x, y) (((x) < (y)) ? (x) : (y))
 #endif

typedef long LONG;
typedef long long LONGLONG;

typedef union _LARGE_INTEGER {
  struct {
    DWORD LowPart;
    LONG  HighPart;
  };
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

uInt32 GetTickCount();
void	QueryPerformanceCounter(LARGE_INTEGER *TickCount);
void	QueryPerformanceFrequency(LARGE_INTEGER *Frq);
#ifdef __cplusplus
}
#endif

#endif // __CS_SDK_UTIL_H__