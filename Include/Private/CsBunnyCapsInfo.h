#ifndef __CS_BUNNY_CAPS_INFO_H__
#define __CS_BUNNY_CAPS_INFO_H__

#include "CsTypes.h"
#include "CsAdvStructs.h"

#define BUNNY_CHANNELS					2
#define BUNNY_MAX_RANGES				16
#define BUNNY_EXT_TRIG_RANGES			2
#define BUNNY_EXT_TRIG_IMPED            2
#define BUNNY_EXT_TRIG_COUPLING         2
#define BUNNY_MAX_IMAGE_NUM            	2

#define BUNNY_IMPED						1
#define BUNNY_COUPLING					2
#define BUNNY_FILTERS					2
#define BUNNY_MAX_SR_COUNT				24
#define BUNNY_MAX_FE_SET_INDEX			(BUNNY_IMPED*BUNNY_COUPLING*BUNNY_FILTERS)  //Imped * coupling * Filter
#define BUNNY_MIN_EXT_CLK               200000000
#define BUNNY_MODE_COUNT				2

#define BUNNY_FILTER_FULL			    1000
#define BUNNY_FILTER_LIMIT			    200


#ifdef _WIN32
#pragma pack (8)
#endif

typedef struct _CSBUNNYBOARDCAPS
{
	CSSAMPLERATETABLE_EX SrTable[BUNNY_MAX_SR_COUNT];
	CS_EXTCLOCK_TABLE    ExtClkTable[BUNNY_MODE_COUNT];
	
	CSRANGETABLE         RangeTable[BUNNY_MAX_RANGES];
	CSIMPEDANCETABLE     ImpedanceTable[BUNNY_IMPED];
	CSCOUPLINGTABLE      CouplingTable[BUNNY_COUPLING];
	CSFILTERTABLE        FilterTable[BUNNY_FILTERS];

	CSRANGETABLE         ExtTrigRangeTable[BUNNY_EXT_TRIG_RANGES];
	CSIMPEDANCETABLE     ExtTrigImpedanceTable[BUNNY_EXT_TRIG_IMPED];
	CSCOUPLINGTABLE      ExtTrigCouplingTable[BUNNY_EXT_TRIG_COUPLING];

#ifdef	__linux__
	int					 g_RefCount;
#endif

}BUNNYBOARDCAPS, *PBUNNYBOARDCAPS;

#ifdef _WIN32
#pragma pack ()
#endif


#endif
