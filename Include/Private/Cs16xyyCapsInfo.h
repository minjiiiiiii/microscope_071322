#ifndef __CS_16xyy_CAPS_INFO_H__
#define __CS_16xyy_CAPS_INFO_H__

#include "CsTypes.h"
#include "CsAdvStructs.h"

#define CSPLNDA_CHANNELS				4
#define CSPLNDA_MAX_RANGES		        8
#define CSPLNDA_MAX_UNRESTRICTED_INDEX	16
#define CSPLNDA_EXT_TRIG_RANGES			2
#define CSPLNDA_MAX_IMAGE_NUM           1

#define CSPLNDA_IMPED					2		// 2 for Channel Input
#define CSPLNDA_COUPLING				2
#define CSPLNDA_FILTERS					2
#define CSPLNDA_EXT_TRIG_RANGES			2
#define CSPLNDA_MAX_SR_COUNT			18
#define CSPLNDA_MIN_EXT_CLK				10000000
#define CSPLNDA_MAX_FE_SET_INDEX		(CSPLNDA_IMPED*CSPLNDA_COUPLING*CSPLNDA_FILTERS)  //Imped * coupling * Filter


#define CSPLNDA_MODE_COUNT				4

#define CSPLNDA_TRIGGER_RES				8

#ifdef _WIN32
#pragma pack (8)
#endif

typedef struct _CS16XYYBOARDCAPS
{
	CSSAMPLERATETABLE_EX SrTable[CSPLNDA_MAX_SR_COUNT];
	CS_EXTCLOCK_TABLE    ExtClkTable[CSPLNDA_MODE_COUNT];
	
	CSRANGETABLE         RangeTable[CSPLNDA_MAX_RANGES];
	CSRANGETABLE         ExtTrigRangeTable[CSPLNDA_EXT_TRIG_RANGES];

	CSIMPEDANCETABLE     ImpedanceTable[CSPLNDA_IMPED];
	CSCOUPLINGTABLE      CouplingTable[CSPLNDA_COUPLING];

	CSFILTERTABLE        FilterTable[CSPLNDA_FILTERS];
	bool                 bDcOffset;

}CS16XYYBOARDCAPS, *PCS16XYYBOARDCAPS;

#ifdef _WIN32
#pragma pack ()
#endif


#endif
