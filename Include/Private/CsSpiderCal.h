//! CsSpiderCal.h
//!
//!

#ifndef __CsSpiderCal_h__
#define __CsSpiderCal_h__

#include "Cs8xxxCapsInfo.h"

// SEND_DAC
// DAC Id and Address for SPIDER cards
#define CSPSR_AD7552_ID			0		// Dac Id (AD75552)

#define	CSPDR_POSITION_1		0		// Channel 1 user offset (Coarse)
#define	CSPDR_POSITION_2		1		// Channel 2 user offset (Coarse)
#define	CSPDR_POSITION_3		2		// Channel 3 user offset (Coarse)
#define	CSPDR_POSITION_4		3		// Channel 4 user offset (Coarse)
#define	CSPDR_POSITION_5		4		// Channel 5 user offset (Coarse)
#define	CSPDR_POSITION_6		5		// Channel 6 user offset (Coarse)
#define	CSPDR_POSITION_7		6		// Channel 7 user offset (Coarse)
#define	CSPDR_POSITION_8		7		// Channel 8 user offset (Coarse)
#define	CSPDR_VCALFINE_1		8		// Channel 1 Vcal (Fine)
#define	CSPDR_VCALFINE_2		9		// Channel 2 Vcal (Fine)
#define	CSPDR_VCALFINE_3		10		// Channel 3 Vcal (Fine)
#define	CSPDR_VCALFINE_4		11		// Channel 4 Vcal (Fine)
#define	CSPDR_VCALFINE_5		12		// Channel 5 Vcal (Fine)
#define	CSPDR_VCALFINE_6		13		// Channel 6 Vcal (Fine)
#define	CSPDR_VCALFINE_7		14		// Channel 7 Vcal (Fine)
#define	CSPDR_VCALFINE_8		15		// Channel 8 Vcal (Fine)
#define	CSPDR_CAL_GAIN_1		16		// Channel 1 Calib Gain
#define	CSPDR_CAL_GAIN_2		17		// Channel 2 Calib Gain
#define	CSPDR_CAL_GAIN_3		18		// Channel 3 Calib Gain
#define	CSPDR_CAL_GAIN_4		19		// Channel 4 Calib Gain
#define	CSPDR_CAL_GAIN_5		20		// Channel 5 Calib Gain
#define	CSPDR_CAL_GAIN_6		21		// Channel 6 Calib Gain
#define	CSPDR_CAL_GAIN_7		22		// Channel 7 Calib Gain
#define	CSPDR_CAL_GAIN_8		23		// Channel 8 Calib Gain
#define	CSPDR_EXTRIG_POSITION	24		// External Triggger Offset
#define CSPDR_EXTRIG_LEVEL		25		// External trigger Level
#define	CSPDR_CAL_VA            26
#define	CSPDR_CAL_VB            27
#define	CSPDR_CAL_CODE          28
#define CSPDR_CAL_REF           29
#define CSPDR_MAX_DAC_CTLS		30		// Total DAC controls



#define		CSPDR_MAX_FE_INDEX		24				// Max Front End index 
#define		CSPDR_MAX_SR_INDEX		21				// Max sample rate index

typedef struct _FRONTEND_SPIDER_DAC_INFO
{
	uInt16	u16Gain;
	uInt16	u16FineOffset;
	uInt16	u16CoarseOffset;
	uInt16	u16CodeDeltaForHalfIR;
	BOOLEAN bCalibrated;
}FRONTEND_SPIDER_DAC_INFO, *PFRONTEND_SPIDER_DAC_INFO;

typedef struct _CSPDR_CAL_INFO
{
	uInt32		u32Valid;
	FRONTEND_SPIDER_DAC_INFO DacInfo[CSPDR_CHANNELS][CSPDR_MAX_FE_SET_INDEX][CSPDR_MAX_RANGES];

} CSPDR_CAL_INFO, *PCSPDR_CAL_INFO;


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
	CSPDR_CAL_INFO		CalibTable;

} CALFILE, *PCALFILE;

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


#define	CSPDR_CAL_DAC_VALID					0x80000000
#define	CSPDR_CAL_DAC_INVALID					0x40000000
#define	CSPDR_CAL_CHAN_VALID					0x20000000
#define	CSPDR_CAL_CHAN_INVALID					0x10000000
#define	CSPDR_CAL_DELAY_VALID					0x08000000
#define	CSPDR_CAL_DELAY_INVALID				0x04000000
#define	CSPDR_CAL_TRIG_LEVEL_VALID				0x02000000
#define	CSPDR_CAL_TRIG_LEVEL_INVALID			0x01000000
#define	CSPDR_CAL_TRIG_ADDR_VALID				0x00800000
#define	CSPDR_CAL_TRIG_ADDR_INVALID			0x00400000
#define	CSPDR_CAL_TRIG_GAIN_VALID				0x00200000
#define	CSPDR_CAL_TRIG_GAIN_INVALID			0x00100000
#define	CSPDR_CAL_EXTCLK_TRIG_ADDR_VALID		0x00080000
#define	CSPDR_CAL_EXTCLK_TRIG_ADDR_INVALID		0x00040000
#define	CSPDR_CAL_DIFFERENTIAL_VALID  			0x00020000
#define	CSPDR_CAL_DIFFERENTIAL_INVALID		 	0x00010000

#define	CSPDR_VALID_MASK						0xAAAAAAAA
#define	CSPDR_PRESERVE_MASK					0x55555555
#define CSPDR_CAL_TRIGGER_GAIN_FACTOR			1000
#define CSPDR_DEFAULT_TRIGGER_GAIN				1200

#define CSPDR_FINE_DELAY_SEED				5
#define CSPDR_COARSE_DELAY_SEED			5
#define CSPDR_COARSE_DELAY_SPAN			5

#define CSPDR_IMAGE_WINDOW_SIZE			5
#define CSPDR_FFT_ITERATIONS				10

#define CSPDR_DELAY_LINE_SPAN			63
#define CSPDR_DELAY_FINE_COARSE_RATIO	37

#define CSPDR_CLOCK_SKEW_STEP			6
#define CSPDR_MAX_CLOCK_SKEW			    (CSPDR_DELAY_LINE_SPAN - 3 * CSPDR_COARSE_DELAY_SPAN)


#define CSPDR_DAC_SPAN					   2048

#endif