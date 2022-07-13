#ifndef _DRV_CONST_H_
#define _DRV_CONST_H_

#include "CsDefines.h"
#include "CsTypes.h"
#include "CsStruct.h"
#include "CsErrors.h"


#define BAD_DEFAULT_FW		0x1
#define BAD_EXPERT1_FW		0x2
#define BAD_EXPERT2_FW		0x4	
#define BAD_CFG_BOOT_FW		0x8


#define ADDON_FIRMWARE      1
#define BASEBOARD_FIRMWARE  2
#define NVRAM_FIRMWARE      3

#define	CS_BASE8_OLDCORE_BOARDTYPE	0x200		// Base-8 Old core, will be obsolete
#define	CSHUSS_BOARDTYPE		CS_BASE8_OLDCORE_BOARDTYPE
#define	CSPLAY_BOARDTYPE		(CSHUSS_BOARDTYPE+1)

#define	CSBRAIN_BOARDTYPE		0x300


// External clock sample skip factor
#define	CS_SAMPLESKIP_FACTOR	1000

//----- Channel
#define CS_CHAN_1	1
#define CS_CHAN_2	2

#define CS_TRIG_ENGINES_1		1
#define CS_TRIG_ENGINES_2		2

//----- Input BNC/SMA: trigger input,channel inputs, constant to be used also the Gain
#define CS_INPUT_EXT_TRIG	0
#define CS_INPUT_CHANNEL	1

//----- Sample config
#define CS_SAMPLE_SIZE_1		1	//----- 1 bytes
#define CS_SAMPLE_SIZE_2		2	//----- 2 bytes
#define CS_SAMPLE_SIZE_4		4	//----- 4 bytes
#define CS_SAMPLE_BITS_8		8
#define CS_SAMPLE_BITS_12		12
#define CS_SAMPLE_BITS_14		14
#define CS_SAMPLE_BITS_16		16
#define CS_SAMPLE_BITS_32		32
 
// Sample Resolution
#define CS_SAMPLE_RES_8		0x80
#define CS_SAMPLE_RES_12	0x800
#define CS_SAMPLE_RES_14	0x2000
#define CS_SAMPLE_RES_16	0x8000
#define CS_SAMPLE_RES_LJ	0x8000
#define CS_SAMPLE_RES_32	0x80000000
#define CS_SAMPLE_RES_1220	1792			// Cs1220 has only 7/8 of the 12xx codes		

// Sample offset
#define CS_SAMPLE_OFFSET_8	          -1
#define CS_SAMPLE_OFFSET_12	          -1
#define CS_SAMPLE_OFFSET_14	          -1
#define CS_SAMPLE_OFFSET_16	          -1
#define CS_SAMPLE_OFFSET_32	          -1

#define CS_SAMPLE_OFFSET_8_LJ	      -1
#define CS_SAMPLE_OFFSET_12_LJ	      -16
#define CS_SAMPLE_OFFSET_14_LJ	      -4
#define CS_SAMPLE_OFFSET_16_LJ	      -1
#define CS_SAMPLE_OFFSET_32_LJ	      -1

#define CS_SAMPLE_OFFSET_UNSIGN_8	  0x7F
#define CS_SAMPLE_OFFSET_UNSIGN_12    0x7FF
#define CS_SAMPLE_OFFSET_UNSIGN_14    0x1FFF
#define CS_SAMPLE_OFFSET_UNSIGN_16    0x7FFF
#define CS_SAMPLE_OFFSET_UNSIGN_32    0x7FFFFFFF

#define CS_SAMPLE_OFFSET_UNSIGN_8_LJ  0x7F
#define CS_SAMPLE_OFFSET_UNSIGN_12_LJ 0x7FF0
#define CS_SAMPLE_OFFSET_UNSIGN_14_lJ 0x7FF0
#define CS_SAMPLE_OFFSET_UNSIGN_16_LJ 0x7FFF
#define CS_SAMPLE_OFFSET_UNSIGN_32_LJ 0x7FFFFFFF



//----- Sample Rate
#define CS_SR_6GHZ		6000000000
#define CS_SR_4GHZ		4000000000
#define CS_SR_3GHZ		3000000000
#define CS_SR_2GHZ		2000000000
#define CS_SR_1p5GHZ	1500000000
#define CS_SR_1GHZ		1000000000
#define CS_SR_500MHZ	500000000
#define CS_SR_420MHZ	420000000
#define CS_SR_400MHZ	400000000
#define CS_SR_250MHZ	250000000
#define CS_SR_210MHZ	210000000
#define CS_SR_200MHZ	200000000
#define CS_SR_160MHZ	160000000
#define CS_SR_125MHZ	125000000
#define CS_SR_105MHZ	105000000
#define CS_SR_100MHZ	100000000
#define CS_SR_80MHZ		80000000
#define CS_SR_75MHZ		750000000
#define CS_SR_65MHZ		65000000
#define CS_SR_50MHZ		50000000
#define CS_SR_40MHZ		40000000
#define CS_SR_25MHZ		25000000
#define CS_SR_20MHZ		20000000
#define CS_SR_10MHZ		10000000
#define CS_SR_5MHZ		5000000
#define CS_SR_2500KHZ	2500000
#define CS_SR_2MHZ		2000000
#define CS_SR_1MHZ		1000000
#define CS_SR_500KHZ	500000
#define CS_SR_250KHZ	250000
#define CS_SR_200KHZ	200000
#define CS_SR_100KHZ	100000
#define CS_SR_50KHZ		50000
#define CS_SR_25KHZ		25000
#define CS_SR_20KHZ		20000
#define CS_SR_10KHZ		10000
#define CS_SR_8KHZ		8000
#define CS_SR_5KHZ		5000
#define CS_SR_2500HZ	2500
#define CS_SR_2KHZ		2000
#define CS_SR_1KHZ		1000

