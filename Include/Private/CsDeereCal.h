//! CsDeereCal.h
//!
//!

#ifndef __CsDeereCal_h__
#define __CsDeereCal_h__

//
// To control from Dynamic Analysis
// Dac Id =  0 or 1.    ===> ADC Core select
// Dac Address = 0 to 36
//
//
// Channel 1 DAC controls
//  Dac Id
//	0		==> DEERE_OFFSET_NULL_1
//	1		==> DEERE_OFFSET_COMP_1
//	2		==> DEERE_USER_OFFSET_1
//	3		==> DEERE_CLKPHASE_0
//	4		==> DEERE_CLKPHASE_2
//	5		==> DEERE_ADC_COARSE_OFFSET (ADC 0)
//	6		==> DEERE_ADC_FINE_OFFSET (ADC 0)
//	7		==> DEERE_ADC_COARSE_GAIN (ADC 0)
//	8		==> DEERE_ADC_MEDIUM_GAIN (ADC 0)
//	9		==> DEERE_ADC_FINE_GAIN (ADC 0)
//	10		==> DEERE_ADC_SKEW (ADC 0)
//	11		==> DEERE_ADC_COARSE_OFFSET (ADC 2)
//	12		==> DEERE_ADC_FINE_OFFSET (ADC 2)
//	13		==> DEERE_ADC_COARSE_GAIN (ADC 2)
//	14		==> DEERE_ADC_MEDIUM_GAIN (ADC 2)
//	15		==> DEERE_ADC_FINE_GAIN (ADC 2)
//	16		==> DEERE_ADC_SKEW (ADC 2)

// Channel 2 DAC controls
//  Dac Id
//	17		==> DEERE_OFFSET_NULL_2	
//	18		==> DEERE_OFFSET_COMP_2
//	19		==> DEERE_USER_OFFSET_2
//	20		==> DEERE_CLKPHASE_1
//	21		==> DEERE_CLKPHASE_3
//	22		==> DEERE_ADC_COARSE_OFFSET (ADC 1)
//	23		==> DEERE_ADC_FINE_OFFSET (ADC 1)
//	24		==> DEERE_ADC_COARSE_GAIN (ADC 1)
//	25		==> DEERE_ADC_MEDIUM_GAIN (ADC 1)
//	26		==> DEERE_ADC_FINE_GAIN (ADC 1)
//	27		==> DEERE_ADC_SKEW (ADC 1)
//	28		==> DEERE_ADC_COARSE_OFFSET (ADC 3)
//	29		==> DEERE_ADC_FINE_OFFSET (ADC 3)
//	30		==> DEERE_ADC_COARSE_GAIN (ADC 3)
//	31		==> DEERE_ADC_MEDIUM_GAIN (ADC 3)
//	32		==> DEERE_ADC_FINE_GAIN (ADC 3)
//	33		==> DEERE_ADC_SKEW (ADC 3)



// SEND_DAC
// DAC Control Id and Address for JohnDeere cards

#define DEERE_ADC_COARSE_OFFSET				    0
#define DEERE_ADC_FINE_OFFSET					1
#define DEERE_ADC_COARSE_GAIN					2
#define DEERE_ADC_MEDIUM_GAIN					3
#define DEERE_ADC_FINE_GAIN						4
#define DEERE_ADC_SKEW							5

// Channel 1 DAC controls
#define DEERE_OFFSET_NULL_1						0
#define DEERE_OFFSET_COMP_1						1
#define DEERE_USER_OFFSET_1						2	
#define DEERE_CLKPHASE_0						3
#define DEERE_CLKPHASE_2						4

// Channel 1 ADC controls
#define DEERE_ADC_BASE_0	        			5
#define DEERE_ADC_BASE_2	        			11

// Channel 2 DAC controls
#define DEERE_OFFSET_NULL_2						17
#define DEERE_OFFSET_COMP_2						18
#define DEERE_USER_OFFSET_2						19
#define DEERE_CLKPHASE_1						20	
#define DEERE_CLKPHASE_3						21

// Channel 2 ADC controls
#define DEERE_ADC_BASE_1	        			22
#define DEERE_ADC_BASE_3	        			28

#define	DEERE_MS_CLK_PHASE_ADJ					34	
#define DEERE_EXTRIG_LEVEL	                    35	
#define DEERE_EXTRIG_OFFSET	                    36	


#define DEERE_U_OFF_SCALE_1                     101  //Not a DAC address
#define DEERE_U_OFF_SCALE_2                     102  //Not a DAC address
#define DEERE_U_OFF_CENTR_1                     103  //Not a DAC address
#define DEERE_U_OFF_CENTR_2                     104  //Not a DAC address
#define DEERE_IR_SCALE_1                        105  //Not a DAC address
#define DEERE_IR_SCALE_2                        106  //Not a DAC address


