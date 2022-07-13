//! CsBunnyCal.h
//!
//!

#ifndef __CsBunnyCal_h__
#define __CsBunnyCal_h__

#include "CsBunnyCapsInfo.h"

// SEND_DAC
// DAC Id and Address for Rabit cards
#define CSPSR_AD7552_ID			0		// Dac Id (AD75552)

#define	BUNNY_COARSE_OFF_1	    0		// Channel 1 coarse offset
#define	BUNNY_FINE_OFF_1		1		// Channel 1 fine offset
#define	BUNNY_POSITION_1		2		// Channel 1 user offset
#define	BUNNY_ADC_GAIN_1		3		// Channel 1 ADC gain
#define	BUNNY_ADC_OFFSET_1	    4		// Channel 1 ADC offset

#define	BUNNY_2_CHAN_DAC		5		// Channel 2 DAC controls offset

#define	BUNNY_COARSE_OFF_2	    5		// Channel 2 coarse offset
#define	BUNNY_FINE_OFF_2		6		// Channel 2 fine offset
#define	BUNNY_POSITION_2		7		// Channel 2 user offset
#define	BUNNY_ADC_GAIN_2		8		// Channel 2 ADC gain
#define	BUNNY_ADC_OFFSET_2	    9		// Channel 2 ADC offset

#define BUNNY_EXTRIG_LEVEL_HIGH	10	// External trigger Level high
#define BUNNY_EXTRIG_LEVEL_LOW	11	// External trigger Level low

#define BUNNY_CAL_DC			12	// DC level control for calibration
#define BUNNY_VAR_REF			13	// Variable reference for calibration

#define BUNNY_DELAY_MS			14	// Delay line for master slave

#define BUNNY_MAX_DAC_CTLS		15	// Total DAC controls

#define BUNNY_DAC_SPAN			2048
#define BUNNY_ADC_REG_SPAN		255
#define BUNNY_ADC_COARSE_SPAN	7
#define BUNNY_ADC_FINE_SPAN	    511

#define BUNNY_CORE_CORRECTION   31   //Debug backdor to write core correction

typedef enum
{
	eccNullOffset = 0,
	eccFEOffset   = eccNullOffset +1,
	eccPosition   = eccFEOffset + 1,
	eccAdcGain    = eccPosition + 1,
	eccAdcOffset  = eccAdcGain + 1,
}eBunnyCalCtrl;

typedef	struct _BunnyChanCalibInfo
{
	uInt16 _NullOffset; //Value to zero out THS4509 input using coarse offset control
	uInt16 _FeOffset;   //Value that produces zero on ADC (FE compensation) using user offset control
	uInt16 _Gain;       //Gain control
	int16  _AdcOff;     //used for digital offset core correction on 4G adc
	int16  _Pos;        //Value that been added to _Base value produces 50% FS Offset
	BOOLEAN bValid;
} BUNNYCHANCALIBINFO, *PBUNNYCHANCALIBINFO;


// Default Calibration values for Rabbit cards

#define	BUNNY_DEFAULTCALIB_NULLOFFSET		2048
#define	BUNNY_DEFAULTCALIB_FEOFFSET			2048
#define	BUNNY_DEFAULTCALIB_GAIN				128
#define	BUNNY_DEFAULTCALIB_ADCOFFSET		128
#define	BUNNY_DEFAULTCALIB_POS				0


#define BUNNY_CALIB_BUF_MARGIN	  512
#define BUNNY_CALIB_DEPTH		  0x2000
#define BUNNY_CALIB_BUFFER_SIZE	  (2 * BUNNY_CALIB_BUF_MARGIN + BUNNY_CALIB_DEPTH)
#define BUNNY_CALIB_BLOCK_SIZE	  64



#define	BUNNYCALIBINFO_CHECKSUM_VALID		0x12345678

