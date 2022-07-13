//! CsBrainiacCal.h
//!
//!

#ifndef __CsBrainiacCal_h__
#define __CsBrainiacCal_h__

#include "CsXYG8capsInfo.h"

// SEND_DAC
// DAC Control Id and Address for Brainiac cards

// Channel 1 DAC controls
#define BRAIN_OFFSET_NULL_1						0
#define BRAIN_OFFSET_COMP_1						1
#define BRAIN_USER_OFFSET_1						2	
#define BRAIN_ADCDRV_OFFSET1_90					3
#define BRAIN_ADCDRV_OFFSET1_270				4		
#define BRAIN_CLKPHASE_OFFSET1_90				5
#define BRAIN_CLKPHASE_OFFSET1_270				6

// Channel 1 ADC controls
#define BRAIN_ADC_COARSE_OFFSET1_90				7
#define BRAIN_ADC_FINE_OFFSET1_90				8
#define BRAIN_ADC_COARSE_GAIN1_90				9
#define BRAIN_ADC_MEDIUM_GAIN1_90				10
#define BRAIN_ADC_FINE_GAIN1_90					11
#define BRAIN_ADC_SKEW1_90						12

#define BRAIN_ADC_COARSE_OFFSET1_270			13
#define BRAIN_ADC_FINE_OFFSET1_270				14
#define BRAIN_ADC_COARSE_GAIN1_270				15
#define BRAIN_ADC_MEDIUM_GAIN1_270				16
#define BRAIN_ADC_FINE_GAIN1_270				17
#define BRAIN_ADC_SKEW1_270						18

// Channel 2 DAC controls
#define BRAIN_OFFSET_NULL_2						19
#define BRAIN_OFFSET_COMP_2						20
#define BRAIN_USER_OFFSET_2						21
#define BRAIN_ADCDRV_OFFSET2_0					22
#define BRAIN_ADCDRV_OFFSET2_180				23
#define BRAIN_CLKPHASE_OFFSET2_0				24	
#define BRAIN_CLKPHASE_OFFSET2_180				25

// Channel 2 ADC controls
#define BRAIN_ADC_COARSE_OFFSET2_0				26
#define BRAIN_ADC_FINE_OFFSET2_0				27
#define BRAIN_ADC_COARSE_GAIN2_0				28
#define BRAIN_ADC_MEDIUM_GAIN2_0				29
#define BRAIN_ADC_FINE_GAIN2_0					30
#define BRAIN_ADC_SKEW2_0						31

#define BRAIN_ADC_COARSE_OFFSET2_180			32
#define BRAIN_ADC_FINE_OFFSET2_180				33
#define BRAIN_ADC_COARSE_GAIN2_180				34
#define BRAIN_ADC_MEDIUM_GAIN2_180				35
#define BRAIN_ADC_FINE_GAIN2_180				36
#define BRAIN_ADC_SKEW2_180						37


#define BRAIN_MAX_DAC_CTLS						38		// Total DAC controls
#define	BRAIN_CHAN2_DAC_CTRL					19


#define CSRB_EXTRIG_LEVEL_HIGH	10	// External trigger Level high
#define CSRB_EXTRIG_LEVEL_LOW	11	// External trigger Level low

#define BRAIN_DAC_SPAN			2048
#define BRAIN_ADC_REG_SPAN		255

typedef enum 
{
	eccNullOffset = 0,
	eccFEOffset   = eccNullOffset +1,
	eccPosition   = eccFEOffset + 1,
	eccAdcGain    = eccPosition + 1,
	eccAdcOffset  = eccAdcGain + 1,
}eRabbitCalCtrl;


typedef	struct _BrainiacAdcCalibInfo
{
	// ADC controls indexed
	uInt8	_CoarseOffset;
	uInt8	_CoarseOffsetB;
	uInt8	_FineOffset;
	uInt8	_FineOffsetB;
	uInt8	_CoarseGain;
	uInt8	_CoarseGainB;
	uInt8	_MedGain; 
	uInt8	_MedGainB; 
	uInt8	_FineGain;
	uInt8	_FineGainB;

	// ADC controls global
	uInt8	_Skew;

} BRAIN_ADC_CALIBINFO, *PBRAIN_ADC_CALIBINFO;


typedef	struct _BrainiacAdcCalibInfoEx
{
	BRAIN_ADC_CALIBINFO Adc0;
	BRAIN_ADC_CALIBINFO Adc90;
	BRAIN_ADC_CALIBINFO Adc180;
	BRAIN_ADC_CALIBINFO Adc270;

} BRAIN_ADC_CALIBINFO_EX, *PBRAIN_ADC_CALIBINFO_EX;


