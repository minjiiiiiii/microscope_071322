#include "CsAppSupport.h"
#include "CsTchar.h"

#ifdef __linux__

#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "limits.h"

#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 2048
#endif

// convert ascii string to 64 bit integer.
long long  _atoll(const char *szValue)
{
   long long i64Value = 0;
   int iVal = 0;
   int is_neg = 0;
   unsigned char  *pos = (unsigned char *)szValue;
   if (!isdigit(iVal = *pos)) {
      while (isspace(iVal))
         iVal = *++pos;
      switch (iVal) {
         case '-':
            is_neg=1;
         case '+':
            iVal = *++pos;
      }
      if (!isdigit(iVal))
         return (0);
   }
   for (i64Value = '0' - iVal; isdigit(iVal = *++pos); ) {
      i64Value *= 10;          /* compute the value */
      i64Value += '0' - iVal;  
   }
   return (is_neg ? i64Value : -i64Value);
}

DWORD GetFileAttributes(LPCTSTR szFilePath)
{
	// for some reason, Linux returns 0 on success
	if(0 == access( szFilePath, F_OK ) )
	{
	    return 1;
	}
	else
	    return INVALID_FILE_ATTRIBUTES;
}

DWORD GetFullPathName(LPCTSTR szIniFile, DWORD nBufferLength, LPTSTR szFilePath, LPTSTR* lpFilePart)
{
	if ( NULL == getcwd(szFilePath, nBufferLength) )
	{
		if ( ERANGE == errno )
		{
			unsigned int nLength = 0;

			// allocate larger buffer and try again
			LPTSTR ptr = (LPTSTR)malloc(nBufferLength * 2);
			if (NULL != getcwd(ptr, nBufferLength * 2))
				nLength = strlen(ptr) + strlen(szIniFile) + 2;
			free(ptr);
			return nLength;
		}
		else
			return 0;
	}
	int nNeededLength = strlen(szFilePath) + strlen(szIniFile) + 2;
	if ( nBufferLength < nNeededLength )
		return nNeededLength;
	else
	{
		strcat(szFilePath, "/");
		strcat(szFilePath, szIniFile);
		return nNeededLength;
	}
}

void RemoveCharFromLine(char *line, char ch)
{
   // remove all occurrences for ch from line

   const char *src = line;
   char *dst = line;

   do
   {
      while (*src == ch)
         ++src;
   }
   while ((*dst++ = *src++) != '\0');
}


void RemoveWhiteSpaceFromLine(char *line)
{
   // remove all occurrences for ch from line

   const char *src = line;
   char *dst = line;

   do
   {
      while (*src == ' ' || *src == '\t')
         ++src;
   }
   while ((*dst++ = *src++) != '\0');
}

void RemoveEndOfLineChars(char *line)
{
   // remove all occurrences for ch from line

   const char *src = line;
   char *dst = line;

   do
   {
      while (*src == '\r' || *src == '\n')
         ++src;
   }
   while ((*dst++ = *src++) != '\0');
}


DWORD GetPrivateProfileSection(LPCTSTR lpAppName,
							   LPTSTR lpReturnedString,
							   DWORD nSize,
							   LPCTSTR lpFileName)
{
	// used mainly to determine if the section exists in the ini file
	// the function reads the key-value pairs that come after the section
	// name and returns the number of characters read.  So, if the section name
	// exists and we're able to read some characters we can assume that
	// it exists. If the buffer is not big enough to hold all the key-value
	// pairs the return value will be equal to nSize minus 2

	FILE *fp = fopen(lpFileName, "r");

	if ( NULL == fp )
		return 0;

	char *in_str = (char *)calloc(nSize, sizeof(char));
	char *section = (char *)calloc(nSize, sizeof(char));

	strcpy(section, "[");
	strcat(section, lpAppName);

	while (!feof(fp)
		&& !ferror(fp)
		&& fgets(in_str, nSize, fp) != NULL)
	{
		RemoveWhiteSpaceFromLine(in_str);
		if ( 0 == strncmp(in_str, section, strlen(section)) )
		{
			break;
		}
	}
	// now we're in the section we want so we need to read nSize characters
	// (while stripping out the white space)
	int count = 0;
	int remaining = nSize - 1;
	while (!feof(fp)
		&& !ferror(fp)
		&& fgets(in_str, nSize, fp) != NULL)
	{
		RemoveWhiteSpaceFromLine(in_str);
		// if the 1st character of the string is an '[', we've
		// reached a new section
		if ( in_str[0] == '[' )
		   break;
		// ignore blank strings
		if ( strlen(in_str) == 0 )
		   continue;
		// ignore comments
		if ( in_str[0] == ';' )
		   continue;
		strncat(lpReturnedString, in_str, remaining);
		remaining -= strlen(in_str);
		count += strlen(in_str);
		if ( remaining <= 0 )
		   break;
	}
	fclose(fp);
	free(in_str);
	free(section);
	if ( count <= nSize )
	   return count;
	else
	{
	   lpReturnedString[nSize-2] = '\0';
	   lpReturnedString[nSize-1] = '\0';
	   return nSize - 2;
	}
}

