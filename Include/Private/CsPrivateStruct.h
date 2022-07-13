/********************************************************************************************************************
 *   CsPrivateStruct.h
 *   Common private structures for CompuScope driver
 *
 *
 *   Version 1.0
 ********************************************************************************************************************/
#ifndef _CS_PRIVATE_STRUCT_H_
#define _CS_PRIVATE_STRUCT_H_

#include "CsTypes.h"
#include "CsStruct.h"

#ifdef _WIN32
#pragma once
#endif

#define MAX_IMAGE_COUNT 3

#define CS_RM_INACTIVE 0x0
#define CS_RM_ACTIVE32 0x1
#define CS_RM_ACTIVE64 0x2
#define CS_RM_ACTIVE_REMOTE 0x4  // System is a remote system being used by someone other than us

#ifdef CS_WIN64
	#define CS_RM_ACTIVE CS_RM_ACTIVE64
#else
	#define CS_RM_ACTIVE CS_RM_ACTIVE32
#endif

#define CS_FIRMWARE_OPTION_TYPE 1
#define CS_HARDWARE_OPTION_TYPE 2

#define FS_BASE_HANDLE		0x00010000
#define RM_BASE_HANDLE		0x00020000
#define RM_DEMO_HANDLE		0x00040000
#define RM_REMOTE_HANDLE	0x00080000


// Aux IO Dialog types for CompuScope Manager
#define AUX_IO_SIMPLE_DLG	0x0001	// simple dialog for Splenda and Spider boards
#define AUX_IO_COBRA_DLG	0x0002	// slightly more complex for Cobra and Cobra Max
#define AUX_IO_JD_DLG		0x0003	// still more complex for John Deere boards


// Macro for naming events in debug mode so they can be debugged with Soft Ice.
#ifdef DEBUG
#define HANDLE_NAME(x) _T("__Cs" x)
#else
#define HANDLE_NAME(x) NULL
#endif

//! EEPROM Read operation
#define CS_READ_EEPROM			20

//! EEPROM Write operation
#define CS_WRITE_EEPROM			21

//! NVRAM Read operation
#define CS_READ_NVRAM			22

//! NVRAM Write operation
#define CS_WRITE_NVRAM			23

//! Read the calibration table
#define	CS_READ_CALIB_TABLE		24

//! /Write the calibration table
#define CS_WRITE_CALIB_TABLE	25

//! Write Delay line
#define CS_WRITE_DELAY_LINE		26

//! Write Calibration DAC
#define CS_SEND_DAC				27

//! Flashing the indication LED
#define CS_FLASHING_LED			28

//! FLASH Read operation
#define CS_READ_FLASH			29

//! FLASH Write operation
#define CS_WRITE_FLASH			30

//! Self Test Mode
#define CS_SELF_TEST_MODE		31

//! Delay Line Test
#define CS_DELAY_LINE_MODE		32

//! Send calibration table to driver
#define	CS_UPDATE_CALIB_TABLE   33

//! Set NIOS in debug mode. NIOS will wait for extermal load
#define CS_NIOS_DEBUG			34

// Calibration :  Request the driver to retrim calibrator
#define CS_TRIM_CALIBRATOR		35

// Calibration :  Request the driver to save calibration table to eeprom
#define CS_SAVE_CALIBTABLE_TO_EEPROM	36

// Calibration :  Request the driver to read calibration table from eeprom
#define CS_READ_CALIBTABLE_FROM_EEPROM		CS_SAVE_CALIBTABLE_TO_EEPROM

// Reset the timestamp ( from CsDrvDo( ACTION_TIMESTAMP_RESET ) )
#define CS_TIMESTAMP_RESET			37

// Send down the new value of trigger address offset
#define CS_TRIGADDR_OFFSET_ADJUST	38

// Send down the new value of trigger level offset
#define	CS_TRIGLEVEL_ADJUST			39

// Request Firmware information
#define	CS_READ_VER_INFO			40

// Read data from BB directly
#define CS_MEM_READ_THRU			41

// Write data from BB directly
#define CS_MEM_WRITE_THRU			42

// Send down the new value of trigger gain
#define	CS_TRIGGAIN_ADJUST			43

//! CsMarvin board addon reset
#define CS_ADDON_RESET				45

//! Trigger enable mode
#define CS_TRIG_ENABLE				46

//! Calib Mode configuration
#define CS_CALIBMODE_CONFIG			47

//! System Info Extended
//! Contains Base board and Addon board firmware options
#define	CS_SYSTEMINFO_EX			48

//! Internal Board caps
//! Returns board capabilities to the user level driver based on hw configuration
#define	CS_DRV_BOARD_CAPS			49

//! Clock out mode
#define CS_CLOCK_OUT				50

//! Peev Adaptor Configuration
#define	CS_PEEVADAPTOR_CONFIG		51

//! Flash layout info
#define	CS_FLASHINFO				52

//! Debug Master/Slave calibration pulse
#define	CS_DEBUG_MS_PULSE			53

//! Debug Master/Slave calibration pulse
#define	CS_DEBUG_MS_OFFSET			54

//! Debug Ext Trigger calibration pulse
#define	CS_DEBUG_EXTTRIGCALIB		55

//! Max Segment padding
#define	CS_MAX_SEGMENT_PADDING		56

//! Trim Front end caps (Spider v1.2 )
#define	CS_SPDR12_TRIM_TCAPS		57

//! Use Dac Calibtable from eeprom
#define	CS_USE_DACCALIBTABLE			58

//! Default value of Use Dac Calibtable. This value is stored in eeprom
#define	CS_DEFAULTUSE_DACCALIBTABLE			59

//! Read the current value of the DAC or ADC (not all cards has this feature)
#define	CS_READ_DAC					60

//! Reset the ADC (not all cards has this feature)
#define	CS_RESET_ADC				61

//! Get ADCs alignment (not all cards has this feature)
#define	CS_ADC_ALIGN				62

//! Debug Prf
#define	CS_DEBUG_PRF				63

//! Calibration Mode Settings
#define CS_SEND_CALIB_MODE			64

//! Calibration DC 
#define CS_SEND_CALIB_DC			65

//! Read Calibration A2D
#define CS_READ_CALIB_A2D			66

//! Perform Coincidence capture
#define	CS_DO_COIN       			67

//! Perform Coincidence data read
#define	CS_READ_COIN       			68

//! Save Trigger-out and Clock-out modes to the on board flash
#define CS_SAVE_OUT_CFG				69

//! Trig out mode
#define CS_TRIG_OUT				    70

//! Splenda Gain Tartget factor
#define CS_GAINTARGET_FACTOR		71

//! Splenda Front Port Reistance
#define CS_FRONTPORT_RESISTANCE		72

//! JohnDeere diagnostic test of ADC data alignment
#define	CS_CHECK_ADC_DATA_ALIGN		73

//! Send Nios command
#define	CS_SEND_NIOS_CMD			74

//! Auxillary input config
#define CS_AUX_IN				    75

//! Auxillary output config
#define CS_AUX_OUT				    76

//! Read PCIe Link info
#define CS_READ_PCIeLINK_INFO	    77

//! Read Gage register
#define	CS_READ_GAGE_REGISTER		78

//! Reset the histogram counters
#define	CS_HISTOGRAM_RESET			79

//! Write Gage register
#define	CS_WRITE_GAGE_REGISTER		80

//! Query for the current boot location (-1=Safe boot, 0=Reg, 1=Expert1, 2=Expert2)
#define	CS_CURRENT_BOOT_LOCATION	81

//! Get/Set the next boot location (0=Reg, 1=Expert1, 2=Expert2)
#define	CS_NEXT_BOOT_LOCATION		82

//! Get the current firmware version of Baseboard and Addon board
#define	CS_CURRENT_FW_VERSION		83

//! Query for the flash sector size
#define	CS_FLASH_SECTOR_SIZE	84

//!Read PCI register
#define CS_READ_PCI_REGISTER	85

//!Write PCI register
#define CS_WRITE_PCI_REGISTER	86

//!For Debug:  Flash operation READ Value
#define CS_FLASH_OP_READ_VAL	87

//!For Debug:  Flash operation WRITE Value
#define CS_FLASH_OP_WRITE_VAL	88

//!For Debug: Write a buffer to flash
#define CS_FLASH_PROG_BUFFER	89



//   CAPS_ID   used in CsGetSystemCaps() to identify the
//   dynamic configuration requested
//
//
//	CAPS_ID  =   MainCapsId | SubCapsId
//
//  -------------------------------------------------
//  |	MainCapsId		 |		0000				|
//  -------------------------------------------------
//  31                15  14                       0
//
//  ------------------------------------------------
//  |   0000		     |      SubCapsId	       |
//  ------------------------------------------------
//  31                15  14                       0

//  Depending on CapsID, SubCapsId has different meaning
//  When call CsDrvGetSyatemCaps(),
//  CapsID and SunCapsID should always be ORed together
//
#define	CAPS_ID_MASK		0xFFFF0000
#define SUBCAPS_ID_MASK     0x0000FFFF

