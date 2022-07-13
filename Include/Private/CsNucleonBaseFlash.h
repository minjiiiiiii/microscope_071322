#ifndef __NUCLEONBASE_FLASH_H__
#define __NUCLEONBASE_FLASH_H__


//		---------------------------		0x000000	
//		|						|
//		|  Boot image			|
//		|						|
//		---------------------------		0x5E00000
//		|						|
//		|  Calib Info 0			|
//		|						|
//		---------------------------		0x600000
//		|						|
//		|  Fw info 0			|
//		|						|
//		---------------------------		0x620000
//		|						|
//		|  Fw Binary image 1	|
//		|						|
//		---------------------------		0xC00000
//		|						|
//		|  Calib Info 1			|
//		|						|
//		---------------------------		0xC20000
//		|						|
//		|  Fw info 1			|
//		|						|
//		---------------------------		0xC40000
//		|						|
//		|  Fw Binary image 2	|
//		|						|
//		---------------------------		0x1220000
//		|						|
//		|  Calib Info 2			|
//		|						|
//		---------------------------		0x1240000
//		|						|
//		|  Fw info 2			|
//		|						|
//		---------------------------		0x1260000
//		|						|
//		|  Fw Binary image 3	|
//		|						|
//		---------------------------		0x1840000
//		|						|
//		|  Calib Info 3			|
//		|						|
//		---------------------------		0x1860000
//		|						|
//		|  Fw info 3			|
//		|						|
//		---------------------------		0x1880000
//		|	Misc board Data		|
//		|						|
//		|						|
//		---------------------------		0x18A0000
//		|	EMPTY / UNUSED		|
//		|						|
//		|						|
//		|						|
//		|						|
//		|  		|
//		|						|
//		---------------------------		0x2000000
                                                         

#define	NUCLEON_FLASH_SECTOR_SIZE		0x20000
#define NUCLEON_FLASH_SECTOR_SIZE0		0x8000		// The sector size for the area between 0x2000000-0x2000 and 0x2000000
#define NUCLEON_FLASH_SECTOR_SIZE1		0x20000		// The sector size  the area above 0x20000

#define NUCLEON_SECTORSIZE_CHANGED_FRONTIER		0x20000
#define	NUCLEON_FLASH_SIZE				0x2000000	// Size of the JohnDeere flash
#define	NUCLEON_FLASH_FWIMAGESIZE		0x5E0000	// Maximum size reserved for JohnDeere FPGA binary image


#define	NUCLEON_FLASH_IMAGETRUCT_SIZE		0x5E0000
#define	NUCLEON_NUMBER_OF_FLASHIMAGES		4			// Included the image 0 which is the boot backup image


#ifdef _WIN32
#pragma pack (1)
#endif



typedef	struct 
{
	uInt32	u32FwVersion;							// The FPGA version
	uInt32	u32FwOptions;							// The FPGA options
	uInt32	u32ChecksumSignature;					// Should be equal to CSMV_FWCHECKSUM_VALID

} NUCLEON_FLASH_FIRMWARE_INFOS;


typedef	union 
{
	CS_FIRMWARE_INFOS				FwInfoStruct;
	uInt8							u8Padding[NUCLEON_FLASH_SECTOR_SIZE];

}  NUCLEON_FLASH_FWINFO_SECTOR;


#define	NUCLEON_FLASH_CALIBINFO_SIZE		NUCLEON_FLASH_SECTOR_SIZE


// Each of fields starts at NUCLEON_FLASH_SECTOR_SIZE (128 K) boundary
typedef struct _NUCLEON_FLASH_IMAGE_STRUCT
{
	uInt8							Image [NUCLEON_FLASH_FWIMAGESIZE];		// Flash Image binary
	uInt8							Calib [NUCLEON_FLASH_CALIBINFO_SIZE];	// Calibration 
	NUCLEON_FLASH_FWINFO_SECTOR		FwInfo;									// Last 128K in this structure

} NUCLEON_FLASH_IMAGE_STRUCT;


typedef struct _NUCLEON_FLASH_MISC_DATA
{
	CS_FLASHFOOTER		Footer;
	uInt32				u32MemSizeKb;

	uInt16				u16TrigOutEnabled;
	uInt16				u16ClkOut;
	CS_AUX_IN_STRUCT	AuxInCfg;
	uInt16				AuxOutCfg;
} NUCLEON_FLASH_MISC_DATA, *PNUCLEON_FLASH_MISC_DATA;

typedef union	_NUCLEON_FLASH_MISC_DATA_SECT 
{
	NUCLEON_FLASH_MISC_DATA	ftData;
	uInt8					u8Padding[NUCLEON_FLASH_SECTOR_SIZE];
} NUCLEON_FLASH_MISC_DATA_SECT, *PNUCLEON_FLASH_MISC_DATA_SECT;


// Each of fields starts at NUCLEON_FLASH_SECTOR_SIZE (128 K) boundary
typedef struct
{
	NUCLEON_FLASH_IMAGE_STRUCT		BootImage;				// Reserved boot image
	NUCLEON_FLASH_IMAGE_STRUCT		FlashImage1;			// Normal
	NUCLEON_FLASH_IMAGE_STRUCT		FlashImage2;			// Expert 1
	NUCLEON_FLASH_IMAGE_STRUCT		FlashImage3;			// Expert 2
	NUCLEON_FLASH_MISC_DATA			BoardData;				// Misc board related data (Expert permission, Aux In/Out ...)

} NUCLEON_FLASH_LAYOUT;


// Nucleon registers

// Firmware versions and options
#define	CSNUCLEON_OPT_RD_CMD			0x30
#define CSNUCLEON_SWR_RD_CMD			0x34
#define CSNUCLEON_HWR_RD_CMD			0x38


#ifdef _WIN32
#pragma pack ()
#endif

#endif
