/*
 * CsLinuxPort.h
 *
 *  Created on: 10-Sep-2008
 *      Author: Ricky Goldstein
 */

#ifndef GAGE_LINUX_PORT_H_
#define GAGE_LINUX_PORT_H_

#if defined __linux__

#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <stdint.h>
#include <dlfcn.h>

#include <linux/limits.h>

#include <syslog.h>

#define __cdecl    /* nothing */
#define __stdcall  /* nothing */
#define __fastcall /* nothing */

#define TRUE 1
#define FALSE 0

#define PAGE_READWRITE 		0x04
#define MEM_COMMIT 			0x100
#define MEM_RELEASE 		0x8000

// integer types

typedef unsigned long int	DWORD;
typedef unsigned long* 		LPDWORD;
typedef unsigned short		WORD;
typedef unsigned char 		BYTE;

typedef void				VOID;
typedef void				*PVOID;

typedef unsigned long 		ULONG_PTR;
typedef unsigned int 		UINT_PTR;
typedef ULONG_PTR 			DWORD_PTR;

typedef void *				HMODULE;
typedef void *				FARPROC;
typedef int64_t				int64;
typedef uint64_t			uint64;

typedef char 				TCHAR;

typedef const char*			LPCTSTR;
typedef const char*			LPCSTR;
typedef char* 				LPTSTR;


typedef int					INT;
typedef char				CHAR;
typedef short				SHORT;
typedef long				LONG;
typedef long*				LPLONG;
typedef CHAR				*PCHAR,  *CHAR_PTR;
typedef SHORT				*PSHORT, *SHORT_PTR;
typedef LONG				*PLONG,  *LONG_PTR;

typedef unsigned int		UINT;
typedef unsigned char		UCHAR;
typedef unsigned short		USHORT;
typedef unsigned long		ULONG;

typedef UCHAR				*PUCHAR;
typedef USHORT				*PUSHORT;
typedef ULONG				*PULONG;
typedef long				NTSTATUS;
typedef long long			LONGLONG;
typedef unsigned long long	ULONGLONG;

typedef char* 				LPSTR;
typedef void*				LPOVERLAPPED;
typedef void*				OVERLAPPED;

typedef int					CSDRVSTATUS;

#ifndef BOOL
typedef int	BOOL;
#endif

#ifndef BOOLEAN
typedef unsigned char BOOLEAN;
#endif

typedef int		FILE_HANDLE;


typedef union _LARGE_INTEGER
{
	struct
	{
		ULONG	LowPart;
		LONG	HighPart;
	};
	LONGLONG	QuadPart;
}LARGE_INTEGER, *PLARGE_INTEGER;

typedef float	real32; 
typedef double	real64; 

typedef sem_t* SEM_HANDLE;
typedef pthread_mutex_t* MUTEX_HANDLE;
typedef void* TIMER_HANDLE;
typedef void* HANDLE;
typedef void* LPVOID;

typedef pthread_mutex_t CRITICAL_SECTION;

#define _MAX_PATH	255
#define  MAX_PATH PATH_MAX
#define _ASSERT assert


#define LOCK    pthread_mutex_lock
#define UNLOCK  pthread_mutex_unlock

#define EnterCriticalSection pthread_mutex_lock
#define LeaveCriticalSection pthread_mutex_unlock


#define Sleep(x) usleep(x*1000)


#if !defined(_TRUNCATE)
	#define _TRUNCATE ((size_t)-1)
#endif

//look into making into a function and call set error if we fail
#define ZeroMemory(x,y)			memset(x,0,y)
#define CopyMemory				memcpy

#define VirtualAlloc(a,b,c,d)	calloc(b, 1)//make into a function and call set error if we fail
#define VirtualFree(a,b,c)		free(a)


// Various utility macros that are defined in Windows

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

#define MIN(a,b) (((a) < (b)) ? (a) : (b))


#define MAKEWORD(a,b) ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))
#define MAKELONG(a,b) ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define LOWORD(l) ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l) ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define LOBYTE(w) ((BYTE)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w) ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))

#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))


// These are defined so we can use TCHAR compatible string calls

#if !defined(_T)
	#define _T(arg) arg
#endif

