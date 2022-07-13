#ifndef __DRVSUPP_H__
#define __DRVSUPP_H__

#ifdef GAGEEX_EXPORTS
#define GAGEEX_API __declspec(dllexport) __stdcall
#else
#define GAGEEX_API __declspec(dllimport) __stdcall
#endif


#include "gage_drv.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GAGE_ASSUME_X12 (GAGE_ASSUME_CS8012|GAGE_ASSUME_CS6012|GAGE_ASSUME_CS1012|GAGE_ASSUME_CS512|GAGE_ASSUME_CS8012_TYPE)

#define	IMPED_1_MOHM_AVAILABLE	0x00000f0f
#define	IMPED_50_OHM_AVAILABLE	0x0000f0f0

#define SINGLE_ENDED_AVAILABLE	0x000000ff
#define DIFFERENTIAL_AVAILABLE	0x0000ff00

#define	COUPLE_DC_AVAILABLE		0x55555555
#define	COUPLE_AC_AVAILABLE		0xaaaaaaaa

#define OFFSET_ADJUST_AVAILABLE	0xcccccccc


// Decription;
//	bit0 - DC, 1 MOhm, No offset adjust
//	bit1 - AC, 1 MOhm, No offset adjust
//	bit2 - DC, 1 MOhm, Offset adjust
//	bit4 - AC, 1 MOhm, Offset adjust
//	bit5 - DC, 50 Ohm, No offset adjust
//	bit6 - AC, 50 Ohm, No offset adjust
//	bit7 - DC, 50 Ohm, Offset adjust
//	bit8 - AC, 50 Ohm, Offset adjust

#pragma pack(8)

typedef struct {
	int16	gain;	 //	Value of the driver constant for the input range.	
	uInt32	caps;	 //	Flag determins impedance and coupling avalible
	double	swing;	 //	Full swing in uV
	double	offset;	 //	Voltage corresponding to the middle of the data range in uV
	char	Hight[8];//	String for hight limit e.g "±347 uV" or "-24.1 V"
	char	Low[8];  //	String for low limit e.g "+1.65 mV"
} RangeItem;

#define DUAL_MODE_AVAILABLE   0x0000ffff
#define SINGLE_MODE_AVAILABLE 0xffff0000
#define MEM_MODE_AVAILABLE    0x00ff00ff
#define RT_MODE_AVAILABLE     0xff00ff00

#define GAGE_ASSUME_DEMO	  0xffff
#define DEMO_EMULATE		  GAGE_ASSUME_CS14100

typedef struct {
	int16	rate;	// Value for driver function
	int16	mult;	// Value for driver function
	int16	index;	// SRindex
	uInt32	mode;	// mode supported
	double  coef;   // factor = 1 or 0.5 for X1 ExtClock;
	double	tbs;	// in ns
	char	text[10];// String for GUI
}SRItem;

#pragma pack()

size_t GAGEEX_API  GetCardSRTable        ( int16 NumOfBoards, uInt16 BoardType, uInt32 ee_option, uInt16 version, void *ptr, size_t size );
size_t GAGEEX_API  GetCardRangeTable     ( uInt16 BoardType, uInt32 ee_option, uInt16 version, void *ptr, size_t size );

uInt32 GAGEEX_API  GetDataRange (gage_driver_info_type* pBoardConfig, int16 Chan );
uInt32 GAGEEX_API  GetImpedCoupling (gage_driver_info_type* pBoardConfig, int16 Chan );
uInt32 GAGEEX_API  GetTrigConfig(gage_driver_info_type* pBoardConfig);

