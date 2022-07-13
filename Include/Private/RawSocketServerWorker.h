#ifndef __RAW_SOCKET_SERVER_WORKER_H__
#define __RAW_SOCKET_SERVER_WORKER_H__

#if defined (_WIN32)
#pragma once
#else
#include <pthread.h>
#endif

#include "misc.h"
#include "ThreadDispatcher.h"
#include "RawSocket.h"

/////////////////////////////////////////////////////////////////////////////
// class CWizRawSocketServerWorker
class CWizRawSocketListener : public CWizMultiThreadedWorker
{
public:
	// Exceptions hierarchy
	struct Xeption {}; // common
	struct XCannotCreate : public Xeption {};  // createsocket fail
	struct XCannotSetHook : public Xeption {}; // WSASetBlockingHook fail
	struct XCannotSetHookEvent : public Xeption {}; // SetEven fail
	struct XCannotListen : public Xeption {};		// Listen fail
// Constructors:
	CWizRawSocketListener (int nPort); // Constructor do almost nothing
	CWizRawSocketListener();
// Destructor:
	virtual ~CWizRawSocketListener ();

public:
// Operations:
// Virtual operations:
	// Interface for CWizThreadDispatcher
	virtual void Prepare();
#if defined (_WIN32)
	virtual BOOL WaitForData (HANDLE hShutDownEvent);
	virtual BOOL TreatData   (HANDLE hShutDownEvent, HANDLE hDataTakenEvent);
#else
	virtual BOOL WaitForData (pthread_cond_t& hShutDownEvent);
	virtual BOOL TreatData   (pthread_cond_t* hShutDownEvent, pthread_cond_t& hDataTakenEvent);
#endif
	virtual void CleanUp();
	// Pure virtual function - do something
	// with the socket connected to the client.
	// Should return TRUE if needs to continue I/O.
	virtual BOOL ReadWrite   (CWizReadWriteSocket& socket) = 0;

	CWizSyncSocket* GetListenSocket() { return m_pListenSocket; } //RG
protected:

// Implementation:
// Virtual implementation:
protected:
// Data Members:
	CWizSyncSocket*				m_pListenSocket;
	int							m_nPort;
	SOCKET						m_hAcceptedSocket;
};

#endif // __RAW_SOCKET_SERVER_WORKER_H__
