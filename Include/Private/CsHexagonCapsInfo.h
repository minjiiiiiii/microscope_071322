#ifndef __CS_HEXAGON_CAPS_INFO_H__
#define __CS_HEXAGON_CAPS_INFO_H__

#include "CsTypes.h"
#include "CsAdvStructs.h"

#define HEXAGON_CHANNELS					4
#define HEXAGON_MAX_RANGES					6

#define HEXAGON_IMPED						3		// one extra for externel trigger
#define HEXAGON_COUPLING					2
#define HEXAGON_FILTERS						2
#define HEXAGON_EXT_TRIG_RANGES				1
#define HEXAGON_MAX_SR_COUNT				48
#define HEXAGON_MAX_FE_SET_INDEX			8     //two coplings two impedances two filters
#define HEXAGON_MAX_FE_SET_IMPED_INC		4
#define HEXAGON_MAX_FE_SET_COUPL_INC		2
#define HEXAGON_MAX_FE_SET_FLTER_INC		1
#define	HEXAGON_MIN_SEGMENTSIZE				32
#define HEXAGON_MAX_EXT_CLK					750000000
#define HEXAGON_500MHZ_MAX_EXT_CLK			500000000

#define HEXAGON_MIN_EXT_CLK					250000000
#define HEXAGON_TS_MEMORY_CLOCK				200000000		// 200MHz clock fixed mem clock


#define	HEXAGON_FILTER_FULL					1000
#define	HEXAGON_FILTER_LIMIT				200

#define HEXAGON_MODE_COUNT					2
#define HEXAGON_DEPTH_INCREMENT				32		// Min depth increment in SINGLE chan mode
#define HEXAGON_DELAY_INCREMENT				32		// Min Trig delay increment in SINGLE chan mode

#pragma pack (8)

typedef struct _CSHEXAGON_BOARDCAPS
{
	CSSAMPLERATETABLE_EX	SrTable[HEXAGON_MAX_SR_COUNT];
	CS_EXTCLOCK_TABLE		ExtClkTable[HEXAGON_MODE_COUNT];

	CSRANGETABLE			RangeTable[HEXAGON_MAX_RANGES];
	CSIMPEDANCETABLE		ImpedanceTable[HEXAGON_IMPED];
	CSCOUPLINGTABLE			CouplingTable[HEXAGON_COUPLING];

	CSRANGETABLE			ExtTrigRangeTable[HEXAGON_EXT_TRIG_RANGES];		
	CSCOUPLINGTABLE			ExtTrigCouplingTable[HEXAGON_COUPLING];
	CSIMPEDANCETABLE		ExtTrigImpedanceTable[HEXAGON_IMPED];

	CSFILTERTABLE			FilterTable[HEXAGON_FILTERS];
	BOOLEAN					bDcOffset;

#ifdef __linux__
	int					 g_RefCount;
#endif

}CSHEXAGON_BOARDCAPS, *PCSHEXAGON_BOARDCAPS;

#pragma pack ()

#endif