//  Value used in CS_SELF_TEST_MODE
#define	CSST_DISABLE				0
#define	CSST_CAPTURE_DATA			1
#define	CSST_BIST					2
#define	CSST_COUNTER_DATA			3
#define	CSST_MISC					4

#define CSMV_111_MHz_NIOS_CLK   0x40000000


typedef enum
{
	ecmCalModeNormal = 0,
	ecmCalModeDc  = ecmCalModeNormal + 1,
	ecmCalModeAc = ecmCalModeDc + 1,
	ecmCalModePci = ecmCalModeAc + 1,
	ecmCalModeMs = ecmCalModePci + 1,
	ecmCalModeExtTrig = ecmCalModeMs + 1,
	ecmCalModeExtTrigChan = ecmCalModeExtTrig + 1,
	ecmCalModeAdc = ecmCalModeExtTrigChan + 1,
	ecmCalModeTAO = ecmCalModeAdc + 1,
	ecmCalModeDual = ecmCalModeTAO + 1,
}eCalMode;


#ifdef _WIN32
#pragma pack (8)
#endif

//!
//! \defgroup PRIVATE_STRUCTURES
//! \{
//!

//! \struct _CSSYSTEMCAPS
//! \brief Structure to represent the static information for each system.
//! The fields in this structure cannot be modified.
typedef struct _CSSYSTEMCAPS
{
	uInt32	u32Size;   					//!< Total size, in bytes, of the structure.
	int64 	i64MemorySize;				//!< Memory size of the board(s).
	uInt32 	u32ModesAvailable;			//!< Which operating modes are available (ie. dual, single).
	cschar	lpBoardName[32];			//!< String representing the board name.
	uInt32	u32MultipleRecordAvailable;	//!< Is multiple record available.
	uInt32	u32ExternalClockAvailable;	//!< Is external clock available.
	uInt32	u32DiffInputAvailable;		//!< Is differential input available.
	int64	i64MaximumSampleRate;		//!< What's the max sample rate for this system.
	uInt32	u32Filter;					//!< The maximum bandwidth in KHz.
	int32	i32ImpedanceAvailable;		//!< Which impedances are available.
	int32	i32NumberOfTriggers;		//!< How many triggers are available in the system.
	int32	i32TriggerType;				//!< What type of trigger(s) is (are) available.
	int32	i32DigitalChannelsAvailable; //!< How many digital channels are available (Combine).
} CSSYSTEMCAPS, *PCSSYSTEMCAPS;


typedef struct _VALID_AUX_CONFIG
{
	char	Str[128];
	uInt32	u32Ctrl;
} VALID_AUX_CONFIG, *PVALID_AUX_CONFIG;


//! \struct _CSSYSTEMCAPS
//! \brief Structure to represent the static information for each system.
//! The fields in this structure cannot be modified.
typedef struct __CAPS_AUX_CONFIG
{
	uInt32	u32Size;   					//!< Total size, in bytes, of the structure.
	uInt8	u8DlgType;					//!< Aux Cfg Dlg type 1, 2, 3, or 4
	BOOL	bClockOut;					//!< Clock out supported
	BOOL	bTrigOut;					//!< Trig out supported
	BOOL	bTrigOut_IN;				//!< Trig out as Input supported
	BOOL	bAuxIN;						//!< Aux input supported
	BOOL	bAuxOUT;					//!< Aux out supported

} CS_CAPS_AUX_CONFIG, *PCS_CAPS_AUX_CONFIG;


/*************************************************************/

//! \struct _CS_CHANNEL_CAPS
//! \brief Structure used by HW Dlls and Kernel Drivers for channel BM transfer capability
//!
typedef struct  _CS_CHANNEL_CAPS
{
	uInt32		u32ChannelIndex;
	BOOLEAN		bBusMasterSupport;
} CS_CHANNEL_CAPS, *PCS_CHANNEL_CAPS;


typedef struct  _CS_DYNAMIC_SYSTEMCAPS
{
	uInt32				ChannelCount;
	CS_CHANNEL_CAPS		ChannelCap[1];
} CS_DYNAMIC_SYSTEMCAPS, *PCS_DYNAMIC_SYSTEMCAPS;


//! \struct _CSDATATRANSFERRESULT
//! \brief  structure used in CsGetAsyncTransferDataResult
//!
typedef struct _CSTRANSFERDATARESULT
{
	int32		i32Status;				//<! Status of data transfer
	int64		i64BytesTransfered;		//<! Bytes transfered to buffer
} CSTRANSFERDATARESULT, *PCSTRANSFERDATARESULT;
/*************************************************************/
//!
//! \}
//!

//----------------------------------------------------------

typedef struct
{
	char	signature[4];		//	NOT null terminated.
	uInt16	size;				//	Size of EEPROM in BITS.
	uInt16	board_type;			//	Encoded board types from GAGE_DRV.H.
	uInt16	version;			//	BCD, XX.XX.
	uInt16	memory_size;		//	Decimal (in kilobytes).
	uInt32	serial_number;		//	BCD, right-justified w/leading zeros.
	uInt32	options;			//	BIT encoded (see EEPROM_OPTIONS_XXXXXXXX).
	uInt16	a_ranges[7];		//	Default calibration values (all bits set if not supported).
	uInt16	a_offsets[7];		//	Default calibration values (all bits set if not supported).
	uInt16	b_ranges[7];		//	Default calibration values (all bits set if not supported).
	uInt16	b_offsets[7];		//	Default calibration values (all bits set if not supported).
	uInt16	power_on_value;		//	Time in 0.1 mSecs for power on delay.
	uInt16	hw_ati_version;		//	BCD, XX.XX.
	uInt16	hw_mem_version;		//	BCD, XX.XX.
	uInt16	hw_ets_version;		//	BCD, XX.XX.
	uInt16	ets_offset;			//	Decimal.
	uInt16	ets_correct;		//	Decimal.
	uInt16	ets_trigger_offset;	//	Decimal.
	uInt8	trig_level_off[2];	//	Decimal.
	uInt8	trig_level_scale[2];//	Decimal.
	uInt16	trig_addr_off[4];	//	uInt4, 16 values in 4 words (layed out linearly -> 0,1,2,3 4,5,6,7 8,9,10,11 12,13,14,15) or
								//	uInt8,  8 values in 4 words (layed out linearly -> 0,1 2,3 4,5 6,7).
	uInt16	a_ranges_50;		//	Default calibration values (all bits set if not supported).
	uInt16	a_offsets_50;		//	Default calibration values (all bits set if not supported).
	uInt16	b_ranges_50;		//	Default calibration values (all bits set if not supported).
	uInt16	b_offsets_50;		//	Default calibration values (all bits set if not supported).
	uInt16	padding[8];			//	Zero filled.

	uInt16	check_sum;			//	Check sum of entire EEPROM except these two bytes.  (location is dependant on EEPROM size).

#ifdef __linux__
}__attribute__ ((packed)) eepromtype1024;
#else

}eepromtype1024;
#endif

//----------------------------------------------------------

typedef struct
{

	char	signature[4];		//	NOT null terminated.
	uInt16	size;				//	Size of EEPROM in BITS.
	uInt16	board_type;			//	Encoded board types from GAGE_DRV.H.
	uInt16	version;			//	BCD, XX.XX.
	uInt16	memory_size;		//	Decimal (in kilobytes).
	uInt32	serial_number;		//	BCD, right-justified w/leading zeros.
	uInt32	options;			//	BIT encoded (see EEPROM_OPTIONS_XXXXXXXX).
	uInt16	a_ranges[7];		//	Default calibration values (all bits set if not supported).
	uInt16	a_offsets[7];		//	Default calibration values (all bits set if not supported).
	uInt16	b_ranges[7];		//	Default calibration values (all bits set if not supported).
	uInt16	b_offsets[7];		//	Default calibration values (all bits set if not supported).
	uInt16	power_on_value;		//	Time in 0.1 mSecs for power on delay.
	uInt16	hw_ati_version;		//	BCD, XX.XX.
	uInt16	hw_mem_version;		//	BCD, XX.XX.
	uInt16	hw_ets_version;		//	BCD, XX.XX.
	uInt16	ets_offset;			//	Decimal.
	uInt16	ets_correct;		//	Decimal.
	uInt16	ets_trigger_offset;	//	Decimal.
	uInt8	trig_level_off[2];	//	Decimal.
	uInt8	trig_level_scale[2];//	Decimal.
	uInt16	trig_addr_off[4];	//	uInt4, 16 values in 4 words (layed out linearly -> 0,1,2,3 4,5,6,7 8,9,10,11 12,13,14,15) or
								//	uInt8,  8 values in 4 words (layed out linearly -> 0,1 2,3 4,5 6,7).
	uInt16	a_ranges_50;		//	Default calibration values (all bits set if not supported).
	uInt16	a_offsets_50;		//	Default calibration values (all bits set if not supported).
	uInt16	b_ranges_50;		//	Default calibration values (all bits set if not supported).
	uInt16	b_offsets_50;		//	Default calibration values (all bits set if not supported).
	uInt16	padding[8];			//	Zero filled.
	uInt16	check_sum;			//	Check sum of entire EEPROM except these two bytes.  (location is NOT dependant on EEPROM size).
	uInt16	a_ranges_d[7];		//	Default calibration values (all bits set if not supported).
	uInt16	a_offsets_d[7];		//	Default calibration values (all bits set if not supported).
	uInt16	b_ranges_d[7];		//	Default calibration values (all bits set if not supported).
	uInt16	b_offsets_d[7];		//	Default calibration values (all bits set if not supported).
	uInt16	a_ranges_d_50;		//	Default calibration values (all bits set if not supported).
	uInt16	a_offsets_d_50;		//	Default calibration values (all bits set if not supported).
	uInt16	b_ranges_d_50;		//	Default calibration values (all bits set if not supported).
	uInt16	b_offsets_d_50;		//	Default calibration values (all bits set if not supported).

	uInt8	TAO_Dual[16];		//  Trigger addres offset for dual mode
	uInt8	TAO_Single[16];     //  Trigger addres offset for single mode
	uInt16  delay_lines[8];     //  Delay lines values to fine tune channel sync

	uInt16	padding_4096[40];	//	Zero filled.
	uInt8	eib_dac_area[192];	//	0x80 filled.

#ifdef __linux__
}__attribute__ ((packed)) eepromtype4096;

