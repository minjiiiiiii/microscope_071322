/*************************************************************
*	CsFS.h				Copyright (c) 2003.					 *
*						Gage Applied Sciences Inc.		     *
*                                                            *
**************************************************************/
#ifndef _CS_FS_H_
#define _CS_FS_H_

#include "CsTypes.h"
#include "CsPrototypes.h"
#include "DiskHead.h"
#include "CsPrivateStruct.h"
#include <stdio.h>


uInt32	CalculateReadingOffset ( uInt32 u32Mode,
								 uInt32 u16DeimationFactor,
								 uInt32	u32RealDepth,
								 uInt32	u32RealSegmentSize,
								 uInt32	u32StartAddressOffset,
								 uInt32 u32TaLow,
								 uInt32 u32TaHigh,
								 uInt32	*u32OffsetAdjust );

uInt32	CalculateReadingOffsetSpider ( uInt32 u32Mode,
								 uInt32	u32RealDepth,
								 uInt32	u32RealSegmentSize,
								 uInt32	u32StartAddressOffset,
								 uInt32 u32TaLow,
								 uInt32 u32TaHigh,
								 uInt32	*u32OffsetAdjust );


int32 FS_API RetrieveChannelFromRawBuffer ( PVOID	pMulrecRawDataBuffer,
											int64	i64RawDataBufferSize,
											uInt32	u32SegmentId,
											uInt16	ChannelIndex,
											int64	i64Start,
											int64	i64Length,
											PVOID	pNormalizedDataBuffer,
											int64*	pi64TrigTimeStamp,
											int64*	pi64ActualStart,
											int64*	pi64ActualLength );

int32 FS_API CreateSigHeader(PCSDISKFILEHEADER pHeader, 
							 PCSACQUISITIONCONFIG pAcqConfig, 
							 PCSCHANNELCONFIG pChanConfig, 
							 int32 i32XferStart, 
							 int32 i32XferLength, 
							 uInt32 u32RecordCount);

int32 FS_API ConvertToSigHeader(PCSDISKFILEHEADER pHeader, PCSSIGSTRUCT pSigStruct, TCHAR* szComment, TCHAR* szName);


int32 FS_API ConvertFromSigHeader(PCSDISKFILEHEADER pHeader, PCSSIGSTRUCT pSigStruct, TCHAR* szComment, TCHAR* szName); 

#endif
