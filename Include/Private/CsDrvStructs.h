#ifndef __CS_DRV_STRUCT__
#define	__CS_DRV_STRUCT__

//#include <vdw.h>
#include "CsTypes.h"
#include "CsStruct.h"
#include "CsPrivateStruct.h"
#include "CsDrvDefines.h"
#include "CsExpert.h"

#if	defined(__WINDOWS__)
#pragma pack (1)
#endif


typedef union _InitStatus
{
	uInt32 dwStatus;
	struct
	{
		uInt32 u32NvRam      : 1;
		uInt32 u32Flash      : 1;
		uInt32 u32Fpga       : 1;
		uInt32 u32Nios       : 1;
		uInt32 u32BbMemTest  : 1;
		uInt32 u32Reserved5  : 1;
		uInt32 u32Reserved6  : 1;
		uInt32 u32Reserved7  : 1;
		uInt32 u32Reserved8  : 1;
		uInt32 u32Reserved9  : 1;
		uInt32 u32Reserved10 : 1;
		uInt32 u32Reserved11 : 1;
		uInt32 u32Reserved12 : 1;
		uInt32 u32Reserved13 : 1;
		uInt32 u32Reserved14 : 1;
		uInt32 u32AddOnPresent : 1;
		uInt32 u32AddOnCfg   : 1;
		uInt32 u32AddOnFpga  : 1;
		uInt32 u32AddOnSpi   : 1;
		uInt32 u32Analog     : 1;
		uInt32 u32Trigger    : 1;
		uInt32 u32Eeeprom    : 1;
		uInt32 u32Bist       : 1;
	}Info;
}INITSTATUS;


typedef struct _CARD_EEPROM_INFO
{
	uInt32			Options;		//	BIT encoded (see EEPROM_OPTIONS_XXXXXXXX).
	uInt16			AddrSize;
	uInt16			AddrMask;
	uInt16			Protect;
	uInt16			WriteRegister;
	uInt16			ReadRegister;
	uInt8			Sdi_bit;
	uInt8			Clk_bit;
	uInt8			Prot_bit;
	uInt8			Cs_bit;
	uInt8			Sdo_bit;
	int16			Present;
	int16			Valid;
	uInt8			IoPort[NUMBER_OF_REGISTERS];
} CARD_EEPROM_INFO, *PCARD_EEPROM_INFO;


typedef struct _stFileHeader
{
	uInt8  target;		// Number of target PLD;
	uInt16 version;		// Revision number of target
	uInt8  mode;
// bit 0-1               bit 2-7 - SkipCount
// 00 - Test Memory
// 01 - Memory Mode
// 10 - RT PreTtig Mode
// 11 - RT MULREC Mode

	char name[NAME_SIZE];
#ifdef __linux__
}__attribute__ ((packed)) stFileHeader;

#else
} STFILEHEADER;
#endif



#if	defined(__WINDOWS__)
#pragma pack ()
#endif


//
//  Structure which have differents parameters of physical hardware configuration
//  Eeprom, NVram ...
//  Usually, these parameters can not be changed once they are configured at manufacturing
//

typedef	struct _CS_BOARD_NODE
{
	int64	i64MaxMemory;				// Memory size of the system. (Physical board limitation)
	BOOLEAN bBusy;
	BOOLEAN	bTriggered;
	uInt32	DpcIntrStatus;			// Keep track of which interrupt received for DPC

	//------ Pour Combine
	uInt16	u32BoardType;				// ID that identifies the card type (ex :CS14100_BOARDTYPE )
	uInt32	u32ActiveAddonOptions;		// Active Addon options
	uInt32	u32AddonOptions[8];			// EEPROM options encoding features like gate, trigger enable, digital in, pulse out
	uInt32	u32BaseBoardOptions[8];		// EEPROM options -------------------------||---------------------------------------
	int64	i64ExpertPermissions;
	uInt32	u32SerNum;					// Serial number from NvRam Base board
	uInt32	u32SerNumEx;				// Serial number from Addon board

	uInt8	u8BadBbFirmware;
	uInt8	u8BadAddonFirmware;
	uInt32	u32BaseBoardVersion;		// HW base board version
	uInt32	u32RawFwVersionB[3];		// Base board raw firmware version as read from registers	
	CSFWVERSION	u32UserFwVersionB[3];	// Base board user firmware version converted from raw one
	uInt32	u32BaseBoardHardwareOptions;
	uInt32	u32AddonBoardVersion;		
	uInt32	u32RawFwVersionA[3];		// Addon raw firmware version as read from registers	
	CSFWVERSION	u32UserFwVersionA[3];		// Addon user firmware version converted from raw one
	uInt32	u32AddonHardwareOptions;

	
	uInt8	NbTriggerMachine;
	uInt8	NbAnalogChannel;
	uInt8	NbDigitalChannel;
	uInt8	SampleRateLimit;

} CS_BOARD_NODE, *PCS_BOARD_NODE;


typedef struct _CS_CHANNEL_PARAMS
{
	// Channel related
	BOOLEAN	bForceCalibration;	// Force Calibration. If the flag is set, Calibration need to be done on this channel.
	uInt32	u32Term;			// Channel coupling: AC or DC and Termination single ended or differential. LowWord : coupling, HiWord: differential.
	uInt32	u32InputRange;			// Channel specific gain, mV	
	uInt32	u32Impedance;		// Channel impedance, Ohm
	uInt32	u32Filter;			// Channel bandwidth, KHz
	int32	i32Position;		// Channel Offset, mV

} CS_CHANNEL_PARAMS, *PCS_CHANNEL_PARAMS;

typedef struct _CS_TRIGGER_PARAMS
{
	// Trigger engine related
	uInt32	u32Condition;	   	// Positve or Negative slope, pulse width, rise time etc.
	int32	i32Level;			// Level for trigger occurrence in % of Full scale
	int32	i32Source;			// Trigger source: Channels 1 or 2, External 1V or 5V,  zero = disable}
	int32	i32Value1;			// A parameter dependant on the condition (duration, time ...)
	int32	i32Value2;			// A parameter dependant on the condition (duration, time ...)
	uInt32	u32Filter;			// in KHz
	uInt32	u32Relation;     	// Relation to the rest of the trigger circuits (AND, OR ..)

	// Back up for trigger source != SOURCE_EXTERNAL
	uInt32	u32ExtImpedance;	// External Trigger impedance
	uInt32	u32ExtCoupling;		// External Trigger coupling AC or DC
	uInt32	u32ExtTriggerRange;	// External Trigger range in mV

	uInt32	u32UserTrigIndex;	// Trigger Index from application

} CS_TRIGGER_PARAMS, *PCS_TRIGGER_PARAMS;


//
// Structure that hold the current configuration
// Most of parameters are changable by software 
// These parmeters are commited.
//

typedef struct _SYSTEM_NODE
{
	CSSYSTEMINFO	SysInfo;			// System Info
	DRVHANDLE		Handle;				// Driver handle that identifies the system

	char			SymbolicLink[50];	// Symbolic link given to HW DLL 
	BOOLEAN			bInitialized;		// The system has been initialized.

	struct _SYSTEM_NODE	*next;				// Pointer to next system node
	
} SYSTEM_NODE, *PSYSTEM_NODE;


#define		Tx_STATE_IDLE		0				// Completed Data transfer
#define		Tx_STATE_ACTIVE		1				// Data transfer is in progress
#define		Tx_STATE_ABORTED	2				// Data transfer is aborted



#endif