#else
}eepromtype4096;
#endif

//----------------------------------------------------------

typedef struct
{
	char	signature[4];		//	NOT null terminated.
	uInt16	size;				//	Size of EEPROM in BITS.
	uInt16	board_type;			//	Encoded board types from GAGE_DRV.H.
	uInt16	version;			//	BCD, XX.XX.
	uInt16	memory_size;		//	Decimal (in kilobytes).
	uInt32	serial_number;		//	BCD, right-justified w/leading zeros.
	uInt32	options;			//	BIT encoded (see EEPROM_OPTIONS_XXXXXXXX).
	uInt16	a_ranges[7];		//	Default calibration values (all bits set if not supported).
	uInt16	a_offsets[7];		//	Default calibration values (all bits set if not supported).
	uInt16	b_ranges[7];		//	Default calibration values (all bits set if not supported).
	uInt16	b_offsets[7];		//	Default calibration values (all bits set if not supported).
	uInt16	power_on_value;		//	Time in 0.1 mSecs for power on delay.
	uInt16	hw_ati_version;		//	BCD, XX.XX.
	uInt16	hw_mem_version;		//	BCD, XX.XX.
	uInt16	hw_ets_version;		//	BCD, XX.XX.
	uInt16	ets_offset;			//	Decimal.
	uInt16	ets_correct;		//	Decimal.
	uInt16	ets_trigger_offset;	//	Decimal.
	uInt8	trig_level_off[2];	//	Decimal.
	uInt8	trig_level_scale[2];//	Decimal.
	uInt16	trig_addr_off[4];	//	uInt4, 16 values in 4 words (layed out linearly -> 0,1,2,3 4,5,6,7 8,9,10,11 12,13,14,15) or
								//	uInt8,  8 values in 4 words (layed out linearly -> 0,1 2,3 4,5 6,7).
	uInt16	a_ranges_50;		//	Default calibration values (all bits set if not supported).
	uInt16	a_offsets_50;		//	Default calibration values (all bits set if not supported).
	uInt16	b_ranges_50;		//	Default calibration values (all bits set if not supported).
	uInt16	b_offsets_50;		//	Default calibration values (all bits set if not supported).
	uInt16	padding[8];			//	Zero filled.
	uInt16	check_sum;			//	Check sum of entire EEPROM except these two bytes.  (location is NOT dependant on EEPROM size).
	uInt16	a_ranges_d[7];		//	Default calibration values (all bits set if not supported).
	uInt16	a_offsets_d[7];		//	Default calibration values (all bits set if not supported).
	uInt16	b_ranges_d[7];		//	Default calibration values (all bits set if not supported).
	uInt16	b_offsets_d[7];		//	Default calibration values (all bits set if not supported).
	uInt16	a_ranges_d_50;		//	Default calibration values (all bits set if not supported).
	uInt16	a_offsets_d_50;		//	Default calibration values (all bits set if not supported).
	uInt16	b_ranges_d_50;		//	Default calibration values (all bits set if not supported).
	uInt16	b_offsets_d_50;		//	Default calibration values (all bits set if not supported).

	uInt8	TAO_Dual[16];		//  Trigger addres offset for dual mode
	uInt8	TAO_Single[16];     //  Trigger addres offset for single mode
	uInt16  delay_lines[8];     //  Delay lines values to fine tune channel sync

	uInt16	padding_4096[40];	//	Zero filled.
	uInt8	eib_dac_area[192];	//	0x80 filled.

	uInt16	padding_16384[468];	//	Zero filled.

	uInt16	cal_OneG_DC[96];
	uInt16	cal_ext_trig_addr[24];	//	0x80 filled.
	uInt16	cal_trig_level[24];	//	0x80 filled.
	uInt16	cal_trig_addr[12];	//	0x7F filled.

	uInt16 cal_ClkTable [24]; //	0x80 filled.
	uInt16 cal_DmuxTable [24];//	0x64 filled.
	uInt16 cal_GainTable [32];//	0x80 filled.
	uInt16 cal_PositionTable [32];//	0x80 filled.
	uInt16 cal_OffsetTable [32]; 	//	0x80 filled.
#ifdef __linux__
}__attribute__ ((packed)) eepromtype16384;
#else

}eepromtype16384;
#endif

//----------------------------------------------------------

typedef union  {

	eepromtype1024	_1024;
	eepromtype4096	_4096;
	eepromtype16384	_16384;

} CP500_EEPROMSTRUCT;

//! \struct _CP500_EEPROM_RW_STRUCT
//! \brief Structure used in CsDrvSet() and CsDrvGet() for Cs12xx, Cs14xx, Cs16xx and Cs82G
//!

typedef struct _CP500_EEPROM_RW_STRUCT
{
	uInt32	u32Size;				// Size of this structure
	uInt16	u16Bits;
	CP500_EEPROMSTRUCT	Eeprom;		// Eeprom structure shared by Cs12xx, Cs14xx, Cs16xx and Cs82G
} CP500_EEPROM_RW_STRUCT, *PCP500_EEPROM_RW_STRUCT;

typedef struct _CS_DELAYLINE_STRUCT
{
	uInt32	u32Size;			// Size of this structure
	uInt8	u8CardNumber;
	uInt16	u16aDelLines[24];	// should be the same size as NB_DELAY_LINES_TABLE * DELAY_LINES_TABLE_SIZE
								// (gage_low.h)
}CS_DELAYLINE_STRUCT, *PCS_DELAYLINE_STRUCT;


//
// Structure used in CsDrvSet() for setting DACs for calibration
//
typedef struct _CS_SENDDAC_STRUCT
{
	uInt32	u32Size;
	uInt8	u8CardNumber;
	uInt8	u8DacId;
	uInt8	u8DacAddress;
	uInt16	u16DacValue;
}CS_SENDDAC_STRUCT, *PCS_SENDDAC_STRUCT;


typedef struct _CS_UPDATE_CALIBTABLE_STRUCT
{
	uInt32	u32Size;
	uInt8	u8CardNumber;
	void	*CalibTable;
	uInt16	u16CalibTableSize;
} CS_UPDATE_CALIBTABLE_STRUCT, *PCS_UPDATE_CALIBTABLE_STRUCT;

//
// Structure used in CsDrvSet() for setting DACs for calibration
//
typedef struct _CS_CALIBMODE_STRUCT
{
	uInt32	u32Size;
	uInt8	u8CardNumber;
	uInt16	u16Channel;
	uInt8	u8CalMode;

} CS_CALIBMODE_STRUCT, *PCS_CALIBMODE_STRUCT;

typedef struct _CS_CALIBDC_STRUCT
{
	uInt32	u32Size;
	uInt8	u8CardNumber;
	uInt32	u32Impedance;
	uInt32	u32Range;
	int32	i32Level;
	int32	i32SetLevel;
} CS_CALIBDC_STRUCT, *PCS_CALIBDC_STRUCT;

typedef struct _CS_READCALIBA2D_STRUCT
{
	uInt32	u32Size;
	uInt8	u8CardNumber;
	int32	i32ExpectedVoltage;
	uInt8	u8Input;
	int32	i32ReadVoltage;
	int32	i32NoiseLevel;

} CS_READCALIBA2D_STRUCT, *PCS_READCALIBA2D_STRUCT;

#define NUM_DAC_VOUT				5
#define MAX_DAC_INDEX				8

// Errom content of Cs8500
// It has only calibration tables
typedef struct _CS8500_EEPROM_STRUCT
{
	int8		TrigLevelAdj[2*MAX_DAC_INDEX];
	int8		TrigAddrAdj[MAX_DAC_INDEX][8];
	uInt8		DACAdj[MAX_DAC_INDEX][NUM_DAC_VOUT];
} CS8500_EEPROM_STRUCT, *PCS8500_EEPROM_STRUCT;


