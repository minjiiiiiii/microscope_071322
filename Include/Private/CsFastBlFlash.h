#ifndef __FASTBL_FLASH_H__
#define __FASTBL_FLASH_H__

#include "CsBunnyCapsInfo.h"

typedef struct _FASTBL_GENERAL_INFO_STRUCTURE
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

} FASTBL_GENERAL_INFO_STRUCTURE;

typedef struct _FASTBL_FLASH_CHAN_CAL_ENTRY
{
	uInt16 u16Offset;
	uInt16 u16Position;
	uInt16 u16Gain;
	uInt16 u16PositionGain;
}FASTBL_FLASH_CHAN_CAL_ENTRY;

typedef struct _FASTBL_FLASH_EXT_TRIG_CAL_ENTRY
{
	uInt16 u16Offset;
	uInt16 u16Gain;
}FASTBL_FLASH_EXT_TRIG_CAL_ENTRY;



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


#define FASTBL_INTEL_FLASH_SECTOR_SIZE	0x20000		// 128 k

#define	FASTBL_FLASH_SIZE				0x800000	// Size of the Bunny add-on flash
#define	FASTBL_FLASH_FWIMAGESIZE		0x220000	// Maximum size reserved for Bunnyt add-on FPGA binary image


#define	FASTBL_FLASH_IMAGETRUCT_SIZE		0x280000
#define	FASTBL_NUMBER_OF_FLASHIMAGES		3			// Included the image 0 which is the boot backup image

#ifdef _WIN32
#pragma pack (1)
#endif

typedef	struct 
{
	uInt32	u32FwOptions;							// The FPGA options
	uInt32	u32ChecksumSignature;					// Should be equal to CSMV_FWCHECKSUM_VALID

} FASTBL_FLASH_FIRMWARE_INFOS;


typedef	union 
{
	CS_FIRMWARE_INFOS				FwInfoStruct;
	uInt8							u8Padding[FASTBL_INTEL_FLASH_SECTOR_SIZE];

}  FASTBL_FLASH_FWINFO_SECTOR;


#define	FASTBL_FLASH_CALIBINFO_SIZE		0x40000


// Each of fields starts at FASTBL_INTEL_FLASH_SECTOR_SIZE (128 K) boundary
typedef struct _FASTBL_FLASH_IMAGE_STRUCT
{
	uInt8							Image [FASTBL_FLASH_FWIMAGESIZE];		// Flash Image binary
	uInt8							Calib [FASTBL_FLASH_CALIBINFO_SIZE];	// Calibration 
	FASTBL_FLASH_FWINFO_SECTOR	FwInfo;										// Last 128K in this structure

} FASTBL_FLASH_IMAGE_STRUCT;


typedef union	_FASTBL_FLASHFOOTER 
{
	CS_FLASHFOOTER	Footer;	
	uInt8			u8Padding[FASTBL_INTEL_FLASH_SECTOR_SIZE];
} FASTBL_FLASHFOOTER, *PFASTBL_FLASHFOOTER;


typedef struct	_FASTBL_EXTRAINFO
{
	uInt32			u32MemSizeKb;
	uInt32			u32HwOptions0;				// Hw options presume "Base"
} FASTBL_EXTRAINFO, *PFASTBL_EXTRAINFO;

// Each of fields starts at FASTBL_INTEL_FLASH_SECTOR_SIZE (128 K) boundary
typedef struct
{
	FASTBL_FLASH_IMAGE_STRUCT		Reserved;		// Boot backup image
	FASTBL_FLASH_IMAGE_STRUCT		FlashImage1;
	FASTBL_FLASH_IMAGE_STRUCT		FlashImage2;

	FASTBL_FLASHFOOTER				Footer;
	FASTBL_EXTRAINFO				ExtrasInfo;

} FASTBL_FLASH_LAYOUT;

#ifdef _WIN32
#pragma pack ()
#endif

#endif