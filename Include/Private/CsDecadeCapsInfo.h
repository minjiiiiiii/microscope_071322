#ifndef __CS_DECADE_CAPS_INFO_H__
#define __CS_DECADE_CAPS_INFO_H__

#include "CsTypes.h"
#include "CsAdvStructs.h"

#define DECADE_CHANNELS					2
#define DECADE_MAX_RANGES		        6

#define DECADE_IMPED					3		// one extra for externel trigger
#define DECADE_COUPLING					2
#define DECADE_FILTERS					2
#define DECADE_EXT_TRIG_RANGES			1
#define DECADE_MAX_SR_COUNT				48
#define DECADE_MAX_FE_SET_INDEX			8 //two coplings two impedances two filters
#define DECADE_MAX_FE_SET_IMPED_INC		4
#define DECADE_MAX_FE_SET_COUPL_INC		2
#define DECADE_MAX_FE_SET_FLTER_INC		1
#define DECADE_MIN_EXT_CLK				200000000
#define DECADE_MAX_EXT_CLK				3000000000

#define	DECADE_FILTER_FULL				1000
#define	DECADE_FILTER_LIMIT				200

#define DECADE_MODE_COUNT				2
#define DECADE_DEPTH_INCREMENT			(32*5)		// Min depth increment (SINGLE Chan). Will be half in DUAL chan
#define DECADE_TRIGGER_RES				DECADE_DEPTH_INCREMENT		// Obslete define. Keep Linux code compiling. Will be deleted later
#define DECADE_DELAY_INCREMENT			(32)		// Min Trig delay increment (SINGLE Chan). Will be half in DUAL chan
#define DECADE_DEPTH_INCREMENT_PACK8	64			// Min depth increment for Pack 8 mode (SINGLE Chan). Will be Half in DUAL chan

#pragma pack (8)

typedef struct _CSDECADE_BOARDCAPS
{
	CSSAMPLERATETABLE_EX	SrTable[DECADE_MAX_SR_COUNT];
	CS_EXTCLOCK_TABLE		ExtClkTable[DECADE_MODE_COUNT];

	CSRANGETABLE			RangeTable[DECADE_MAX_RANGES];
	CSIMPEDANCETABLE		ImpedanceTable[DECADE_IMPED];
	CSCOUPLINGTABLE			CouplingTable[DECADE_COUPLING];

	CSRANGETABLE			ExtTrigRangeTable[DECADE_EXT_TRIG_RANGES];		
	CSCOUPLINGTABLE			ExtTrigCouplingTable[DECADE_COUPLING];
	CSIMPEDANCETABLE		ExtTrigImpedanceTable[DECADE_IMPED];

	CSFILTERTABLE			FilterTable[DECADE_FILTERS];
	BOOLEAN					bDcOffset;

#ifdef __linux__
	int					 g_RefCount;
#endif

}CSDECADE_BOARDCAPS, *PCSDECADE_BOARDCAPS;

#pragma pack ()

#endif