DWORD GetPrivateProfileString(LPCTSTR lpAppName,
							  LPCTSTR lpKeyName,
							  LPCTSTR lpDefault,
							  LPTSTR lpReturnedString,
							  DWORD nSize,
							  LPCTSTR lpFileName)
{
	// if lpAppName is NULL, we copy all section names to the buffer
	// if lpAppName is not NULL and lpKeyName is NULL, we copy all key
	// names in that section to the buffer.
	DWORD dwCount = 0;

	char *str = (char *)calloc(nSize, sizeof(char));

	FILE *fp = fopen(lpFileName, "r");

	if ( NULL == fp )
   	   return 0;

	char AllSections = (NULL == lpAppName) ? 1 : 0;
	char AllKeys = (NULL == lpKeyName) ? 1 : 0;

	char *in_str = (char *)calloc(nSize, sizeof(char));
	char *section = (char *)calloc(nSize, sizeof(char));

	if ( AllSections )
	{
		strcpy(section, "[");
		int count = 0;
		int remaining = nSize - 1;

		while (!feof(fp)
	   			&& !ferror(fp)
				&& fgets(in_str, nSize, fp) != NULL)
		{
			RemoveWhiteSpaceFromLine(in_str);
		   	if ( in_str[0] == '[' )
		   	{
				// remove characters after the trailing ], if any
				char *p = strchr(in_str, ']');
				if ( NULL != ++p )
				{
					if ( 0 != strcmp(p, "\n") )
						strcpy(p, "\n");
				}
				// remove trailing ], if it's there
				RemoveCharFromLine(in_str, '[');
				RemoveCharFromLine(in_str, ']');
				int length = strlen(in_str);
				strncat(str, in_str, remaining);
				count += length;
				remaining -= length;
	   		}
			if ( remaining <= 0 )
				break;
		}
		str[nSize-1] = '\0';
		if ( count < nSize )
		{
			strcpy(lpReturnedString, str);
			dwCount = (DWORD)count;
		}
	   else
	   {
			strcpy(lpReturnedString, str);
	        lpReturnedString[nSize-2] = '\0';
	        lpReturnedString[nSize-1] = '\0';
	        dwCount = (DWORD)nSize - 2;
	   }
	}
	else // we know what section to look for
	{
		strcpy(section, "[");
		strcat(section, lpAppName);

        while (!feof(fp)
	   			&& !ferror(fp)
				&& fgets(in_str, nSize, fp) != NULL)
		{
	   		RemoveWhiteSpaceFromLine(in_str);
	   		if ( 0 == strncmp(in_str, section, strlen(section)) )
	   		{
				break;
	   		}
		}
		// at this point we should be in the right section
		if ( AllKeys )
		{
			// return all the keys in this section that fit into lpReturned string
			int count = 0;
			int remaining = nSize - 1; // for the '\0' at end
			while (!feof(fp)
					&& !ferror(fp)
					&& fgets(in_str, nSize, fp) != NULL)
			{
				RemoveWhiteSpaceFromLine(in_str);
				// if the 1st character of the string is an '[', we've
				// reached a new section
                if ( in_str[0] == '[' )
					break;
				// ignore blank strings
				if ( strlen(in_str) == 0 )
					continue;
				// ignore line if it's only a line return
				if ( 0 == strcmp(in_str, "") )
					continue;
				// ignore comments
				if ( in_str[0] == ';' )
					continue;

				char *p = strchr(in_str, '=');
				if ( !p )
					continue;
				*p = '\0';
				if ( strlen(in_str) == 0 )
					continue;

				strcat(in_str, "\r\n");

				strncat(str, in_str, remaining);
				remaining -= strlen(in_str);
				count += strlen(in_str);
				if ( remaining <= 0 )
					break;
			}
			str[nSize-1] = '\0';
			if ( count <= nSize )
			{
				strcpy(lpReturnedString, str);
				dwCount = (DWORD)count;
			}
			else
			{
				strcpy(lpReturnedString, str);
				lpReturnedString[nSize-2] = '\0';
				lpReturnedString[nSize-1] = '\0';
				dwCount = (DWORD)nSize - 2;
			}
	   }
	   else // find the key and return the value (or the default value)
	   {
			while (!feof(fp)
				&& !ferror(fp)
				&& fgets(in_str, nSize, fp) != NULL)
			{
				RemoveWhiteSpaceFromLine(in_str);
				// if the 1st character of the string is an '[', we've
				// reached a new section without finding our string, so
				// return the default
				if ( in_str[0] == '[' )
				{
					if ( NULL == lpDefault )
						strcpy(str, "");
					else
		      			strncpy(str, lpDefault, nSize);
				  break;
				}
				// ignore blank strings
				if ( strlen(in_str) == 0 )
					continue;
				// ignore comments
				if ( in_str[0] == ';' )
					continue;
				if ( 0 == strncasecmp(in_str, lpKeyName, strlen(lpKeyName)) )
				{
					// we've found a match
					char *p = strchr(in_str, '=');
					if ( p )
					{
						p++;

						if ( !p )
							strcpy(str, lpDefault);
						else
						{
							// remove line feed and carriage return
							RemoveEndOfLineChars(p);
							strcpy(str, p);
						}
						break;
					}
				}
			}
			strcpy(lpReturnedString, str);
			dwCount = (DWORD)strlen(lpReturnedString);
		}
	}
	fclose(fp);
	free(str);
	free(in_str);
	free(section);
	return dwCount;
}

DWORD GetPrivateProfileInt(LPCTSTR lpAppName,
							  LPCTSTR lpKeyName,
							  int nDefault,
							  LPCTSTR lpFileName)	
{   
    char szSectionName[MAX_LINE_LENGTH];
    char buff[MAX_LINE_LENGTH];
    char *szTmp;
    int len = strlen(lpKeyName);
    int i = 0;
    int isOK =0;

    FILE *fp = fopen(lpFileName, "r");
    if( !fp ) return(0);

    sprintf(szSectionName,"[%s]",lpAppName); 
    /*  Search for AppName */
    do
    {   
	if (!fgets(buff, MAX_LINE_LENGTH, fp))
        {   fclose(fp);
            return(nDefault);
        }
    } while( strncmp(buff,szSectionName, strlen(szSectionName)) );
	
    /* AppName found. Search for the KeyName */
    do
    {   
	if (!fgets(buff, MAX_LINE_LENGTH, fp) || buff[0] == '\0' )
        {   fclose(fp);
            return(nDefault);
        }
    }  while( strncasecmp(buff,lpKeyName,len) );

	/* Parse value */
    szTmp = strrchr(buff,'=');    /* equal sign ?*/
    if (szTmp==NULL)
    {
		fclose(fp);	
      return(nDefault);
    }
   szTmp++;

	/* valid digit string */
   for(i = 0; i < strlen(szTmp); i++ )
   {
        if (isdigit(szTmp[i]))
        {
            isOK = 1;
            break;
        }
   }
   
   // minor validation only, atol can take care of space +1/-
   if (!isOK)
	{	
		fclose(fp);	
      return(nDefault);
	}
   
    fclose(fp);                
    return(atol(szTmp));		/* Return the value */   
}
#endif // __linux__


