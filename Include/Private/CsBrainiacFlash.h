#ifndef __BRAINIAC_FLASH_H__
#define __BRAINIAC_FLASH_H__

#include "CsxyG8CapsInfo.h"

typedef struct _BRAIN_GENERAL_INFO_STRUCTURE
{
	uInt32  dwSignature;  // CSI_FWCHECKSUM_VALID ( 0x45474147)
	uInt32  dwSerialNumber;
	uInt32	dwHWVersion;
	uInt32	dwHWOptions;
	uInt32  dwNumberOfImages;
	uInt32  dwImageSize;
	uInt32  dwImageChecksum[CSRB_MAX_IMAGE_NUM];
	uInt32  dwImageOptions[CSRB_MAX_IMAGE_NUM];
	char    strOEMName[16];
	uInt32  dwOEMcode;
	uInt32  dwReserved[41];

} BRAIN_GENERAL_INFO_STRUCTURE;

typedef struct _BRAIN_FLASH_CHAN_CAL_ENTRY
{
	uInt16 u16Offset;
	uInt16 u16Position;
	uInt16 u16Gain;
	uInt16 u16PositionGain;
}BRAIN_FLASH_CHAN_CAL_ENTRY;

typedef struct _BRAIN_FLASH_EXT_TRIG_CAL_ENTRY
{
	uInt16 u16Offset;
	uInt16 u16Gain;
}BRAIN_FLASH_EXT_TRIG_CAL_ENTRY;


//		---------------------------		0x000000	
//		|						|
//		|  Fw Binary image 1	|
//		|						|
//		---------------------------		0x600000
//		|						|
//		|  Calib Info 1			|
//		|						|
//		---------------------------		0x7C0000
//		|						|
//		|  Fw info 1			|
//		|						|
//		---------------------------		0x7E0000
//		|						|
//		|  Fw Binary image 2	|
//		|						|
//		---------------------------		0xDE0000
//		|						|
//		|  Calib Info 2			|
//		|						|
//		---------------------------		0xFA0000
//		|						|
//		|  Fw info 2			|
//		|						|
//		---------------------------		0xFC0000	
//		|						|
//		|  Addon Footer			|
//		|						|
//		---------------------------		0xFFFFFF
                                                         


#define BRAIN_INTEL_FLASH_SECTOR_SIZE	0x20000		// 128 k

#define	BRAIN_FLASH_SIZE				0x1000000	// Size of the Brainiac flash
#define	BRAIN_FLASH_FWIMAGESIZE			0x600000	// Maximum size reserved for Brainiac FPGA binary image


#define	BRAIN_FLASH_IMAGETRUCT_SIZE		0x280000
#define	BRAIN_NUMBER_OF_FLASHIMAGES		2			// Included the image 0 which is the boot backup image

#ifdef _WIN32
#pragma pack (1)
#endif

typedef	struct 
{
	uInt32	u32FwOptions;							// The FPGA options
	uInt32	u32ChecksumSignature;					// Should be equal to CSMV_FWCHECKSUM_VALID

} BRAIN_FLASH_FIRMWARE_INFOS;


typedef	union 
{
	CS_FIRMWARE_INFOS				FwInfoStruct;
	uInt8							u8Padding[BRAIN_INTEL_FLASH_SECTOR_SIZE];

}  BRAIN_FLASH_FWINFO_SECTOR;


#define	BRAIN_FLASH_CALIBINFO_SIZE		0x1C0000


// Each of fields starts at BRAIN_INTEL_FLASH_SECTOR_SIZE (128 K) boundary
typedef struct _BRAIN_FLASH_IMAGE_STRUCT
{
	uInt8							Image [BRAIN_FLASH_FWIMAGESIZE];		// Flash Image binary
	uInt8							Calib [BRAIN_FLASH_CALIBINFO_SIZE];	// Calibration 
	BRAIN_FLASH_FWINFO_SECTOR		FwInfo;										// Last 128K in this structure

} BRAIN_FLASH_IMAGE_STRUCT;


typedef union	_BRAIN_FLASHFOOTER 
{
	CS_FLASHFOOTER	Footer;	
	uInt8			u8Padding[BRAIN_INTEL_FLASH_SECTOR_SIZE];
} BRAIN_FLASHFOOTER, *PBRAIN_FLASHFOOTER;


typedef struct	_BRAIN_EXTRAINFO
{
	uInt32			u32MemSizeKb;
	uInt32			u32HwOptions0;				// Hw options presume "Base"
} BRAIN_EXTRAINFO, *PBRAIN_EXTRAINFO;


// Each of fields starts at BRAIN_INTEL_FLASH_SECTOR_SIZE (256 K) boundary
typedef struct
{
	BRAIN_FLASH_IMAGE_STRUCT		FlashImage1;
	BRAIN_FLASH_IMAGE_STRUCT		FlashImage2;

	CS_FLASHFOOTER					Footer;

} BRAIN_FLASH_LAYOUT;



#ifdef _WIN32
#pragma pack ()
#endif

#endif