//----- External Sample Rate: MIN and MAX
#define CS_EXT_CLK	-1

//----- Impedance, constant to be used also for the Gain	//not for USER
#define CS_IMP_1M_OHM		0x1
#define	CS_IMP_50_OHM		0x2
#define CS_IMP_EXT_TRIG		0x4
#define	CS_IMP_DIRECT_ADC	0x8
#define	CS_IMP_HiZ			0x10

//----- Trigger Level		12bits engine //NOT FOR USER
#define CS_TRIG_LEVEL_MAX	0x7ff
#define CS_TRIG_LEVEL_MIN	0x0



//----- Limit of Hw Dept counter of the current Base board Firmware
#define CSMV_LIMIT_HWDEPTH_COUNTER 	0x20000000				//	29 bits of counter for 128 bit words

//----- Minimum Segment size
#define CSMV_MIN_SEG_SIZE	8

// Amount of memory in bytes at the end of each record that HW reserved to store ETBs
#define	BYTESRESERVED_HWMULREC_TAIL				32


// Invalid samples at the end of posttrigger data because of FIFO continuous read
// This number will change accross the sample rate ( +/- 1, 2 samples )
// The value is the maximum and works on all sample rates
// The value will be double in Single mode
// Should be a power of 2
#define	MAX_TAIL_INVALID_SAMPLES			32

// Assume the Max trigger address offset
// This value will be used in calculation for ensuring the postrigger depth
// In order to simplify calculation for both Single and Dual mode, this value should be power of 4
#define MAX_TRIGGER_ADDRESS_OFFSET			32


//
// Private base board Hardware or Firmware options
//

#define	CS_OPTION_BIT_0			    0x1	
#define	CS_OPTION_BIT_1				0x2	
#define	CS_OPTION_BIT_2				0x4	
#define	CS_OPTION_BIT_3				0x8	
#define	CS_OPTION_BIT_4				0x10	
#define	CS_OPTION_BIT_5				0x20	
#define	CS_OPTION_BIT_6				0x40	
#define	CS_OPTION_BIT_7				0x80	
#define	CS_OPTION_BIT_8				0x100	
#define	CS_OPTION_BIT_9				0x200	
#define	CS_OPTION_BIT_10			0x400	
#define	CS_OPTION_BIT_11			0x800	
#define	CS_OPTION_BIT_12			0x1000	
#define	CS_OPTION_BIT_13			0x2000	
#define	CS_OPTION_BIT_14			0x4000	
#define	CS_OPTION_BIT_15			0x8000	
#define	CS_OPTION_BIT_16			0x10000	
#define	CS_OPTION_BIT_17			0x20000	
#define	CS_OPTION_BIT_18			0x40000	
#define	CS_OPTION_BIT_19			0x80000	
#define	CS_OPTION_BIT_20			0x100000	
#define	CS_OPTION_BIT_21			0x200000	
#define	CS_OPTION_BIT_22			0x400000	
#define	CS_OPTION_BIT_23			0x800000	
#define	CS_OPTION_BIT_24			0x1000000	
#define	CS_OPTION_BIT_25			0x2000000	
#define	CS_OPTION_BIT_26			0x4000000	
#define	CS_OPTION_BIT_27			0x8000000	
#define	CS_OPTION_BIT_28			0x10000000	
#define	CS_OPTION_BIT_29			0x20000000	
#define	CS_OPTION_BIT_30			0x40000000	
#define	CS_OPTION_BIT_31			0x80000000

#define CS_OUT_NONE                 0x0001
// clk out
#define CS_CLKOUT_SAMPLE            0x0002
#define CS_CLKOUT_REF               0x0004
#define CS_CLKOUT_GBUS              0x0008
//trig out mode
#define CS_TRIGOUT_MODE             0x0001
#define CS_PULSEOUT_MODE            0x0002
#define CS_EXTTRIG_EN_MODE          0x0004
#define CS_TS_RESET_MODE            0x0008

// Trig out & pulse out
#define CS_TRIGOUT                  0x0002
#define CS_PULSEOUT_DATAVALID       0x0004
#define CS_PULSEOUT_NOT_DATAVALID   0x0008
#define CS_PULSEOUT_START_DATAVALID 0x0010
#define CS_PULSEOUT_END_DATAVALID   0x0020
#define CS_PULSEOUT_SYNC            0x0040
//Ext trig enable
#define CS_EXTTRIGEN_LIVE           0x0002
#define CS_EXTTRIGEN_POS_LATCH      0x0004
#define CS_EXTTRIGEN_NEG_LATCH      0x0008
#define CS_EXTTRIGEN_POS_LATCH_ONCE 0x0010
#define CS_EXTTRIGEN_NEG_LATCH_ONCE 0x0020

#define CS_AUXIN_TS_RESET           0x0008

#endif   // _DRV_CONST_H_

