// CsDecadeOptions.h
//
// Hardware and Firmware (non-Expert) options for Decade (EON Express) cards
//
// For Expert Firmware options, see CsExpert.h
//

#ifndef __CsDecadeOptions__h_
#define __CsDecadeOptions__h_


#include "CsDrvConst.h"

//
// Base board Hardware options
//
#define	DECADE_BBHW_ADDON_1V07							CS_OPTION_BIT_0			// 1V07 Addon


// Base board options that require Special Firmware
#define	DECADE_BBHW_OPT_FWREQUIRED_MASK					DECADE_BBHW_ADDON_1V07

//
// Addon Hardware options
//

#define	DECADE_ADDON_HW_OPTION_1CHANNEL6G			CS_OPTION_BIT_0			// 1 Channel cards
#define	DECADE_ADDON_HW_OPTION_AC_COUPLING				CS_OPTION_BIT_1			// AC Coupling cards

// Addon board options that require Special Firmware
#define	CSRB_AOHW_OPT_FWREQUIRED_MASK				CS_OPTION_BIT_3



#endif	//__CsRabbitOptions__h_

