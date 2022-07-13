
#ifdef _WIN32
#include "windows.h"
#include "stdio.h"
#endif

#include "CsPrototypes.h"
#include "CsTchar.h"
#include "CsSdkMisc.h"
#include "CsAppSupport.h"

static BOOL g_bSuccess = TRUE;


void DisplayErrorString(const int32 i32Status)
{
	TCHAR	szErrorString[255];
	if( CS_FAILED (i32Status) )
	{
		g_bSuccess = FALSE;
	}

	CsGetErrorString(i32Status, szErrorString, 255);
	_ftprintf(stderr, _T("\n%s\n"), szErrorString);
}

void DisplayFinishString(const int32 i32FileFormat)
{
	if ( g_bSuccess )
	{
		if ( TYPE_SIG == i32FileFormat )
		{
			_ftprintf (stdout, _T("\nAcquisition completed. \nAll channels are saved as GageScope SIG files in the current working directory.\n"));
		}
		else if ( TYPE_BIN == i32FileFormat )
		{
			_ftprintf (stdout, _T("\nAcquisition completed. \nAll channels are saved as binary files in the current working directory.\n"));
		}
		else
		{
			_ftprintf (stdout, _T("\nAcquisition completed. \nAll channels are saved as ASCII data files in the current working directory.\n"));

		}
	}
	else
	{
		_ftprintf (stderr, _T("\nAn error has occurred.\n"));

	}
}

BOOL DataCaptureComplete(const CSHANDLE hSystem)
{
	int32 i32Status;
/*
	Wait until the acquisition is complete.
*/
	i32Status = CsGetStatus(hSystem);
	while (!(ACQ_STATUS_READY == i32Status))
	{
		i32Status = CsGetStatus(hSystem);
	}

	return TRUE;
}
