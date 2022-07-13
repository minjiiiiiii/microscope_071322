//! CsHexagonCal.h
//!
//!

#ifndef __CsHexagonCal_h__
#define __CsHexagonCal_h__

#include "CsHexagonCapsInfo.h"


#define HEXAGON_DAC_SPAN				2048
#define HEXAGON_ADC_REG_SPAN			255
#define HEXAGON_ADC_COARSE_SPAN		7
#define HEXAGON_ADC_FINE_SPAN	    511


// SEND_DAC
// DAC Id and Address for HEXAGON cards
#define CSPSR_AD7552_ID			0		// Dac Id (AD75552)

#define	HEXAGON_POSITION_1		0		// Channel 1 user offset (Coarse)
#define	HEXAGON_POSITION_2		1		// Channel 2 user offset (Coarse)
#define	HEXAGON_POSITION_3		2		// Channel 3 user offset (Coarse)
#define	HEXAGON_POSITION_4		3		// Channel 4 user offset (Coarse)

#define	HEXAGON_VCALFINE_1		8		// Channel 1 Vcal (Fine)
#define	HEXAGON_VCALFINE_2		9		// Channel 2 Vcal (Fine)
#define	HEXAGON_VCALFINE_3		10		// Channel 3 Vcal (Fine)
#define	HEXAGON_VCALFINE_4		11		// Channel 4 Vcal (Fine)

#define	HEXAGON_CAL_GAIN_1		16		// Channel 1 Calib Gain
#define	HEXAGON_CAL_GAIN_2		17		// Channel 2 Calib Gain
#define	HEXAGON_CAL_GAIN_3		18		// Channel 3 Calib Gain
#define	HEXAGON_CAL_GAIN_4		19		// Channel 4 Calib Gain

#define	HEXAGON_EXTRIG_POSITION	24		// External Triggger Offset
#define HEXAGON_EXTRIG_LEVEL	25		// External trigger Level
#define HEXAGON_MAX_DAC_CTLS	30		// Total DAC controls


#define HEXAGON_TRIM_CAP_50_CHAN1 32    //Var Cap
#define HEXAGON_TRIM_CAP_50_CHAN2 33    //Var Cap
#define HEXAGON_TRIM_CAP_50_CHAN3 34    //Var Cap
#define HEXAGON_TRIM_CAP_50_CHAN4 35    //Var Cap

#define HEXAGON_TRIM_CAP_10_CHAN1 36    //Var Cap
#define HEXAGON_TRIM_CAP_10_CHAN2 37    //Var Cap
#define HEXAGON_TRIM_CAP_10_CHAN3 38    //Var Cap
#define HEXAGON_TRIM_CAP_10_CHAN4 39    //Var Cap


#define		HEXAGON_MAX_FE_INDEX		24				// Max Front End index
#define		HEXAGON_MAX_SR_INDEX		21				// Max sample rate index

typedef struct _FRONTEND_HEXAGON_DAC_INFO
{
	uInt16 u16Gain;
	uInt16 u16FineOffset;
	uInt16 u16CoarseOffset;
	uInt16 u16CodeDeltaForHalfIR;
	double fVoltOff;
	BOOLEAN bCalibrated;
}FRONTEND_HEXAGON_DAC_INFO, *PFRONTEND_HEXAGON_DAC_INFO;

typedef struct _HEXAGON_CAL_INFO
{
	uInt32		u32Valid;
	uInt32		u32Checksum;
	uInt32		u32Active;
	FRONTEND_HEXAGON_DAC_INFO DacInfo[HEXAGON_CHANNELS][HEXAGON_MAX_FE_SET_INDEX][HEXAGON_MAX_RANGES];
	uInt32      u32FrontPortResistance_mOhm[HEXAGON_CHANNELS];
	uInt16		u16GainTgFactor[HEXAGON_CHANNELS][HEXAGON_MAX_RANGES][HEXAGON_IMPED][HEXAGON_FILTERS];
	uInt16      u16TrimCap[HEXAGON_CHANNELS][HEXAGON_MAX_RANGES];

} CSHEXAGON_CAL_INFO, *PCSHEXAGON_CAL_INFO;


typedef enum
{
	ecdOffset = 0,
	ecdPosition = ecdOffset + 1,
	ecdGain  = ecdPosition + 1,
}eCalDacId;

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


#define	HEXAGON_CAL_INFO_VALID					0x80000000
#define	HEXAGON_CAL_INFO_INVALID				0x40000000
#define	HEXAGON_CAL_USAGE_VALID					0x20000000
#define	HEXAGON_CAL_USAGE_INVALID				0x10000000
#define	HEXAGON_CAL_PORT_RESISTANCE_VALID		0x08000000
#define	HEXAGON_CAL_PORT_RESISTANCE_INVALID		0x04000000
#define	HEXAGON_CAL_TARGETFACTOR_VALID			0x02000000
#define	HEXAGON_CAL_TARGETFACTOR_INVALID		0x01000000
#define	HEXAGON_CAL_VARCAP_VALID    			0x00800000
#define	HEXAGON_CAL_VARCAP_INVALID		        0x00400000


#define	HEXAGON_VALID_MASK						0xAAAAAAAA
#define	HEXAGON_PRESERVE_MASK					0x55555555
#define HEXAGON_CAL_TRIGGER_GAIN_FACTOR			1000
#define HEXAGON_DEFAULT_TRIGGER_GAIN			HEXAGON_CAL_TRIGGER_GAIN_FACTOR
#define HEXAGON_DEFAULT_TRIG_ADDR_OFF   			-2
#define HEXAGON_DEFAULT_TRIG_ADDR_OFF_SINGLE		-4

#define HEXAGON_DAC_SPAN						2048
#define HEXAGON_DEFAULT_PORT_RESISTANCE_1	    145
#define HEXAGON_DEFAULT_PORT_RESISTANCE_REST	130

#define HEXAGON_DEFAULT_GAINTARGET_FACTOR		8192

#endif
