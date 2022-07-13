#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "CsTypes.h"
//----------------------------------------------------------
//	CompuScope EEPROM size and structure definitions.	

#define	EEPROM_SIGNATURE	"GAGE"

#define	DEFAULT_BOARD_EEPROM_VER_2125	0x0130
#define	DEFAULT_HWATI_EEPROM_VER_2125	0x0130
#define	DEFAULT_HWMEM_EEPROM_VER_2125	0x0121

#define	DEFAULT_BOARD_EEPROM_VER_8012	0x0300
#define	DEFAULT_HWATI_EEPROM_VER_8012	0x0000
#define	DEFAULT_HWMEM_EEPROM_VER_8012	0x0000

#define	DEFAULT_BOARD_EEPROM_VER_82G	0x0130	//nat070700
#define	DEFAULT_BOARD_EEPROM_VER_3200	0x0300	//nat040101

#define	DEFAULT_BOARD_EEPROM_VER_121X0	0x0110
#define	DEFAULT_HWATI_EEPROM_VER_121X0	0x0000
#define	DEFAULT_HWMEM_EEPROM_VER_121X0	0x0000

#define CS_EEPROM_REGISTERS_1024		64
#define CS_EEPROM_REGISTERS_4096		256
#define CS_EEPROM_REGISTERS_16384		1024


#define	CS_EEPROM_VALID_SIZE(size)			(((size) == (CS_EEPROM_REGISTERS_16384 << 4)) || ((size) == (CS_EEPROM_REGISTERS_4096 << 4)) || ((size) == (CS_EEPROM_REGISTERS_1024 << 4)))
#define	CS_EEPROM_VALID_SIZE_EXT_1(size)	(((size) == (CS_EEPROM_REGISTERS_16384 << 4)) || ((size) == (CS_EEPROM_REGISTERS_4096 << 4)))
#define	CS_EEPROM_VALID_SIZE_EXT_2(size)	(((size) == (CS_EEPROM_REGISTERS_16384 << 4)))

#define	CS_EEPROM_VALID_REGISTERS(eeprom_registers)	((eeprom_registers == CS_EEPROM_REGISTERS_16384) || (eeprom_registers == CS_EEPROM_REGISTERS_4096) || (eeprom_registers == CS_EEPROM_REGISTERS_1024))
#define	CS_EEPROM_REGISTERS_SUPPORTED	CS_EEPROM_REGISTERS_16384


//----------------------------------------------------------

//	EEPROM indexes, these are in units of uInt16's.  This is how the EEPROM is organized.	

#define EEPROM_INDEX_SIGNATURE				0	//	NOT null terminated.	
#define EEPROM_INDEX_SIZE					2	//	Size of EEPROM in BITS.	
#define EEPROM_INDEX_BOARD_TYPE				3	//	Encoded board types from GAGE_DRV.H.	
#define EEPROM_INDEX_VERSION				4	//	BCD, XX.XX.	
#define EEPROM_INDEX_MEMORY_SIZE			5	//	Decimal (in kilobytes).	
#define EEPROM_INDEX_SERIAL_NUMBER			6	//	BCD, right-justified w/leading zeros.	
#define EEPROM_INDEX_OPTIONS				8	//	BIT encoded (see EEPROM_OPTIONS_XXXXXXXX).	
#define EEPROM_INDEX_A_RANGES				10	//	Default calibration values (all bits set if not supported).	
#define EEPROM_INDEX_A_OFFSETS				17	//	Default calibration values (all bits set if not supported).	
#define EEPROM_INDEX_B_RANGES				24	//	Default calibration values (all bits set if not supported).	
#define EEPROM_INDEX_B_OFFSETS				31	//	Default calibration values (all bits set if not supported).	
#define EEPROM_INDEX_POWER_ON_VALUE			38	//	Time in 0.1 mSecs for power on delay.	
#define EEPROM_INDEX_HW_ATI_VERSION			39	//	BCD, XX.XX.	
#define EEPROM_INDEX_HW_MEM_VERSION			40	//	BCD, XX.XX.	
#define EEPROM_INDEX_HW_ETS_VERSION			41	//	BCD, XX.XX.	
#define EEPROM_INDEX_ETS_OFFSET				42	//	Decimal.	
#define EEPROM_INDEX_ETS_CORRECT			43	//	Decimal.	
#define EEPROM_INDEX_ETS_TRIGGER_OFFSET		44	//	Decimal.	
#define EEPROM_INDEX_TRIG_LEVEL_OFF			45	//	2 x uInt8, actually Decimal.	
#define EEPROM_INDEX_TRIG_LEVEL_SCALE		46	//	2 x uInt8, actually Decimal.	
#define EEPROM_INDEX_TRIG_ADDR_OFF			47	//	uInt4, 16 values in 4 words (layed out linearly -> 0,1,2,3 4,5,6,7 8,9,10,11 12,13,14,15) or	
												//	uInt8,  8 values in 4 words (layed out linearly -> 0,1 2,3 4,5 6,7).	
