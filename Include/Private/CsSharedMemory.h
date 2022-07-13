/////////////////////////////////////////////////////////////
// CsSharedMemory.h
/////////////////////////////////////////////////////////////


#ifndef _CS_SHARED_MEMORY_H_
#define _CS_SHARED_MEMORY_H_

#ifdef _WIN32
  #include <tchar.h>
  #include <psapi.h>
  #include <stdlib.h>
  #include <shellapi.h>

#elif defined __linux__
  #include <unistd.h>
  #include <stdlib.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <fcntl.h>
  #include <sys/mman.h>
  #include <limits.h>
  #include <stdio.h>
#endif

// Structures for shared mapped memory

#define		GAGE_SW_DRIVERS_REG		"SOFTWARE\\Gage\\Drivers"
#define		MAX_DRIVERS				64	// Max number of drivers
#define		MAX_ACQ_SYSTEMS			50
#define		MAX_CS_PROCESS			50
#define		DRIVER_MAX_NAME_LENGTH	50	// Max Dll name  Ex:"Cs12xx.dll"



#define DISP_SHARED_MEM_FILE		_T("CsDisp_Shared_Memory")
#define RM_SHARED_MEM_FILE			_T("CsRm_Shared_Memory")

typedef struct _DLL_LOOKUP_TABLE
{
	DRVHANDLE		DrvHdl;			// Handle from Low Level Driver
	CSHANDLE		CsHdl;			// Handle from Resource Manager
	char			DrvName[DRIVER_MAX_NAME_LENGTH];	// Dll name

} DLL_LOOKUP_TABLE, *PDLL_LOOKUP_TABLE;

typedef struct _SHARED_DISP_GLOBALS
{
	uInt16	g_NumOfDrivers;			// Number of Drivers
	uInt16	g_NumOfSystems;			// Total number of Acquisition Systems
	DLL_LOOKUP_TABLE g_LookupTable[MAX_ACQ_SYSTEMS];
	char	g_DrvDLLNames[MAX_DRIVERS][DRIVER_MAX_NAME_LENGTH];
	uInt32	g_ProcessAttachedCount;
	int32	g_DispatchDllLastError;
	BOOL	g_bForceIndependantMode;
	volatile long	g_Critical;

#ifdef __linux__
	int		g_RefCount;
#endif

} SHARED_DISP_GLOBALS, *PSHARED_DISP_GLOBALS;

template<typename It> class SharedMem 
{
public:
	SharedMem(LPCTSTR tstrName, bool bForceLocal = false, bool bNoPrefix = false, It* pIt = NULL);
	~SharedMem();
	It* it(){return _pIt;}

#ifdef __linux__
	bool IsCreated(){return 0 != (int)m_hMapFile;}
#else
	bool IsCreated(){return NULL != (void *)m_hMapFile;}
#endif
	bool IsMapped(){return NULL != _pIt;}
	void Clear(void){if(IsMapped()){memset(_pIt, 0, sizeof(It));}}
	bool IsMemInitialized() {return m_bMemInitialized;};

#ifdef __linux__
	TCHAR* GetMappedName() { return m_tchMappedName; }
	int  GetRefCount() { return _pIt->g_RefCount; }
#endif

private:
	It* _pIt;
	SharedMem(){};
	bool	m_bMemInitialized;
#ifdef __linux__
	int m_hMapFile;
//	int m_nRefCount;
#else
	HANDLE m_hMapFile;
#endif
	TCHAR  m_tchMappedName[_MAX_PATH];

};