void CS_SUPPORT_API CsAs_SetApplicationDefaults(CSAPPLICATIONDATA *pAppData)
{
	pAppData->i32SaveFormat = DEFAULT_SAVE_FILE_FORMAT;
	pAppData->i64TransferLength = DEFAULT_TRANSFER_LENGTH;
	pAppData->i64TransferStartPosition = DEFAULT_TRANSFER_START_POSITION;
	_tcsncpy(pAppData->lpszSaveFileName, DEFAULT_SAVE_FILE_NAME, sizeof(DEFAULT_SAVE_FILE_NAME));
	pAppData->u32PageSize = DEFAULT_PAGE_SIZE;
	pAppData->u32TransferSegmentCount = DEFAULT_TRANSFER_SEGMENT_COUNT;
	pAppData->u32TransferSegmentStart = DEFAULT_TRANSFER_SEGMENT_START;
	_tcscpy(pAppData->lpszFirDataFileName, _T(""));
}


int32 CS_SUPPORT_API CsAs_ConfigureSystem(const CSHANDLE hSystem, const int nChannelCount, const int nTriggerCount, const LPCTSTR szIniFile, uInt32* pu32Mode)
{
	int32 i32Status;
	int32 i32ReturnValue = 0;
	int i;
	CSACQUISITIONCONFIG			CsAcquisitionCfg = {0};
 	CSTRIGGERCONFIG				CsTriggerCfg = {0};
	CSCHANNELCONFIG				CsChannelCfg = {0};
	CSSYSTEMINFO				CsSystemInfo = {0};
	uInt32						u32ChannelIndexIncrement = 1;
/*
	Read the ini file to get the capture parameters
*/
	CsAcquisitionCfg.u32Size = sizeof(CSACQUISITIONCONFIG);
	i32Status = CsAs_LoadConfiguration(hSystem, szIniFile, ACQUISITION_DATA, &CsAcquisitionCfg);
/*
	Check if the call failed.  If the call did fail we'll return the status so the
	caller will know to free the CompuScope system so it's available for another application.
	The status can also be CS_INVALID_FILENAME which means the ini file was not
	found.
*/
	if (CS_FAILED(i32Status))
		return i32Status;
	i32ReturnValue |= i32Status;
/*
	Send the values from the ini file to the driver. Note that the values
	are not validated until we commit them with CsDo(ACTION_COMMIT)
*/
	i32Status = SetAcquisitionParameters(hSystem, &CsAcquisitionCfg);
	if (CS_FAILED(i32Status))
		return i32Status;
/*
	We need to remember the mode so we don't have to call CsGet again for it.
	It will be used later on in determining the number of active channels.
*/
	*pu32Mode = CsAcquisitionCfg.u32Mode;
	CsSystemInfo.u32Size = sizeof(CSSYSTEMINFO);
	CsGetSystemInfo(hSystem, &CsSystemInfo);

	u32ChannelIndexIncrement = CsAs_CalculateChannelIndexIncrement(&CsAcquisitionCfg, &CsSystemInfo );

	CsChannelCfg.u32Size = sizeof(CSCHANNELCONFIG);

    if ( 0 != (CsAcquisitionCfg.u32Mode & CS_MODE_SINGLE_CHANNEL2) )
		i = 2;
	else
		i = 1;
	for (; i <= nChannelCount; i += u32ChannelIndexIncrement)
	{
		CsChannelCfg.u32ChannelIndex = (uInt32)i;
		i32Status = CsAs_LoadConfiguration(hSystem, szIniFile, CHANNEL_DATA, &CsChannelCfg);
/*
		Check if the call failed.  If the call did fail we'll return the error code so the caller
		will know to free the CompuScope system so it's available for another application
*/
		if (CS_FAILED(i32Status))
			return i32Status;

		i32ReturnValue |= i32Status;

		i32Status = SetChannelParameters(hSystem, &CsChannelCfg);
		if (CS_FAILED(i32Status))
			return i32Status;
	}

	CsTriggerCfg.u32Size = sizeof(CSTRIGGERCONFIG);
	for (i = 1; i <= nTriggerCount; i++)
	{
		CsTriggerCfg.u32TriggerIndex = (uInt32)i;
		i32Status = CsAs_LoadConfiguration(hSystem, szIniFile, TRIGGER_DATA, &CsTriggerCfg);
/*
		Check if the call failed.  If the call did fail we'll return the error code so the caller
		will know to free the CompuScope system so it's available for another application
*/
		if (CS_FAILED(i32Status))
			return i32Status;

		i32ReturnValue |= i32Status;

		i32Status = SetTriggerParameters(hSystem, &CsTriggerCfg);
		if (CS_FAILED(i32Status))
			return i32Status;
	}
	i32ReturnValue |= CS_SUCCESS;
	return i32ReturnValue;
}

