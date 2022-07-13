#ifndef __RABBIT_FLASH_H__
#define __RABBIT_FLASH_H__

#include "CsxyG8CapsInfo.h"

typedef struct _RABBIT_GENERAL_INFO_STRUCTURE
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

} RABBIT_GENERAL_INFO_STRUCTURE;

typedef struct _RABBIT_FLASH_CHAN_CAL_ENTRY
{
	uInt16 u16Offset;
	uInt16 u16Position;
	uInt16 u16Gain;
	uInt16 u16PositionGain;
}RABBIT_FLASH_CHAN_CAL_ENTRY;

typedef struct _RABBIT_FLASH_EXT_TRIG_CAL_ENTRY
{
	uInt16 u16Offset;
	uInt16 u16Gain;
}RABBIT_FLASH_EXT_TRIG_CAL_ENTRY;




//	LAYOUT OF THE RABBIT ADDON FLASH
//	
//	Each of fields always starts at sector boundary RABBIT_INTEL_FLASH_SECTOR_SIZE (128 K)

//		---------------------------		0x000000	
//		|						|
//		|  Fw Binary image 1	|
//		|						|
//		---------------------------		0x300000
//		|						|
//		|  Calib Info 1			|
//		|						|
//		---------------------------		0x3C0000
//		|						|
//		|  Fw info 1			|
//		|						|
//		---------------------------		0x3E0000
//		|						|
//		|  Fw Binary image 2	|
//		|						|
//		---------------------------		0x6E0000
//		|						|
//		|  Calib Info 2			|
//		|						|
//		---------------------------		0x7A0000
//		|						|
//		|  Fw info 2			|
//		|						|
//		---------------------------		0x7C0000	
//		|						|
//		|  Addon Footer			|
//		|						|
//		---------------------------		0x7FFFFF
                                                         


#define RABBIT_INTEL_FLASH_SECTOR_SIZE		0x20000		// 128 k

#define	RBT_ADDONFLASH_SIZE					0x800000	// Size of the Rabbit add-on flash
#define	RBT_ADDONFLASH_FWIMAGESIZE			0x300000	// Maximum size reserved for Rabbit add-on FPGA binary image


#define	RBT_ADDONFLASH_IMAGETRUCT_SIZE		((RBT_ADDONFLASH_SIZE-2*RABBIT_INTEL_FLASH_SECTOR_SIZE) / 2)
#define	RBT_NUMBER_OF_ADDDONIMAGES			2

#ifdef _WIN32
#pragma pack (1)
#endif

typedef	struct 
{
	uInt32	u32AddOnFwOptions;						// The FPGA options
	uInt32	u32ChecksumSignature;					// Should be equal to CSMV_FWCHECKSUM_VALID

} RBT_ADDONFLASH_FIRMWARE_INFOS;


typedef	union 
{
	CS_FIRMWARE_INFOS				FwInfoStruct;
	uInt8							u8Padding[RABBIT_INTEL_FLASH_SECTOR_SIZE];

}  RBT_ADDONFLASH_FWINFO_SECTOR;


#define	RBT_ADDONFLASH_CALIBINFO_SIZE	(RBT_ADDONFLASH_IMAGETRUCT_SIZE - RBT_ADDONFLASH_FWIMAGESIZE - sizeof(RBT_ADDONFLASH_FWINFO_SECTOR) )


// Each of fields starts at RABBIT_INTEL_FLASH_SECTOR_SIZE (128 K) boundary
typedef struct _RBT_ADDONFLASH_IMAGE_STRUCT
{
	uInt8							Image [RBT_ADDONFLASH_FWIMAGESIZE];		// Flash Image binary
	uInt8							Calib [RBT_ADDONFLASH_CALIBINFO_SIZE];	// Calibration 
	RBT_ADDONFLASH_FWINFO_SECTOR	FwInfo;									// Last 128K in this structure

} RBT_ADDONFLASH_IMAGE_STRUCT;


// Each of fields starts at RABBIT_INTEL_FLASH_SECTOR_SIZE (128 K) boundary
typedef struct
{
	RBT_ADDONFLASH_IMAGE_STRUCT		FlashImage1;
	RBT_ADDONFLASH_IMAGE_STRUCT		FlashImage2;

	CS_FLASHFOOTER					Footer;

} RBT_ADDONFLASH_LAYOUT;

#ifdef _WIN32
#pragma pack ()
#endif

#endif