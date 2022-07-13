#ifndef __CSMV_BBXXL_FLASH_H__
#define __CSMV_BBXXL_FLASH_H__

#include "CsPrivateStruct.h"


// IMPORTANT
// The real size of BIGFPGA FLASH is 8M
// The structure defined below uses only half of flash size


//	LAYOUT OF THE BASEBOARD BIGFPGA FLASH
//	
//	Each of fields always starts at sector boundary COMBINE_FLASH_SECTOR_SIZE (64 K)

//		---------------------------		0x000000	
//		|						|
//		|  Fw Binary image 1	|
//		|						|
//		---------------------------		0x180000
//		|						|
//		|  Calib Info 1			|
//		|						|
//		---------------------------		0x1E0000
//		|						|
//		|  Fw info 1			|
//		|						|
//		---------------------------		0x1F0000
//		|						|
//		|  Fw Binary image 2	|
//		|						|
//		---------------------------		0x370000
//		|						|
//		|  Calib Info 2			|
//		|						|
//		---------------------------		0x3D0000
//		|						|
//		|  Fw info 2			|
//		|						|
//		---------------------------		0x3E0000	
//		|						|
//		|  BB Flash Footer		|
//		|						|
//		---------------------------		0x400000
                                                         

#define	COMBINE_FLASH_SECTOR_SIZE		FLASH_SECTOR_SIZE

#define	CSMV_BBXXL_FLASH_SIZE			0x400000	// Size of the BB FAT flash
#define	CSMV_BBXXL_FWIMAGESIZE			0x180000	// Maximum size reserved for FAT FPGA binary image


#define	CSMV_BBXXL_IMAGETRUCT_SIZE		((CSMV_BBXXL_FLASH_SIZE-2*COMBINE_FLASH_SECTOR_SIZE) / 2)
#define	CSMV_BBXXL_NUMOFIMAGES			2

#ifdef _WIN32
#pragma pack (1)
#endif

typedef	union 
{
	CS_FIRMWARE_INFOS				FwInfoStruct;
	uInt8							u8Padding[COMBINE_FLASH_SECTOR_SIZE];

}  CSMV_BBXXL_FIRMWAREINFO_SECTOR;


#define	CSMV_BBXXL_CALIBINFO_SIZE	(CSMV_BBXXL_IMAGETRUCT_SIZE - CSMV_BBXXL_FWIMAGESIZE - sizeof(CSMV_BBXXL_FIRMWAREINFO_SECTOR) )


// Each of fields starts at RABBIT_INTEL_FLASH_SECTOR_SIZE (128 K) boundary
typedef struct _CSMV_BBXXL_FLASHIMAGESTRUCT
{
	uInt8	Image [CSMV_BBXXL_FWIMAGESIZE];		// Flash Image binary

	uInt8	Calib [CSMV_BBXXL_CALIBINFO_SIZE];	// Calibration 

	CSMV_BBXXL_FIRMWAREINFO_SECTOR	FwInfo;		// Last 128K in this structure


} CSMV_BBXXL_FLASHIMAGESTRUCT;


// Each of fields starts at RABBIT_INTEL_FLASH_SECTOR_SIZE (128 K) boundary
typedef struct
{
	CSMV_BBXXL_FLASHIMAGESTRUCT		FlashImage1;
	CSMV_BBXXL_FLASHIMAGESTRUCT		FlashImage2;

	CS_FLASHFOOTER					Footer;

} CSMV_BBXXL_FLASHLAYOUT;


#ifdef _WIN32
#pragma pack ()
#endif

#endif