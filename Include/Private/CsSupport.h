
#pragma once

#include <Windows.h>
#include <tchar.h>

// Functions Enable/Disable File System redirection for 32-bit process under 64-bit OS
typedef BOOL (WINAPI *LPFN_WOW64DISABLEWOW64FSREDIRECTION) (PVOID*);
typedef BOOL (WINAPI *LPFN_WOW64REVERTWOW64FSREDIRECTION) (PVOID);

//Function to determine if we're running under a 64 bit OS
typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

// Function to extract the 32-bit emulation System folder on 64-Bit OS
typedef UINT (WINAPI *LPFN_GETSYSTEMWOW64DIRECTORY) (LPTSTR, UINT);

//-----------------------------------------------------------------------------
inline BOOL Is32on64(void)
{
	#ifdef CS_WIN64
		return FALSE;
	#else
		BOOL bIsWow64 = FALSE;
		LPFN_ISWOW64PROCESS pfnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), 
																	_T("IsWow64Process"));
		if (NULL != pfnIsWow64Process)
		{
			if (!pfnIsWow64Process(GetCurrentProcess(),&bIsWow64))
			{
				// Assume 32 bit OS
				bIsWow64 = FALSE;
			}
		}
		return bIsWow64;
	#endif
}
