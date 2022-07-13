//******************************************************************************
// @file          CWinEventHandle.h
// @copyright     GNU Library General Public License
// @version       $Header$
// @author        Richard Dengler
// @language      C++ ANSI V3
// @description   A Wrapper around pthread_cond_t. Used to emulate win32-events.
//******************************************************************************
#ifndef CWINEVENTHANDLE_H
#define CWINEVENTHANDLE_H

#include <pthread.h>
#include <string>
#include <set>


#define WINAPI
#define WINBASEAPI
#define CONST const

#define STATUS_WAIT_0   ((DWORD)0x00000000L)
#define STATUS_TIMEOUT  ((DWORD)0x00000102L)

#define WAIT_TIMEOUT    STATUS_TIMEOUT
#define WAIT_OBJECT_0   ((STATUS_WAIT_0 ) + 0 )
#define INFINITE        0xFFFFFFFF    // Infinite timeout

typedef unsigned long DWORD;
typedef int BOOL;

struct SECURITY_ATTRIBUTES
{
    BOOL bInheritHandle;
};

typedef SECURITY_ATTRIBUTES* LPSECURITY_ATTRIBUTES;
typedef wchar_t WCHAR; // Note: sizeof(wchar_t) == 4!
typedef CONST WCHAR* LPCWSTR;

//class CWinEventHandle;
/*******************************************************************************
Opaque, polymorphal HANDLE. Base class. Used internally.
*******************************************************************************/
class CBaseHandle
{
public:
  CBaseHandle() {}
  virtual ~CBaseHandle() {}
  virtual bool wait(unsigned numMs) { return false; }
  virtual bool close() { return false; }

//  friend class CWinEventHandle;
//protected:
//  CBaseHandle() {}

};

class CWinEventHandle : public CBaseHandle
{
public:
  CWinEventHandle(bool manualReset = false, bool signaled = false, const wchar_t* name = NULL);
  virtual ~CWinEventHandle();
  bool close();
  inline void incRefCount() { m_RefCount++; }
  inline int decRefCount() { m_RefCount--; return m_RefCount; }
  bool signaled() const { return m_Signaled; }
  std::wstring name() const { return m_Name; }
  void reset();
  void signal();
  bool pulse();
  bool wait(unsigned numMs);
  bool wait();
  bool isManualReset() { return m_ManualReset; } // Used in WaitForMultipleObjects()
  void subscribe(CWinEventHandle* subscriber);
  void unSubscribe(CWinEventHandle* subscriber);
private:
  pthread_mutex_t m_Mutex;
  pthread_cond_t m_Cond;
  bool m_ManualReset;
  bool m_Signaled;
  int m_Count;
  int m_RefCount;
  std::wstring m_Name;
  std::set<CWinEventHandle*> m_Subscriber; // Used in WaitForMultipleObjects()
};

typedef CWinEventHandle* EVENT_HANDLE;

WINBASEAPI DWORD WINAPI WaitForSingleObject(EVENT_HANDLE hHandle, DWORD dwMilliseconds);
WINBASEAPI DWORD WINAPI WaitForMultipleObjects(
    DWORD nCount, CONST EVENT_HANDLE *lpHandles, BOOL bWaitAll, DWORD dwMilliseconds);
WINBASEAPI BOOL WINAPI SetEvent(EVENT_HANDLE hEvent);
WINBASEAPI BOOL WINAPI ResetEvent(EVENT_HANDLE hEvent);
WINBASEAPI BOOL WINAPI PulseEvent(EVENT_HANDLE hEvent);  // Used in CRsEvent.cpp

WINBASEAPI EVENT_HANDLE WINAPI CreateEvent(
    LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCWSTR lpName);

WINBASEAPI EVENT_HANDLE WINAPI OpenEvent(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCWSTR lpName);
WINBASEAPI BOOL WINAPI CloseHandle(EVENT_HANDLE hObject);

//WINBASEAPI DWORD WINAPI GetTickCount();

#endif

