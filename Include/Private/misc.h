#ifndef __MISC_H__
#define __MISC_H__

#include "CsTypes.h"

#if defined(__linux__) && !defined(__KERNEL__)
	#include "CsLinuxPort.h"
	#include "CWinEventHandle.h"
#endif

#define FUNCTION_NAME_BUFFER_SIZE 10

#define _CsRm_WinSock_Port_32	2143
#define _CsRm_WinSock_Port_64	2145

#if defined(CS_WIN64)
	#define _CsRm_WinSock_Port _CsRm_WinSock_Port_64
#else
	#define _CsRm_WinSock_Port _CsRm_WinSock_Port_32
#endif

#if defined(_WIN32)

#include <winsock2.h>
#include "CsTypes.h" // needs to be after winsock2.h because CsTypes.h includes windows.h

#define SOCKET_WOULD_BLOCK WSAEWOULDBLOCK
#define SOCKET_IN_PROGRESS WSAEINPROGRESS
#define SOCKET_INVALID_VALUE WSAEINVAL
#define LOCK    EnterCriticalSection
#define UNLOCK  LeaveCriticalSection


typedef int SOCKET_LENGTH;
typedef HANDLE MUTEX_HANDLE;
typedef HANDLE TIMER_HANDLE;

#else

#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>

#endif  // _WIN32

#ifdef __cplusplus
extern "C"{
#endif

#ifdef __linux__

int GetLastError(void);
int WSAGetLastError(void);
void WSASetLastError(int nError);

void InitializeCriticalSection(CRITICAL_SECTION *cCriticalSection);
void DeleteCriticalSection(CRITICAL_SECTION *cCriticalSection);
int ReleaseMutex(MUTEX_HANDLE hMutex);

SEM_HANDLE CreateSemaphore(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, long lInitialCount, long lMaximumCount, LPCSTR lpName);
int32 DestroySemaphore(SEM_HANDLE pSemaphore);
BOOL ReleaseSemaphore(SEM_HANDLE hSemaphore, LONG lReleaseCount, LPLONG lpPreviousCount);

DWORD GetCurrentProcessId(void);
HMODULE LoadLibrary(LPCTSTR lpFileName);
BOOL FreeLibrary(HMODULE handle);
FARPROC GetProcAddress(HMODULE handle, LPCSTR lpSymbol);

BOOL IsBadWritePtr(void *p, UINT_PTR ucb); // RG
BOOL IsBadReadPtr(const void *p, UINT_PTR ucb); //RG

DWORD GetTickCount();//RG - JUST FOR NOW

pthread_t GetCurrentThread(void);

int _ecvt_s(char *pBuffer, size_t SizeInBytes, double dValue, int nCount, int *nDec, int *nSign);

#else


#endif

uInt32 GetProcessFromProcessList (uInt32 u32ProcessID);
int32 GetProcessName (uInt32 u32ProcessID, TCHAR *lpProcessName);
void DisplayErrorMessage(int nErrorCode, int nErrorType = 0);

MUTEX_HANDLE MakeMutex(MUTEX_HANDLE hMutex, BOOL bInitialOwner, LPCTSTR strName);
int GetMutex(MUTEX_HANDLE hMutex);
void DestroyMutex(MUTEX_HANDLE hRmMutex);

void CalculateTimeActive(DWORD dwTimeStarted, DWORD *dwHours, DWORD *dwMinutes, DWORD *dwSeconds, DWORD *dwMilliseconds);

#ifdef __cplusplus
}
#endif

#endif // __MISC_H__
