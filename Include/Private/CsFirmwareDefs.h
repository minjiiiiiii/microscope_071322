#ifndef _CS_FIRMWARE_DEFS_H_
#define _CS_FIRMWARE_DEFS_H_

#include "CsTypes.h"
#include "CsDrvConst.h"

#ifdef _WIN32
#pragma once
#endif

// these following 4 defines are deprecated. User CsGetParams with CS_FLASHINFO instead
const int FLASH_IMAGE_FILE_SIZE = 1048576;
const int FLASH_IMAGE_COUNT  = 3;
const int FLASH_OPTIONAL_IMAGE_COUNT = 2;
const int BASEBOARD_HEADER_OFFSET = FLASH_IMAGE_FILE_SIZE * FLASH_IMAGE_COUNT; // 3 Megabytes from the start of the flash

#define DEFAULT_KEY_FILENAME _T("CsExpertLicense.dat")
#define COMPANY_NAME _T("Gage Applied")
#define NEW_DAT_FILE_SIGNATURE 0x81614121
#define ADDON_FIRMWARE_UPDATE_REG_KEY _T("SOFTWARE\\Gage\\FirmwareUpdates\\AddOn")
#define BASEBOARD_FIRMWARE_UPDATE_REG_KEY _T("SOFTWARE\\Gage\\FirmwareUpdates\\BaseBoard")

// Fwl file version.
// Change this number when modifiy the FWL_FILE_HEADER structure
// Major, Minor and Revision one byte each
// Ex 0x01030C is version 1.03.12
#define	OLD_FWLFILE_VERSION				0x010201
#define	PREVIOUS_FWLFILE_VERSION		OLD_FWLFILE_VERSION
#define	FWLFILE_VERSION					0x010202
#define FWL_DESCRIPTION_LENGTH			128
#define	FWL_FWCHECKSUM_VALID			0x45474147		// uInt32 value of "GAGE"

#define FPGA_IMAGE_ONE					1
#define FPGA_IMAGE_TWO					2

#define FPGA_IMAGE_COUNT				2

#pragma pack (8)

typedef struct _FPGA_HEADER_INFO
{
	uInt32	u32ImageOffset;		// Offset of the image from beginning of file
	uInt32	u32ImageSize;		// Size of image
	uInt32	u32Version;			// Version of FPGA image
	uInt32	u32Option;			// Option number of FPGA image
	uInt32  u32Destination;		// Addon or baseboard, currently unused
	TCHAR	strType[30];		// Type of optional image;
	TCHAR	strFileName[30];	// Filename of optional image;
} FPGA_HEADER_INFO, *PFPGA_HEADER_INFO;


typedef struct _FWL_FILE_HEADER
{
	uInt32	u32Size;									// Size of this structure
	TCHAR	szDescription[FWL_DESCRIPTION_LENGTH];		// File description
	uInt32  u32BoardType;								// Board type that the images are for
	uInt32	u32Version;									// File Version
	uInt32	u32Checksum;								// Checksum for file corruption error
	uInt32	u32Count;									// Number of rbf entries following this header
	uInt32	u32ProductId;								// Unique indentifire for each product
} FWL_FILE_HEADER, *PFWL_FILE_HEADER;

typedef struct _BOARD_DATA_
{
	uInt32	dwSerialNumber;
	uInt32	dwPermissions;
} BOARD_DATA, *PBOARD_DATA;

#pragma pack ()
#endif // _CS_FIRMWARE_DEFS_H_