#define tstrcpy  strcpy
#define tstrncpy strncpy
#define _tcscat  strcat
#define _tcscpy(str1, str2) strcpy(str1, str2)
#define _tcslen(str1) strlen(str1)
#define _tfopen(filename, access)  fopen(filename, access)
#define _gettc    getc
#define _puttc    putc
#define _stscanf  sscanf
#define _stprintf sprintf
#define _tprintf  printf
#define _tstoi   atoi
#define _ttoi    atoi
#define _tstoi64 atol
#define _tcscmp strcmp
#define _tcsnccmp strncmp
#define _tcsncmp strncmp
#define _tcsicmp strcasecmp

// Defines for Windows specific string routines

#define lstrcpy  strcpy
#define lstrcpyn strncpy
#define lstrlen strlen
#define wsprintf sprintf
#define lstrcat strcat

// Defines for Windows specific routines
#define CopyMemory memcpy
#define OutputDebugString(x) printf("%s", x)
#define _ecvt ecvt

// Defines for Microsoft's new safe string routins

#define _tcstok_s(a,b,c) strtok()
#define _stprintf_s(a,b,c, ...)	sprintf(a,c,__VA_ARGS__)
#define sprintf_s			snprintf
#define _sntprintf_s(a,b,c,d,e) snprintf(a,c,d,e) //RG - CHECK IF RIGHT
#define _tcscat_s(a, b, c)		strcat(a, c)
#define	_tcscpy_s(a, b, c)		strcpy(a, c)
#define	strcpy_s(a, b, c)		strcpy(a, c)
#define strncpy_s(a, b, c, d)	strncpy(a, c, d)
#define _tcsncpy_s(a, b, c, d)  strncpy(a, c, d) //RG ? CHECK IF RIGHT
//#define strcat_s(a, b, c)       strcat(a, c)  //RG causes problems, is already defined in GageWrapper.c


// Socket defines

#define SD_SEND 1
#define SOCKET_ERROR (-1)

#define INVALID_SOCKET (SOCKET)0
#define SOCKET_WOULD_BLOCK EWOULDBLOCK
#define SOCKET_IN_PROGRESS EINPROGRESS
#define SOCKET_INVALID_VALUE EINVAL
#define SO_DONTLINGER -1

typedef unsigned int SOCKET;
typedef socklen_t SOCKET_LENGTH;

#define closesocket close

#define DEMO_TRACE_LEVEL 	1
#define RM_TRACE_LEVEL		2

#if defined(_DEBUG)  ||  defined(RELEASE_TRACE)
#define TRACE(a, ...) syslog(LOG_DEBUG, __VA_ARGS__)
#else
#define TRACE(a, ...)
#endif

#define AddToMessageLog(a, ...) syslog(LOG_INFO, __VA_ARGS__)

#define UNREFERENCED_PARAMETER(a) (a)


inline LONG InterlockedCompareExchange(volatile LONG *target, LONG new_value, LONG old_value) {
#if defined(__GNUC__) && \
        (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1))
  return __sync_val_compare_and_swap(target, old_value, new_value);
#else
#ifdef __i486__
  // Use cmpxchgl: http://0xcc.net/blog/archives/000128.html
  LONG result;
  asm volatile ("lock; cmpxchgl %1, %2"
                : "=a" (result)
                : "r" (new_value), "m" (*(target)), "0"(old_value)
                : "memory", "cc");
  return result;
#else  // __i486__
#error dont know how to InterlockedCompareExchange
#endif  // __i486__
#endif  // __GNUC__
}

inline LONG InterlockedExchange(LONG volatile *dest, LONG val)
{
    LONG ret;
#ifdef __x86_64__
    __asm__ __volatile__( "lock; xchgl %0,(%1)" : "=r" (ret) :"r" (dest), "0" (val) : "memory" );
#else
    do ret = *dest; while (!__sync_bool_compare_and_swap( dest, ret, val ));
#endif
    return ret;
}

inline LONG InterlockedIncrement(volatile LONG *target)
{
	return __sync_add_and_fetch(target, 1);
}

inline LONG InterlockedDecrement(volatile LONG *target)
{
	return __sync_sub_and_fetch(target, 1);
}
#endif // __linux__
#endif /* GAGE_LINUX_PORT_H_ */
