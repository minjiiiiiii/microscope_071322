#ifndef __SPLENDA_FLASH_H__
#define __SPLENDA_FLASH_H__

#include "CsSplendaCapsInfo.h"


#define SPLNDA_NUMBER_OF_FLASHIMAGES 1

//		-----------------------	  ---	-------------------------   ---------	
//		|				    |			|						|			|
//		|					|			|						|			|
//		|		IMAGE 1		|			|	Calib Info 1		|			|
//		|					|			|						|			|
//		|					|			|						|			|
//		|					|			|						|			|
//		|					|			|						|			|
//		|					|			-------------------------			|
//		|					|			|						|			|
//		|					|			|   Fw info 1			|			|
//		|					|			|						|			|
//		---------------------	 ---	-------------------------   -------	|
//		|					|			|						|
//		|	 Flash Footer	|			|   Flash Footer		|
//		|					|			|						|
//		---------------------	 ---	---------------------------	
//		|					|			|						|		
//		|	Trig Clk		|			|	Trig Clk			|		
//		|	 Out Cfg		|			|	 Out Cfg			|		
//		|					|			|						|	
//		---------------------	 ---	---------------------------	
//		|					|			|						|		
//		|	Reserved		|			|	Reserved			|		
//		|					|			|						|	
//		---------------------	 ---	---------------------------	
//		|					|			|						|		
//		|	Hidden Struct	|			|	Hidden Struct		|		
//		|	HW Limitations	|			|	HW Limitations		|		
//		|					|			|						|		
//		---------------------	 ---	---------------------------	

#define SPLNDA_FLASH_SIZE			        0x8000   // 32 KBytes Addon Splenda Flash Size
#define SPLNDA_INTEL_FLASH_SECTOR_SIZE		0x20000		// 128 k
#define SPLNDA_FLASH_INFO_ADDR              0 // ?(SPLNDA_FLASH_SIZE-SPLNDA_INTEL_FLASH_SECTOR_SIZE)    // Last page 

#define	SPLNDA_FLASH_CALIBINFO_SIZE			0x6000 // 24 KBytes

typedef	struct _SPLNDA_FLASH_FIRMWARE_INFOS
{
	uInt32	u32FwOptions;							// The FPGA options
	uInt32	u32ChecksumSignature;					// Should be equal to CSMV_FWCHECKSUM_VALID

} SPLNDA_FLASH_FIRMWARE_INFOS;

typedef struct _SPLNDA_FLASH_IMAGE_STRUCT
{
	uInt8						Calib [SPLNDA_FLASH_CALIBINFO_SIZE];	// Calibration 
	SPLNDA_FLASH_FIRMWARE_INFOS	FwInfo;	
} SPLNDA_FLASH_IMAGE_STRUCT;



typedef struct _SPLENDA_FOOTER
{
	CS_FLASHFOOTER	Ft;
	uInt16			u16TrigOutEnabled;
	uInt16			u16ClkOut;

} SPLENDA_FLASHFOOTER, *PSPLENDA_FLASHFOOTER;

typedef struct _SPLNDA_FLASH_LAYOUT // i don't need to use unions here as there's no sector size
{
	SPLNDA_FLASH_IMAGE_STRUCT		FlashImage;		// check if we need a Boot backup image
	SPLENDA_FLASHFOOTER				Footer;

} SPLNDA_FLASH_LAYOUT;

#endif // __SPLENDA_FLASH_H__

