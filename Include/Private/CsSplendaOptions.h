// CsSplendaOptions.h
//
// Hardware and Firmware (non-Expert) options for Splenda cards
//
// For Expert Firmware options, see CsExpert.h
//


#ifndef __CsSplendaOptions__h_
#define __CsSplendaOptions__h_


#include "CsDrvConst.h"


//
// Base board Hardware options
//

#define CSPLNDA_BB_HW_OPTION_OSCAR			CS_OPTION_BIT_0

// Base board options that require Special Firmware
#define	CSPLNDA_BBHW_OPT_FWREQUIRED_MASK	CSPLNDA_BB_HW_OPTION_OSCAR


//
// Addon Hardware options
//

#define CSPLNDA_ADDON_HW_OPTION_VAR_CAP 	CS_OPTION_BIT_0
#define CSPLNDA_ADDON_HW_OPTION_100MS   	CS_OPTION_BIT_1
#define CSPLNDA_ADDON_HW_OPTION_AC_GAIN_ADJ	CS_OPTION_BIT_2
#define CSPLNDA_ADDON_HW_OPTION_1MOHM_DIV10	CS_OPTION_BIT_3
#define CSPLNDA_ADDON_HW_OSCAR_SR0			CS_OPTION_BIT_4
#define CSPLNDA_ADDON_HW_OSCAR_SR1			CS_OPTION_BIT_5
#define CSPLNDA_ADDON_HW_OPTION_ALT_PINOUT 	CS_OPTION_BIT_16

// Addon board options that require Special Firmware
#define	CSPLNDA_AOHW_OPT_FWREQUIRED_MASK				CSPLNDA_ADDON_HW_OPTION_ALT_PINOUT


//
// Addon Hardware options
//

#endif	//__CsSplendaOptions__h_