template <typename It>	SharedMem<It>::SharedMem(LPCTSTR tstrName, bool bForceLocal, bool bNoPrefix, It* pIt):
	_pIt(NULL)
{
#if defined (_WINDOWS_)
	if( !bForceLocal )
	{
		TCHAR	tstrProcessName[_MAX_PATH];
		::GetModuleBaseName( ::GetCurrentProcess(), NULL, tstrProcessName, _countof(tstrProcessName) );

		if (0 == ::_tcsicmp (tstrProcessName, _T("CsTest+.exe")) ||
			(0 == ::_tcsicmp(tstrProcessName, _T("CsTest64.exe"))))
		{
			LPWSTR *szArglist;
			int nArgs;
			szArglist = ::CommandLineToArgvW(::GetCommandLineW(), &nArgs);
			if( NULL != szArglist )
			{
				for(int i = 1; i < nArgs; i++)
				{
					if( _T('-') == szArglist[i][0] || _T('/') == szArglist[i][0]  )
					{
						if ((0 == ::_wcsicmp(szArglist[i]+1, L"disp")) ||
							(0 == ::_wcsicmp(szArglist[i]+1, L"event")))
						{
							bForceLocal = true;
						}
					}
				}
				::LocalFree(szArglist);
			}
		}
		else if (0 == ::_tcsicmp (tstrProcessName, _T("GageServer.exe")))
		{
			bForceLocal = true;
		}
	}

	::_tcscpy_s(m_tchMappedName, _countof(m_tchMappedName), bForceLocal? _T(""):_T("Global\\") );

	if( !bNoPrefix )
	{
#ifdef CS_WIN64
		::_tcscat_s(m_tchMappedName, _countof(m_tchMappedName), _T("64bit-") );
#else
		::_tcscat_s(m_tchMappedName, _countof(m_tchMappedName), _T("32bit-") );
#endif
	}

	TCHAR tstrLowCaseName[_MAX_PATH];
	::_tcscpy_s(tstrLowCaseName, _countof(tstrLowCaseName), tstrName );
	::_tcslwr_s(tstrLowCaseName, _countof(tstrLowCaseName));
	::_tcscat_s(m_tchMappedName, _countof(m_tchMappedName), tstrLowCaseName );

	SECURITY_ATTRIBUTES sa, *pSa(NULL);
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	SECURITY_DESCRIPTOR SD;
	if (::InitializeSecurityDescriptor(&SD, SECURITY_DESCRIPTOR_REVISION))
	{
		// Give the security descriptor a NULL Dacl
		if (::SetSecurityDescriptorDacl(&SD, TRUE, (PACL)NULL, FALSE))
		{
			sa.lpSecurityDescriptor = &SD;
			pSa = &sa;
		}
	}

	m_hMapFile = ::CreateFileMapping( INVALID_HANDLE_VALUE,  pSa, PAGE_READWRITE,  0, sizeof(It),  m_tchMappedName);

	// if we're creating the memory map for the first time let's initialize it
	m_bMemInitialized = ERROR_ALREADY_EXISTS == ::GetLastError();

	if (m_hMapFile != NULL && m_hMapFile != INVALID_HANDLE_VALUE)
	{
		_pIt = (It*)::MapViewOfFile( m_hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(It));
		// if the file didn't exist before let's initialize it
		if (NULL != _pIt && !m_bMemInitialized)
		{
			if( NULL != pIt )
			{
				::CopyMemory( _pIt, pIt, sizeof(It) );
			}
			else
			{
				::ZeroMemory(  _pIt, sizeof(It) );
			}
		}
	}
	else
	{
		m_hMapFile = NULL;
	}

#elif defined __linux__
/*
	TCHAR tstrProcessName[_MAX_PATH];
	uInt32 u32Pid = ::GetCurrentProcessId();
	::GetProcessName(u32Pid, tstrProcessName);
	printf("In %s\n", tstrProcessName);
*/
	m_bMemInitialized = false;

	strcpy(m_tchMappedName, tstrName);
	// TODO: make sure that shared memory is removed before creating if for the first time
	m_hMapFile = shm_open(m_tchMappedName, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

	if ( -1 == m_hMapFile )
	{
		if ( EEXIST == ::GetLastError() ) // shared memory already exists so lets open it
		{
			m_bMemInitialized = true;
			m_hMapFile = shm_open(m_tchMappedName, O_RDWR | O_CREAT, 0666);
			if ( -1 == m_hMapFile )
			{
				perror("shm_open failed: ");
				m_hMapFile = 0;
			}
		}
		else
		{
			perror("shm_open failed: ");
			m_hMapFile = 0; // we couldn't open or create shared memory
		}
	}
	else
	{
		// make sure the shared memory objects have read/write permission for everyone.
		// the call to shm_open will only do this if the umask of the system allows it,
		// while fchmod will do it regardless
		if (-1 == fchmod(m_hMapFile, 0666))
		{
			fprintf(stdout, "Cannot set read / write permissions on shared memory\n");
		}
	}
	if ( 0 != m_hMapFile )
	{
		if ( ftruncate(m_hMapFile, sizeof(It)) == -1 )
		{
    		perror("ftruncate: ");
		}
		else
		{
			_pIt = (It*)mmap (NULL, sizeof(It), PROT_READ | PROT_WRITE, MAP_SHARED, m_hMapFile, 0);

			if (MAP_FAILED == _pIt)
			{
				perror("mmap: ");
			}
			else
			{
				// if the file didn't exist before let's initialize it
				if ( (NULL != _pIt) && !m_bMemInitialized)
				{
					if( NULL != pIt )
					{
						memcpy(_pIt, pIt, sizeof(It));
						_pIt->g_RefCount = 1;
					}
					else
					{
						memset(_pIt, 0, sizeof(It) );
						_pIt->g_RefCount = 1;//RG
					}
				}
				else if ( NULL != _pIt )
				{
					_pIt->g_RefCount++;
				}
			}
		}
	}
	else
	{
		fprintf(stdout, "shmget failed\n");
//    	m_hMapFile = 0;
	}
#endif
}

template <typename It>	SharedMem<It>::~SharedMem()
{
#if defined (_WINDOWS_)
	if (NULL != _pIt)
	{
		::UnmapViewOfFile(_pIt);
	}

	if (NULL != m_hMapFile)
	{
		::CloseHandle(m_hMapFile);
	}

#elif defined __linux__
/*
	TCHAR tstrProcessName[_MAX_PATH];
	uInt32 u32Pid = ::GetCurrentProcessId();
	::GetProcessName(u32Pid, tstrProcessName);
	printf("In %s\n", tstrProcessName);
*/
	if (NULL != _pIt)
	{
		_pIt->g_RefCount--;//RG

		if (0 != munmap(_pIt, sizeof(It)))
		{
			perror("munmap failed: ");
		}
		else
		{
//			_pIt->g_RefCount--;//RG
//			printf("Destructor 2: %s: Reference count = %d\n", m_tchMappedName, u16ReferenceCount);	//RG
		}
	}
/*
	if (0 != m_hMapFile)
	{
		if ( u16ReferenceCount <= 0 )
		{
			if (shm_unlink(m_tchMappedName) == -1)
			{
				perror("shm_unlink failed: ");
			}
		}
	}
*/
#endif
}

#endif // _CS_SHARED_MEMORY_H_