int32 CS_SUPPORT_API CsAs_LoadConfiguration(const CSHANDLE hSystem, const LPCTSTR szIniFile, const int32 i32Type, void* pConfig)
{
	TCHAR	szFilePath[MAX_PATH];
	int32	i32Ret = CS_SUCCESS;
	BOOL	bFileNotFound = FALSE;
/*
	Validate if the file exists
*/
	GetFullPathName(szIniFile, MAX_PATH, szFilePath, NULL);

	if (INVALID_FILE_ATTRIBUTES == GetFileAttributes(szFilePath))
		bFileNotFound = TRUE;

	if (ACQUISITION_DATA == i32Type)
	{
		if (bFileNotFound)
		{
			CSACQUISITIONCONFIG csAcqConfig = {0};
			csAcqConfig.u32Size = sizeof(CSACQUISITIONCONFIG);
			i32Ret = CsGet(hSystem, CS_ACQUISITION, CS_CURRENT_CONFIGURATION, &csAcqConfig);
			if (CS_FAILED(i32Ret))
				return i32Ret;
			else
			{
				CopyMemory(pConfig, &csAcqConfig, csAcqConfig.u32Size);
				return (CS_INVALID_FILENAME);
			}
		}
		else
			i32Ret = LoadAcquisitionConfiguration(hSystem, szFilePath, (PCSACQUISITIONCONFIG)pConfig);
	}
	else if (CHANNEL_DATA == i32Type)
	{
		if (bFileNotFound)
		{
			CSCHANNELCONFIG csChanConfig = {0};
			csChanConfig.u32ChannelIndex = ((PCSCHANNELCONFIG)pConfig)->u32ChannelIndex;
            csChanConfig.u32Size = sizeof(CSCHANNELCONFIG);
			i32Ret = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &csChanConfig);
			if (CS_FAILED(i32Ret))
				return i32Ret;
			else
			{
				CopyMemory(pConfig, &csChanConfig, csChanConfig.u32Size);
				return (CS_INVALID_FILENAME);
			}
		}
		else
			i32Ret = LoadChannelConfiguration(hSystem, szFilePath, (PCSCHANNELCONFIG)pConfig);
	}
	else if (TRIGGER_DATA == i32Type)
	{
		if (bFileNotFound)
		{
			CSTRIGGERCONFIG csTrigConfig = {0};
			csTrigConfig.u32TriggerIndex = ((PCSTRIGGERCONFIG)pConfig)->u32TriggerIndex;
            csTrigConfig.u32Size = sizeof(CSTRIGGERCONFIG);
			i32Ret = CsGet(hSystem, CS_TRIGGER, CS_CURRENT_CONFIGURATION, &csTrigConfig);
			if (CS_FAILED(i32Ret))
				return i32Ret;
			else
			{
				CopyMemory(pConfig, &csTrigConfig, csTrigConfig.u32Size);
				return (CS_INVALID_FILENAME);
			}
		}
		else
			i32Ret = LoadTriggerConfiguration(hSystem, szFilePath, (PCSTRIGGERCONFIG)pConfig);
	}
	else if (APPLICATION_DATA == i32Type)
	{
		if (bFileNotFound)
		{
			CsAs_SetApplicationDefaults((PCSAPPLICATIONDATA)pConfig);
			return CS_INVALID_FILENAME;
		}
		else
			i32Ret = LoadApplicationData(szFilePath, (PCSAPPLICATIONDATA)pConfig);
	}
	else
		return (CS_INVALID_REQUEST);

	return (i32Ret);
}


