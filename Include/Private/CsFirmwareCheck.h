#pragma once
#include "CsPrivatePrototypes.h"
#include <string>
using namespace std;

#define SKIP_CHECK_FIRMWARE_KEY _T("SYSTEM\\CurrentControlSet\\Services")
#define SKIP_CHECK_FIRMWARE_VALUE_NAME _T("SkipCheckFirmware")

// CFirmwareCheck class

class CFirmwareCheck
{
public:
	CFirmwareCheck(DWORD dwBoardType)
	{
		HKEY	hKey;
		TCHAR	cValueBuffer[50];
		DWORD 	dwValueBuffSize;
		DWORD	dwDataBuffer;
		DWORD 	dwDataBuffSize;
		DWORD	dwDataType;

		m_strBoardName = BoardTypeToName(dwBoardType);
		string strRegKey = SKIP_CHECK_FIRMWARE_KEY;
		strRegKey += _T("\\");
		strRegKey += m_strBoardName;
		strRegKey += _T("\\Parameters");

		// The HKEY_LOCAL_MACHINE\SYSTEM\\CurrentControlSet\\Services\Csxxx\Parameters field has
		// to exist for the CompuScope system to run so we can always assume that it is there
		long lRetVal = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, strRegKey.c_str(), 0, KEY_QUERY_VALUE | KEY_SET_VALUE, &hKey);
		if (ERROR_SUCCESS == lRetVal)
		{
			dwValueBuffSize = sizeof(cValueBuffer);
			dwDataBuffSize = sizeof(DWORD);
			lRetVal = ::RegQueryValueEx(hKey, SKIP_CHECK_FIRMWARE_VALUE_NAME, NULL, 
							&dwDataType, (LPBYTE)&dwDataBuffer, &dwDataBuffSize); 
			if (ERROR_SUCCESS == lRetVal)
			{
				m_dwValue = dwDataBuffer;
				m_bRemove = false;
			}
			else // if the value didn't exist we want to get rid of it afterwards
				m_bRemove = true;
			
			// If the value was set to 0, we want to change it to 1. If it 
			// was already 1 we don't have to change it. If the value didn't exist
			// we want to set it to 1.
			if (0 == m_dwValue || m_bRemove)
			{
				dwDataBuffer = 1;
				dwDataBuffSize = sizeof(DWORD);
				lRetVal = ::RegSetValueEx(hKey, SKIP_CHECK_FIRMWARE_VALUE_NAME, NULL, REG_DWORD, 
							(LPBYTE)&dwDataBuffer, dwDataBuffSize);

			}	
		}
		::RegCloseKey(hKey);
	};
	
	~CFirmwareCheck(void)
	{
		HKEY	hKey;
		DWORD	dwDataBuffer;
		DWORD 	dwDataBuffSize;

		CString strRegKey = SKIP_CHECK_FIRMWARE_KEY;
		strRegKey += _T("\\");
		strRegKey += (m_strBoardName.c_str());
		strRegKey += _T("\\Parameters");

		long lRetVal = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, strRegKey, 0, KEY_READ | KEY_WRITE, &hKey);
		if (ERROR_SUCCESS == lRetVal)
		{
			if (m_bRemove)
			{
				::RegDeleteValue(hKey, SKIP_CHECK_FIRMWARE_VALUE_NAME);
			}
			else
			{
				dwDataBuffer = static_cast<DWORD>(m_dwValue);
				dwDataBuffSize = sizeof(DWORD);
				lRetVal = ::RegSetValueEx(hKey, _T("SkipCheckFirmware"), NULL, REG_DWORD, 
						(LPBYTE)&dwDataBuffer, dwDataBuffSize);
			}
			::RegCloseKey(hKey);
		}
	};
private:

	string BoardTypeToName(uInt32 u32BoardType)
	{
		if (CsIsSpiderBoard(u32BoardType))
			return _T("Cs8xxx");
		else if (CsIsCombineBoard(u32BoardType))
		{
			if (CS14200_BOARDTYPE == u32BoardType)
				return _T("Cs14200");
			else if (CS14105_BOARDTYPE == u32BoardType)
				return _T("Cs14105");
			else if (CS12400_BOARDTYPE == u32BoardType)
				return _T("Cs12400");
			else if (CS14200v2_BOARDTYPE == u32BoardType)
				return _T("Cs14200x");
			else 
				return _T("Unknown");
		}
		else
			return _T("Unknown");
	};

	bool m_bRemove;
	DWORD m_dwValue;
	string m_strBoardName;
};
