#ifndef __BUNNY_FLASH_H__
#define __BUNNY_FLASH_H__

#include "CsBunnyCapsInfo.h"

typedef struct _BUNNY_GENERAL_INFO_STRUCTURE
{
	uInt32  dwSignature;  // CSI_FWCHECKSUM_VALID ( 0x45474147)
	uInt32  dwSerialNumber;
	uInt32	dwHWVersion;
	uInt32	dwHWOptions;
	uInt32  dwNumberOfImages;
	uInt32  dwImageSize;
	uInt32  dwImageChecksum[BUNNY_MAX_IMAGE_NUM];
	uInt32  dwImageOptions[BUNNY_MAX_IMAGE_NUM];
	char    strOEMName[16];
	uInt32  dwOEMcode;
	uInt32  dwReserved[41];

} BUNNY_GENERAL_INFO_STRUCTURE;

typedef struct _BUNNY_FLASH_CHAN_CAL_ENTRY
{
	uInt16 u16Offset;
	uInt16 u16Position;
	uInt16 u16Gain;
	uInt16 u16PositionGain;
}BUNNY_FLASH_CHAN_CAL_ENTRY;

typedef struct _BUNNY_FLASH_EXT_TRIG_CAL_ENTRY
{
	uInt16 u16Offset;
	uInt16 u16Gain;
}BUNNY_FLASH_EXT_TRIG_CAL_ENTRY;



//		---------------------------		0x000000	
//		|							|
//		|  Fw Binary image 1		|
//		|							|
//		---------------------------		0x220000
//		|							|
//		|  Calib Info 1				|
//		|							|
//		---------------------------		0x260000
//		|							|
//		|  Fw info 1				|
//		|							|
//		---------------------------		0x280000
//		|							|
//		|  Fw Binary image 2		|
//		|							|
//		---------------------------		0x4A0000
//		|							|
//		|  Calib Info 2				|
//		|							|
//		---------------------------		0x4E0000
//		|							|
//		|  Fw info 2				|
//		|							|
//		---------------------------		0x500000
//		|							|
//		|  Fw Binary image 3		|
//		|							|
//		---------------------------		0x720000
//		|							|
//		|  Calib Info 3				|
//		|							|
//		---------------------------		0x760000
//		|							|
//		|  Fw info 3				|
//		|							|
//		---------------------------		0x780000	
//		|							|
//		|  Flash Footer				|
//		|							|
//		---------------------------		0x7A0000
//		|							|
//		| Options for Bunny Card	|
//		|(Number oo channels		|
//		| Max sampleing rate etc )  |
//		|							|
//		---------------------------		0x7E0000
//		|							|
//		| Reserved for Hardware		|	
//		|							|
//		---------------------------		0x800000         


#define BUNNY_INTEL_FLASH_SECTOR_SIZE	0x20000		// 128 k

#define	BUNNY_FLASH_SIZE				0x800000	// Size of the Rabbit add-on flash
#define	BUNNY_FLASH_FWIMAGESIZE			0x220000	// Maximum size reserved for Rabbit add-on FPGA binary image


#define	BUNNY_FLASH_IMAGETRUCT_SIZE		0x280000
#define	BUNNY_NUMBER_OF_FLASHIMAGES		3			// Included the image 0 which is the boot backup image

#ifdef _WIN32
#pragma pack (1)
#endif

typedef	struct 
{
	uInt32	u32FwOptions;							// The FPGA options
	uInt32	u32ChecksumSignature;					// Should be equal to CSMV_FWCHECKSUM_VALID

} BUNNY_FLASH_FIRMWARE_INFOS;


typedef	union 
{
	CS_FIRMWARE_INFOS				FwInfoStruct;
	uInt8							u8Padding[BUNNY_INTEL_FLASH_SECTOR_SIZE];

}  BUNNY_FLASH_FWINFO_SECTOR;


#define	BUNNY_FLASH_CALIBINFO_SIZE		0x40000


// Each of fields starts at BUNNY_INTEL_FLASH_SECTOR_SIZE (128 K) boundary
typedef struct _BUNNY_FLASH_IMAGE_STRUCT
{
	uInt8							Image [BUNNY_FLASH_FWIMAGESIZE];		// Flash Image binary
	uInt8							Calib [BUNNY_FLASH_CALIBINFO_SIZE];	// Calibration 
	BUNNY_FLASH_FWINFO_SECTOR	FwInfo;										// Last 128K in this structure

} BUNNY_FLASH_IMAGE_STRUCT;


typedef union	_BUNNY_FLASHFOOTER 
{
	CS_FLASHFOOTER	Footer;	
	uInt8			u8Padding[BUNNY_INTEL_FLASH_SECTOR_SIZE];
} BUNNY_FLASHFOOTER, *PBUNNY_FLASHFOOTER;


typedef struct	_BUNNY_EXTRAINFO
{
	uInt32			u32MemSizeKb;
	uInt32			u32HwOptions0;				// Hw options presume "Base"
} BUNNY_EXTRAINFO, *PBUNNY_EXTRAINFO;

// Each of fields starts at BUNNY_INTEL_FLASH_SECTOR_SIZE (128 K) boundary
typedef struct
{
	BUNNY_FLASH_IMAGE_STRUCT		Reserved;		// Boot backup image
	BUNNY_FLASH_IMAGE_STRUCT		FlashImage1;
	BUNNY_FLASH_IMAGE_STRUCT		FlashImage2;

	BUNNY_FLASHFOOTER				Footer;
	BUNNY_EXTRAINFO					ExtrasInfo;

} BUNNY_FLASH_LAYOUT;

#ifdef _WIN32
#pragma pack ()
#endif

#endif