/*
	Load user Acquisition Data
*/
int32 LoadAcquisitionConfiguration(const CSHANDLE hSystem, const LPCTSTR szIniFile, PCSACQUISITIONCONFIG pConfig)
{
	int32	i32Status = CS_SUCCESS;
	TCHAR	szSection[100];
	TCHAR	szDefault[100];
	TCHAR	szString[100];
	uInt32	u32MaskedMode;
	BOOL	bUsingDefaults = FALSE;
	int64	i64SegmentCount = 0;
	CSACQUISITIONCONFIG CsAcqCfg = {0};
	CsAcqCfg.u32Size = sizeof(CSACQUISITIONCONFIG);

	if (pConfig)
	{
		uInt32	u32StructSize = sizeof(CSACQUISITIONCONFIG);

		ZeroMemory(pConfig, u32StructSize);
		pConfig->u32Size = u32StructSize;
	}
	else
		return (CS_INVALID_PARAMETER);
/*
	Check if the Acquisition section exists in the ini file.
*/
	_tcscpy(szString, _T(""));
	_tcscpy(szSection, _T("Acquisition"));
	if (0 == GetPrivateProfileSection(szSection, szString, 100, szIniFile))
		bUsingDefaults = TRUE;
/*
	Get user's acquisition Data
*/
	i32Status = CsGet( hSystem, CS_ACQUISITION, CS_CURRENT_CONFIGURATION, &CsAcqCfg);
	if (CS_FAILED(i32Status))
		return (i32Status);
/*
	If we're using defaults, just copy the structure to the user-supplied buffer
	and return.
*/
	if (bUsingDefaults)
	{
		memcpy(pConfig, &CsAcqCfg, pConfig->u32Size);
		return (CS_USING_DEFAULT_ACQ_DATA);
	}

	u32MaskedMode = CsAcqCfg.u32Mode & CS_MASKED_MODE;
/*
	If CsAcqCfg.u32Mode and u32MaskedMode are the same, there's no mode options set
*/
	if (CsAcqCfg.u32Mode == u32MaskedMode)
	{
		if (CS_MODE_OCT == u32MaskedMode)
			_tcscpy(szDefault, _T("Octal"));
		else if (CS_MODE_QUAD == u32MaskedMode)
			_tcscpy(szDefault, _T("Quad"));
		else if (CS_MODE_SINGLE == u32MaskedMode)
			_tcscpy(szDefault, _T("Single"));
		else
			_tcscpy(szDefault, _T("Dual"));
	}
	else
	{
/*
		There are mode options set so use the actual number to keep them
*/
		_stprintf(szDefault, _T("%u"), (unsigned int)CsAcqCfg.u32Mode);
	}
	GetPrivateProfileString(szSection, _T("Mode"), szDefault, szString, 100, szIniFile);

/*
	If the string is one of the following keywords, any mode options will be overwritten.
	To use mode options you must have a number in the INI file.
*/
	if (0 == _tcsicmp(szString, _T("Quad")))
		CsAcqCfg.u32Mode = CS_MODE_QUAD;
	else if (0 == _tcsicmp(szString, _T("Q")))
		CsAcqCfg.u32Mode = CS_MODE_QUAD;
	else if (0 == _tcsicmp(szString, _T("32-bit")))
		CsAcqCfg.u32Mode = CS_MODE_QUAD;
	else if (0 == _tcsicmp(szString, _T("32")))
		CsAcqCfg.u32Mode = CS_MODE_QUAD;
	else if (0 == _tcsicmp(szString, _T("Single")))
        CsAcqCfg.u32Mode = CS_MODE_SINGLE;
	else if (0 == _tcsicmp(szString, _T("S")))
        CsAcqCfg.u32Mode = CS_MODE_SINGLE;
	else if (0 == _tcsicmp(szString, _T("SingleB")))
        CsAcqCfg.u32Mode = CS_MODE_SINGLE | CS_MODE_SINGLE_CHANNEL2;
	else if (0 == _tcsicmp(szString, _T("8-bit")))
        CsAcqCfg.u32Mode = CS_MODE_SINGLE;
	else if (0 == _tcsicmp(szString, _T("Dual")))
		CsAcqCfg.u32Mode = CS_MODE_DUAL;
	else if (0 == _tcsicmp(szString, _T("D")))
		CsAcqCfg.u32Mode = CS_MODE_DUAL;
	else if (0 == _tcsicmp(szString, _T("16-bit")))
		CsAcqCfg.u32Mode = CS_MODE_DUAL;
	else if (0 == _tcsicmp(szString, _T("Octal")))
		CsAcqCfg.u32Mode = CS_MODE_OCT;
	else if (0 == _tcsicmp(szString, _T("O")))
		CsAcqCfg.u32Mode = CS_MODE_OCT;
	else
	{
/*
		See if the string can be converted into a number
		First check to see if it's hex or not and convert it accordingly
*/
		if ('0' == szString[0] && 'x' == szString[1])
			_stscanf(szString, _T("%x"), (unsigned int *)&CsAcqCfg.u32Mode);
		else
			CsAcqCfg.u32Mode = _ttol(szString);
	}

	_stprintf(szDefault, _T(F64), CsAcqCfg.i64SampleRate);
	GetPrivateProfileString(szSection, _T("SampleRate"), szDefault, szString, 100, szIniFile);
	CsAcqCfg.i64SampleRate = _ttoi64(szString);

	_stprintf(szDefault, _T(F64), CsAcqCfg.i64Depth);
	GetPrivateProfileString(szSection, _T("Depth"), szDefault, szString, 100, szIniFile);
	CsAcqCfg.i64Depth = _ttoi64(szString);

	// Just in case the user has left out the segment size, we'll
	// make it equal to the depth as default
	_stprintf(szDefault, _T(F64), CsAcqCfg.i64SegmentSize);
	GetPrivateProfileString(szSection, _T("SegmentSize"), szDefault, szString, 100, szIniFile);
	CsAcqCfg.i64SegmentSize = _ttoi64(szString);

	_stprintf(szDefault, _T("%u"), CsAcqCfg.u32SegmentCount);
	GetPrivateProfileString(szSection, _T("SegmentCount"), szDefault, szString, 100, szIniFile);
	
	// The full segment count might be larger than a uint32. If this is the case it's using both
	// u32SegmentCount and i32SegmentCountHigh
	i64SegmentCount = _ttoi64(szString);
	if (-1 == i64SegmentCount)
	{
		CsAcqCfg.u32SegmentCount = UINT_MAX;
		CsAcqCfg.i32SegmentCountHigh = -1;
	}
	else if (i64SegmentCount > UINT_MAX)
	{
		CsAcqCfg.u32SegmentCount = i64SegmentCount & 0x00000000FFFFFFFF;
		CsAcqCfg.i32SegmentCountHigh = (i64SegmentCount & 0xFFFFFFFF00000000) >> 32;
	}
	else
	{
		CsAcqCfg.u32SegmentCount = (uInt32)i64SegmentCount;
		CsAcqCfg.i32SegmentCountHigh = 0;
	}


	_stprintf(szDefault, _T(F64), CsAcqCfg.i64TriggerHoldoff);
	GetPrivateProfileString(szSection, _T("TriggerHoldoff"), szDefault, szString, 100, szIniFile);
	CsAcqCfg.i64TriggerHoldoff = _ttoi64(szString);

	_stprintf(szDefault, _T(F64), CsAcqCfg.i64TriggerTimeout);
	GetPrivateProfileString(szSection, _T("TriggerTimeout"), szDefault, szString, 100, szIniFile);
	CsAcqCfg.i64TriggerTimeout = _ttoi64(szString);

	_stprintf(szDefault, _T(F64), CsAcqCfg.i64TriggerDelay);
	GetPrivateProfileString(szSection, _T("TriggerDelay"), szDefault, szString, 100, szIniFile);
	CsAcqCfg.i64TriggerDelay = _ttoi64(szString);

	_stprintf(szDefault, _T("%u"), CsAcqCfg.u32ExtClk);
	GetPrivateProfileString(szSection, _T("ExtClk"), szDefault, szString, 100, szIniFile);
	CsAcqCfg.u32ExtClk = _ttol(szString);

	// Do the TimeStampClock value
	if ((CsAcqCfg.u32TimeStampConfig & TIMESTAMP_MCLK) == TIMESTAMP_MCLK)
		_stprintf(szDefault, _T("Fixed"));
	else
		_stprintf(szDefault, _T("Sample"));

	GetPrivateProfileString(szSection, _T("TimeStampClock"), szDefault, szString, 100, szIniFile);
	// If it's fixed we set the TIMESTAMP_MCLK bit, otherwise clear the bit
	if (0 == _tcsicmp(szString, _T("Fixed")))
		CsAcqCfg.u32TimeStampConfig |= TIMESTAMP_MCLK;
	else
		CsAcqCfg.u32TimeStampConfig &= ~TIMESTAMP_MCLK;

	// Do the TimeStampMode value
	if ((CsAcqCfg.u32TimeStampConfig & TIMESTAMP_FREERUN) == TIMESTAMP_FREERUN)
		_stprintf(szDefault, _T("Free"));
	else
		_stprintf(szDefault, _T("Reset"));

	GetPrivateProfileString(szSection, _T("TimeStampMode"), szDefault, szString, 100, szIniFile);
	// If it's free, then set the TIMESTAMP_FREERUN bit, otherwise clear it
	if (0 == _tcsicmp(szString, _T("Free")))
		CsAcqCfg.u32TimeStampConfig |= TIMESTAMP_FREERUN;
	else
		CsAcqCfg.u32TimeStampConfig &= ~TIMESTAMP_FREERUN;

/*
	Copy settings back to the user-supplied buffer
*/
	memcpy(pConfig, &CsAcqCfg, pConfig->u32Size);
	return (CS_SUCCESS);
}