typedef struct _BUNNY_CAL_INFO
{
	uInt32			u32Size;			// Size of this structure
	uInt32			u32Checksum;		// Checksum for valid table

	uInt32			u32Valid;			// Which of following table is are valid
	uInt32			u32Active;			// Which of following table is are active (used by drivers )
	BUNNYCHANCALIBINFO	ChanCalibInfo[BUNNY_CHANNELS][BUNNY_MAX_RANGES];// 2 channels
	uInt16			u16TrigLevelOffset[2][CS_MAX_TRIG_COND];		    // 2 trigger engines x trigger condition
	uInt16			u16TriggerGain[2][CS_MAX_TRIG_COND];			    // 2 trigger engines x trigger condition

	uInt16			u16ExtTrigLevelOffset1V[2][CS_MAX_TRIG_COND];	    // 2 trigger engines x trigger condition
	uInt16			u16ExtTrigLevelOffset5V[2][CS_MAX_TRIG_COND];	    // 2 trigger engines x trigger condition
	uInt16			u16ExtTriggerGain1V[2][CS_MAX_TRIG_COND];		    // 2 trigger engines x trigger condition
	uInt16			u16ExtTriggerGain5V[2][CS_MAX_TRIG_COND];		    // 2 trigger engines x trigger condition

	int8			i8TrigAddrOffsetAdjust[BUNNY_MAX_SR_COUNT][2];		// Reserve space for each sample rate
																		// and 2 mode (dual and single)

	int8			i8ExtClkTrigAddrOffAdj[4][2];						// Reserve space for Ext clock 2 ranges (interleave and non-interleave)
																		// and 2 mode (dual and single)
																		// Must be a positive value.

} BUNNY_CAL_INFO, *PBUNNY_CAL_INFO;


#define		DESCRIPTION_LENGTH		128
typedef struct _BUNNY_CALFILE_HEADER
{
	uInt32		u32Size;
	uInt8		u8Description[DESCRIPTION_LENGTH];
	uInt32		u32Version;				// File Version
	uInt32		u32Checksum;			// TBD
	uInt32		u32BoardType;			// TBD

} BUNNY_CALFILE_HEADER, *PBUNNY_CALFILE_HEADER;


typedef struct _BUNNY_CALFILE
{
	BUNNY_CALFILE_HEADER	CalHdr;
	BUNNY_CAL_INFO CalibTable;

} BUNNY_CALFILE, *PBUNNY_CALFILE;



///! in CsSet : CS_SAVE_CALIBTABLE_TO_EEPROM
///! u32Valid defines validity up to 16 portions of the caltable.
///! Logicaly u32Valid is split in 16 pairs of bits. In each pair the more significant
///! bit represent valid state and the less significant one invalid state.
///! For the portion to be valid the more significant bit should be set and the less
///! significant bit cleared, this is done to invalidate uninitialized media regardless
///! wheather it is filled with ones or zeros.
///! However after inititialization, less significat bit in each pair shoud be cleared
///! and validity will be determined only my more significat bit. That allow us to use the
///! less significant bit to incicate pairs that should be left unmodified, threrefore
///! 1x - means set
///! 00 - means clear
///! 01 - means preserve


#define	BUNNY_CAL_DAC_VALID					0x80000000
#define	BUNNY_CAL_DAC_INVALID				0x40000000
#define	BUNNY_CAL_CHAN_VALID					0x20000000
#define	BUNNY_CAL_CHAN_INVALID				0x10000000
#define	BUNNY_CAL_DELAY_VALID				0x08000000
#define	BUNNY_CAL_DELAY_INVALID				0x04000000
#define	BUNNY_CAL_TRIG_LEVEL_VALID			0x02000000
#define	BUNNY_CAL_TRIG_LEVEL_INVALID			0x01000000
#define	BUNNY_CAL_TRIG_ADDR_VALID			0x00800000
#define	BUNNY_CAL_TRIG_ADDR_INVALID			0x00400000
#define	BUNNY_CAL_TRIG_GAIN_VALID			0x00200000
#define	BUNNY_CAL_TRIG_GAIN_INVALID			0x00100000
#define	BUNNY_CAL_EXTCLK_TRIG_ADDR_VALID		0x00080000
#define	BUNNY_CAL_EXTCLK_TRIG_ADDR_INVALID	0x00040000
#define	BUNNY_CAL_DIFFERENTIAL_VALID  		0x00020000
#define	BUNNY_CAL_DIFFERENTIAL_INVALID   	0x00010000

#define	BUNNY_VALID_MASK					0xAAAAAAAA
#define	BUNNY_PRESERVE_MASK				0x55555555

#endif
