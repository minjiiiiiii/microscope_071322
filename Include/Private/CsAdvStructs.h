/********************************************************************************************************************
 *   CsAdvStruct.h
 *
 *
 *   Version 1.0
 ********************************************************************************************************************/
#ifndef _CS_ADVANCE_STRUCT_H_
#define _CS_ADVANCE_STRUCT_H_

#if defined(__linux__) && !defined(__KERNEL__)
	#include "CsLinuxPort.h"
#endif

#include "CsTypes.h"
#include "CsStruct.h"
#include "CsPrivateStruct.h"

#ifdef _WIN32
#pragma once
#endif

#define	DEFAULT_SWFIFO_SIZE			4
#define	DEFAULT_NOSODIM_MEMORY		(128*1024)				// In bytes
#define	FIXMULRECSIZE				(DEFAULT_NOSODIM_MEMORY / 4)

#define MAX_MULRECSTREAM_SEMGENTSIZE	16384			// Max trigger depth in Mulrec Stream mode (in samples)
#define MAX_MULREC_FOOTERS				16				// Mulrec Foooter (in samples)



#ifdef _WIN32
#pragma pack (8)
#endif


// These 2 structures should be obsolete. I'll comment them out for now.
// They should eventually be completely removed
/*
typedef struct _STMMULREC_SEGMENTINFO
{
	uInt32				u32SegmentNumber;
	int32				i32ActualStart;
	uInt32				u32ActualLength;
	uInt32				u32TriggerCount	;
	int64				i64TriggerTimestamp;
} STMMULREC_SEGMENTINFO, *PSTMMULREC_SEGMENTINFO;


typedef struct _CARD_DRIVER_PARAMS
{
	SEM_HANDLE		hStmSemaphore;					// Semaphore handle for Realtime

	STMSTATUS	StmStatus;

	CSFOLIO		StmBuffer[4];
	PUCHAR		pStmBufferX;
	PSTMMULREC_SEGMENTINFO	pMulRecSegmentInfo;
	PVOID		pChannelData[10];
} CARD_DRIVER_PARAMS, *PCARD_DRIVER_PARAMS;
*/

// Structure CSSAMPLERATETABLE
typedef struct _CSSAMPLERATETABLE_EX
{
	CSSAMPLERATETABLE	PublicPart;		// Pubblic part of SampleRate Table
	// The following fields are reserved for driver use and
	// hidden from user view
	uInt32	u32Mode;				// Reserved for internal drivbers use
	uInt32  u32CardSupport;			//
} CSSAMPLERATETABLE_EX, *PCSSAMPLERATETABLE_EX;


// Structure CS_EXTCLOCK_TABLE
typedef struct _CS_EXTCLOCK_TABLE
{
	int64	i64Max;				//	Max limit for external clock rate
	int64	i64Min;				//	Min limit for external clock rate
	uInt32	u32Mode;			//  Reserved for internal drivers use
	uInt32  u32SkipCount;       //  External Clock SkipCount for the mode where 1000 corresponds to 1
	uInt32  u32CardSupport;		//  Card idenfifier
} CS_EXTCLOCK_TABLE, *PCS_EXTCLOCK_TABLE;

// Structure CSRANGETABLE_EX
typedef struct _CSRANGETABLE_EX
{
	CSRANGETABLE	PublicPart;		// Pubblic part of SampleRate Table
	// The following fields are reserved for driver use and
	// hidden from user view
	uInt32	u32Option;				// Reserved for internal drivbers use
} CSRANGETABLE_EX, *PCSRANGETABLE_EX;





#ifdef _WIN32
#pragma pack ()
#endif


//!
//! \}
//!

#endif