/*
	Load user Channel Data
*/
int32 LoadChannelConfiguration(const CSHANDLE hSystem, const LPCTSTR szIniFile, PCSCHANNELCONFIG pConfig)
{
	int32	i32Status = CS_SUCCESS;
	TCHAR	szChannel[100];
	TCHAR	szDefault[100];
	TCHAR	szString[100];
	uInt32	u32Coupling;
	uInt32	u32DifferentialInput;
	uInt32	u32DirectADC;
	BOOL	bUsingDefaults = FALSE;

	CSCHANNELCONFIG	CsChanCfg = {0};

	if (NULL == pConfig)
		return (CS_INVALID_PARAMETER);

	_stprintf(szChannel, _T("Channel%u"), pConfig->u32ChannelIndex);

/*
	Validate if Channel section exists in the file
*/
	_tcscpy(szString, _T(""));
	if (0 == GetPrivateProfileSection(szChannel, szString, 100, szIniFile))
		bUsingDefaults = TRUE;

	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = pConfig->u32ChannelIndex;
	pConfig->u32Size = CsChanCfg.u32Size;

/*
	Get users Channel(s) Data
*/
	i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
	if (CS_FAILED(i32Status))
		return (i32Status);

/*
	If we're using defaults, just copy the default values to the user supplied
	buffer and return.
*/
	if (bUsingDefaults)
	{
		memcpy(pConfig, &CsChanCfg, pConfig->u32Size);
		return (CS_USING_DEFAULT_CHANNEL_DATA);
	}
	if ((CsChanCfg.u32Term & CS_COUPLING_MASK) == CS_COUPLING_AC)
		_tcscpy(szDefault, _T("AC"));
	else
		_tcscpy(szDefault, _T("DC"));

	_stprintf(szDefault, _T("%u"), CsChanCfg.u32Term & CS_COUPLING_MASK);
	GetPrivateProfileString(szChannel, _T("Coupling"), szDefault, szString, 100, szIniFile);

	if ((0 == _tcsicmp(szString, _T("DC"))) || (0 == _tcsicmp(szString, _T("1"))))
		u32Coupling = CS_COUPLING_DC;
	else if ((0 == _tcsicmp(szString, _T("AC")))|| (0 == _tcsicmp(szString, _T("2"))))
		u32Coupling = CS_COUPLING_AC;
	else /*	assume that the string represents a number	*/
		u32Coupling = _ttol(szString);

	_stprintf(szDefault, _T("%i"), (CsChanCfg.u32Term & CS_DIFFERENTIAL_INPUT) ? 1 : 0);
	GetPrivateProfileString(szChannel, _T("DiffInput"), szDefault, szString, 100, szIniFile);
	u32DifferentialInput = _ttol(szString);

	_stprintf(szDefault, _T("%i"), (CsChanCfg.u32Term & CS_DIRECT_ADC_INPUT) ? 1 : 0);
	GetPrivateProfileString(szChannel, _T("DirectADC"), szDefault, szString, 100, szIniFile);
	u32DirectADC = _ttol(szString);

	CsChanCfg.u32Term = u32Coupling;
	if (0 != u32DifferentialInput)
		CsChanCfg.u32Term |= CS_DIFFERENTIAL_INPUT;

	if (0 != u32DirectADC)
		CsChanCfg.u32Term |= CS_DIRECT_ADC_INPUT;


	_stprintf(szDefault, _T("%u"), CsChanCfg.u32InputRange);
	GetPrivateProfileString(szChannel, _T("Range"), szDefault, szString, 100, szIniFile);
	CsChanCfg.u32InputRange = _ttol(szString);

	_stprintf(szDefault, _T("%u"), CsChanCfg.u32Impedance);
	GetPrivateProfileString(szChannel, _T("Impedance"), szDefault, szString, 100, szIniFile);
	CsChanCfg.u32Impedance = _ttol(szString);

	_stprintf(szDefault, _T("%u"), CsChanCfg.u32Filter);
	GetPrivateProfileString(szChannel, _T("Filter"), szDefault, szString, 100, szIniFile);
	CsChanCfg.u32Filter = _ttol(szString);

	_stprintf(szDefault, _T("%d"), CsChanCfg.i32DcOffset);
	GetPrivateProfileString(szChannel, _T("DcOffset"), szDefault, szString, 100, szIniFile);
	CsChanCfg.i32DcOffset = _ttol(szString);

/*
	Copy settings back to the user-supplied buffer
*/
	memcpy(pConfig, &CsChanCfg, pConfig->u32Size);
	return (CS_SUCCESS);
}


