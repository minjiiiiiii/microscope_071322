// CsHexagonOptions.h
//
// Hardware and Firmware (non-Expert) options for Hexagon (EON Express) cards
//
// For Expert Firmware options, see CsExpert.h
//

#ifndef __CsHexagonOptions__h_
#define __CsHexagonOptions__h_


#include "CsDrvConst.h"

//
// Base board Hardware options
//


// Base board options that require Special Firmware
#define	HEXAGON_BBHW_OPT_FWREQUIRED_MASK		0


//
// Addon Hardware options
//

#define	HEXAGON_ADDON_HW_OPTION_2CHANNELS			CS_OPTION_BIT_0			// 2- Channel cards
#define	HEXAGON_ADDON_HW_OPTION_500MHZ				CS_OPTION_BIT_1			// 500MHZ ADC cards
#define	HEXAGON_ADDON_HW_OPTION_AC_COUPLING			CS_OPTION_BIT_2			// AC Couple cards
#define	HEXAGON_ADDON_HW_OPTION_LOWRANGE_MV			CS_OPTION_BIT_3			// Low input range 480mV (+/-240mV)

// Addon board options that require Special Firmware
#define	CSRB_AOHW_OPT_FWREQUIRED_MASK				0



#endif	//__CsHexagonOptions__h_

