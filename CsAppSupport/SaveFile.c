#include <stdlib.h>
#include "CsAppSupport.h"
#include "CsTchar.h"

#ifdef _WIN32
	#pragma warning(disable : 4996)
#endif

int g_nLastSaveError = 0;
TCHAR g_errorStr[_MAX_PATH];
extern int errno;


#ifdef __linux__

#include <errno.h>

int _get_errno(int* pValue)
{
	if (NULL == pValue)
		return EINVAL;

	*pValue = errno;
	return 0;
}

#endif // __linux__

LPCTSTR CS_SUPPORT_API CsAs_GetLastFileError(void)
{
	_tcsncpy( g_errorStr, _tcserror( g_nLastSaveError ),  _MAX_PATH-1);
	return g_errorStr;
}

int64 CS_SUPPORT_API CsAs_SaveFile(LPCTSTR szFileName, void* pBuffer, const int sType, FileHeaderStruct *pHeader)
{
	FILE* pFile = 0;
	TCHAR* pExt;
	char szSaveFileName[MAX_PATH+1] = {0};

/*
	Error checking.  If anything is wrong return 0, else return
	the number of bytes written to the file.
*/

	if (NULL == pBuffer)
		return (CS_NULL_POINTER);

	if ((NULL == szFileName) || ( 0 == _tcslen(szFileName)))
		return (CS_INVALID_FILENAME);

	if (0 >= pHeader->i64Length)
		return (CS_INVALID_LENGTH);

	_tcscpy(szSaveFileName, szFileName);

/*
	Search for file extension
*/
	pExt = _tcsrchr(szSaveFileName, _T('.'));
	if( NULL == pExt )
		pExt = szSaveFileName + _tcslen(szSaveFileName);

	if( TYPE_SIG == sType )
	{
		CSSIGSTRUCT SigStruct;
		size_t szSize = (size_t)(pHeader->u32SegmentCount)*(size_t)(pHeader->i64Length)*pHeader->u32SampleSize;

/*
		Build SIG file header
*/
		SigStruct.u32Size = sizeof(CSSIGSTRUCT);
		SigStruct.i64SampleRate = pHeader->i64SampleRate;
		SigStruct.i64RecordStart = pHeader->i64Start;
		SigStruct.i64RecordLength = pHeader->i64Length;
		SigStruct.u32RecordCount = pHeader->u32SegmentCount;
		SigStruct.u32SampleBits = 2 == pHeader->u32SampleSize ? 12 : 8;
		SigStruct.u32SampleSize = pHeader->u32SampleSize;
		SigStruct.i32SampleOffset = pHeader->i32SampleOffset;
		SigStruct.i32SampleRes = pHeader->i32SampleRes;
		SigStruct.u32Channel = CS_CHAN_1;
		SigStruct.u32InputRange = pHeader->u32InputRange;
		SigStruct.i32DcOffset = pHeader->i32DcOffset;

		if( NO_TIME_STAMP_VALUE == pHeader->dTimeStamp )
			pHeader->dTimeStamp = 0.;
		SigStruct.TimeStamp.u16Hour         = (uInt16)(pHeader->dTimeStamp/(60*60));
		SigStruct.TimeStamp.u16Minute       = (uInt16)((pHeader->dTimeStamp - SigStruct.TimeStamp.u16Hour*60.) /60);
		SigStruct.TimeStamp.u16Second       = (uInt16)(pHeader->dTimeStamp - SigStruct.TimeStamp.u16Hour*(60*60.) - SigStruct.TimeStamp.u16Minute * 60.);
		SigStruct.TimeStamp.u16Point1Second = (uInt16)((int64)(pHeader->dTimeStamp*10) % 10);
/*
		Save as SIG file extension
*/
		_tcsncpy(pExt, _T(".sig"), MAX_PATH - (int)_tcslen(szSaveFileName) );
		return CsAs_SaveSigFile(szSaveFileName, _T("Channel"), _T("Saved by CsSDK"), pBuffer, szSize, &SigStruct);
	}
	else if ( TYPE_BIN == sType )
	{
		uInt32 u32WriteSize = (uInt32) pHeader->i64Length;

/*
		Save as DAT file extension
*/
		_tcsncpy(pExt, _T(".dat"), MAX_PATH - (int)_tcslen(szSaveFileName) );
		pFile = fopen(szSaveFileName, _T("wb"));
		if (!pFile)
			return (CS_OPEN_FILE_ERROR);

		fwrite(pBuffer, 1, pHeader->u32SampleSize*u32WriteSize, pFile );
		fclose(pFile);
		return CS_SUCCESS;
	}
	else if ( TYPE_BIN_APPEND == sType )
	{
		uInt32	u32WriteSize = (uInt32) pHeader->i64Length;

/*
		Save as DAT file extension
*/
		_tcsncpy(pExt, _T(".dat"), MAX_PATH - (int)_tcslen(szSaveFileName) );
		pFile = fopen(szSaveFileName, _T("ab"));
		if (!pFile)
			return (CS_OPEN_FILE_ERROR);
		fwrite(pBuffer, 1, pHeader->u32SampleSize*u32WriteSize, pFile );
		fclose(pFile);
		return CS_SUCCESS;
	}

/*
	Save as TXT file extension
*/
	_tcsncpy(pExt, _T(".txt"), MAX_PATH - (int)_tcslen(szSaveFileName) );

/*
	Create or open the filename
*/
	pFile = _tfopen(szSaveFileName, _T("w"));
	if (pFile)
	{
		int64	i = 0;
		TCHAR	szFormat[25];
/*
		Set the format string according to
		the type of file requested.
*/
		if (TYPE_DEC == sType)
			_tcscpy(szFormat, _T("%i\n"));
		else if (TYPE_HEX == sType)
			_tcscpy(szFormat, _T("%08X\n"));
		else if (TYPE_FLOAT == sType)
			_tcscpy(szFormat, _T("%f\n"));
		else
		{
			fclose(pFile);
			return(CS_INVALID_PARAMETER);
		}
/*
		Write "header" information
*/

/*
		Check _ftprintf return only first time and in the main save loop.
		The possible error in between will be caught by a later check.
*/
		if ( 0 < _ftprintf(pFile, _T("----------------------\n")) )
		{
			_ftprintf(pFile, _T("Start address  = \t"F64"\n"), pHeader->i64Start);
			_ftprintf(pFile, _T("Data length    = \t"F64"\n"), pHeader->i64Length);
			_ftprintf(pFile, _T("Sample size    = \t%u\n"), pHeader->u32SampleSize);
			_ftprintf(pFile, _T("Sample res     = \t%d\n"), pHeader->i32SampleRes);
			_ftprintf(pFile, _T("Sample offset  = \t%d\n"), pHeader->i32SampleOffset);
			_ftprintf(pFile, _T("Input range    = \t%u\n"), pHeader->u32InputRange);
			_ftprintf(pFile, _T("Dc offset      = \t%d\n"), pHeader->i32DcOffset);
			_ftprintf(pFile, _T("Segment count  = \t%u\n"), pHeader->u32SegmentCount);
			_ftprintf(pFile, _T("Segment number = \t%u\n"), pHeader->u32SegmentNumber);
			_ftprintf(pFile, _T("Average count = \t%u\n"), pHeader->u32AverageCount);

			if (NO_TIME_STAMP_VALUE != pHeader->dTimeStamp)
				_ftprintf(pFile, _T("Time stamp	    = \t%.2f microseconds\n"), pHeader->dTimeStamp);
			_ftprintf(pFile, _T("----------------------\n"));


			if (TYPE_FLOAT == sType)
			{
				float* pfBuffer = (float *)pBuffer;
				for (i = 0; i < pHeader->i64Length; i++)
				{
					if ( 0 > _ftprintf(pFile, szFormat,  pfBuffer[i]))
					{
						_get_errno(&g_nLastSaveError);
						fclose(pFile);
						return (CS_MISC_ERROR);
					}
				}
			}
			else if ((TYPE_DEC == sType)||(TYPE_HEX == sType))
			{
				switch (pHeader->u32SampleSize)
				{
					case 1:
					{
						uInt8* p8Buffer = (uInt8*)pBuffer;
						for (i = 0; i < pHeader->i64Length; i++)
						{
							if ( 0 > _ftprintf(pFile, szFormat, p8Buffer[i]))
							{
								_get_errno(&g_nLastSaveError);
								fclose(pFile);
								return (CS_MISC_ERROR);
							}
						}
					}
					break;

					case 2:
					{
						int16* p16Buffer = (int16*)pBuffer;
						for (i = 0; i < pHeader->i64Length; i++)
						{
							if ( 0 > _ftprintf(pFile, szFormat, p16Buffer[i]))
							{
								_get_errno(&g_nLastSaveError);
								fclose(pFile);
								return (CS_MISC_ERROR);
							}
						}
					}
					break;

					case 4:
					{
						int32* p32Buffer = (int32*)pBuffer;
						for (i = 0; i < pHeader->i64Length; i++)
						{
							if ( 0 > _ftprintf(pFile, szFormat, p32Buffer[i]))
							{
								_get_errno(&g_nLastSaveError);
								fclose(pFile);
								return (CS_MISC_ERROR);
							}
						}
					}
					break;
				}
			}
			fclose(pFile);
		}
		else
		{
			_get_errno(&g_nLastSaveError);
			fclose(pFile);
			return (CS_MISC_ERROR);
		}
		return (i * pHeader->u32SampleSize);
	}
	else
	{
		_get_errno(&g_nLastSaveError);
		return (CS_MISC_ERROR);
	}
}