#define DEERE_R_COUNT                           60  //Not a DAC address
#define DEERE_N_COUNT                           61  //Not a DAC address
#define DEERE_AC_ATTEN                          62  //Not a DAC address
#define DEERE_EXT_TRIG_SHIFT                    63  //Not a DAC address
#define DEERE_ADC_CORRECTION                    64  //Not a DAC address


#define DEERE_MAX_DAC_CTLS						36	// Total DAC and ADC controls
#define	DEERE_CHAN2_DAC_CTRL					17

#define DEERE_MAX_CAL_ITER                      30
#define DEERE_NULL_OFFSET_ERROR                 20  // µV


typedef	struct _DeereAdcCalibInfo
{
	// ADC controls indexed per core
	uInt8	_CoarseOffsetA;
	uInt8	_CoarseOffsetB;
	uInt8	_FineOffsetA;
	uInt8	_FineOffsetB;
	uInt8	_CoarseGainA;
	uInt8	_CoarseGainB;
	uInt8	_MedGainA; 
	uInt8	_MedGainB; 
	uInt8	_FineGainA;
	uInt8	_FineGainB;

	// ADC controls global
	uInt8	_Skew;
} DEERE_ADC_CALIBINFO, *PDEERE_ADC_CALIBINFO;


typedef	struct _DeereAdcCalibInfoEx
{
	DEERE_ADC_CALIBINFO Adc0;
	DEERE_ADC_CALIBINFO Adc90;
	DEERE_ADC_CALIBINFO Adc180;
	DEERE_ADC_CALIBINFO Adc270;

} DEERE_ADC_CALIBINFO_EX, *PDEERE_ADC_CALIBINFO_EX;


typedef	struct _DeereChanCalibInfo
{
	uInt16	_OffsetNull;
	uInt16	_OffsetComp;
	uInt16	_UserOffset;
	int16	_UserOffsetScale;
	uInt16  _UserOffsetCentre;
	uInt16  _InputRangeScale;
	uInt16	_AdcDrvOffset_LoP;			// Lower phase 0 (Chan2) or 90 (Chan1)
	uInt16	_AdcDrvOffset_HiP;			// Higher phase 180 (Chan2) or 270 (Chan1)
	uInt16	_ClkPhaseOff_LoP;			// Lower phase 0 (Chan2) or 90 (Chan1)
	uInt16	_ClkPhaseOff_HiP;			// Higher phase 180 (Chan2) or 270 (Chan1)
	uInt16  _RefPhaseOff;               // Reference clock phase adjustment
	BOOLEAN   bValid;
} DEERE_CHANCALIBINFO, *PDEERE_CHANCALIBINFO;

#define DEERE_IR_SCALE_FACTOR              0x4000

// Default Calibration values for JohnDeere cards
#define	DEERE_CALIB_TIMEOUT_SHORT KTIME_MILISEC(300)
#define	DEERE_CALIBMS_TIMEOUT     KTIME_SECOND(2)

#define	DEERECALIBINFO_CHECKSUM_VALID		0x12345678

#define DEERE_PULSE_CAL_DC_OFFSET           -50 //mV
#define DEERE_EXT_TRIG_DELAY_1M              -5 //ns 
#define DEERE_EXT_TRIG_DELAY_50              -4 //ns 

typedef struct _DEERE_CAL_INFO
{
	uInt32						u32Size;			// Size of this structure
	uInt32						u32Checksum;		// Checksum for valid table 

	uInt32						u32Valid;			// Which of following table is are valid
	DEERE_CHANCALIBINFO			ChanCalibInfo[DEERE_CHANNELS][DEERE_MAX_RANGES];			// 2 channels
	DEERE_ADC_CALIBINFO		    AdcCalInfo[DEERE_ADC_COUNT][DEERE_MAX_RANGES];				// Adc calib Single-Pinpong
	int8						i8TrigAddrOffsetAdjust[DEERE_MAX_SR_COUNT][DEERE_MODE_COUNT];		// Reserve space for each sample rate
																		// and 2 mode (dual and single)
} DEERE_CAL_INFO, *PDEERE_CAL_INFO;


#define		DESCRIPTION_LENGTH		128
typedef struct _DEERE_CALFILE_HEADER
{
	uInt32		u32Size;
	uInt8		u8Description[128];
	uInt32		u32Version;				// File Version
	uInt32		u32Checksum;			// TBD
	uInt32		u32BoardType;			// TBD

} DEERE_CALFILE_HEADER, *PDEERE_CALFILE_HEADER;


