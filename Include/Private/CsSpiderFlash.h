#ifndef __SPIDER_FLASH_H__
#define __SPIDER_FLASH_H__

#include "Cs8xxxCapsInfo.h"

#define SPDR_PUBLIC_FLASH_INFO_SIZE         64*sizeof(uInt32)

typedef struct _SPDR_GENERAL_INFO_STRUCTURE
{
	uInt32  dwSignature;  // CSI_FWCHECKSUM_VALID ( 0x45474147)
	uInt32  dwSerialNumber;
	uInt32	dwHWVersion;
	uInt32	dwHWOptions;
	uInt32  dwNumberOfImages;
	uInt32  dwImageSize;
	uInt32  dwImageChecksum[CSPDR_MAX_IMAGE_NUM];
	uInt32  dwImageOptions[CSPDR_MAX_IMAGE_NUM];
	char    strOEMName[16];
	uInt32  dwOEMcode;
	uInt32  u32ClkOut;
	uInt32  u32TrigOutEnabled;
} SPDR_GENERAL_INFO_STRUCTURE;

typedef struct _SPDR_FLASH_CHAN_CAL_ENTRY
{
	uInt16 u16Offset;
	uInt16 u16Position;
	uInt16 u16Gain;
	uInt16 u16PositionGain;
}SPDR_FLASH_CHAN_CAL_ENTRY;

typedef struct _SPDR_FLASH_EXT_TRIG_CAL_ENTRY
{
	uInt16 u16Offset;
	uInt16 u16Gain;
}SPDR_FLASH_EXT_TRIG_CAL_ENTRY;

typedef struct _SPDR_FLASH_STRUCT
{
	union
	{
		SPDR_GENERAL_INFO_STRUCTURE   data;   
		uInt8                         a[SPDR_PUBLIC_FLASH_INFO_SIZE];                                                   //  64 uInt32s
	}Info;
	SPDR_FLASH_CHAN_CAL_ENTRY     ChanCaltableHighImped[CSPDR_CHANNELS][CSPDR_MAX_UNRESTRICTED_INDEX][CSPDR_MAX_RANGES];//4096 uInt32s
	SPDR_FLASH_CHAN_CAL_ENTRY     ChanCaltableLowImped[CSPDR_CHANNELS][CSPDR_MAX_UNRESTRICTED_INDEX][CSPDR_MAX_RANGES]; //4096 uInt32s
	SPDR_FLASH_EXT_TRIG_CAL_ENTRY ExtTrigCalTable[CSPDR_EXT_TRIG_RANGES];                                               //   2 uInt32s   
}SPDR_FLASH_STRUCT;                                                                                                     


#define SPDR_FLASH_SIZE			            0x800000	// Addon Spider Flash Size
#define SPDR_INTEL_FLASH_SECTOR_SIZE		0x20000		// 128 k
#define SPDR_FLASH_INFO_ADDR                (SPDR_FLASH_SIZE-SPDR_INTEL_FLASH_SECTOR_SIZE)    // Last page 
#endif