/*
	Load user Trigger Data
*/
int32 LoadTriggerConfiguration(const CSHANDLE hSystem, const LPCTSTR szIniFile, PCSTRIGGERCONFIG pConfig)
{
	int32	i32Status = CS_SUCCESS;
	TCHAR	szTrigger[100];
	TCHAR	szDefault[100];
	TCHAR	szString[100];
	BOOL	bUsingDefaults = FALSE;

	CSTRIGGERCONFIG	CsTriggerCfg = {0};

	if (NULL == pConfig)
		return (CS_INVALID_PARAMETER);

	_stprintf(szTrigger, _T("Trigger%u"), pConfig->u32TriggerIndex);

/*
	Validate if Trigger section exists in file
*/
	_tcscpy(szString, _T(""));
	if (0 == GetPrivateProfileSection(szTrigger, szString, 100, szIniFile))
		bUsingDefaults = TRUE;

	CsTriggerCfg.u32Size = sizeof(CSTRIGGERCONFIG);
	CsTriggerCfg.u32TriggerIndex = pConfig->u32TriggerIndex;
	pConfig->u32Size = CsTriggerCfg.u32Size;

/*
	Get users trigger(s) data
*/
	i32Status = CsGet(hSystem, CS_TRIGGER, CS_CURRENT_CONFIGURATION, &CsTriggerCfg);
	if (CS_FAILED(i32Status))
		return (i32Status);

/*
	If we're using defaults just copy the default parameters to the user supplied
	buffer and return.
*/
	if (bUsingDefaults)
	{
		memcpy(pConfig, &CsTriggerCfg, pConfig->u32Size);
		return (CS_USING_DEFAULT_TRIGGER_DATA);
	}

	if (CS_TRIG_COND_NEG_SLOPE == CsTriggerCfg.u32Condition)
		_tcscpy(szDefault, _T("Falling"));
	else if (CS_TRIG_COND_PULSE_WIDTH == CsTriggerCfg.u32Condition)
		_tcscpy(szDefault, _T("PulseWidth"));
	else
		_tcscpy(szDefault, _T("Rising"));

	GetPrivateProfileString(szTrigger, _T("Condition"), szDefault, szString, 100, szIniFile);


	if ((0 == _tcsicmp(szString, _T("Falling"))) || (0 == _tcsicmp(szString, _T("F"))))
		CsTriggerCfg.u32Condition = CS_TRIG_COND_NEG_SLOPE;
	else if ((0 == _tcsicmp(szString, _T("Negative"))) || (0 == _tcsicmp(szString, _T("N"))))
		CsTriggerCfg.u32Condition = CS_TRIG_COND_NEG_SLOPE;
	else if (0 == _tcsicmp(szString, _T("0")))
		CsTriggerCfg.u32Condition = CS_TRIG_COND_NEG_SLOPE;
	else if ((0 == _tcsicmp(szString, _T("Rising"))) || (0 == _tcsicmp(szString, _T("R"))))
		CsTriggerCfg.u32Condition = CS_TRIG_COND_POS_SLOPE;
	else if ((0 == _tcsicmp(szString, _T("Positive"))) || (0 == _tcsicmp(szString, _T("P"))))
		CsTriggerCfg.u32Condition = CS_TRIG_COND_POS_SLOPE;
	else if (0 == _tcsicmp(szString, _T("1")))
		CsTriggerCfg.u32Condition = CS_TRIG_COND_POS_SLOPE;
	else if (0 == _tcsicmp(szString, _T("PulseWidth")))
		CsTriggerCfg.u32Condition = CS_TRIG_COND_PULSE_WIDTH;


	_stprintf(szDefault, _T("%d"), CsTriggerCfg.i32Level);
	GetPrivateProfileString(szTrigger, _T("Level"), szDefault, szString, 100, szIniFile);
	CsTriggerCfg.i32Level = _ttol(szString);


	if (CS_TRIG_SOURCE_EXT == CsTriggerCfg.i32Source)
		_tcscpy(szDefault, _T("External"));
	else if (CS_TRIG_SOURCE_DISABLE == CsTriggerCfg.i32Source)
		_tcscpy(szDefault, _T("Disable"));
	else if (CS_TRIG_SOURCE_CHAN_2 == CsTriggerCfg.i32Source)
		_tcscpy(szDefault, _T("2"));
	else
		_stprintf(szDefault, _T("%d"), CsTriggerCfg.i32Source);


	GetPrivateProfileString(szTrigger, _T("Source"), szDefault, szString, 100, szIniFile);

	if (0 == _tcsicmp(szString, _T("External")))
		CsTriggerCfg.i32Source = CS_TRIG_SOURCE_EXT;
	else if (0 == _tcsicmp(szString, _T("Disable")))
		CsTriggerCfg.i32Source = CS_TRIG_SOURCE_DISABLE;
	else /*	assume it's a number. if it's wrong we'll fail on CsCommit	*/
		CsTriggerCfg.i32Source = _ttol(szString);

	if (CsTriggerCfg.u32ExtCoupling == CS_COUPLING_AC)
		_tcscpy(szDefault, _T("AC"));
	else
		_tcscpy(szDefault, _T("DC"));

	GetPrivateProfileString(szTrigger, _T("Coupling"), szDefault, szString, 100, szIniFile);
	if (0 == _tcsicmp(szString, _T("DC")))
		CsTriggerCfg.u32ExtCoupling = CS_COUPLING_DC;
	else if (0 == _tcsicmp(szString, _T("AC")))
		CsTriggerCfg.u32ExtCoupling = CS_COUPLING_AC;
	else /*	assume it's a number.  if not, we'll fail on CsCommit	*/
		CsTriggerCfg.u32ExtCoupling = _ttol(szString);


	_stprintf(szDefault, _T("%u"), CsTriggerCfg.u32ExtTriggerRange);
	GetPrivateProfileString(szTrigger, _T("Range"), szDefault, szString, 100, szIniFile);
	CsTriggerCfg.u32ExtTriggerRange = _ttol(szString);

	_stprintf(szDefault, _T("%u"), CsTriggerCfg.u32ExtImpedance);
	GetPrivateProfileString(szTrigger, _T("Impedance"), szDefault, szString, 100, szIniFile);
	CsTriggerCfg.u32ExtImpedance = _ttol(szString);

	_stprintf(szDefault, _T("%u"), CsTriggerCfg.u32Relation);
	GetPrivateProfileString(szTrigger, _T("Relation"), szDefault, szString, 100, szIniFile);
	CsTriggerCfg.u32Relation = _ttol(szString);

	memcpy(pConfig, &CsTriggerCfg, pConfig->u32Size);
	return (CS_SUCCESS);
}

