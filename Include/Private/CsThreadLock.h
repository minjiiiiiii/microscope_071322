#include <stdlib.h>


#if defined(__linux__) && !defined(__KERNEL__)
	#include <CsLinuxPort.h>
	#include <misc.h>
	#include <CWinEventHandle.h>//TODO::RG
#endif


#pragma once

class Critical_Section
{
private:
	CRITICAL_SECTION m_sect;
	int				 m_nCount;

public:
	Critical_Section(Critical_Section& sect) {m_sect = sect.m_sect; ::InitializeCriticalSection(&m_sect); }
	Critical_Section() { ::InitializeCriticalSection(&m_sect); }
	~Critical_Section() { ::DeleteCriticalSection(&m_sect); }

	void acquire() { ::EnterCriticalSection(&m_sect); }
	void release() { ::LeaveCriticalSection(&m_sect); }

#ifdef __linux__
	bool tryAcquire() 
	{
		return true;
	}
#else
	bool tryAcquire() 
	{ 
		return ( TRUE == ::TryEnterCriticalSection(&m_sect) );
	}

	int getCount(){ return m_nCount;}
#endif

};

#if defined(_WIN32)

class _MutexLock
{
public:
	_MutexLock(const char* const srtName = NULL) 
	{
		strcpy_s(m_strName, sizeof(m_strName), "_CsMutexLock");
		if(NULL != srtName )
		{
			strncpy_s( m_strName, _countof(m_strName), srtName,  _TRUNCATE);
		}
		m_nCount = 0;
		m_hnd = ::CreateMutex(NULL, FALSE, m_strName);
	}

	~_MutexLock() {if(NULL != m_hnd)  ::CloseHandle(m_hnd); }

	void acquire()
	{
		::WaitForSingleObject(m_hnd, INFINITE); 
		m_nCount++; 
	}
	bool tryAcquire() { return WAIT_TIMEOUT != ::WaitForSingleObject(m_hnd, 0); }
	void release() 
	{ 
		::ReleaseMutex(m_hnd);
		m_nCount--;
	}
	int getCount(){ return m_nCount;}

private:
	HANDLE m_hnd;
	int m_nCount;
	char m_strName[30];
};



class _SemaphoreLock
{
public:
	_SemaphoreLock(const char* const srtName = NULL) 
	{
		strcpy_s(m_strName, sizeof(m_strName), "_CsMutexLock");
		if(NULL != srtName )
		{
			strncpy_s( m_strName, _countof(m_strName), srtName,  _TRUNCATE);
		}
		m_nCount = 1;
		m_hnd = ::CreateSemaphore(NULL, 1, 1, m_strName);
	}

	~_SemaphoreLock() {if(NULL != m_hnd)  ::CloseHandle(m_hnd); }

	void acquire() 
	{ 
		::WaitForSingleObject(m_hnd, INFINITE); 
		m_nCount--;
	}
	bool tryAcquire() 
	{ 
		if(WAIT_TIMEOUT != ::WaitForSingleObject(m_hnd, 0))
		{
			m_nCount--;
			return true;
		}
		return false; 
	}
	void release() 
	{ 
		::ReleaseSemaphore(m_hnd, 1, NULL); 
		m_nCount++;
	}
	int getCount(){ return m_nCount;}

private:
	HANDLE m_hnd;
	int m_nCount;
	char m_strName[30];
};

#else

class _MutexLock
{
public:
	_MutexLock(const char* const srtName = NULL)
	{
		strcpy_s(m_strName, sizeof(m_strName), "_CsMutexLock");
		if(NULL != srtName )
		{
			strncpy_s( m_strName, _countof(m_strName), srtName,  _TRUNCATE);
		}
//RG	m_hnd = ::CreateMutex(NULL, FALSE, m_strName);
		m_hMutex = ::MakeMutex(NULL, FALSE, m_strName);
	}

	~_MutexLock() {if(NULL != m_hnd)  ::CloseHandle(m_hnd); }

	void acquire() { ::WaitForSingleObject(m_hnd, INFINITE); }

	bool tryAcquire() { return WAIT_TIMEOUT != ::WaitForSingleObject(m_hnd, 0); }
	void release() { ::ReleaseMutex(m_hMutex); }

private:
//	HANDLE m_hnd;
	EVENT_HANDLE m_hnd;
	MUTEX_HANDLE m_hMutex;
	char m_strName[30];
};


#endif


template< class Key > class Lock_Guard
{
public:
	Lock_Guard(Key aKey): _key(aKey) { lock(); }
	Lock_Guard() { lock(); }
	~Lock_Guard() { unlock(); }
    
	void lock() {_key.acquire(); }
	void unlock() { _key.release(); }
	bool attepmt() { return _key.tryAcquire();}
	int  count() { return _key.getCount();}
    
private:
	Key _key;
};

