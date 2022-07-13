#ifndef __RM_H__
#define __RM_H__
#if defined(_WIN32)
#pragma once
#endif

#define SOCKET_BUFFER_LENGTH 2048

#define INDEX           register int
#define WINDEX          register WORD
#define LINDEX          register long
#define DWINDEX         register DWORD

#define RM_WAIT_HINT     3000

#define GAGERESOURCEMANAGERREFRESHEVENT_NAME _T("GageResourceManagerRefreshEvent")
#define GAGERESOURCEMANAGERSTOPTIMERTHREADEVENT_NAME _T("GageResourceManagerStopTimerThreadEvent")
#define GAGERESOURCEMANAGERUSBCOMMUNICATIONEVENT_NAME _T("__CsUsbComEvent")

#if defined (_WIN32)
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <stdio.h>
#include <tchar.h>
#endif

#endif // __RM_H>>
