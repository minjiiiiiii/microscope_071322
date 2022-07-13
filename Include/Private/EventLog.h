/*****************************************************************************
// File Name:
//		eventlog.h
//
// Contents:
//		Constants, structures, and function
//		declarations used for event logging.
//
******************************************************************************/
#ifndef __GAGE_EVENTLOG__
#define __GAGE_EVENTLOG__


// Header files
//
#include "CsTypes.h"


class	CsEventLog
{
private:
	char	m_szSourceName[128];
public:
	CsEventLog() { strcpy_s(m_szSourceName, sizeof(m_szSourceName), "CsDriver"); };

	void	SetSourceName(char *szSourceName){ strcpy_s(m_szSourceName, sizeof(m_szSourceName), szSourceName); };
	void	ReportEventString(DWORD dwEventID, TCHAR* szMsg1 = 0, TCHAR* szMsg2 = 0 );
};

#endif	// __GAGE_EVENTLOG__

