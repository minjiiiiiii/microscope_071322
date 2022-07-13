#ifndef __DEERE_FLASH_H__
#define __DEERE_FLASH_H__

typedef struct _DEERE_FLASH_CHAN_CAL_ENTRY
{
	uInt16 u16Offset;
	uInt16 u16Position;
	uInt16 u16Gain;
	uInt16 u16PositionGain;
}DEERE_FLASH_CHAN_CAL_ENTRY;

typedef struct _DEERE_FLASH_EXT_TRIG_CAL_ENTRY
{
	uInt16 u16Offset;
	uInt16 u16Gain;
}DEERE_FLASH_EXT_TRIG_CAL_ENTRY;


//		---------------------------		0x000000	
//		|						|
//		|  Fw Binary image 1	|
//		|						|
//		---------------------------		0x320000
//		|						|
//		|  Calib Info 1			|
//		|						|
//		---------------------------		0x340000
//		|						|
//		|  Fw info 1			|
//		|						|
//		---------------------------		0x360000
//		|						|
//		|  Fw Binary image 2	|
//		|						|
//		---------------------------		0x680000
//		|						|
//		|  Calib Info 2			|
//		|						|
//		---------------------------		0x6A0000
//		|						|
//		|  Fw info 2			|
//		|						|
//		---------------------------		0x6C0000
//		|						|
//		|  Fw Binary image 3	|
//		|						|
//		---------------------------		0x9E0000
//		|						|
//		|  Calib Info 3			|
//		|						|
//		---------------------------		0xA00000
//		|						|
//		|  Fw info 3			|
//		|						|
//		---------------------------		0xA20000
//		|						|
//		|						|
//		|	EMPTY / UNUSED		|
//		|						|
//		|						|
//		|						|
//		---------------------------		0xFC0000	
//		|						|
//		|  Addon Footer			|
//		|						|
//		---------------------------		0x1000000
                                                         


#define DEERE_INTEL_FLASH_SECTOR_SIZE	0x20000		// 128 k

#define	DEERE_FLASH_SIZE				0x1000000	// Size of the JohnDeere flash
#define	DEERE_FLASH_FWIMAGESIZE			0x320000	// Maximum size reserved for JohnDeere FPGA binary image
#define	DEERE_NUMBER_OF_FLASHIMAGES		3			// Included the image 0 which is the boot backup image


#ifdef _WIN32
#pragma pack (1)
#endif



typedef	struct 
{
	uInt32	u32FwOptions;							// The FPGA options
	uInt32	u32ChecksumSignature;					// Should be equal to CSMV_FWCHECKSUM_VALID
	uInt32	u32FwVersion;							// The FPGA version

} DEERE_FLASH_FIRMWARE_INFOS;


typedef	union 
{
	CS_FIRMWARE_INFOS				FwInfoStruct;
	uInt8							u8Padding[DEERE_INTEL_FLASH_SECTOR_SIZE];

}  DEERE_FLASH_FWINFO_SECTOR;


#define	DEERE_FLASH_CALIBINFO_SIZE		DEERE_INTEL_FLASH_SECTOR_SIZE


// Each of fields starts at DEERE_INTEL_FLASH_SECTOR_SIZE (128 K) boundary
typedef struct _DEERE_FLASH_IMAGE_STRUCT
{
	uInt8							Image [DEERE_FLASH_FWIMAGESIZE];		// Flash Image binary
	uInt8							Calib [DEERE_FLASH_CALIBINFO_SIZE];		// Calibration 
	DEERE_FLASH_FWINFO_SECTOR		FwInfo;									// Last 128K in this structure

} DEERE_FLASH_IMAGE_STRUCT;

typedef struct _DEERE_FLASHFOOTER
{
	CS_FLASHFOOTER		Footer;	
	uInt16				u16TrigOutEnabled;
	uInt16				u16ClkOut;
	CS_AUX_IN_STRUCT	AuxInCfg;
	uInt16				AuxOutCfg;
} DEERE_FLASHFOOTER, *PDEERE_FLASHFOOTER;

typedef union	_DEERE_FLASHFOOTER_ALIGNED 
{
	DEERE_FLASHFOOTER ftData;
	uInt8			  u8Padding[2*DEERE_INTEL_FLASH_SECTOR_SIZE];
} DEERE_FLASHFOOTER_ALIGNED, *PDEERE_FLASHFOOTER_ALIGNED;

typedef struct	_DEERE_EXTRAINFO
{
	uInt32			u32MemSizeKb;
	uInt32			u32HwOptions0;				// Hw options presume "Base"
} DEERE_EXTRAINFO, *PDEERE_EXTRAINFO;



#define		DEERE_UNUSED_SPACE_SIZE			(DEERE_FLASH_SIZE-3*sizeof(DEERE_FLASH_IMAGE_STRUCT)-sizeof(DEERE_FLASHFOOTER_ALIGNED))

// Each of fields starts at DEERE_INTEL_FLASH_SECTOR_SIZE (128 K) boundary
typedef struct
{
	DEERE_FLASH_IMAGE_STRUCT		FlashImage1;
	DEERE_FLASH_IMAGE_STRUCT		FlashImage2;
	DEERE_FLASH_IMAGE_STRUCT		FlashImage3;

	char							EmptySpace[DEERE_UNUSED_SPACE_SIZE];

	DEERE_FLASHFOOTER_ALIGNED		Footer;

} DEERE_FLASH_LAYOUT;



#ifdef _WIN32
#pragma pack ()
#endif

#endif