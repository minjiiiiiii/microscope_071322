#include <stdio.h>
#include <unistd.h>
#include "CsAppSupport.h"
#include "CsTchar.h"

int32 CS_SUPPORT_API CsAs_ConvertToVolts(const int64 i64Depth, const uInt32 u32InputRange, const uInt32 u32SampleSize,
										 const int32 i32SampleOffset, const int32 i32SampleResolution, const int32 i32DcOffset,
										 const void* const pBuffer,  float* const pVBuffer)
{
/*	Converts the raw data in the buffer pBuffer to voltages and puts them into pVBuffer.
	The conversion is done using the formula:
	voltage = ((sample_offset - raw_value) / sample_resolution) * gain
	where gain is calculated in volts by gain_in_millivolts / CS_GAIN_2_V (2000).
	The DC Offset is added to each element of the voltage buffer
*/

	double					dScaleFactor;
	int64					i;
	int32					i32Status = CS_SUCCESS;

	dScaleFactor = (double)(u32InputRange) / (double)(CS_GAIN_2_V);

	switch (u32SampleSize)
	{
		double dOffset;
		double dValue;
		uInt8 *p8ShortBuffer;
		int16 *p16ShortBuffer;
		int32 *p32ShortBuffer;

		case 1:
			p8ShortBuffer = (uInt8 *)pBuffer;
			for (i = 0; i < i64Depth; i++)
			{
				dOffset = i32SampleOffset - (double)(p8ShortBuffer[i]);
				dValue = dOffset / (double)i32SampleResolution;
				dValue *= dScaleFactor;
				dValue += (double)(i32DcOffset) / 1000.0;
				pVBuffer[i] = (float)dValue;
			}
			break;

		case 2:
			p16ShortBuffer = (int16 *)pBuffer;
			for (i = 0; i < i64Depth; i++)
			{
				dOffset = i32SampleOffset - (double)(p16ShortBuffer[i]);
				dValue = dOffset / (double)i32SampleResolution;
				dValue *= dScaleFactor;
				dValue += (double)(i32DcOffset) / 1000.0;
				pVBuffer[i] = (float)dValue;
			}
			break;

		case 4:
			p32ShortBuffer = (int32 *)pBuffer;
			for (i = 0; i < i64Depth; i++)
			{
				dOffset = i32SampleOffset - (double)(p32ShortBuffer[i]);
				dValue = dOffset / (double)i32SampleResolution;
				dValue *= dScaleFactor;
				dValue += (double)(i32DcOffset) / 1000.0;
				pVBuffer[i] = (float)dValue;
			}
			break;

		default:
			i32Status = CS_MISC_ERROR;
			break;
	}

	return i32Status;
 }

int32 SetAcquisitionParameters(const CSHANDLE hSystem, const CSACQUISITIONCONFIG* const CsAcquisitionCfg)
{
	int32 i32Status = CS_SUCCESS;

	i32Status = CsSet(hSystem, CS_ACQUISITION, CsAcquisitionCfg);
	return i32Status;
}

int32 SetChannelParameters(const CSHANDLE hSystem, const CSCHANNELCONFIG* const pCsChannelCfg)
{
	int32 i32Status = CS_SUCCESS;

	i32Status = CsSet(hSystem, CS_CHANNEL, pCsChannelCfg);
	return i32Status;
}


int32 SetTriggerParameters(const CSHANDLE hSystem, const CSTRIGGERCONFIG* const pCsTriggerCfg)
{
	int32 i32Status = CS_SUCCESS;

	i32Status = CsSet(hSystem, CS_TRIGGER, pCsTriggerCfg);
	return i32Status;
}


uInt32 CS_SUPPORT_API CsAs_CalculateChannelIndexIncrement(const CSACQUISITIONCONFIG* const pAqcCfg, const CSSYSTEMINFO* const pSysInfo )
{
/*
	Regardless  of the Acquisition mode, numbers are assigned to channels in a
	CompuScope system as if they all are in use.
	For example an 8 channel system channels are numbered 1, 2, 3, 4, .. 8.
	All modes make use of channel 1. The rest of the channels indices are evenly
	spaced throughout the CompuScope system. To calculate the index increment,
	user must determine the number of channels on one CompuScope board and	then
	divide this number by the number of channels currently in use on one board.
	The latter number is lower 12 bits of acquisition mode.
*/
	uInt32 u32ChannelIncrement = 1;

	uInt32 u32MaskedMode = pAqcCfg->u32Mode & CS_MASKED_MODE;
	uInt32 u32ChannelsPerBoard = pSysInfo->u32ChannelCount / pSysInfo->u32BoardCount;

	if( u32MaskedMode == 0 )
		u32MaskedMode = 1;

	u32ChannelIncrement = u32ChannelsPerBoard / u32MaskedMode;

/*
	 If we have an invalid mode (i.e quad mode when there's only 2 channels
	 in the system) then u32ChannelIncrement might be 0. Make it 1, the
	 invalid mode will be caught when CsDrvDo(ACTION_COMMIT) is called.
*/
	return max( 1, u32ChannelIncrement);
}

#ifdef __linux__

#ifdef  VIRTUAL_ALLOC_PAGE_ALIGN

/* Allocate buffer and return page align address for the user.  
*/
void* CS_SUPPORT_API VirtualAlloc(void* lpAddress, size_t dwSize, DWORD  flAllocationType, DWORD  flProtect)
{
   uInt8 *pu8Buf = NULL;
   void* pBuf = NULL;
   VAllocBuf*  pvBufferSt = NULL; 
   int pagesize = sysconf(_SC_PAGESIZE);
   
   if (dwSize)
      pBuf = malloc(dwSize + pagesize + sizeof(VAllocBuf));
   if (pBuf)
   {
      // Get page align address
      pu8Buf = (uInt8*)(( (uInt64)pBuf + pagesize + sizeof(VAllocBuf) ) & ~(pagesize-1) ); 
      
      // Record buffer infos for later use
      pvBufferSt = (VAllocBuf*)pu8Buf -1;
      pvBufferSt->SigStart = VALLOC_SIG_START; 
      pvBufferSt->SigEnd = VALLOC_SIG_END; 
      pvBufferSt->pBuffer = pBuf;
      pvBufferSt->pBufferPage = pu8Buf;
      return pu8Buf; // pvBufferSt->pBufferPage;
   }
   return NULL;   
}

bool CS_SUPPORT_API VirtualFree(void* lpAddress, size_t dwSize, DWORD dwFreeType)
{
   // Find the original address
   VAllocBuf*  pvBufferSt = NULL; 
  
   if (lpAddress)
   {
      pvBufferSt = (VAllocBuf *)lpAddress - 1;
      if (pvBufferSt->pBuffer)
      {
         // Make sure buffer not corrupt.
         if ( (pvBufferSt->SigStart == VALLOC_SIG_START) && (pvBufferSt->SigEnd == VALLOC_SIG_END) )
         {
            free(pvBufferSt->pBuffer);
            return(TRUE);
         }
      }
      fprintf(stderr, "virtual buffer corrupted! \n"); 
   }
  
   return FALSE; 
}

#else
   
void* CS_SUPPORT_API VirtualAlloc(void* lpAddress, size_t dwSize, DWORD  flAllocationType, DWORD  flProtect)
{
   void* pBuf = NULL;
   if (dwSize)
      pBuf = malloc( dwSize );
   return(pBuf);
}
   
bool CS_SUPPORT_API VirtualFree(void* lpAddress, size_t dwSize, DWORD dwFreeType)
{
   if (lpAddress)
      free(lpAddress);
   return(TRUE); 
}   
#endif

#endif