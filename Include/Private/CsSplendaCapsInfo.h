#ifndef __CS_SPLENDA_CAPS_INFO_H__
#define __CS_SPLENDA_CAPS_INFO_H__

#include "CsTypes.h"
#include "CsAdvStructs.h"

#define CSPLNDA_CHANNELS				4
#define CSPLNDA_MAX_RANGES		        9
#define CSPLNDA_MAX_UNRESTRICTED_INDEX	16
#define CSPLNDA_EXT_TRIG_RANGES			2
#define CSPLNDA_MAX_IMAGE_NUM           1

#define CSPLNDA_IMPED					3		// one extra for externel trigger
#define CSPLNDA_COUPLING				2
#define CSPLNDA_FILTERS					2
#define CSPLNDA_EXT_TRIG_RANGES			2
#define CSPLNDA_MAX_SR_COUNT			18
#define CSPLNDA_MIN_EXT_CLK				10000000
#define CSPLNDA_MAX_FE_SET_INDEX		8 //two coplings two impedances two filters
#define CSPLNDA_MAX_FE_SET_IMPED_INC    4
#define CSPLNDA_MAX_FE_SET_COUPL_INC    2
#define CSPLNDA_MAX_FE_SET_FLTER_INC    1

#define CSPLNDA_MODE_COUNT				3

#define CSPLNDA_TRIGGER_RES				8
#define CSPLNDA_PCIE_TRIGGER_RES		32

#ifdef _WIN32
#pragma pack (8)
#endif

typedef struct _CSSPLENDABOARDCAPS
{
	CSSAMPLERATETABLE_EX SrTable[CSPLNDA_MAX_SR_COUNT];
	CS_EXTCLOCK_TABLE    ExtClkTable[CSPLNDA_MODE_COUNT];

	CSRANGETABLE         RangeTable[CSPLNDA_MAX_RANGES];
	CSRANGETABLE         ExtTrigRangeTable[CSPLNDA_EXT_TRIG_RANGES];

	CSIMPEDANCETABLE     ImpedanceTable[CSPLNDA_IMPED];
	CSCOUPLINGTABLE      CouplingTable[CSPLNDA_COUPLING];

	CSFILTERTABLE        FilterTable[CSPLNDA_FILTERS];
	BOOLEAN              bDcOffset;

#ifdef __linux__
	int					 g_RefCount;
#endif

}CSSPLENDABOARDCAPS, *PCSSPLENDABOARDCAPS;

#ifdef _WIN32
#pragma pack ()
#endif

#define	MAX_SPLNDA_TRIGGER_ADDRESS_OFFSET	24		// Should be muliple of 8
#define	MAX_SPLNDA_TAIL_INVALID_SAMPLES		(7*8)	// Invalid sample at tail in Single mode
													// Half in Dual, 1/4 in Quad and 1/8 in Oct
#define	CSPLNDA_PRE_TRIG_PIPELINE			8		// Number of head samples lost due to negative trigger address

#endif