#define EEPROM_INDEX_A_RANGE_50				51	//	Default calibration values (all bits set if not supported).	
#define EEPROM_INDEX_A_OFFSET_50			52	//	Default calibration values (all bits set if not supported).	
#define EEPROM_INDEX_B_RANGE_50				53	//	Default calibration values (all bits set if not supported).	
#define EEPROM_INDEX_B_OFFSET_50			54	//	Default calibration values (all bits set if not supported).	
#define EEPROM_INDEX_PADDING				55	//	uInt16, zero filled.	
#define EEPROM_INDEX_1024_CHECK_SUM			63	//	Check sum of entire 1K  EEPROM except these two bytes.  (location is NOT dependant on EEPROM size).	
#define EEPROM_INDEX_4096_CHECK_SUM			63	//	Check sum of entire 4K  EEPROM except these two bytes.  (location is NOT dependant on EEPROM size).	
#define EEPROM_INDEX_16384_CHECK_SUM		63	//	Check sum of entire 16K EEPROM except these two bytes.  (location is NOT dependant on EEPROM size).	
#define EEPROM_INDEX_A_RANGES_D				64	//	Default calibration values (all bits set if not supported).	
#define EEPROM_INDEX_A_OFFSETS_D			71	//	Default calibration values (all bits set if not supported).	
#define EEPROM_INDEX_B_RANGES_D				78	//	Default calibration values (all bits set if not supported).	
#define EEPROM_INDEX_B_OFFSETS_D			85	//	Default calibration values (all bits set if not supported).	
#define EEPROM_INDEX_A_RANGE_D_50			92	//	Default calibration values (all bits set if not supported).	
#define EEPROM_INDEX_A_OFFSET_D_50			93	//	Default calibration values (all bits set if not supported).	
#define EEPROM_INDEX_B_RANGE_D_50			94	//	Default calibration values (all bits set if not supported).	
#define EEPROM_INDEX_B_OFFSET_D_50			95	//	Default calibration values (all bits set if not supported).	
#define EEPROM_INDEX_PADDING_4096			96	//	uInt16, zero filled.	
#define EEPROM_INDEX_EIB_DAC_AREA			160	//	uInt8, 0x80 filled.	
#define EEPROM_INDEX_PADDING_16384			256	//	uInt16, zero filled.	

#define EEPROM_INDEX_RANGE_OFFSET_SIZE		7	//	7 x uInt16, organized differently for each board class.	


//*******************************************************//
// Legacy values for Input Range (EEProm linkage)
//  CompuScope input range values.  
//	Supported by Board:												CS1610	CS14100	CS12100	CS3200
#define	CP500_INDEX_10V				0	//	+/- 10 volts.			 Yes	   No	  No	  No		
#define	CP500_INDEX_5V				1	//	+/- 5 volts.			 Yes	   Yes	  Yes	  Yes	
#define	CP500_INDEX_2V				2	//	+/- 2 volts.			 Yes	   Yes	  Yes	  Yes	
#define	CP500_INDEX_1V				3	//	+/- 1 volts.			 Yes	   Yes	  Yes	  Yes	
#define	CP500_INDEX_500MV			4	//	+/- 500 millivolts.		 Yes	   Yes	  Yes	  Yes	
#define	CP500_INDEX_200MV			5	//	+/- 200 millivolts.		 Yes	   Yes	  Yes	  Yes	
#define	CP500_INDEX_100MV			6	//	+/- 100 millivolts.		 Yes	   Yes	  Yes	  Yes	
#define	CP500_INDEX_50MV			7	//	+/- 50 millivolts.		 Yes	   No	  No	  No	
#define	CP500_GAINTABLE_SIZE		8	

#define	CP500_DAC_TABLE_SIZE		(8 * CP500_GAINTABLE_SIZE)	//	Row 0)	Single Channel mode		Channel A Range
														        //	Row 1)	Single Channel mode		Channel A Offse
                                                                //	Row 2)	Single Channel mode		Channel B Range
														        //	Row 3)	Single Channel mode		Channel B Offset
																//	Row 4)	Dual Channel mode		Channel A Range
																//	Row 5)	Dual Channel mode		Channel A Offset
																//	Row 6)	Dual Channel mode		Channel B Range
																//	Row 7)	Dual Channel mode		Channel B Offset	


#endif // __EEPROM_H__ 

//	End of EEPROM.H.	

