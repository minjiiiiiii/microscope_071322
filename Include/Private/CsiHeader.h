#ifndef __CsiHeader_h__
#define __CsiHeader_h__

#include "CsTypes.h"

#ifdef __linux__
  #define CSI_FILE_PATH "/usr/local/share/Gage"
#endif

// extern int GetCSIVersion(char*, char*, int);
// extern char* GetCSIVersion(char*);

#define	CSI_FWCHECKSUM_VALID			0x45474147		// uInt32 value of "GAGE"


// Csi Entries Target
#define	CSI_STANDALONE_BOARD			0x80000000

#define	CSI_BASEBOARD_TARGET			0
#define	CSI_BBCOMBINE_TARGET			0

#define	CSI_CS14200_TARGET				(CSI_BBCOMBINE_TARGET+1)
#define	CSI_CS14105_TARGET				(CSI_BBCOMBINE_TARGET+2)
#define	CSI_CS12400_TARGET				(CSI_BBCOMBINE_TARGET+3)
#define	CSI_CS14200x_TARGET				(CSI_BBCOMBINE_TARGET+4)

#define	CSI_BBSPIDER_TARGET				10
#define	CSI_CS8xxx_TARGET				(CSI_BBSPIDER_TARGET+1)

#define	CSI_BBRABBIT_TARGET				20
#define	CSI_CSXYG8_TARGET				(CSI_BBRABBIT_TARGET+1)

#define	CSI_BBCOMBINEFAT_TARGET			30

#define	CSI_BBSPIDERV12_TARGET			40
#define	CSI_CS8xxxV12_TARGET			(CSI_BBSPIDERV12_TARGET+1)
#define	CSI_CSZAP_TARGET    			(CSI_CS8xxxV12_TARGET+1)

#define	CSI_BBSPIDER_LP_TARGET			50
#define	CSI_CS8xxxLP_TARGET				(CSI_BBSPIDER_LP_TARGET+1)

#define CSI_BBSPLENDA_TARGET			60
#define CSI_CSSPLENDA_TARGET			(CSI_BBSPLENDA_TARGET+1)

#define	CSI_BBBUNNY_TARGET				(70 | CSI_STANDALONE_BOARD)
#define	CSI_HUSS_TARGET 				(CSI_BBBUNNY_TARGET)

#define	CSI_BBBRAINIAC_TARGET			(80 | CSI_STANDALONE_BOARD)
#define	CSI_BRAIN_TARGET 				(CSI_BBBRAINIAC_TARGET)

#define	CSI_BBPITCH_TARGET				(90 | CSI_STANDALONE_BOARD)
#define	CSI_PITCH_TARGET 				(CSI_BBPITCH_TARGET)

#define	CSI_BBPITCH_M_TARGET			(100 | CSI_STANDALONE_BOARD)
#define	CSI_PITCH_M_TARGET				(CSI_BBPITCH_M_TARGET)

#define	CSI_BBFASTBL_TARGET				(120 | CSI_STANDALONE_BOARD)
#define	CSI_FASTBL_TARGET 				(CSI_BBFASTBL_TARGET)
#define	CSI_FASTBL_NM_TARGET 			(CSI_BBFASTBL_TARGET + 1)

#define	CSI_BBFASTBL4G_TARGET			(140 | CSI_STANDALONE_BOARD)
#define	CSI_FASTBL4G_TARGET 			(CSI_BBFASTBL4G_TARGET)
#define	CSI_FASTBL4G_NM_TARGET 			(CSI_BBFASTBL4G_TARGET + 1)

#define	CSI_BBFASTBL3G_TARGET			(130 | CSI_STANDALONE_BOARD)
#define	CSI_FASTBL3G_TARGET				(CSI_BBFASTBL3G_TARGET)
#define	CSI_FASTBL3G_NM_TARGET 			(CSI_BBFASTBL3G_TARGET + 1)

#define	CSI_BBDEERE_TARGET				(150 | CSI_STANDALONE_BOARD)
#define	CSI_DEERE_TARGET 				(CSI_BBDEERE_TARGET)

#define	CSI_USB_BB_TARGET				170
#define	CSI_USB_114_TARGET				(CSI_USB_BB_TARGET+1)
#define	CSI_USB_214_TARGET				(CSI_USB_114_TARGET+1)
#define	CSI_USB_112_TARGET				(CSI_USB_214_TARGET+1)
#define	CSI_USB_108_TARGET				(CSI_USB_112_TARGET+1)

