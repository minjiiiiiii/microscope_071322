//! Cs14160Cal.h
//!
//!

#ifndef __CsMarvinCal_h__
#define __CsMarvinCal_h__


typedef	struct _ChanCalibInfo
{
	uInt16 _O_1;
	uInt16 _O_2;
	uInt16 _G_1;
	uInt16 _G_2;
	int16  _P_C; //Value that been added to  middle dac value produces 1/2 FS Offset
} CHANCALIBINFO, *PCHANCALIBINFO;


//dac code that produce a given calibration votage

typedef	struct _DacCalibValue
{
	uInt16 _Hi;  // + 90% FS in all but ±5 V (+3.5V in ±10 V)
	uInt16 _Lo;  // - 90% FS in all but ±5 V (-3.5V in ±10 V)
	uInt16 _MiP; // +  2% FS 
	uInt16 _MiN; // -  2% FS
	uInt16 _PP;  // + 50% FS 
	uInt16 _PN;  // - 50% FS 
} DACCALIBVALUE, *PDACCALIBVALUE;

typedef	struct _DelayLine
{
	uInt8 _A_1; // Chan A 1st A/d
	uInt8 _A_2; // Chan A 2nd A/d
	uInt8 _B_1; // Chan B 1st A/d
	uInt8 _B_2; // Chan B 2nd A/d
	uInt8 _A_1_f; // Fine adjustment Chan A 1st A/d
	uInt8 _A_2_f; // Fine adjustment Chan A 2nd A/d
	uInt8 _B_1_f; // Fine adjustment Chan B 1st A/d
	uInt8 _B_2_f; // Fine adjustment Chan B 2nd A/d
} DELAYLINE, *PDELAYLINE;


#define		CSMARVIN_MAX_FE_INDEX		16				// Max Front End index 
#define		CSMARVIN_MAX_SR_INDEX		21				// Max sample rate index

typedef struct _CSMARVIN_CAL_INFO
{
	DACCALIBVALUE	DacCalibValue[CSMARVIN_MAX_FE_INDEX];
	CHANCALIBINFO	ChanCalibInfo[2+1][CSMARVIN_MAX_FE_INDEX];			// 2 channels + 1 for 0 based index
	DELAYLINE		DelayLine[CSMARVIN_MAX_SR_INDEX];
	uInt32			u32Valid;

	uInt16			u16TrigLevelOffset[2][CS_MAX_TRIG_COND];			// 2 trigger engines x trigger condition
	uInt16			u16TriggerGain[2][CS_MAX_TRIG_COND];				// 2 trigger engines x trigger condition

	uInt16			u16ExtTrigLevelOffset1V[2][CS_MAX_TRIG_COND];		// 2 trigger engines x trigger condition
	uInt16			u16ExtTrigLevelOffset5V[2][CS_MAX_TRIG_COND];		// 2 trigger engines x trigger condition
	uInt16			u16ExtTriggerGain1V[2][CS_MAX_TRIG_COND];			// 2 trigger engines x trigger condition
	uInt16			u16ExtTriggerGain5V[2][CS_MAX_TRIG_COND];			// 2 trigger engines x trigger condition

	uInt8			u8TrigAddrOffsetAdjust[CSMARVIN_MAX_SR_INDEX][2];	// Reserve space for each sample rate
																		// and 2 mode (dual and single)
																		// Must be a positive value.

	uInt8			u8ExtClkTrigAddrOffAdj[2][2];						// Reserve space for Ext clock 2 ranges (interleave and non-interleave)
																		// and 2 mode (dual and single)
																		// Must be a positive value.

} CSMARVIN_CAL_INFO, *PCSMARVIN_CAL_INFO;


#define		DESCRIPTION_LENGTH		128
typedef struct _CALFILE_HEADER
{
	uInt32		u32Size;
	uInt8		u8Description[128];
	uInt32		u32Version;				// File Version
	uInt32		u32Checksum;			// TBD
	uInt32		u32BoardType;			// TBD

} CALFILE_HEADER, *PCALFILE_HEADER;


typedef struct _CALFILE
{
	CALFILE_HEADER		CalHdr;
	CSMARVIN_CAL_INFO	CalibTable;

} CALFILE, *PCALFILE;



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


#define	CSMARVIN_CAL_DAC_VALID					0x80000000
#define	CSMARVIN_CAL_DAC_INVALID				0x40000000
#define	CSMARVIN_CAL_CHAN_VALID					0x20000000
#define	CSMARVIN_CAL_CHAN_INVALID				0x10000000
#define	CSMARVIN_CAL_DELAY_VALID				0x08000000
#define	CSMARVIN_CAL_DELAY_INVALID				0x04000000
#define	CSMARVIN_CAL_TRIG_LEVEL_VALID			0x02000000
#define	CSMARVIN_CAL_TRIG_LEVEL_INVALID			0x01000000
#define	CSMARVIN_CAL_TRIG_ADDR_VALID			0x00800000
#define	CSMARVIN_CAL_TRIG_ADDR_INVALID			0x00400000
#define	CSMARVIN_CAL_TRIG_GAIN_VALID			0x00200000
#define	CSMARVIN_CAL_TRIG_GAIN_INVALID			0x00100000
#define	CSMARVIN_CAL_EXTCLK_TRIG_ADDR_VALID		0x00080000
#define	CSMARVIN_CAL_EXTCLK_TRIG_ADDR_INVALID	0x00040000
#define	CSMARVIN_CAL_DIFFERENTIAL_VALID  		0x00020000
#define	CSMARVIN_CAL_DIFFERENTIAL_INVALID   	0x00010000

#define	CSMARVIN_VALID_MASK					0xAAAAAAAA
#define	CSMARVIN_PRESERVE_MASK				0x55555555
#define CSMARVIN_CAL_TRIGGER_GAIN_FACTOR	1000
#define CSMARVIN_DEFAULT_TRIGGER_GAIN		1200

#define CSMARVIN_FINE_DELAY_SEED			5
#define CSMARVIN_COARSE_DELAY_SEED			5
#define CSMARVIN_COARSE_DELAY_SPAN			5

#define CSMARVIN_CLOCK_SKEW_STEP			6
#define CSMARVIN_MAX_CLOCK_SKEW			    (CSMARVIN_DELAY_LINE_SPAN - 3 * CSMARVIN_COARSE_DELAY_SPAN)

#define CSMARVIN_IMAGE_WINDOW_SIZE			5
#define CSMARVIN_FFT_ITERATIONS				10

#define CSMARVIN_DELAY_LINE_SPAN			63
#define CSMARVIN_DELAY_FINE_COARSE_RATIO	37

#define CSMARVIN_DAC_SPAN			        2048

#endif