//! \struct _CP500_EEPROM_RW_STRUCT
//! \brief Structure used in CsDrvSet() and CsDrvGet() for Cs8500
//!
typedef struct _CS8500_EEPROM_RW_STRUCT
{
	uInt32	u32Size;					// Size of this structure
	CS8500_EEPROM_STRUCT	Eeprom;		// Eprom contents only for Cs8500
}CS8500_EEPROM_RW_STRUCT, *PCS8500_EEPROM_RW_STRUCT;


typedef struct _CS_SELF_TEST_STRUCT
{
	uInt16	u16Value;
}CS_SELF_TEST_STRUCT, *PCS_SELF_TEST_STRUCT;


typedef struct _CS_CLOCK_OUT_STRUCT
{
	uInt16	u16Value;
	uInt16  u16Valid;
}CS_TRIG_ENABLE_STRUCT, *PCS_TRIG_ENABLE_STRUCT,
 CS_CLOCK_OUT_STRUCT, *PCS_CLOCK_OUT_STRUCT;


typedef struct _CS_TRIG_OUT_STRUCT
{
	uInt16	u16Mode;
	uInt16	u16ValidMode;
	uInt16	u16Value;
	uInt16  u16Valid;
}CS_TRIG_OUT_STRUCT, *PCS_TRIG_OUT_STRUCT;


typedef struct _CS_AUX_IN_STRUCT
{
	uInt16	u16ExtTrigEnVal;
	uInt16  u16ModeVal;
} CS_AUX_IN_STRUCT, *PCS_AUX_IN_STRUCT;

typedef struct _CS_AUX_OUT_STRUCT
{
	uInt16	u16ModeVal;
} CS_AUX_OUT_STRUCT, *PCS_AUX_OUT_STRUCT;


typedef struct _CS_PLX_DELAYLINE_STRUCT
{
	uInt16	u16Edge;
	uInt16	u16Delay;
	uInt16	u16Falling;
	uInt16  u16Fine;

}CS_PLX_DELAYLINE_STRUCT, *PCS_PLX_DELAYLINE_STRUCT;


typedef struct _CS_TRIGADDRESS_OFFSET_STRUCT
{
	uInt32	u32Size;
	uInt8	u8CardNumber;
	uInt8	u8TrigAddrOffset;

}CS_TRIGADDRESS_OFFSET_STRUCT, *PCS_TRIGADDRESS_OFFSET_STRUCT;

typedef struct _CS_TRIGLEVEL_OFFSET_STRUCT
{
	uInt32	u32Size;
	uInt8	u8CardNumber;
	uInt8	u8TrigEngine;
	int16	i16TrigLevelOffset;

}CS_TRIGLEVEL_OFFSET_STRUCT, *PCS_TRIGLEVEL_OFFSET_STRUCT;

typedef struct _CS_TRIGGAIN_STRUCT
{
	uInt32	u32Size;
	uInt8	u8CardNumber;
	uInt8	u8TrigEngine;
	int16	i16TrigGain;

}CS_TRIGGAIN_STRUCT, *PCS_TRIGGAIN_STRUCT;

typedef struct _CS_MEM_TEST_STRUCT
{
	uInt32	u32Address;
	uInt32	u32Data1; // Sample 1 and 2
	uInt32	u32Data2; // Sample 3 and 4
	uInt32	u32Data3; // Sample 5 and 6
	uInt32	u32Data4; // Sample 7 and 8

	uInt32	u32Result1;
	uInt32	u32Result2;
	uInt32	u32Result3;
	uInt32	u32Result4;

}CS_MEM_TEST_STRUCT, *PCS_MEM_TEST_STRUCT;

typedef struct _CS_COIN_STRUCT
{
	uInt32	u32Size;
	uInt8	u8CardNumber;
	void*	pResultBuffers;
	uInt32	u32BufferSize;
	uInt32	u32NumChannels;
	int32   i32TimeOut_uS;
	uInt32  u32Count;
	int32   i32Start;
	uInt32  u32Length;
}CS_COIN_STRUCT, *PCS_COIN_STRUCT;


typedef struct _CS_READ_COIN_STRUCT
{
	uInt32	u32Size;
	int32	i32ReadTimeOut_mS;
	void	*pResultBuffers;
	uInt32	u32BufferSize;

	uInt32	u32ActualLength;

}CS_READ_COIN_STRUCT, *PCS_READ_COIN_STRUCT;



#ifdef _WIN32
#pragma pack ()
#pragma pack (1)
#endif

//-----------------------------------------------------------------------
// Legacy CP500 boards NVRAM structure
//-----------------------------------------------------------------------
typedef struct _NVRAM_IMAGE
{
	uInt8	bios_rom_sig_1;
	uInt8	bios_rom_sig_2;
	uInt8	length;
	uInt32	init_entry_point;
	uInt8	_reserved_1[0x11];
	uInt16	ptr_pci_data_struct;
	uInt8	_unknown_1[6];

	uInt32  SN;
	uInt32  NextSN;
	uInt8   master;
	uInt8   PLD_num;         // PLD_num + nvPLD_num should be <12
	uInt16  Version;
	uInt16  EEsize;
	uInt16  options;
	uInt16  VersionPLD0;
	uInt16  VersionPLD1;
	uInt16  VersionPLD2;
	uInt16  VersionPLD3;
	uInt16  VersionPLD4;
	uInt16  VersionPLD5;
	uInt16  VersionPLD6;
	uInt16  options_ext;


	uInt16	vendor_id;
	uInt16	device_id;
	uInt8	_not_used_1;
	uInt8	bus_mast_config;
	uInt16	_not_used_2;
	uInt32	rev_id_class_code;
	uInt8	_not_used_3;
	uInt8	latency_timer;
	uInt8	header_type;
	uInt8	self_test;
	uInt8	init_baddr0;
	uInt8	required_0xff;
	uInt8	required_0xe8;
	uInt8	required_0x10;
	uInt32	baddr1;
	uInt32	baddr2;
	uInt32	baddr3;
	uInt32	baddr4;
	uInt32	baddr5;
	uInt8	_not_used_4[8];
	uInt32	exp_rom_addr;
	uInt8	_not_used_5[8];
	uInt8	int_line;
	uInt8	int_pin;
	uInt8	min_grant;
	uInt8	max_lat;

} NVRAM_IMAGE, *PNVRAM_IMAGE;


//! \struct _CS_NVRAM_RW_STRUCT
//! \brief Structure used in CsDrvSet() and CsDrvGet()
//!
typedef struct _CS_NVRAM_RW_STRUCT
{
	uInt32			u32Size;					// Size of this structure
	NVRAM_IMAGE		NvRam;						// NvRam contents for CP500 based boards
}CS_NVRAM_RW_STRUCT, *PCS_NVRAM_RW_STRUCT;



//-----------------------------------------------------------------------
// Combine PLX based boards NVRAM structure
//-----------------------------------------------------------------------


typedef struct _PLX_NVRAM_IMAGE_DATA	//------ 4096bits => 512 bytes => 256 words => addr 0 to 200h
										//------ Half of the Eeprom is reseved for the PLX boot image (addr 0h up to FFh)
										//------ free space starts at 0x100h
{
	uInt16	VendorId;						//----- 0h
	uInt16	DeviceId;						//----- 2h
	uInt16	ClassRev;						//----- 4h
	uInt16  ClassCode;						//----- 6h
	uInt16	IntPin;							//----- 8h
	uInt16	MaxLatency;						//-----	ah
	uInt32	MailBox0;						//----- ch
	uInt32	MailBox1;						//----- 10h
	uInt32	Space0Range;					//----- 14h
	uInt32	Space0Remap;					//----- 18h
	uInt32	ModeDmaArbitration;				//----- 1ch
	uInt16	EndianDescriptor;				//----- 20h
	uInt16	VpdBoundary;					//----- 22h
	uInt32	ExpansionROMRange;				//----- 24h
	uInt32	ExpansionROMRemap;				//----- 28h
	uInt32	Space0Descriptor;				//----- 2ch
	uInt32	DirectMaster2PCIRange;			//----- 30h
	uInt32	DirectMasterMemoryLocalBaseAddr;//----- 34h
	uInt32	DirectMasterIOLocalBaseAddr;	//----- 38h
	uInt32	DirectMasterPCIMemoryRemap;		//----- 3ch
	uInt32	DirectMasterPCIIOPCIConf;		//----- 40h
	uInt16	SubsystemVendorId;				//----- 46h
	uInt16	SubsystemId;					//----- 44h
	uInt32	Space1Range;					//----- 48h
	uInt32	Space1Remap;					//----- 4ch
	uInt32	Space1Descriptor;				//----- 50h
	uInt32	HotSwapControl;					//----- 54h
	uInt32	PCIArbiterControl;				//----- 58h
	uInt16	PLX_Reserved[82];				//----- 5ch->FEh ----

	uInt32	MemorySize;					//-----	130h ---- Decimal (in kilobytes). Memory sold not the actual, but should be less than the actual!!!
	uInt16	BaseBoardVersion;			//-----	134h ---- BCD, XX.XX.
	uInt32  BaseBoardSerialNumber;		//------136h ---- usualily represented as astring
	uInt32  BaseBoardHardwareOptions;	//------140h ---- Base board  hardware options

#ifdef __linux__
}__attribute__ ((packed)) PLX_NVRAM_IMAGE_DATA, *PPLX_NVRAM_IMAGE_DATA;
#else
}PLX_NVRAM_IMAGE_DATA, *PPLX_NVRAM_IMAGE_DATA;
#endif

