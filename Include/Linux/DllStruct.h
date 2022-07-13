#ifndef _CS_DLLSTRUCT_H_
#define _CS_DLLSTRUCT_H_

#include "CsTypes.h"
#include "CsAdvStructs.h"
#include "CsSharedMemory.h"



#define		MAX_NAME_LENGTH		64	// Max Dll name  Ex:"Cs12xx.dll"
#define		MAX_CARDS_MS		10	// Max cards in M/S system
#define		CS_MAX_PADDING		512

#define		FIELD_OFFSET(type, field)    ((LONG)(LONG_PTR)&(((type *)0)->field))


typedef struct _CHANNEL_DATA_TRANSFER
{
	uInt32			u32SegmentTx;				// Current Segment
	uInt32			u32TriggerAddress;			// Origial trigger address rerturned fom HW
	uInt32			u32StartTxAddr;				// Current StartAddress of transfer
	uInt16			u16ChannelTx;				// Current Channel
	uInt32			u32DescriptorSize;			// Current Desciptor Size
	BOOL			bUseSlaveTransfer;			// Bus master not supported
	BOOL			bMulrecRawTxMode;			// Multiple record raw data transfer
	uInt8			*pTempDataBuffer;			// Temporary data buffer used for Dmux
												// (Single channel data transfer slave only)
	uInt32			u32LastBytesTransfered;		// Last bytes transfered
	LARGE_INTEGER	i64TotalBytesTransfered;	// Total bytes transfered
	uInt32			u32TxState;					// State of data transfer engine (active or idle)
	BOOL			bFirstTransfer;				// The first chunk of data in Multiple Chunks data transfer
	BOOL			bLastTransfer;				// The last chunk of data in Multiple Chunks data transfer
	int32			i32Status;					// Current transfer status


	uInt32			u32AsynThreadId;
	EVENT_HANDLE	hAsynThread;
	EVENT_HANDLE	hAsynEvent;
	EVENT_HANDLE	hUserAsynEvent;

} CHANNEL_DATA_TRANSFER, *PCHANNEL_DATA_TRANSFER;


#if QQQLINUX
typedef struct _CSTxPARAMS
{
	DRVHANDLE				DrvHdl;
	IN_PARAMS_TRANSFERDATA	InParams;
	PVOID					pBaseHwDLL;
	HANDLE					hBlockTxEvent;		// Block transfer
	HANDLE					*hUserNotifyEvent;
	BOOLEAN					bAbort;
	BOOLEAN					bMulrecRawDataTx;
} CSTxPARAMS, *PCSTxPARAMS;
#endif

typedef struct _DRVSYSTEM
{
	DRVHANDLE			DrvHandle;			// CS Driver habdle
	CSSYSTEMINFO		SysInfo;
	CSSYSTEMINFOEX		SysInfoEx;			// Private systeminfo
	CSACQUISITIONCONFIG AcqConfig;

	EVENT_HANDLE		hSerialAsyncTransfer;// Handle of the thread when a big Async transfer is divided by seires of
											// smaller transfers by DLL.

	char				SymbolicLink[MAX_NAME_LENGTH];	// CS system SymbolicLink

	EVENT_HANDLE				hDataAvailableEvent2;	// Generic place holdder for Data available event.
	EVENT_HANDLE				hDataAvailableEvent;	// Generic place holdder for Data available event.
	EVENT_HANDLE				hAcqEvent;			// Generic place holdder for Acq .system event.
	EVENT_HANDLE				hErrorEvent;		// Generic place holdder for Error event.
	EVENT_HANDLE				hSwFifoFullEvent;	// Generic place holdder for Error event.
	PVOID				pBufferAllocated;	// Internal buffer
	uInt32				u32ReadIndex;		// Mulrec Stream Read index

	uInt32				u32NumOfFolios;		// Number Of Folios



//	PCARD_DRIVER_PARAMS	pCardParams;		// Pointer array of card Params  // should be obsolete now
	PVOID               pCapsInfo;          // Pointer to board specific caps info structure

	//QQQWDK
	uInt8				u8CardIndexList[MAX_CARDS_MS];
	PVOID				pFirstInSystem;

	uInt8			u8FirstCardIndex;		// Index of the fist card

	uInt16			u16AcqStatus;		// Acquisition System Status
	BOOL			bInitialized;		// The system has been initialized.
	BOOL			bReset;				// Abort current operation and
										// reset the system to the default state

	BOOL			bEndAcquisitionNotification;	// protect race condition for EndOfBusy notification
	uInt32			u32TriggerNotification;		// number of trigger notification to application

	uInt32			u32TriggeredCount;			// number of triggerred event received by interrupts



	EVENT_HANDLE		hAcqSystemCleanup;
	EVENT_HANDLE			hThreadIntr;				// thread waiting for interrupts
	uInt32			u32ThreadIntrId;			// thread waiting for interrupts
	EVENT_HANDLE			hEventTriggered;
	EVENT_HANDLE			hEventEndOfBusy;

	EVENT_HANDLE			hUserEventTriggered;
	EVENT_HANDLE			hUserEventEndOfBusy;
	uInt16			u16ActiveChannelTx;				// Active Channel Data Transfer


}DRVSYSTEM, *PDRVSYSTEM;



typedef struct _HW_DLL_LOOKUPTABLE
{
	uInt16		u16SystemCount;
	DRVSYSTEM	DrvSystem[MAX_ACQ_SYSTEMS];
} HW_DLL_LOOKUPTABLE, *PHW_DLL_LOOKUPTABLE;


typedef struct _SHARED_DLL_GLOBALS
{
	uInt32				ProcessCount;
	HW_DLL_LOOKUPTABLE	g_StaticLookupTable;
	volatile long		g_Critical;
	uInt16				g_RefCount;
} SHARED_DLL_GLOBALS, *PSHARED_DLL_GLOBALS;

typedef SharedMem< SHARED_DLL_GLOBALS >  SHAREDDLLMEM;
typedef SHAREDDLLMEM*  PSHAREDDLLMEM;
//typedef vector <PSHAREDDLLMEM> VECSHAREDDLLMEM;


typedef struct _GLOBAL_PERPROCESS
{
	PVOID			pFirstUnCfg;			// Before organized master/slave operation, all card detected are
												// considered as unconfig cards.
												// This pointer points to the first unconfig card
	PVOID			pLastUnCfg;			// Pointer to the last unconfig card
	PVOID			pInvalidCfg;		// Pointer to list of card that have invalidate configuration
												// (Ex: Slave cards but missing the Master card)
	uInt16			NbSystem;			// Number of System DllStructdetected.

	BOOL			bForceIndependantMode; // FALSE (0)  Default
												 // Driver will do Organize Master/Slave operaton
												 // TRUE (1)
												 // Each card detected in system will have its own DRVHANDLE
												 // This mode is used when we want to change the confiruration
												 // of M/S or Independant


	PVOID			hNativeFirstCard;		// First card delected

} GLOBAL_PERPROCESS, *PGLOBAL_PERPROCESS;




#endif   // _CS_DLLSTRUCT_H_
