#ifndef __CsEventLog_h__
#define __CsEventLog_h__

//	Constants, structures, and function dir *.hdeclarations used for event logging.

#if defined _SPIDER_DRV_
	#define		EVENT_LOG_NAME		"Cs8xxxWdf"
#elif defined _FASTBALL_DRV_
	#define		EVENT_LOG_NAME		"CscdG8Wdf"
#elif defined _RABBIT_DRV_
	#define		EVENT_LOG_NAME		"CsxyG8Wdf"
#elif defined _SPLENDA_DRV_
	#define		EVENT_LOG_NAME		"Cs16xyyWdf"
#elif defined _JDEERE_DRV_
	#define		EVENT_LOG_NAME		"CscdG12Wdf"
#elif defined _COBRAMAXPCIE_DRV_
	#define		EVENT_LOG_NAME		"CsEcdG8Wdf"
#elif defined _DECADE_DRV_
	#define		EVENT_LOG_NAME		"CsE12xGyWdf"
#elif defined _HEXAGON_DRV_
	#define		EVENT_LOG_NAME		"CsE16bcdWdf"
#elif defined _DEM0_DRV_
	#define	    EVENT_LOG_NAME		"CsDemo"
#elif defined _REMOTE_DRV_
	#define		EVENT_LOG_NAME		"CsDevRemote"
#elif defined _GAGE_SERVER_	
	#define		EVENT_LOG_NAME		"GageServer" 
#else
	#define		EVENT_LOG_NAME		"GageDriverWdf"
#endif

class CsEventLog
{
public:
	CsEventLog(void);
	~CsEventLog(void);

#ifdef _WINDOWS_
	BOOL Report(DWORD dwErrorId, LPTSTR lpMsgIn);
#endif
#ifdef __linux__
	BOOL ReportLinux(const char *dwErrorId, const char* lpMsgIn);
#endif
private:
	HANDLE m_hEventLog;
	DWORD  m_dwError;
};

#ifdef	__linux__
/* TODO: convert to logging */
#define Report(id, ...) ReportLinux(#id, __VA_ARGS__)
#endif
#endif // __CsEventLog_h__