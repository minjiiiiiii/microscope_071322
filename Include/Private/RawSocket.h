#ifndef __RAW_SOCKET_H__
#define __RAW_SOCKET_H__

#if defined (_WIN32)
	#pragma once
	#include <winsock2.h>
#else
	#ifndef __KERNEL__
		#include <string.h>
		#include <sys/socket.h>
		#include <netinet/in.h> // for ntohl, htonl, ntohs, htons
		#include <arpa/inet.h> // for inet_addr
		#include <netdb.h>     // for hostent and gethostbyname()
		#include <stdlib.h>
		#include <CsLinuxPort.h>

		typedef struct  hostent HOSTENT;
		typedef HOSTENT* LPHOSTENT;
		typedef struct in_addr* LPIN_ADDR;
		typedef sockaddr SOCKADDR;
		typedef sockaddr_in SOCKADDR_IN;

		#define _CVTBUFSIZE (309+40)
	#endif // __KERNEL
#endif // _WIN32

#include <stdlib.h>
#include "misc.h"

/////////////////////////////////////////////////////////////////////////////
// class CWizSyncSocket
// Simple encapsulation of the SOCKET handle and
// simple operations with it.
class CWizSyncSocket
{
public:
	// Exception class if createsocket fails in constructor
	struct XCannotCreate {};
	// Constructors
	CWizSyncSocket(int nPort);	// Connects for listening
								// on the port nPort
	CWizSyncSocket(SOCKET h = INVALID_SOCKET); // incapsulates
								// ready socket handle
	// Destructor
	~CWizSyncSocket();

	BOOL	Create(int nPort);	// Creates listening socket
	void	Close();			// Closes socket
	SOCKET	Accept();			// waits to accept connection
								// and returns a descriptor
								// for the accepted packet
	BOOL	Connect(LPCTSTR lpszHostAddress, UINT nHostPort );
								// establishes a connection to a peer
	SOCKET	H() const { return m_hSocket; }
								// returns a handle of the socket
	BOOL GetHostName(LPTSTR lpszAddress, size_t nAddrSize, UINT& rSocketPort);
	BOOL GetPeerName(LPTSTR lpszAddress, size_t nAddrSize, UINT& rPeerPort);

protected:
	void Init(SOCKET h);		// initialize data members
	BOOL InitializeSocket(int nPort);
								// associates a local address
								// with a socket and establishes
								// a socket to listen for incoming connection
	int	 SetIntOption(int level, int optname, int val);
								// sets a socket option
	SOCKET	m_hSocket;			// socket handle

};

/////////////////////////////////////////////////////////////////////////////
// class CWizReadWriteSocket
// Class provides synchronous I/O for the socket
class CWizReadWriteSocket : public CWizSyncSocket
{
	public:
		struct X {};
		struct XRead	: public X {};
		struct XWrite	: public X {};
	public:
		// constructor usually receives a handle from Accept
		CWizReadWriteSocket(SOCKET h = INVALID_SOCKET)
			: CWizSyncSocket(h) {}

		// Read/write any data. Both functions return
		// an actual number of bytes read/written,
		// accept pointer to data and number of bytes.
		int	Read(void *pData, int nLen);
		int	Write(const void *pData, int nLen);
		// Read/write strings. nLen is in characters,
		// not bytes.
		BOOL ReadString  (char*  lpszString, int nLen);
		BOOL ReadString  (WCHAR* lpszString, int nLen); //RICKY - CHECK
		// If nLen == -1, the actual length is calculated
		// assuming lpszString is zero-terminated.
		BOOL WriteString (const char* lpszString, int nLen);
		BOOL WriteString (const WCHAR* lpszString, int nLen = -1); //RICKY - CHECK
};

/////////////////////////////////////////////////////////////////////////////
template<class T>
BOOL	RawRead(CWizReadWriteSocket& rSocket, T& data)
{
	return (rSocket.Read (&data, sizeof(T)) == sizeof(T));
}

template<class T>
BOOL	RawWrite(CWizReadWriteSocket& rSocket, const T& data)
{
	return (rSocket.Write (&data, sizeof(T)) == sizeof(T));
}

/////////////////////////////////////////////////////////////////////////////
template<class T>
void	RawReadX(CWizReadWriteSocket& rSocket, T& data)
{
	if (!RawRead(rSocket, data))
		throw CWizReadWriteSocket::XRead();
}

template<class T>
void	RawWriteX(CWizReadWriteSocket& rSocket, const T& data)
{
	if (!RawWrite(rSocket, data))
		throw CWizReadWriteSocket::XWrite();
}

/////////////////////////////////////////////////////////////////////////////

inline CWizReadWriteSocket& operator>>(CWizReadWriteSocket& rSocket, int& i)
{
	int ni;
	RawReadX(rSocket, ni);
	i = ntohl(ni);
	return rSocket;
}

inline CWizReadWriteSocket& operator<<(CWizReadWriteSocket& rSocket, int i)
{
	int ni = htonl(i);
	RawWriteX(rSocket, ni);
	return rSocket;
}

/////////////////////////////////////////////////////////////////////////////
inline CWizReadWriteSocket& operator>>(CWizReadWriteSocket& rSocket, char& i)
{
	RawReadX(rSocket, i);
	return rSocket;
}

inline CWizReadWriteSocket& operator<<(CWizReadWriteSocket& rSocket, char i)
{
	RawWriteX(rSocket, i);
	return rSocket;
}

/////////////////////////////////////////////////////////////////////////////
inline CWizReadWriteSocket& operator>>(CWizReadWriteSocket& rSocket, short& i)
{
	short ni;
	RawReadX(rSocket, ni);
	i = ntohs(ni);
	return rSocket;
}

inline CWizReadWriteSocket& operator<<(CWizReadWriteSocket& rSocket, short i)
{
	short ni = htons(i);
	RawWriteX(rSocket, ni);
	return rSocket;
}
/////////////////////////////////////////////////////////////////////////////
inline CWizReadWriteSocket& operator>>(CWizReadWriteSocket& rSocket, double& d)
{
	const int MAX_CHAR = 30;
	char buffer[MAX_CHAR];

	if(!rSocket.ReadString(buffer,MAX_CHAR))
		throw CWizReadWriteSocket::XRead();

	d = atof(buffer);
	return rSocket;
}

inline CWizReadWriteSocket& operator<<(CWizReadWriteSocket& rSocket, double d)
{
	int     decimal,   sign;
	char    *buffer = NULL;
	int     precision = 10;
	int		err;

	buffer = (char*) malloc(_CVTBUFSIZE);
	err = _ecvt_s(buffer, _CVTBUFSIZE, d, precision, &decimal, &sign);

	if (NULL == buffer || 0 == *buffer || 0 != err)
		buffer = (char *)"0";

	if(!rSocket.WriteString(buffer, (int)strlen(buffer)))
		throw CWizReadWriteSocket::XWrite();

	free(buffer);

	return rSocket;
}

/////////////////////////////////////////////////////////////////////////////
inline CWizReadWriteSocket& operator>>(CWizReadWriteSocket& rSocket, u_long& ul)
{
	u_long l;

	RawReadX(rSocket, l);
	ul = ntohl(l);
	return rSocket;
}

inline CWizReadWriteSocket& operator<<(CWizReadWriteSocket& rSocket, u_long ul)
{
	const u_long l = htonl(ul);
	RawWriteX(rSocket, l);
	return rSocket;
}

#endif //__RAW_SOCKET_H__