#define FLASH_SECTOR_SIZE			0x10000
#define	IMAGENAME_LENGTH			24			// FPGA image file name length
#define	PLX_NVRAM_IMAGE_SIZE		0x200
#define	SPIDER_FLASHIMAGE_SIZE		0x90400		// Maximum size reserved for Spider add-on flash image
#define	ADDON_FLASHIMAGE_SIZE		0x70000		// Maximum size reserved for Combine add-on flash image
#define	CALIB_INFO_SIZE				0x90000		// Maximum size reserved for Calibration info
#define	ADDON_FLASH_HDR_SIZE		0x60000

#define	BB_FLASHIMAGE_SIZE			0x100000	// Maximum size reserved for base board flash image
#define	BB_FLASH_HDR_SIZE			0x80000
#define ADDONFLASH32MBIT_SIZE		0x400000
#define	BBFLASH32Mbit_SIZE			0x400000

//
// Please add the following ASSERT for detection of overflow
//
// ASSERT( PLX_NVRAM_IMAGE_SIZE >=  sizeof( PLX_NVRAM_IMAGE_DATA ) )
//
typedef struct _PLX_NVRAM_IMAGE
{

	PLX_NVRAM_IMAGE_DATA	Data;				// PLX_NVRAM_IMAGE_DATA as defined above
	uInt8					u8Padding[PLX_NVRAM_IMAGE_SIZE-sizeof(PLX_NVRAM_IMAGE_DATA)];

} PLX_NVRAM_IMAGE, *PPLX_NVRAM_IMAGE;


//! \struct _CS_NVRAM_RW_STRUCT
//! \brief Structure used in CsDrvSet() and CsDrvGet()
//!
typedef struct _CS_PLX_NVRAM_RW_STRUCT
{
	uInt32				u32Size;					// Size of this structure
	PLX_NVRAM_IMAGE		PlxNvRam;					// NvRam contents for PLX based boards
}CS_PLX_NVRAM_RW_STRUCT, *PCS_PLX_NVRAM_RW_STRUCT;


//----------------------------------------------------------
//------ EEPROM STRUCTURE FOR ADD_ON BOARDS COMPATIBLE WITH COMBINE BASE BOARDS (PLX)
//----------------------------------------------------------


//----------------------------------------------------------
//----- Actually it's not an EEPROM but a FLASH
//----- Am29LV033C is a 4M bytes Flash (4194304 bytes) 0h - > 3FFFFFh
//----- Size of the image of the ADD_ON FPGA: size 3534640 bits = 441830 bytes
//----------------------------------------------------------

typedef struct
{
	uInt32	u32AddOnOptions[3];					//----- 300000h -> 30000Bh	----- u32Options2 for each image
	uInt16	u16AddOnBoardVersion;				//----- 30000Ch -> 30000Dh	----- BCD, XX.XX.
	uInt32  u32AddOnBoardSerialNumber;			//----- 30000Eh -> 300011h  ----- usualy represented as as string
	uInt32	u32HardwareAddOnOptions;			//----- 300012h -> 300015h	----- Real addon hardware capabilities

#ifdef __linux__
}__attribute__ ((packed)) AddonHdrElement;

#else
}AddonHdrElement;
#endif


typedef struct
{
	AddonHdrElement			HdrElement;							// Addon HeaderElement as defined above
														
	uInt8					u8Padding[ADDON_FLASH_HDR_SIZE-sizeof(AddonHdrElement)];	// Should never access this

#ifdef __linux__
}__attribute__ ((packed)) AddOnFlashHeader;
#else
}AddOnFlashHeader;
#endif

typedef struct
{
	uInt8	Image1[ADDON_FLASHIMAGE_SIZE];		//----- 0h		-> 6FFFFh	----- Flash Image1
	uInt8	Calib1[CALIB_INFO_SIZE];			//----- 70000h	-> FFFFFh	----- Calibration for Image 1
	uInt8	Image2[ADDON_FLASHIMAGE_SIZE];		//----- 100000h	-> 16FFFFh	----- Flash Image1
	uInt8	Calib2[CALIB_INFO_SIZE];			//----- 170000h	-> 1FFFFFh	----- Calibration for Image 2
	uInt8	Image3[ADDON_FLASHIMAGE_SIZE];		//----- 200000h	-> 26FFFFh	----- Flash Image1
	uInt8	Calib3[CALIB_INFO_SIZE];			//----- 270000h	-> 2FFFFFh	----- Calibration for Image 3

	AddOnFlashHeader	ImagesHeader;			//---- 30000h
	uInt32				u32ChecksumSignature[3];	// Should be equal to CSMV_FWCHECKSUM_VALID

#ifdef __linux__
}__attribute__ ((packed)) AddOnFlashData;

#else
}AddOnFlashData;
#endif


//
// Please add the following ASSERT for detection of overflow
//
// ASSERT( ADDONFLASH32MBIT_SIZE >=  sizeof( AddOnFlashData ) )
//
typedef struct
{
	AddOnFlashData		Data;					// AddOnFlashData as defined above
	uInt8				u8Padding[ ADDONFLASH32MBIT_SIZE-sizeof(AddOnFlashData) ];

#ifdef __linux__
}__attribute__ ((packed)) AddOnFlash32Mbit;

#else
}AddOnFlash32Mbit;
#endif


typedef struct
{
	uInt32	u32Version;							// Version
	uInt32	u32FpgaOptions;						// flexible options, reflect the FPGA image

#ifdef __linux__
}__attribute__ ((packed)) HeaderElement;
#else
} HeaderElement;
#endif


//
// Please add the following ASSERT for detection of overflow
//
// ASSERT( BBFLASH_HDR_SIZE >=  4*sizeof( HeaderElement ) )
//

typedef struct
{
	HeaderElement			HdrElement[4];					// HeaderElement as defined above
															// 3 Images + 1 Boot pld
	uInt8					u8Padding[BB_FLASH_HDR_SIZE-4*sizeof(HeaderElement)];	// Should never access this

#ifdef __linux__
}__attribute__ ((packed)) BaseBoardFlashHeader;
#else
}BaseBoardFlashHeader;
#endif


//----------------------------------------------------------
//------ FLASH STRUCTURE FOR COMBINE BASE BOARDS (PLX)
//----- Am29LV033C is a 4M bytes Flash (4194304 bytes) 0h - > 3FFFFh
//------ Size of one image = 7894144 bits => 986768 bytes
//----------------------------------------------------------

typedef struct
{
	uInt8					DefaultImage[BB_FLASHIMAGE_SIZE];		//----- 0h - > FFFFFh ---- Flash Image
	uInt8					OptionnalImage1[BB_FLASHIMAGE_SIZE];	//----- 100000h -> 1FFFFF
	uInt8					OptionnalImage2[BB_FLASHIMAGE_SIZE];	//----- 200000h -> 2FFFFF
	BaseBoardFlashHeader	ImagesHeader;							//----- 300000h -> 37FFFF
	uInt32					u32ChecksumSignature[3];				// Should be equal to CSMV_FWCHECKSUM_VALID
    int64					i64ExpertPermissions;					// What is allowed to be programmed on this board
#ifdef __linux__
}__attribute__ ((packed)) BaseBoardFlashData;

#else
} BaseBoardFlashData;
#endif


//
// Please add the following ASSERT for detection of overflow
//
// ASSERT( BBFLASH32Mbit_SIZE >=  sizeof( BaseBoardFlashData ) )
//

typedef struct
{
	BaseBoardFlashData		Data;														// BaseBoardFlashData as defined above
	uInt8					u8Padding[BBFLASH32Mbit_SIZE-sizeof(BaseBoardFlashData)];	// Should never access this

#ifdef __linux__
}__attribute__ ((packed)) BaseBoardFlash32Mbit;

#else
}BaseBoardFlash32Mbit;
#endif


typedef union
{
	uInt32	u32Reg;
	struct
	{
		unsigned int uMinor : 4;
		unsigned int uMajor : 4;
		unsigned int uRev   : 8;
		unsigned int uYear  : 4;
		unsigned int uDay   : 8;
		unsigned int uMonth : 4;
	} Info;

} FPGABASEBOARD_OLDFWVER;

typedef union
{
	uInt32	u32Reg;
	struct
	{
		unsigned int uYear     : 6;
		unsigned int uDay      : 5;
		unsigned int uMonth	   : 4;
		unsigned int uReserved : 1;
		unsigned int uMinor	   : 4;
		unsigned int uMajor    : 4;
		unsigned int uRev      : 7;
	} Info;
} FPGAADDON_OLDFWVER;

typedef union _FPGA_FWVERSION
{
	uInt32 u32Reg;
	struct
	{
		unsigned int uMinor		: 9;
		unsigned int uMajor		: 5;
		unsigned int uState		: 1;
		unsigned int uNotUsed1	: 1;
		unsigned int uIncRev	: 6;
		unsigned int uRev		: 9;
		unsigned int uNotUsed0	: 1;
	} Version;

} FPGA_FWVERSION, *PFPGA_FWVERSION;


