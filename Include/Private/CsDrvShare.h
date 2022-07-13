/////////////////////////////////////////////////////////////
// CsDrvShare.h
/////////////////////////////////////////////////////////////


#ifndef _CS_DRV_MAP_MEMORY_H_
#define _CS_DRV_MAP_MEMORY_H_

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

#define _PAGE_SIZE    4096
#define _PAGE_SHIFT   12

template<typename It> class DrvMemShared 
{
public:
	DrvMemShared(LPCTSTR tstrName, int size, bool bPageAligned  = false, It* pIt = NULL);

	~DrvMemShared();
	It* it(){return _pIt;}

	bool IsCreated(){return 0 != (int)m_hMapFile;}
	bool IsMapped(){return NULL != _pIt;}
	void Clear(void){if(IsMapped()){memset(_pIt, 0, sizeof(It));}}
	bool IsMapExisted() {return m_bMapExist;};
	TCHAR* GetMappedName() { return m_tchMappedName; }
	int GetMapSize() { return mapSize; }

private:
	It*   _pIt;
	DrvMemShared(){};
	bool	m_bMapExist;
	int   m_hMapFile;
   int   mapSize;                // real map size, may be bigger if page aligned
   int   Size;                   // size of structure
	TCHAR  m_tchMappedName[_MAX_PATH];
};

template <typename It>	DrvMemShared<It>::DrvMemShared(LPCTSTR tstrName, int size, bool bPageAligned, It* pIt):
	_pIt(NULL)
{
   m_bMapExist = true;
	strcpy(m_tchMappedName, tstrName);
   // just open the share memory
   if ((m_hMapFile = shm_open(m_tchMappedName, O_RDWR , S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH))==-1)
   {
      // Create if not exist
		if ( ENOENT == ::GetLastError() ) // shared memory already exists so lets open it
      {
         m_hMapFile = shm_open(m_tchMappedName, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
         m_bMapExist = false;
      }
   }
	if ( -1 == m_hMapFile )
   {
		perror("shm_open failed: ");
   }

	if ( m_hMapFile > 0 )
	{
      if (bPageAligned)
         mapSize = (size + _PAGE_SIZE) & ~(_PAGE_SIZE -1);
      else
         mapSize = size;      
      
		if (-1 == fchmod(m_hMapFile, 0666))
		{
			fprintf(stdout, "Cannot set read / write permissions on shared memory\n");
		}

		if ( ftruncate(m_hMapFile, mapSize) == -1 )
		{
    		perror("ftruncate: ");
		}
		else
		{
			_pIt = (It*)mmap (NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, m_hMapFile, 0);

			if (MAP_FAILED == _pIt)
			{
				perror("mmap: ");
			}
      }   
	}
}

template <typename It>	DrvMemShared<It>::~DrvMemShared()
{
	if (NULL != _pIt)
	{
		if (0 != munmap(_pIt, sizeof(It)))
		{
			perror("munmap failed: ");
		}
	}

	if (m_hMapFile)
	{
		if (close(m_hMapFile) == -1)
			perror("close failed: ");
	}
}

#endif // _CS_DRV_MAP_MEMORY_H_