int32 GAGEEX_API IsSampleRateChangeNullInput (uInt16 BoardType, uInt32 ee_options, uInt16 version);
void  GAGEEX_API GetSkipLimits       (uInt16 BoardType, uInt32 ee_options, uInt16 version, int16 Mode, int32 *Min, int32 *Max);
int32 GAGEEX_API CheckExtRateLimit   (uInt16 BoardType, uInt32 ee_options, uInt16 version, double *Rate);
int32 GAGEEX_API CheckExtRateLimitEx (uInt16 u16BoardType, uInt32 ee_options, uInt16 version, int16 i16Mode, double* pRate);
void  GAGEEX_API CreateCardName      (uInt16 BoardType, uInt32 ee_options, uInt16 version, LPSTR dest, size_t StrSize);
int32 GAGEEX_API GetNumCannels       (uInt16 BoardType, uInt32 ee_options, uInt16 version); //determine number of channels per card
int32 GAGEEX_API GetNumChannels      (uInt16 BoardType, uInt32 ee_options, uInt16 version); //determine number of channels per card
int32 GAGEEX_API GetCardModes        (uInt16 BoardType, uInt32 ee_options, uInt16 version); //determine supported modes
void  GAGEEX_API SetCardModeOptions  (uInt16 BoardType, uInt32 ee_options, uInt16 version, int16* pCurrModeOptions); //determine supported mode options
void  GAGEEX_API SetCardModeOptionsEx(gage_driver_info_type* pBoardConfig,int16* pCurrModeOptions); //determine supported mode options
int32 GAGEEX_API GetCardTriggerNum   (uInt16 BoardType, uInt32 ee_options, uInt16 version); //determine number of triggers per card
int32 GAGEEX_API GetEnablePreTrig    (uInt16 BoardType, uInt32 ee_options, uInt16 version, uInt32 IndMode); //determine support of insure pretrigger
int32 GAGEEX_API GetExtTrigCaps      (uInt16 BoardType, uInt32 ee_options, uInt16 version); //Caps of ext trigger
int32 GAGEEX_API GetTrigCaps         (uInt16 BoardType, uInt32 ee_options, uInt16 version); //Banwidth and Sensitivity caps
int32 GAGEEX_API GetCardTriggerChannelSource (uInt16 BoardType, uInt32 ee_options, uInt16 version); //determine existance of channel triggers

int32 GAGEEX_API UseTransferBuffer (uInt16 BoardType, uInt32 ee_options, uInt16 version, int16 mode);
int32 GAGEEX_API IsBufferDemuxed (uInt16 BoardType, uInt32 ee_options, uInt16 version, int16 mode);
int32 GAGEEX_API AcqCountAvailable	(uInt16 BoardType, uInt32 ee_options, uInt16 version);
int32 GAGEEX_API IsDiffInputAvailable (uInt16 BoardType, uInt32 ee_options, uInt16 version);
int32 GAGEEX_API IsNullInputAvailable (uInt16 BoardType, uInt32 ee_options, uInt16 version);
int32 GAGEEX_API IsRealTimeAvailable (uInt16 BoardType, uInt32 ee_options, uInt16 version);
int32 GAGEEX_API IsReferenceClockAvailable(uInt16 BoardType, uInt32 ee_options, uInt16 version);
void  GAGEEX_API GetChannelOffsetLimits (uInt16 BoardType, uInt32 , uInt16 , float* pfMin, float* pfMax);

int16 GAGEEX_API MakeDefaultSettingsForCard ( gage_driver_info_type* pBoardConfig, int Master );
int   GAGEEX_API GetDefaultPowerSetting(uInt16 BoardType, uInt32 ee_options, uInt16 version);
DWORD GAGEEX_API IsDllUsed ( LPCSTR lpcstrFileName /* "gage_drv" */ );
int32 GAGEEX_API GetMaxPreMulRec(gage_driver_info_type* pBoardConfig);
DWORD GAGEEX_API GetMaxGroupNum(gage_driver_info_type* pBoardConfig);
DWORD GAGEEX_API GetGroupSize(gage_driver_info_type* pBoardConfig, long lPre);
int32 GAGEEX_API GetMinDepth(gage_driver_info_type* pBoardConfig);
int32 GAGEEX_API IsDigital(gage_driver_info_type* pBoardConfig);
void  GAGEEX_API GetTmbParams(TRGMBOARD *TmbBoard, double* dTmbInc, long* lTmbWidth);

#define TRIG_SENSE			0x01
#define TRIG_HI_REJECT		0x02
#define TRIG_LO_REJECT		0x04
#define TRIG_NOISE_REJECT	0x08


#define EXT_TRIGGER_LEVEL	0x01
#define EXT_TRIGGER_SLOPE	0x02
#define EXT_TRIGGER_COUPL	0x04
#define EXT_TRIGGER_RANGE	0x08
#define EXT_TRIGGER_IMPED	0x10
#define EXT_TRIGGER_ALL		(EXT_TRIGGER_LEVEL |\
							 EXT_TRIGGER_SLOPE |\
							 EXT_TRIGGER_COUPL |\
							 EXT_TRIGGER_RANGE )



#ifdef __cplusplus
}
#endif

#endif // __DRVSUPP_H__
