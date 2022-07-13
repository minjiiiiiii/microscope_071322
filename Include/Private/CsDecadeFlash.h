#ifndef __DECADE_FLASH_H__
#define __DECADE_FLASH_H__



//	LAYOUT OF THE DECADE FLASH
//	
//	Each of fields always starts at sector boundary DECADE_INTEL_FLASH_SECTOR_SIZE (512 K)

//		---------------------------		0x0000000	
//		|						|
//		|  Safeboot				|
//		|						|
//		---------------------------		0x2080000
//		|						|
//		|  Calib Info -1		|
//		|						|
//		---------------------------		0x2100000
//		|						|
//		|  Fw info -1			|
//		|						|
//		---------------------------		0x2180000
//		|						|
//		|  Fw Binary image 0	|
//		|						|
//		---------------------------		0x4200000
//		|						|
//		|  Calib Info 0			|
//		|						|
//		---------------------------		0x4280000
//		|						|
//		|  Fw info 0			|
//		|						|
//		---------------------------		0x4300000
//		|						|
//		|  Fw Binary image 1	|
//		|						|
//		---------------------------		0x6380000
//		|						|
//		|  Calib Info 1			|
//		|						|
//		---------------------------		0x6400000
//		|						|
//		|  Fw info 1			|
//		|						|
//		---------------------------		0x6480000
//		|						|
//		|  Decade Footer		|
//		|						|
//		---------------------------		0x6500000
//		|						|
//		|  Unused (free space)	|
//		|						|
//		-------------------------		0x7F80000
//		|						|
//		|  Reserved				|
//		|						|
//		---------------------------		0x8000000
                                                         


#define DECADE_FLASH_SECTOR_SIZE			0x80000		// 128 k x 2 WORD x 2 flashes parallele

#define	DECADE_FLASH_SIZE					0x8000000	// Size of the Decade flash
#define	DECADE_FWIMAGESIZE					0x2080000	// Maximum size reserved Decade FPGA binary image

#define	DECADE_NUMBER_OF_IMAGES				3

#pragma pack (1)

typedef	union 
{
	CS_FIRMWARE_INFOS				FwInfoStruct;
	uInt8							u8Padding[DECADE_FLASH_SECTOR_SIZE];

}  DECADE_FWINFO_SECTOR;


typedef struct _DECADE_MISC_DATA
{
	uInt32					u32MemSizeKb;	// Limited the Memory size
	CS_FLASHFOOTER			BaseboardInfo;	// Base board Infos (S/N, HW version and options ...)
	CS_FLASHFOOTER			AddonInfo;		// Addon board Infos (S/N, HW version and options ...)
	uInt16					u16TrigOutEnable;	// Trig enable mode or trigout mode
	uInt16					ClockOutCfg;		// Clock out config (eClkOutMode)

} DECADE_MISC_DATA, *PDECADE_MISC_DATA;

// Each of fields starts at DECADE_INTEL_FLASH_SECTOR_SIZE (128 K) boundary
typedef struct _DECADE_FLS_IMAGE_STRUCT
{
	uInt8						Image [DECADE_FWIMAGESIZE];			// Flash Image binary
	uInt8						Calib [DECADE_FLASH_SECTOR_SIZE];	// Reserved/Calibration for future use
	DECADE_FWINFO_SECTOR		FwInfo;									// Last 128K in this structure

} DECADE_FLS_IMAGE_STRUCT;


// Each of fields starts at DECADE_INTEL_FLASH_SECTOR_SIZE (128 K) boundary
typedef struct
{
	DECADE_FLS_IMAGE_STRUCT		SafeBoot;
	DECADE_FLS_IMAGE_STRUCT		FlashImage0;
	DECADE_FLS_IMAGE_STRUCT		FlashImage1;

	DECADE_MISC_DATA			BoardData;

} DECADE_FLASH_LAYOUT;


#pragma pack ()

#endif