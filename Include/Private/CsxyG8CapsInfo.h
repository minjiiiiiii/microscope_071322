#ifndef __CS_xyG8_CAPS_INFO_H__
#define __CS_xyG8_CAPS_INFO_H__

#include "CsTypes.h"
#include "CsAdvStructs.h"

#define CSRB_TRIGGER_RES				16

#define CSRB_CHANNELS					2
#define CSRB_MAX_RANGES					16
#define CSRB_EXT_TRIG_RANGES			2
#define CSRB_EXT_TRIG_IMPED             2
#define CSRB_EXT_TRIG_COUPLING          2
#define CSRB_MAX_IMAGE_NUM            	2

#define CSRB_IMPED						1
#define CSRB_COUPLING					2
#define CSRB_FILTERS					2
#define CSRB_EXT_TRIG_RANGES			2
#define CSRB_MAX_SR_COUNT				24
#define CSRB_MAX_FE_SET_INDEX			(CSRB_IMPED*CSRB_COUPLING*CSRB_FILTERS)  //Imped * coupling * Filter
#define CSRB_MIN_EXT_CLK                200000000
#define CSRB_MODE_COUNT					2

#define CSRB_FILTER_FULL			1000
#define CSRB_FILTER_LIMIT			200


#ifdef _WIN32
#pragma pack (8)
#endif

typedef struct _CSXYG8BOARDCAPS
{
	CSSAMPLERATETABLE_EX SrTable[CSRB_MAX_SR_COUNT];
	CS_EXTCLOCK_TABLE    ExtClkTable[CSRB_MODE_COUNT];
	
	CSRANGETABLE         RangeTable[CSRB_MAX_RANGES];
	CSIMPEDANCETABLE     ImpedanceTable[CSRB_IMPED];
	CSCOUPLINGTABLE      CouplingTable[CSRB_COUPLING];
	CSFILTERTABLE        FilterTable[CSRB_FILTERS];

	CSRANGETABLE         ExtTrigRangeTable[CSRB_EXT_TRIG_RANGES];
	CSIMPEDANCETABLE     ExtTrigImpedanceTable[CSRB_EXT_TRIG_IMPED];
	CSCOUPLINGTABLE      ExtTrigCouplingTable[CSRB_EXT_TRIG_COUPLING];

#ifdef 	__linux__
	uInt32			g_RefCount;
#endif

}CSXYG8BOARDCAPS, *PCSXYG8BOARDCAPS;

#ifdef _WIN32
#pragma pack ()
#endif


#endif
