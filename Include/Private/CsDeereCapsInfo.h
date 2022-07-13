#ifndef __CS_DEERE_CAPS_INFO_H__
#define __CS_DEERE_CAPS_INFO_H__

#include "CsTypes.h"
#include "CsAdvStructs.h"

#define DEERE_TRIGGER_RES			   16

#define DEERE_CHANNELS					2
#define DEERE_MAX_RANGES			   16
#define DEERE_EXT_TRIG_RANGES			2
#define DEERE_EXT_TRIG_IMPED            2
#define DEERE_EXT_TRIG_COUPLING         2
#define DEERE_MAX_IMAGE_NUM            	2
#define DEERE_ADC_COUNT                 4
#define DEERE_ADC_CORES                 2

#define DEERE_IMPED						1
#define DEERE_COUPLING					2
#define DEERE_FILTERS					2
#define DEERE_EXT_TRIG_RANGES			2
#define DEERE_MAX_SR_COUNT			   24
#define DEERE_MAX_FE_SET_INDEX			(DEERE_IMPED*DEERE_COUPLING*DEERE_FILTERS)  //Imped * coupling * Filter
#define DEERE_MIN_EXT_CLK       160000000  //160 MHz
#define	DEERE_ADC_DLL_FAST_CLK  160000000  //160 MHz
#define DEERE_MODE_COUNT				2

#define DEERE_FILTER_FULL_4			1000
#define DEERE_FILTER_LIMIT_4		70
#define DEERE_FILTER_FULL_2			1000
#define DEERE_FILTER_LIMIT_2		70
#define DEERE_FILTER_FULL_1			300
#define DEERE_FILTER_LIMIT_1		70

#define DEERE_MAX_SQUARE_PRETRIGDEPTH	(4092*16)

#ifdef _WIN32
#pragma pack (8)
#endif

typedef struct _CSDEEREBOARDCAPS
{
	CSSAMPLERATETABLE_EX SrTable[DEERE_MAX_SR_COUNT];
	CS_EXTCLOCK_TABLE    ExtClkTable[DEERE_MODE_COUNT];
	
	CSRANGETABLE         RangeTable[DEERE_MAX_RANGES];
	CSIMPEDANCETABLE     ImpedanceTable[DEERE_IMPED];
	CSCOUPLINGTABLE      CouplingTable[DEERE_COUPLING];
	CSFILTERTABLE        FilterTable[DEERE_FILTERS];

	CSRANGETABLE         ExtTrigRangeTable[DEERE_EXT_TRIG_RANGES];
	CSIMPEDANCETABLE     ExtTrigImpedanceTable[DEERE_EXT_TRIG_IMPED];
	CSCOUPLINGTABLE      ExtTrigCouplingTable[DEERE_EXT_TRIG_COUPLING];

#ifdef	__linux__
	int					 g_RefCount;
#endif

}CSDEEREBOARDCAPS, *PCSDEEREBOARDCAPS;

#ifdef _WIN32
#pragma pack ()
#endif


#endif
