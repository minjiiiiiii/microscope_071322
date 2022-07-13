// CsVersionDB.h : main header file for the CsVersionDB DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "msglog.h"

#include "CVersionSet.h"

// String constant for DSN Creation
const TCHAR DB_DSN_NAME[]		=	"GageVersionDB";
const TCHAR	DB_DESC[]			=	"DESCRIPTION=Keeps the driver version information from different installs";

const TCHAR UPDATE_DB_DSN_NAME[]	=	"CS VersionUpdate DB";
const TCHAR	UPDATE_DB_DESC[]		=	"DESCRIPTION=Temporary DB to update the Gage CS Version DB";

const TCHAR ACCESS_DB_DRIVER[]	= "Microsoft Access Driver (*.mdb)";
const TCHAR	SELECT_ALL_QUERY[]	= "SELECT * FROM CompuScopeDrv";

const TCHAR	DEFAULT_UPDATE_DB_NAME[] = "GageVersionUpdateDB.mdb";

// Functions Prototype
BOOL UpdateDB(LPCTSTR = NULL);

BOOL QueryRecords(LPTSTR szFileName, int nSizeName, 
				  long* plMajorNumber, long* plMinorNumber, 
				  long* plPatchNumber, long* plBuildNumber,
				  LPTSTR szCategory, int nSizeCategory,
				  BOOL*	pbMandatory);


// Support Function Prototypes
BOOL CreateDataSourceLink(LPCTSTR strDSN_Name, LPCTSTR strDSN_Desc, LPCTSTR strDatabase, DWORD* pdwErrorCode);
BOOL RemoveDataSourceLink(LPCTSTR strDSN_Name, DWORD* pdwErrorCode);

BOOL RegisterErrorHandling(void);
void ReportEventMsg(WORD wEventType, DWORD dwEventID, WORD cInserts, LPCTSTR szMsg);

class CCsVersionDBApp : public CWinApp
{
public:
	CCsVersionDBApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};