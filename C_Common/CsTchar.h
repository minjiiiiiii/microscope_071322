#ifndef __CS_TCHAR_H__
#define __CS_TCHAR_H__


	#ifdef USE_LOCAL_TCHAR

		#define _tmain main
		#define _T
		#define TCHAR char
		#define _TCHAR char

		#define _ftprintf fprintf
		#define _stprintf sprintf
		#define _tcscpy lstrcpy
		#define _tcsicmp stricmp
		#define _stscanf sscanf
		#define _ttol atol
		#define _ttoi atoi
		#define _atoi64 atoi64
		#define _tcslen strlen
		#define _tfopen fopen
		#define _tcsncpy lstrcpyn
		#define _tscanf scanf
		#define _ftscanf fscanf
		#define _fgetts fgets
		#define _tcscmp strcmp
		#define _tcsncmp strncmp
		#define _tcstok strtok
		#define _tcschr strchr
		#define _tcsrchr strrchr
		#define _tcserror strerror
		#define _tfopen fopen
		
		#ifndef _countof
			#define _countof(x) sizeof(x)/sizeof(x[0])
		#endif

	#else
		#ifndef __linux__
			#include <tchar.h>
			#include <conio.h>
		#endif

	#endif // USE_LOCAL_TCHAR

#endif // __CS_TCHAR_H__