typedef	struct _DacCache
{
	uInt16	u16Value;			// Value of 
	BOOLEAN	bReadValid;			// Read back valid
} DAC_CACHE;

typedef	struct _BrainiacChanCalibInfo
{
	uInt16	_OffsetNull;
	uInt16	_OffsetComp;
	uInt16	_UserOffset;

	// DAC controls
	uInt16	_AdcDrvOffset_LowP;			// Lower phase 0 (Chan2) or 90 (Chan1)
	uInt16	_AdcDrvOffset_HiP;			// Higher phase 180 (Chan2) or 270 (Chan1)
	uInt16	_ClkPhaseOff_LowP;			// Lower phase 0 (Chan2) or 90 (Chan1)
	uInt16	_ClkPhaseOff_HiP;			// Higher phase 180 (Chan2) or 270 (Chan1)

	bool   bValid;
} BRAIN_CHANCALIBINFO, *PBRAIN_CHANCALIBINFO;


typedef	struct _BrainiacDacCalibCache
{
	DAC_CACHE	_OffsetNull;
	DAC_CACHE	_OffsetComp;
	DAC_CACHE	_UserOffset;

	// DAC controls
	DAC_CACHE	_AdcDrvOffset_LowP;			// Lower phase 0 (Chan2) or 90 (Chan1)
	DAC_CACHE	_AdcDrvOffset_HiP;			// Higher phase 180 (Chan2) or 270 (Chan1)
	DAC_CACHE	_ClkPhaseOff_LowP;			// Lower phase 0 (Chan2) or 90 (Chan1)
	DAC_CACHE	_ClkPhaseOff_HiP;			// Higher phase 180 (Chan2) or 270 (Chan1)

} BRAIN_CHANCALIBCACHE, *PBRAIN_CHANCALIBCACHE;



// Default Calibration values for Rabbit cards

#define	CSRB_DEFAULTCALIB_NULLOFFSET		2048
#define	CSRB_DEFAULTCALIB_FEOFFSET			2048
#define	CSRB_DEFAULTCALIB_GAIN				128
#define	CSRB_DEFAULTCALIB_ADCOFFSET			128
#define	CSRB_DEFAULTCALIB_POS				0


#define		BRAIN_MAX_SR_INDEX				21					// Max sample rate index


#define		CSRBCALIBINFO_CHECKSUM_VALID		0x12345678

typedef struct _BRAIN_CAL_INFO
{
	uInt32						u32Size;			// Size of this structure
	uInt32						u32Checksum;		// Checksum for valid table 

	uInt32						u32Valid;			// Which of following table is are valid
	BRAIN_CHANCALIBINFO			ChanCalibInfo[2][CSRB_MAX_RANGES];			// 2 channels
	BRAIN_ADC_CALIBINFO_EX		AdcCalInfo[CSRB_MAX_RANGES];				// Adc calib Single-Pinpong
	int8						i8TrigAddrOffsetAdjust[BRAIN_MAX_SR_INDEX][2];		// Reserve space for each sample rate
																		// and 2 mode (dual and single)
} BRAIN_CAL_INFO, *PBRAIN_CAL_INFO;


#define		DESCRIPTION_LENGTH		128
typedef struct _BRAIN_CALFILE_HEADER
{
	uInt32		u32Size;
	uInt8		u8Description[128];
	uInt32		u32Version;				// File Version
	uInt32		u32Checksum;			// TBD
	uInt32		u32BoardType;			// TBD

} BRAIN_CALFILE_HEADER, *PBRAIN_CALFILE_HEADER;


typedef struct _BRAIN_CALFILE
{
	BRAIN_CALFILE_HEADER	CalHdr;
	BRAIN_CAL_INFO			CalibTable;

} BRAIN_CALFILE, *PBRAIN_CALFILE;



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


#define	CSRB_CAL_ADC_VALID					0x80000000
#define	CSRB_CAL_ADC_INVALID				0x40000000
#define	CSRB_CAL_DAC_VALID					0x20000000
#define	CSRB_CAL_DAC_INVALID				0x10000000
#define	CSRB_CAL_CHAN_VALID					0x08000000
#define	CSRB_CAL_CHAN_INVALID				0x04000000
#define	CSRB_CAL_TRIG_ADDR_VALID			0x02800000
#define	CSRB_CAL_TRIG_ADDR_INVALID			0x01000000

#define	BRAIN_VALID_MASK					0xAAAAAAAA
#define	BRAIN_PRESERVE_MASK					0x55555555

#endif