int32 CS_SUPPORT_API CsAs_SaveSigFile(LPCTSTR szFileName, LPCTSTR szChannelName, LPCTSTR szChannelComment, const void* const pBuffer, const size_t szSize, PCSSIGSTRUCT pSigStruct)
{
	CSDISKFILEHEADER header;
	int32 i32Res = CS_SUCCESS;
	FILE* pFile = NULL;
	size_t res;
	if (NULL == pBuffer)
		return (CS_NULL_POINTER);

	if ((NULL == szFileName) || ( 0 == _tcslen(szFileName)))
		return (CS_INVALID_FILENAME);

	i32Res = CsConvertToSigHeader(&header, pSigStruct, (TCHAR*)szChannelComment,(TCHAR*)szChannelName);
	if( CS_FAILED( i32Res ) )
		return i32Res;

	pFile = _tfopen(szFileName, _T("wb"));
	if ( NULL == pFile )
	{
		_get_errno(&g_nLastSaveError);
		return (CS_OPEN_FILE_ERROR);
	}

	res = fwrite(&header, 1, sizeof(header), pFile );
	//if( sizeof(header) != fwrite(&header, sizeof(header), sizeof(header), pFile ) )
	if( sizeof(header) != res )
	{
		_get_errno(&g_nLastSaveError);
		fclose(pFile);
		return (CS_MISC_ERROR);
	}
	res = fwrite(pBuffer, 1, szSize, pFile );
	//if( szSize != fwrite(pBuffer, szSize, szSize, pFile ) )
	if( szSize != res )
	{
		_get_errno(&g_nLastSaveError);
		fclose(pFile);
		return (CS_MISC_ERROR);
	}

	fclose(pFile);

	return CS_SUCCESS;

}
