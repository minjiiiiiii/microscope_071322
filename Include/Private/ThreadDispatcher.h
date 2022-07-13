#ifndef __THREAD_DISPATCHER_H__
#define __THREAD_DISPATCHER_H__

#include "misc.h"

#if defined (_WIN32)
#pragma once

#include <windows.h>
#include <crtdbg.h>

#else
#include <assert.h>
#include <pthread.h>
#include <linux/stddef.h>

void* CWizThreadDispatcherFun(LPVOID pParam);
void* CWizThreadDispatcher_WorkerThread_Fun(LPVOID pParam);
#endif
/////////////////////////////////////////////////////////////////////////////
// Class Interface for CWizThreadDispatcher.
// The derived class must implement:
// 1. WaitForData.
//	The function received handle to event which becomes signalled
// when the server shuts down.
// The function must return FALSE if received shut down signal,
// or wait until some data becomes availible (or whatever) and
// return TRUE;
// 2. TreatData
//	The function received handle to event which becomes signalled
// when the server shuts down, and the handle to event when it
// started to treat data (or whatever), i.e. when it's safe to
// call WaitForData again.
// IMPORTANT!!! You MUST Set hDataTakenEvent somewhere in the
// function, or deadlock will occur!!! DUMNED!!!
// The function must return FALSE if received shut down signal,
// or wait until data treatmen finished (or whatever) and
// return TRUE;
class CWizMultiThreadedWorker
{
	public:
		CWizMultiThreadedWorker() {}
		virtual ~CWizMultiThreadedWorker() {}

		virtual void Prepare     () = 0;
#if defined (_WIN32)
		virtual BOOL WaitForData (HANDLE hShutDownEvent) = 0;
		virtual BOOL TreatData   (HANDLE hShutDownEvent, HANDLE hDataTakenEvent) = 0;
#else
		virtual BOOL WaitForData (pthread_cond_t& hShutDownEvent) = 0;
		virtual BOOL TreatData (pthread_cond_t* hShutDownEvent, pthread_cond_t& hDataTakenEvent) = 0;
#endif

		virtual void CleanUp     () =  0;

	class Stack
		{
		public:
			Stack(CWizMultiThreadedWorker& rW)
				: m_rW(rW)
				{ m_rW.Prepare(); }

			~Stack()
				{ m_rW.CleanUp(); }

			Stack& operator = (Stack&){ _ASSERT(0); return *this;}

		private:
			CWizMultiThreadedWorker& m_rW;
		};
};
/////////////////////////////////////////////////////////////////////////////
// class CWizThreadDispatcher
class CWizThreadDispatcher
{
public:
// Constructors:
	// Usially MaxThreads = (2..5)*NumberOfProcessors
	CWizThreadDispatcher (CWizMultiThreadedWorker &rWorker, int MaxThreads = 5);
// Destructor:
	virtual ~CWizThreadDispatcher ();

	CWizThreadDispatcher& operator = (CWizThreadDispatcher&){ _ASSERT(0); return *this;}

public:
// Operations:
	void	Start();	// Starts Dispatching
	void	Stop(BOOL bWait = TRUE); // Signals to stop and (?) waits for all threads to exit
	void	WaitShutDown();			 // Waits for all threads to exit after signaling to stop
	void	SetShutDownEvent() { m_ShutDownEvent.Set(); }

public:
// Classes
	// Exceptions the class can throw: (+CMemoryException)
	struct Xeption {};
	struct XCannotCreate : public Xeption {};
	struct XWaitFailed : public Xeption {};
	// Event wrapper
	class Event
	{
	public:
		Event(BOOL bManualReset);
		~Event();
		void	Set();
#if defined (_WIN32)
		HANDLE	m_h;
#else
		pthread_cond_t m_h;
#endif
	};
protected:
	class WorkerThread
	{
	public:
#if defined (_WIN32)
		WorkerThread(CWizMultiThreadedWorker &rWorker,
				HANDLE hDataReadyEvent,
				HANDLE hStartedTreatEvent,
				HANDLE hShutDownEvent);
#else
		WorkerThread(CWizMultiThreadedWorker &rWorker,
				pthread_cond_t& hDataReadyEvent,
				pthread_cond_t& hStartedTreatEvent,
				pthread_cond_t& hShutDownEvent);
#endif