typedef union _FWVERSION
{
	uInt32 u32Reg;
	struct
	{
		unsigned int uIncRev	: 10;
		unsigned int uRev		: 8;
		unsigned int uMinor		: 9;
		unsigned int uMajor		: 5;
	} Version;

} CSFWVERSION, *PCSFWVERSION;



typedef struct _CS_FW_VER_INFO
{
	uInt32	u32Size;				// Size of this structure
	union
	{
		uInt8 u8Reg;
		struct
		{
			unsigned int uMinor : 4;
			unsigned int uMajor : 4;
		}Info;
	}BbCpldInfo;

	CSFWVERSION			BaseBoardFwVersion;			// Decorate version used by new CSI 
	CSFWVERSION			AddonFwVersion;				// Decorate version used by new CSI 
	FPGA_FWVERSION		BbFpgaInfo;					// Original firmware version
	FPGA_FWVERSION		AddonFpgaFwInfo;			// Original firmware version
	uInt32				u32BbFpgaOptions;
	uInt32				u32AddonFpgaOptions;

	union
	{
		uInt32 u32Reg;
		struct
		{
			unsigned int uYear     : 6;
			unsigned int uDay      : 5;
			unsigned int uMonth	   : 4;
			unsigned int uReserved : 1;
			unsigned int uMinor	   : 4;
			unsigned int uMajor    : 4;
			unsigned int uRev      : 7;
		}Info;
	}AnCpldFwInfo;

	union
	{
		uInt32 u32Reg;
		struct
		{
			unsigned int uYear     : 6;
			unsigned int uDay      : 5;
			unsigned int uMonth	   : 4;
			unsigned int uReserved : 1;
			unsigned int uMinor	   : 4;
			unsigned int uMajor    : 4;
			unsigned int uRev      : 7;
		}Info;
	}TrigCpldFwInfo;

	union
	{
		uInt32 u32Reg;
		struct
		{
			unsigned int uYear     : 6;
			unsigned int uDay      : 5;
			unsigned int uMonth    : 4;
			unsigned int uReserved : 1;
			unsigned int uMinor    : 4;
			unsigned int uMajor    : 4;
			unsigned int uRev      : 7;
		}Info;
	}ConfCpldInfo;
}CS_FW_VER_INFO, *PCS_FW_VER_INFO;


//! \struct _CSSYSTEMSTATE
//! \brief Structure to represent the state of each system.
//!

#ifdef _WIN32
#pragma pack()
#endif


#ifdef _WIN32
#pragma pack(8)
#endif

typedef struct _CSSYSTEMINFOEX
{
	uInt32	u32Size;   					//!<  Total size, in bytes, of the structure.
	uInt32	u32AddonHwOptions;			//!<  EEPROM options encoding features of the add-on pcb.
	uInt32	u32BaseBoardHwOptions;		//!<  EEPROM options encoding features of the baseboard pcb.
	uInt32	u32BaseBoardFwOptions[8];	//!<  EEPROM options encoding features of optional baseboard firmware.
	uInt32	u32AddonFwOptions[8];		//!<  EEPROM options encoding features of optional add-on firmware.
	CSFWVERSION	u32BaseBoardFwVersions[8];	//!<  EEPROM options encoding version of optional baseboard firmware.
	CSFWVERSION	u32AddonFwVersions[8];		//!<  EEPROM options encoding version of optional add-on firmware.
	int64	i64ExpertPermissions;		//!<  Permissions for Expert features
	uInt16	u16DeviceId;				//!<  Device Id
} CSSYSTEMINFOEX, *PCSSYSTEMINFOEX;


//! \struct _MULRECRAWDATA_HEADER
//! \brief  Header of raw Mulrec data
//!
typedef struct _MULRECRAWDATA_HEADER
{
	uInt32		u32Size;					// Size of this structure
	uInt32		u32BoardType;				// Board Type
	uInt32		u32Mode;					// Acquisition Mode
	uInt16		u16ChannelSkip;				// Channel skip. Depend on Mode DUAL or SINGLE ...
	uInt32		u32FirstSegment;			// First Segment Number in raw data
	uInt32		u32LastSegment;				// Last Segment Number in raw data
	uInt32		u32CardCount;				// Number of cards in system
	uInt32		u32ChannelsPerCard;			// Number of channels per cards
	uInt32		u32ChannelsInRawData;		// Number of channels in raw data
	uInt32		u32SampleSize;				// The sample size
	uInt32		u32BbFwOption;				// BaseBoard Firmware option
	uInt32		u32AoFwOption;				// Addon board Firmware option
	uInt32		u32DecimationFactor;		// Decimation factor
	uInt16		u16FooterSize;				// Size of the footer
	BOOLEAN		bBigMemoryFirmware;			// Firmware support big memory
	uInt16		u16TrigMasterCardIndex;		// Index of TriggerMaster card
	uInt32		u32TrigAddrAdjust;			// Trigger Address Offset adjustment
	uInt32		u32DmaOffsetAdjust;			// Offset adjustment because of Dma
	int64		i64Depth;					// Depth of the current acquisition
	int64		i64SegmentSize;				// Segment size of the current acquisition
	int64		i64TriggerDelay;			// Trigger Delay of the current acquisition
	int64		i64TriggerHoldOff;			// Trigger Hold off of the current acquisition
	int64		i64RealDepth;				// Real Depth in raw Data
	int64		i64RealSegmentSize;			// Real Segment size in raw Data
	int64		i64DataBufferSize;			// Raw data buffer size include this header
	int64		i64MemorySegmentSize;		// Segment size in memory (included footer and all channels data )
	
} MULRECRAWDATA_HEADER, *PMULRECRAWDATA_HEADER;


#ifdef _WIN32
#pragma pack ()
#endif

//
// CS_IOCTL_REGISTER_STREAMING_BUFFERS
//

//! \struct STM_BUFFER_DESCRIPTOR
//! \brief  Streaming Buffers Descriptors
//!
typedef struct _CSFOLIO
{
	void		*pBuffer;				// Pointer to the buffer
	uInt32		u32BufferSize;			// Buffer size in bytes

} CSFOLIO, *PCSFOLIO;

//! \struct in_STREAMING_BUFFER_LIST
//! \brief  Streaming Buffers List
//!
typedef struct _CSFOLIOARRAY
{
	uInt16		u16BufferCount;
	CSFOLIO		StmBuffer[4];

} CSFOLIOARRAY, *PCSFOLIOARRAY;


typedef struct _CSFOLIOSTATUS
{
	BOOLEAN		bFolioBusy;
	uInt32		u32Length;
	int32		i32Status;
	uInt32		u32SamplesDropped;
	uInt32		u32TrigAddrOffset;

} CSFOLIOSTATUS, *PCSFOLIOSTATUS;


typedef struct _STMSTATUS
{
	int32				i32Status;
	CSFOLIOSTATUS		BlockInfo[4];
			
} STMSTATUS, *PSTMSTATUS;


//! \struct _CS_CALIBMODE_PARAMS
//! \brief  Calibration Configuration structure
//!
typedef struct _CS_CALIBMODE_PARAMS
{
	uInt32		u32Size;				//!< Total size, in bytes, of the structure.
	uInt16		u16ChannelIndex;		//!< Channel Index
	eCalMode	CalibMode;				//!< Calibration Mode
	uInt32   	u32Frequency;			//!< Calibration frequency used on spider

} CS_CALIBMODE_PARAMS, *PCS_CALIBMODE_PARAMS;

typedef struct _CSEXPERTPARAM
{
	uInt32		u32Size;
	uInt32		u32ActionId;
} CSEXPERTPARAM, *PCSEXPERTPARAM;


//! \struct _CS_GENERIC_EEPROM_READWRITE
//! \brief Structure used in CsDrvSet() and CsDrvGet()
//!
typedef struct _CS_GENERIC_EEPROM_READWRITE
{
	uInt32				u32Size;					// Size of this structure
	uInt32				u32BufferSize;				// Buffer Size
	uInt32				u32Offset;					// Read or Write offset
	void				*pBuffer;					// pointer to allocated buffer
}CS_GENERIC_EEPROM_READWRITE, *PCS_GENERIC_EEPROM_READWRITE,
 CS_GENERIC_FLASH_READWRITE, *PCS_GENERIC_FLASH_READWRITE;



#ifdef CS_WIN64

//! \struct _CS_GENERIC_EEPROM_READWRITE_32
//! \brief Structure used in CsDrvSet() and CsDrvGet()
//!
typedef struct _CS_GENERIC_EEPROM_READWRITE_32
{
	uInt32				u32Size;					// Size of this structure
	uInt32				u32BufferSize;				// Buffer Size
	uInt32				u32Offset;					// Read or Write offset
	VOID*POINTER_32		pBuffer32;					// pointer to allocated buffer
}CS_GENERIC_EEPROM_READWRITE_32, *PCS_GENERIC_EEPROM_READWRITE_32,
 CS_GENERIC_FLASH_READWRITE_32, *PCS_GENERIC_FLASH_READWRITE_32;

#endif


