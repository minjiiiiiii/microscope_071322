//! DrvCommonType_h
//!
//!
#include "CsDrvConst.h"

#ifndef __CsDrvCommonType_h__
#define __CsDrvCommonType_h__

typedef struct _PCI_CONFIG_HEADER_0
{
    USHORT  VendorID;
    USHORT  DeviceID;
    USHORT  Command;
    USHORT  Status;
    UCHAR   RevisionID;
    UCHAR   ProgIf;
    UCHAR   SubClass;
    UCHAR   BaseClass;
    UCHAR   CacheLineSize;
    UCHAR   LatencyTimer;
    UCHAR   HeaderType;
    UCHAR   BIST;
    ULONG   BaseAddresses[6];
	ULONG	CardBusCISPtr;
    USHORT	SubsystemVendorID;
	USHORT	SubsystemID;
	ULONG	ROMBaseAddress;
    ULONG   Reserved2[2];
    UCHAR   InterruptLine;
    UCHAR   InterruptPin;
    UCHAR   MinimumGrant;
    UCHAR   MaximumLatency;
} PCI_CONFIG_HEADER_0;



typedef enum
{
	AccessAuto = 0,
	AccessFirst = AccessAuto + 1,
	AccessMiddle = AccessAuto + 2,
	AccessLast = AccessAuto + 3,
} FlashAccess;


typedef enum
{
	ermStandAlone = 0,
	ermMaster = ermStandAlone + 1,
	ermSlave  = ermMaster + 1,
	ermLast   = ermSlave + 1,
}eRoleMode;

typedef enum
{
	etoTrigOut       = CS_TRIGOUT_MODE,
	etoPulseOut      = CS_PULSEOUT_MODE,
	etoExtTrigEnable = CS_EXTTRIG_EN_MODE,
}eTrigOutMode;

typedef enum
{
	epmNone = CS_OUT_NONE,
	epmDataValid      = CS_PULSEOUT_DATAVALID,
	epmNotDataValid   = CS_PULSEOUT_NOT_DATAVALID,
	epmStartDataValid = CS_PULSEOUT_START_DATAVALID,
	epmEndDataValid   = CS_PULSEOUT_END_DATAVALID,
	epmSync           = CS_PULSEOUT_SYNC,
}ePulseMode;

typedef enum
{
	eteAlways      = CS_OUT_NONE,
	eteExtLive     = CS_EXTTRIGEN_LIVE,
	eteExtPosLatch = CS_EXTTRIGEN_POS_LATCH,
	eteExtNegLatch = CS_EXTTRIGEN_NEG_LATCH,
	eteExtPosLatchOnce = CS_EXTTRIGEN_POS_LATCH_ONCE,
	eteExtNegLatchOnce = CS_EXTTRIGEN_NEG_LATCH_ONCE,
}eTrigEnableMode;

typedef enum
{
	eclkoNone = CS_OUT_NONE,
	eclkoSampleClk =CS_CLKOUT_SAMPLE,
	eclkoRefClk = CS_CLKOUT_REF,
	eclkoGBusClk = CS_CLKOUT_GBUS,
}eClkOutMode;

typedef enum
{
	eAuxInNone = CS_OUT_NONE,
	eAuxInExtTrigEnable = CS_EXTTRIG_EN_MODE,
	eAuxInTimestampReset = CS_TS_RESET_MODE,
}eAuxIn;

typedef enum
{
	eAuxOutNone = CS_OUT_NONE,
	eAuxOutBusyOut = CS_PULSEOUT_DATAVALID,
}eAuxOut;



typedef struct _PLXBASE_DATA
{
	PCI_CONFIG_HEADER_0 PCIConfigHeader;

	uInt32				IntBaseMask;
	CS_BOARD_NODE		CsBoard;
	INITSTATUS			InitStatus;

	BOOLEAN				bFlashReset;				// Reset flash is needed before any operation on Flash
	uInt32				u32NvRamSize;

} PLXBASE_DATA, *PPLXBASE_DATA;


typedef struct _PLDACORE_DATA
{
	PCI_CONFIG_HEADER_0 PCIConfigHeader;

	// public vrariables
	BOOLEAN                bDirectGio;
	BOOLEAN				bGioEnabled;

	uInt32				u32RegCSR;

	uInt32				IntBaseMask;
	uInt8				u8ActiveImageId;			// Current active FPGA image;

} PLDACORE_DATA, *PPLDACORE_DATA;


#endif