typedef struct _DEERE_CALFILE
{
	DEERE_CALFILE_HEADER	CalHdr;
	DEERE_CAL_INFO			CalibTable;

} DEERE_CALFILE, *PDEERE_CALFILE;



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


#define	DEERE_CAL_ADC_VALID					0x80000000
#define	DEERE_CAL_ADC_INVALID				0x40000000
#define	DEERE_CAL_DAC_VALID					0x20000000
#define	DEERE_CAL_DAC_INVALID				0x10000000
#define	DEERE_CAL_CHAN_VALID				0x08000000
#define	DEERE_CAL_CHAN_INVALID				0x04000000
#define	DEERE_CAL_TRIG_ADDR_VALID			0x02800000
#define	DEERE_CAL_TRIG_ADDR_INVALID			0x01000000
#define	DEERE_VALID_MASK					0xAAAAAAAA
#define	DEERE_PRESERVE_MASK					0x55555555

#define DEERE_CALREF0		    4096
#define DEERE_CALREF1		    2048
#define DEERE_CALREF2		    1024
#define DEERE_CALREF3		       0
#define DEERE_MAX_CALREF_ERR_C  50
#define DEERE_MAX_CALREF_ERR_P   5
#define DEERE_POS_CAL_LEVEL      1
#define DEERE_GND_CAL_LEVEL      0
#define DEERE_NEG_CAL_LEVEL     -1

#define TRACE_NULL_OFFSET      0x00000001 //Trace of the offset nulling
#define TRACE_CAL_FE_OFFSET    0x00000002 //Fine offset setting
#define TRACE_CAL_GAIN         0x00000004 //Gain offset settings
#define TRACE_CAL_POS          0x00000008 //Position calibration settings

#define TRACE_CAL_SIGNAL       0x00000010 //Trace final result of calibration signal DAC
#define TRACE_CAL_DAC          0x00000020 //Trace access to All calibration DACs
#define TRACE_CAL_RESULT       0x00000040 //Trace result of failed calibration if we go on
#define TRACE_CAL_SIG_MEAS     0x00000080 //Trace  of the calibration ADC reading

#define TRACE_VERB             0x00000100 //Trace final result of calibration signal DAC verbose
#define TRACE_CAL_INPUT        0x00000200 //Trace calibration input connection
#define TRACE_ADC_REG          0x00000400 //Trace access to All calibration registers of ADC
#define TRACE_ADC_CORE_ORDER   0x00000800 //Trace order of ADC core on the bus

#define TRACE_CAL_PROGRESS     0x00001000 //Trace calibration progress
#define TRACE_CAL_MS	       0x00002000 //Trace Master/Slave TrigAddr Offset calibration
#define TRACE_CAL_EXTTRIG	   0x00004000 //Trace Ext trigger Offset calibration
#define TRACE_CAL_ADCALIGN	   0x00008000 //Trace Adc Align calibration

#define TRACE_MS_BIST_TEST	   0x00010000 //Trace M/S Built in Self Test
#define TRACE_ADC_REG_DIR      0x00020000 //Trace Direct Access to the ADC
#define TRACE_CONF_4360        0x00040000 //Trace configuration override for 4360
#define TRACE_EXTTRIG_LEVEL    0x00080000 //Trace configuration of extternal trigger level

#define TRACE_MATCH_OFF_MED    0x00100000 //Trace matching the offset
#define TRACE_MATCH_OFF_FINE   0x00200000 //Trace matching the adc gain
#define TRACE_MATCH_GAIN_MED   0x00400000 //Trace matching the offset
#define TRACE_MATCH_GAIN_FINE  0x00800000 //Trace matching the adc gain

#define TRACE_ADC_MATCH        0x01000000 //Trace results of adc core matching
#define TRACE_CORE_SKEW_MATCH  0x02000000 //Trace matching of the core skew
#define TRACE_ADC_PHASE_MATCH  0x04000000 //Trace matching of the Adc skew
#define TRACE_CORE_SKEW_MEAS   0x08000000 //Trace core skew measurment

#define TRACE_CAL_SCALE_GAIN   0x10000000 //Trace dynamic target gain adjustments
#define TRACE_RES_20000000     0x20000000 //Trace reserved
#define TRACE_FINAL_RESULT     0x40000000 //Trace final calibration result
#define TRACE_USAGE            0x80000000 //Trace usage


#define	DEERE_ACTION_PRE_COMMIT			1			// Pre commit - Change Kernel mode HW settings
#define	DEERE_ACTION_CALIB				2			// User mode  DLL calibration settings 
#define	DEERE_ACTION_COMMIT				3			// Final commit

#endif