#define	CSI_BBSPIDER_PCIEx_TARGET		180
#define	CSI_CS8xxxPciEx_TARGET			(CSI_BBSPIDER_PCIEx_TARGET+1)

#define CSI_BBSPLENDA_PCIEx_TARGET		190
#define CSI_BBOSCAR_PCIEx_TARGET		200
#define CSI_SPLENDA_PCIEx_TARGET		(CSI_BBSPLENDA_PCIEx_TARGET+1)

#define CSI_BBZAP_PCIEx_TARGET			210
#define CSI_ZAP_PCIEx_TARGET			(CSI_BBZAP_PCIEx_TARGET+1)

#define CSI_BBRABBIT_PCIEx_TARGET		220
#define CSI_CSXYG8_PCIEx_TARGET			(CSI_BBRABBIT_PCIEx_TARGET+1)

#define CSI_BBCOBRAMAX_PCIEx_TARGET		230
#define CSI_CSCDG8_PCIEx_TARGET			(CSI_BBCOBRAMAX_PCIEx_TARGET+1)

#define CSI_BBDECADE12_TARGET			(240 |CSI_STANDALONE_BOARD)
#define CSI_CSDC12_TARGET				(CSI_BBDECADE12_TARGET+1)

#define CSI_BBHEXAGON_TARGET			(250 |CSI_STANDALONE_BOARD)
#define CSI_CSDC16_TARGET				(CSI_BBHEXAGON_TARGET+1)

#define CSI_BBHEXAGON_PXI_TARGET		(260 |CSI_STANDALONE_BOARD)
#define CSI_CSHEX_PXI_TARGET			(CSI_BBHEXAGON_PXI_TARGET+1)

#define CSI_BBHEXAGON_A3_TARGET			(270 |CSI_STANDALONE_BOARD)
#define CSI_CSDC16_A3_TARGET			(CSI_BBHEXAGON_TARGET+1)

#define CSI_BBHEXAGON_A3_PXI_TARGET		(280 |CSI_STANDALONE_BOARD)
#define CSI_CSHEX_PXI_A3_TARGET			(CSI_BBHEXAGON_PXI_TARGET+1)

// Csi file version.
// Change this number when modifiy the MVCSI_ENTRY or CSI_FILE_HEADER structure
// Major, Minor and Revision one byte each
// Ex 0x01030C is version 1.03.12
#define	LEGACY_CSIFILE_VERSION			0x010000
#define	OLD_CSIFILE_VERSION				0x020001
#define	PREVIOUS_CSIFILE_VERSION		OLD_CSIFILE_VERSION
#define	CSIFILE_VERSION					0x020002
#define CSI_DESCRIPTION_LENGTH			128

#pragma pack (1)


// Csi header for lecacy cards only (Cs8500, Cs12xx, Cs14xx... )
typedef struct _LEGACYCSI_FILE_HEADER
{
	char	Description[128];
	uInt32	Version;
	uInt32	Checksum;
	uInt32	NumberOfEntry;
	
} LEGACYCSI_FILE_HEADER, *PLEGACYCSI_FILE_HEADER;


typedef struct _CSI_ENTRY
{
	char	strFileName[32];	// Original filename FPGA image
	uInt32	u32Target;			// Target Base board or Addon Board;
	uInt32	u32FwVersion;		// Version of FPGA image
	uInt32	u32FwOptions;		// Firmware options
	uInt32	u32HwOptions;		// Hardware options
	uInt32	u32ImageOffset;		// Offset of the image from beginning of file
	uInt32	u32ImageSize;		// Size of image
} CSI_ENTRY, *PCSI_ENTRY;



typedef struct _CSI_FILE_HEADER
{
	uInt32	u32Size;				// Size of this structure
	char	szDescription[CSI_DESCRIPTION_LENGTH];		// File description
	uInt32	u32Version;				// File Version
	uInt32	u32Checksum;			// TBD
									// Checksum for file corruption error
	uInt32	u32NumberOfEntry;		// Number of Csi entries following this header
} CSI_FILE_HEADER, *PCSI_FILE_HEADER;

#pragma pack ()


typedef struct _ID_BOARDTYPE
{
	char	szName[32];
	uInt32	u32BoardType;
	uInt32	u32Id;
	char	szCsiFileName[24];
} ID_BOARDTYPE, *PID_BOARDTYPE;



#endif  //__CsiHeader_h__

