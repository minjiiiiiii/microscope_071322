#ifndef __CS_8xxx_CAPS_INFO_H__
#define __CS_8xxx_CAPS_INFO_H__

#include "CsTypes.h"
#include "CsAdvStructs.h"

#define CSPDR_TRIGGER_RES				16

#define CSPDR_CHANNELS					8
#define CSPDR_MAX_RANGES		        16
#define CSPDR_MAX_UNRESTRICTED_INDEX	16
#define CSPDR_EXT_TRIG_RANGES			2
#define CSPDR_MAX_IMAGE_NUM            	7

#define CSPDR_IMPED						3		// 2 for Channel Input and 1 for External trigger
#define CSPDR_COUPLING					2
#define CSPDR_FILTERS					2
#define CSPDR_EXT_TRIG_RANGES			2
#define CSPDR_MAX_SR_COUNT				32
#define CSPDR_MIN_EXT_CLK               2000000
#define CSPDR_MAX_FE_SET_INDEX			(CSPDR_IMPED*CSPDR_COUPLING*CSPDR_FILTERS)  //Imped * coupling * Filter

#define	CSPDR_ZAP_AVG_SIZE				5

#define CSPDR_MODE_COUNT                4



#ifdef _WIN32
#pragma pack (8)
#endif

typedef struct _CS8XXXBOARDCAPS
{
	CSSAMPLERATETABLE_EX SrTable[CSPDR_MAX_SR_COUNT];
	CS_EXTCLOCK_TABLE    ExtClkTable[CSPDR_MODE_COUNT];

	CSRANGETABLE         RangeTable[CSPDR_MAX_RANGES];
	CSRANGETABLE         ExtTrigRangeTable[CSPDR_EXT_TRIG_RANGES];

	CSIMPEDANCETABLE     ImpedanceTable[CSPDR_IMPED];
	CSCOUPLINGTABLE      CouplingTable[CSPDR_COUPLING];

	CSFILTERTABLE        FilterTable[CSPDR_FILTERS];
	BOOLEAN	             bDcOffset;

#ifdef	__linux__
	int					 g_RefCount;
#endif

}CS8XXXBOARDCAPS, *PCS8XXXBOARDCAPS;

#ifdef _WIN32
#pragma pack ()
#endif


#endif