int32 LoadApplicationData(const LPCTSTR szIniFile, PCSAPPLICATIONDATA pConfig)
{
	TCHAR	szDefault[100];
	TCHAR	szString[100];
	TCHAR	szSection[100];
	BOOL	bUsingDefaults = FALSE;

	CSAPPLICATIONDATA CsAppData = {0};

	if (NULL == pConfig)
		return (CS_INVALID_PARAMETER);

	_tcscpy(szSection, _T("Application"));
/*
	Check if the Application section exists in the ini file.
*/
	_tcscpy(szString, _T(""));
	if (0 == GetPrivateProfileSection(szSection, szString, 100, szIniFile))
		bUsingDefaults = TRUE;

/*
	If we're using defaults just copy the default parameters to the user supplied
	buffer and return.
*/
	if (bUsingDefaults)
	{
		CsAs_SetApplicationDefaults(&CsAppData);
		memcpy(pConfig, &CsAppData, sizeof(CSAPPLICATIONDATA));
		return (CS_USING_DEFAULT_APP_DATA);
	}


	_stprintf(szDefault, _T(F64), (int64)DEFAULT_TRANSFER_START_POSITION);
	GetPrivateProfileString(szSection, _T("StartPosition"), szDefault, szString, 100, szIniFile);
	CsAppData.i64TransferStartPosition = _ttoi64(szString);

	_stprintf(szDefault, _T(F64), (int64)DEFAULT_TRANSFER_LENGTH);
	GetPrivateProfileString(szSection, _T("TransferLength"), szDefault, szString, 100, szIniFile);
	CsAppData.i64TransferLength = _ttoi64(szString);

	_stprintf(szDefault, _T("%i"), DEFAULT_TRANSFER_SEGMENT_START);
	GetPrivateProfileString(szSection, _T("SegmentStart"), szDefault, szString, 100, szIniFile);
	CsAppData.u32TransferSegmentStart = _ttoi(szString);

	_stprintf(szDefault, _T("%i"), DEFAULT_TRANSFER_SEGMENT_COUNT);
	GetPrivateProfileString(szSection, _T("SegmentCount"), szDefault, szString, 100, szIniFile);
	CsAppData.u32TransferSegmentCount = _ttol(szString);

	_stprintf(szDefault, _T("%i"), DEFAULT_PAGE_SIZE);
	GetPrivateProfileString(szSection, _T("PageSize"), szDefault, szString, 100, szIniFile);
	CsAppData.u32PageSize = _ttol(szString);

	_stprintf(szDefault, _T("%s"), DEFAULT_SAVE_FILE_NAME);
	GetPrivateProfileString(szSection, _T("SaveFileName"), szDefault, szString, 100, szIniFile);
	_tcsncpy(CsAppData.lpszSaveFileName, szString, 100);

	_stprintf(szDefault, _T("%s"), DEFAULT_FIR_DATA_FILE_NAME);
	GetPrivateProfileString(szSection, _T("FirDataFileName"), szDefault, szString, 100, szIniFile);
	_tcsncpy(CsAppData.lpszFirDataFileName, szString, 100);

	_stprintf(szDefault, _T("%i"), DEFAULT_SAVE_FILE_FORMAT);
	GetPrivateProfileString(szSection, _T("SaveFileFormat"), szDefault, szString, 100, szIniFile);
	if (0 == _tcsicmp(szString, _T("TYPE_FLOAT")))
		CsAppData.i32SaveFormat = TYPE_FLOAT;
	else if (0 == _tcsicmp(szString, _T("TYPE_DEC")))
		CsAppData.i32SaveFormat = TYPE_DEC;
	else if (0 == _tcsicmp(szString, _T("TYPE_HEX")))
		CsAppData.i32SaveFormat = TYPE_HEX;
	else if (0 == _tcsicmp(szString, _T("TYPE_SIG")))
		CsAppData.i32SaveFormat = TYPE_SIG;
	else if (0 == _tcsicmp(szString, _T("TYPE_BIN")))
		CsAppData.i32SaveFormat = TYPE_BIN;
	else if (0 == _tcsicmp(szString, _T("TYPE_BIN_APPEND")))
		CsAppData.i32SaveFormat = TYPE_BIN_APPEND;
	else /* assume it's a number	*/
		CsAppData.i32SaveFormat = _ttol(szString);

/*
	Copy  back the data to the user supplied buffer
*/
	memcpy(pConfig, &CsAppData, sizeof(CSAPPLICATIONDATA));
	return (CS_SUCCESS);
}