#define HWOPTIONS_TEXT_LENGTH				32
typedef struct _CS_HWOPTIONS_CONVERT2TEXT
{
	uInt32		u32Size;					// input: size of this structure
	BOOLEAN		bBaseBoard;					// input  BB: 1, AO: 0
	uInt8		u8BitPosition;				// input  0 - 31
	uInt32		u32RevMask;					// output - reserved
	char		szOptionText[HWOPTIONS_TEXT_LENGTH];			// output ("option1", "option2", "??")
}CS_HWOPTIONS_CONVERT2TEXT, *PCS_HWOPTIONS_CONVERT2TEXT, 
 CS_FWOPTIONS_CONVERT2TEXT, *PCS_FWOPTIONS_CONVERT2TEXT;

//! \struct _CS_SPDR12_TRIM_TCAP_STRUCT
//! \brief  Trim the front end TCAPs (Spider 1.2 only)
//!
typedef struct _CS_SPDR12_TRIM_TCAP_STRUCT
{
	uInt32		u32Size;				//!< Total size, in bytes, of the structure.
	uInt16		u16ChannelIndex;		//!< Channel Index
	BOOL		bTCap2Sel;				//!< TCAP2 selec. (FALSE: Tcap1, TRUE: Tcap2)
	uInt8		u8TrimCount;			//!< Trim Count

} CS_SPDR12_TRIM_TCAP_STRUCT, *PCS_SPDR12_TRIM_TCAP_STRUCT;



typedef struct _CS_ADC_ALIGN_STRUCT
{
	uInt32	u32Size;

	uInt16  u16CardId;
	// ADC align (Absolute value)
	int32	i32Adc0;
	int32	i32Adc90;
	int32	i32Adc180;
	int32	i32Adc270;

	// ADC order (0, 1, 2, 3 )
	uInt8	u8Order0;
	uInt8	u8Order90;
	uInt8	u8Order180;
	uInt8	u8Order270;

}CS_ADC_ALIGN_STRUCT, *PCS_ADC_ALIGN_STRUCT;




#pragma pack (1)

typedef	struct 
{
	uInt32	u32FirmwareOptions;						// The FPGA firmware options
	uInt32	u32ChecksumSignature;					// Should be equal to CSMV_FWCHECKSUM_VALID
	uInt32	u32FirmwareVersion;						// The FPGA firmware version

} CS_FIRMWARE_INFOS, *PCS_FIRMWARE_INFOS;


typedef struct 
{
	uInt32  u32SerialNumber;			// Base board or Addon board serial number
	uInt32	u32HwVersion;				// BB or Addon board Hw version
	uInt32	u32HwOptions;				// BB or Addon board Hw options
	int64	i64ExpertPermissions;

} CS_FLASHFOOTER, *PCS_FLASHFOOTER;


#pragma pack ()

//	LAYOUT of COMPUSCOPE NEW FLASH


//		-----------------------	  ---	-------------------------   ---------	
//		|				    |			|						|			|
//		|					|			|  Fw Binary image 1	|			|
//		|		IMAGE 1		|			|						|			|
//		|					|			-------------------------			|
//		|					|			|						|			|
//		|					|			|  Calib Info 1			|			|
//		|					|			|						|			|
//		|					|			-------------------------			|
//		|					|			|						|			|
//		|					|			|  Fw info 1			|			|
//		|					|			|						|			|
//		---------------------	 ---	-------------------------   -------	|
//		|					|			|						|	|  |  | |
//		|					|			|  Fw Binary image 2	|	A  |  | |
//		|		IMAGE 2		|			|						| 	|  |  | D
//		|					|			-------------------------   -  B  | |		
//		|					|			|						|      |  | |
//		|					|			|  Calib Info 2			|      |  C |
//		|					|			|						|      |  | |
//		|					|			-------------------------   ----  | |	
//		|					|			|						|         | |
//		|					|			|  Fw info 2			|		  | |
//		|					|			|						|		  | |
//		--------------------_	 ---	-------------------------   ------- |
//		|					|			|						|			|
//		.					.			. 						.			|
//		.					.			.						.			|
//		.					.			.						.			|
//		|		IMAGE n		|			| 						|			|
//		|					|			|						|			|
//		|					|			|						|			|
//		---------------------	 ---	-------------------------   ---------	
//		|					|			|						|
//		|	 Flash Footer	|			|   Flash Footer		|
//		|					|			|						|
//		---------------------	 ---	---------------------------	




typedef struct 
{
	// INPUT
	uInt32	u32Addon;					// 0: Base board, 1: Addon

	// OUTPUT
	uInt32	u32FlashType;				// Structure of flash
										// 0: Old Combine Flash structure
										// 1: New Flash Structure
	uInt32  u32NumOfImages;				// Max number of images fit in Flash
	uInt32	u32ImageStructSize;			// Size of each Image structure.(C in the picture)								
	uInt32	u32CalibInfoOffset;			// Relative offset of CalibInfo from beginning of each image (A in the picture)
	uInt32	u32FwInfoOffset;			// Relative offset of Fw Info  from beginning of each image (B in the picture)
	uInt32	u32FlashFooterOffset;		// Position of the Flash Footer from beginning of the flash (D in the picture)
	uInt32	u32WritableStartOffset;		// Offset of the first writeble firmware image from beginning of flash.
										// This offset is defined to protect the BootImage firmware.
	uInt32	u32FwBinarySize;			// The real size of FPGA binayy								

} CS_FLASHLAYOUT_INFO, *PCS_FLASHLAYOUT_INFO;


typedef	struct _FWLnCSI_INFO
{
	uInt32	u32ProductId;			// Device Id
	uInt32	u32BaseId;				// Base board Id
	uInt32	u32AddonId;				// Addon Id
	uInt32	u32BoardType;			// BoardType
	char	szHwDllName[24];		// Hw Dll 
	char	szBaseClass[24];		// Baseboard class (Combine, Spider or Rabbit)
	char	szProduct[24];			// Cs14200, ST12AVG ....
	char	szFwFileName[24];		// Csi and Fwl file name without extension.
		
} FWLnCSI_INFO, *PFWLnCSI_INFO;


typedef struct _SEND_NIOS_CMD
{
	uInt32	u32Command;
	uInt32	u32DataIn;		// Send to Nios
	uInt32	u32DataOut;		// From Nios
	
	uInt32	u32Timeout;		// Timout in 100 us 
	uInt16	u16CardIndex;	// Card index in M/S: 1,2,3 ... (or 0 for all cards)
	BOOLEAN	bRead;			// Read Data from Nios->> u32DataOut above

} CS_SEND_NIOS_CMD_STRUCT, *PCS_SEND_NIOS_CMD_STRUCT;

typedef struct _RD_GAGE_REGISTER
{
	uInt16	u16CardIndex;	// Card index in M/S: 1,2,3 ... (or 0 for all cards)
	uInt16	u16Offset;		// Register offset
	uInt32	u32Data;		// WRITE: Data IN,
							// READ: Data Out
} CS_RD_GAGE_REGISTER_STRUCT, *PCS_RD_GAGE_REGISTER_STRUCT;

typedef struct _RW_GAGE_REGISTER
{
	uInt16	u16CardIndex;	// Card index in M/S: 1,2,3 ... (or 0 for all cards)
	uInt32	u32Offset;		// Register offset
	uInt32	u32Data;		// WRITE: Data IN,
							// READ: Data Out
} CS_RW_GAGE_REGISTER_STRUCT, *PCS_RW_GAGE_REGISTER_STRUCT;


typedef struct _RAZOR_GAINTARGET_FACTOR
{
	uInt16	u16Channel;			//in
	uInt32	u32InputRange;		//in
	uInt32	u32Impedance;		//in
	uInt32	u32Filter;			//in

	uInt16	u16Factor;			// in (write), out (read)

} RAZOR_GAINTARGET_FACTOR, *PRAZOR_GAINTARGET_FACTOR;	

typedef struct _RAZOR_FROTNPORT_RESIST
{
	uInt16	u16Channel;			//in
	uInt32	u32FrPortRes;		// in (write), out (read)

} RAZOR_FROTNPORT_RESISTANCE_HiZ, *PRAZOR_FROTNPORT_RESISTANCE_HiZ;

typedef struct _PCIeLINK_INFO
{
	// In
	uInt16  u16CardIndex;		// Card Index in M/S system

	// Out
	uInt8	MaxLinkSpeed;
	uInt8	MaxLinkWidth;
	uInt8	LinkSpeed;
	uInt8	LinkWidth;

	uInt8	MaxPayloadSize;
	uInt8	CapturedSlotPowerLimit;
	uInt8	CapturedSlotPowerLimitScale;

} PCIeLINK_INFO, *PPCIeLINK_INFO;


typedef struct _FIRMWARE_VERSION_STRUCT
{
	CSFWVERSION	BaseBoard;
	CSFWVERSION AddonBoard;

} FIRMWARE_VERSION_STRUCT, *PFIRMWARE_VERSION_STRUCT;

typedef struct _WRITEFLASH_PROGRESS_STAT
{
	uInt32	u32SectorsCompleted;		//!< Number of sectors written so far
	uInt32	u32SectorsTotal	;			//!< Number of total sectors to be written

} WRITEFLASH_PROGRESS_STRUCT, *PWRITEFLASH_PROGRESS_STRUCT;