		WorkerThread& operator = (WorkerThread& ){ _ASSERT(0); return *this;}

#ifdef __linux__
		friend void *CWizThreadDispatcher_WorkerThread_Fun(LPVOID pParam);
#else
		friend UINT __stdcall CWizThreadDispatcher_WorkerThread_Fun(LPVOID pParam);
#endif
	private:
		UINT Run();

		enum { DataWaitHCount = 2 };
		CWizMultiThreadedWorker&	m_rWorker;
#if defined (_WIN32)
		HANDLE	m_hDataWait [DataWaitHCount];
		HANDLE	m_hStartedTreatEvent;
#else
		pthread_cond_t *m_hDataWait [DataWaitHCount];
		pthread_cond_t& m_hStartedTreatEvent;
#endif
	};
// Implementation:
#ifdef __linux__
	friend void* CWizThreadDispatcherFun(LPVOID pParam);
	friend void* CWizThreadDispatcher_WorkerThread_Fun(LPVOID pParam);
#else
	friend UINT __stdcall CWizThreadDispatcherFun(LPVOID pParam);
	friend UINT __stdcall CWizThreadDispatcher_WorkerThread_Fun(LPVOID pParam);
#endif
// Virtual implementation:
	virtual UINT  Run();
// Data members
	enum { StartedTreatmentEventsCount = 2};

	int							m_nMaxThreads;
	CWizMultiThreadedWorker&	m_rWorker;
	Event						m_ShutDownEvent;
	Event						m_HasDataEvent;
	Event						m_StartedDataTreatEvent;
#if defined (_WIN32)
	HANDLE						m_ahStartedTreatmentEvents[StartedTreatmentEventsCount];
#else
	pthread_cond_t*				m_ahStartedTreatmentEvents[StartedTreatmentEventsCount];
#endif

#if defined (_WIN32)
	HANDLE						m_hThisThread;
	HANDLE*						m_ahWorkersHandles;
	HANDLE						m_hDispatchThread;
#else
	pthread_t					m_hThisThread;
	pthread_t*					m_ahWorkersHandles;
	pthread_cond_t				m_hDispatchThread;
	pthread_mutex_t				m_mFinishMutex;
#endif
};

/////////////////////////////////////////////////////////////////////////////
inline CWizThreadDispatcher::Event::Event(BOOL bManualReset)
//	: m_h (::CreateEvent(NULL, bManualReset, FALSE, NULL))
{
#if defined (_WIN32)
      m_h  = ::CreateEvent(NULL, bManualReset, FALSE, NULL);
	if (m_h == NULL)
       		throw CWizThreadDispatcher::XCannotCreate();
#else

        ::pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
        ::pthread_mutex_lock(&mut);
        ::pthread_cond_init(&m_h, NULL);
        ::pthread_mutex_unlock(&mut);
        if (&m_h == NULL)
                throw CWizThreadDispatcher::XCannotCreate();

#endif
}

inline CWizThreadDispatcher::Event::~Event()
{
#if defined (_WIN32)
	if (m_h != NULL)
		::CloseHandle(m_h);
#else
//      if (&m_h != NULL)
//            ::pthread_cond_destroy(&m_h);
#endif
}

inline void CWizThreadDispatcher::Event::Set()
{
#if defined (_WIN32)
	_ASSERT(m_h != NULL);
	SetEvent(m_h); // May fail because is set already RICKY
#else
	_ASSERT(&m_h != NULL);
        pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_lock(&mut);
        pthread_cond_broadcast(&m_h);
        pthread_mutex_unlock(&mut);
#endif
}
///////////////////////////////////////////////////////////////////
#endif // __THREAD_DISPATCHER_H__