typedef struct _CSSYSTEMSTATE
{
	uInt32		u32Size;				//!< Size of the structure.
	char		strBoardName[32];		//!< Name of the CompuScope boards in the system.
	uInt32		u32BoardType;			//!< CompuScope board type.
	uInt32		u32NumberOfBoards;		//!< Number of boards in the system.
	uInt32		u32NumberOfChannels;	//!< Number of channels in the system.
	int64		i64MemorySize;			//!< Memory size of the board.
	uInt32		u32NumberOfBits;		//!< Number of sample bits in the system.(8, 12, 14, b6, 32 bits).
	RMHANDLE	rmHandle;				//!< Handle that uniquely indentifies the system.
	cschar		strSerialNumber[16][32];//!< Serial numbers of all boards in a system (max 16).
	int8		i8Active;				//!< Is the system currently active (being used by some process).
	uInt32		u32Hours;				//!< Number of hours the system has currently been active.
	uInt32		u32Minutes;				//!< Number of minutes the system has currently been active.
	uInt32		u32Seconds;				//!< Number of seconds the system has currently been active.
	uInt32		u32Milliseconds;		//!< Number of milliseconds the system has currently been active.
	uInt32		u32ProcessID;			//!< Identifier of the process that owns the system.
	char		lpOwner[256];			//!< Name of the process that owns the system.
	CS_FW_VER_INFO csVersionInfo; 		//!< Structure containing firmware information
	CSSYSTEMINFOEX csSystemInfoEx;	 	//!< Structure containing optional firmware versions and options
	uInt32		u32BaseBoardVersion;	//!< Version of the baseboard
	uInt32		u32AddOnVersion;		//!< Version of the addon board
	PCIeLINK_INFO  csPCIeInfo[16];		//!< Structure containing information about the PCIe slot link width and speed  for each board
	char		lpIpAddress[32];		//!< Ip address of remote device (if any) that contains the system
	bool		bCanChangeBootFw;		//!< Flag to determine if a board can boot from it's expert images (Image 1 or 2)
	int			nBootLocation;			//!< Which image the current system is booting from (0, 1 or 2)
	int			nNextBootLocation;		//!< The image the current system will boot from next boot up (0, 1 or 2)
	CSFWVERSION fwVersion;				//!< The version of the current boot firmware
	int			nImageCount;			//!< Total number of images
	bool		bIsChecksumValid[MAX_IMAGE_COUNT];	//!< Is the checksum of each image valid (max 3 images per board, RG ?? boards per system)
}CSSYSTEMSTATE, *PCSSYSTEMSTATE;

typedef union _KERNEL_MISC_STATE
{
	uInt32	u32Value;
	struct
	{
		uInt32	OverVoltage		:1;				// Overvoltage has occured on one of channels
	} Bits;

}  KERNEL_MISC_STATE, *PKERNEL_MISC_STATE,
   io_KERNEL_MISC_STATE, *P_io_KERNEL_MISC_STATE,
   BOARD_VOLATILE_STATE, *PBOARD_VOLATILE_STATE;

#ifdef _WINDOWS_
// structure for holding timing results from the GageDiskStream subsystem

typedef struct _CSTIMESTAT_DISKSTREAM
{
	struct
	{
		uInt32	 u32Size;
		uInt32	 u32ActionId;
	} in;
	struct
	{
		LONGLONG llAcquirePerfCount;
		LONGLONG llXferPerfCount;
		LONGLONG llWritePerfCount;
		LONGLONG llUpdateClosePerfCount;
		LONGLONG llPreCreatePerfCount;
	} out;
} CSTIMESTAT_DISKSTREAM, *PCSTIMESTAT_DISKSTREAM;

typedef struct _CSTIMEFLAG_DISKSTREAM
{
	uInt32	u32Size;
	uInt32	u32ActionId;
	BOOL	bFlag;
} CSTIMEFLAG_DISKSTREAM, *PCSTIMEFLAG_DISKSTREAM;	

typedef union _KERNEL_MISC_STATE
{
	uInt32	u32Value;
	struct
	{
		uInt32	Invalid			:1;				// Invalid state: System went back from sleep or application crash
		uInt32	OverVoltage		:1;				// Overvoltage has occured on one of channels
	} Bits;

}  KERNEL_MISC_STATE, *PKERNEL_MISC_STATE,
   BOARD_VOLATILE_STATE, *PBOARD_VOLATILE_STATE;


#ifdef CS_WIN64
/*************************************************************/

//! \struct CSSYSTEMCONFIG
//! \brief  Structure containing the whole configuration: Acquisition settings, Channels settings and Triggers settings.
//!
typedef struct
{
	//! Total size, in Bytes, of the structure.
	uInt32					u32Size;   		//!< Total size, in Bytes, of the structure.
	//! Acquisition Configuration
	CSACQUISITIONCONFIG*POINTER_32	pAcqCfg;		//!< \link CSACQUISITIONCONFIG Acquisition Configuration \endlink
	//!  Channels' configuration
	ARRAY_CHANNELCONFIG*POINTER_32	pAChannels;		//!< Pointer to an \link ARRAY_CHANNELCONFIG array \endlink of channel configurations
	//!  Trigger engines' configuration
	ARRAY_TRIGGERCONFIG*POINTER_32	pATriggers;		//!< Pointer to an \link ARRAY_TRIGGERCONFIG array \endlink of trigger engine configurations
	//!
} CSSYSTEMCONFIG_32, *PCSSYSTEMCONFIG_32;


//! \struct IN_PARAMS_TRANSFERDATA
//! \brief  Structure used in CsTransfer() to specify data to be transferred.
//! May be used to transfer digitized data or time-stamp data.
//!
//! \sa CsTransfer
typedef struct
{
	//!  Channel index
	uInt16	u16Channel;			//!< Channel index (will be ignored in time-stamp mode)
	//! Transfer Modes
	uInt32	u32Mode;			//!< See \link TRANSFER_MODES Transfer Modes \endlink
	//! The segment of interest
	uInt32	u32Segment;			//!< The segment of interest
	//!  Start address for transfer
	int64	i64StartAddress;	//!< Start address for transfer relative to the trigger address
	//! Size of the requested data transfer
	int64	i64Length;			//!< Size of the requested data transfer (in samples)
	//! Pointer to the target buffer
	VOID*POINTER_32	pDataBuffer;		//!< Pointer to application-allocated buffer to hold requested data.  For 8-bit CompuScope models,
	                            //!< data values are formatted as uInt8. For analog input CompuScope models with more than 8-bit
	                            //!< resolution (e.g. 12 bit, 14 bit, 16 bit), data values are formatted as Int16.  For digital
	                            //!< input CompuScope models in 32-bit input mode, data values are formatted as uInt32.
	                             //!< For time-stamp data transfer, time-stamp values are formatted as 64-bit integers.
	//! Notification event
	VOID*POINTER_32	hNotifyEvent;		//!< Optional: Pointer to the Handle of application-created event. The event will be signalled
	                            //!< once data transfer is complete
//!
} IN_PARAMS_TRANSFERDATA_32, *PIN_PARAMS_TRANSFERDATA_32;


//! \struct IN_PARAMS_TRANSFERDATA
//! \brief  Structure used in CsTransfer() to specify data to be transferred.
//! May be used to transfer digitized data or time-stamp data.
//!
//! \sa CsTransfer
typedef struct
{
	//!  Channel index
	uInt16	u16Channel;			//!< Channel index (will be ignored in time-stamp mode)
	//! Transfer Modes
	uInt32	u32Mode;			//	Slave , BusMaster, DATA_ONLY, TIMESTAMP_ONLY, DATA_WITH_TAIL, INTERLEAVED
	//! The segment of interest
	uInt32	u32StartSegment;			//!< The first segment of interest

	uInt32	u32NumOfSegments;			//!< Number of segments

	//!  Start address for transfer
	int64	i64StartAddress;	//!< Start address for transfer relative to the trigger address
	//! Size of the requested data transfer
	int64	i64Length;			//!< Size of the requested data transfer (in samples)

	//! Pointer to the target buffer
	VOID*POINTER_32	pDataBuffer;		//!< Pointer to application-allocated buffer to hold requested data.  For 8-bit CompuScope models,
	                            //!< data values are formatted as uInt8. For analog input CompuScope models with more than 8-bit
	                            //!< resolution (e.g. 12 bit, 14 bit, 16 bit), data values are formatted as Int16.  For digital
	                            //!< input CompuScope models in 32-bit input mode, data values are formatted as uInt32.
	                             //!< For time-stamp data transfer, time-stamp values are formatted as 64-bit integers.

	int64	i64BufferLength;

	//! Notification event
	VOID*POINTER_32	hNotifyEvent;		//!< Optional: Pointer to the Handle of application-created event. The event will be signalled
	                            //!< once data transfer is complete
//!
} IN_PARAMS_TRANSFERDATAEX_32, *PIN_PARAMS_TRANSFERDATAEX_32;

#endif

#endif		// _WINDOWS_


//!
//! \}
//!

#endif
