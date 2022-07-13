// CsSpiderOptions.h
//
// Hardware and Firmware (non-Expert) options for Spider cards
//
// For Expert Firmware options, see CsExpert.h
//


#ifndef __CsSpiderOptions__h_
#define __CsSpiderOptions__h_


#include "CsDrvConst.h"


//
// Base board Hardware options
//


// Base board options that require Special Firmware
#define	CSPDR_BBHW_OPT_FWREQUIRED_MASK			0



//
// Addon Hardware options
//

#define CSPDR_AOHW_OPT_MODIFIED_CAL			CS_OPTION_BIT_0
#define CSPDR_AOHW_OPT_BOOSTED_CAL_AMP		CS_OPTION_BIT_1
#define CSPDR_AOHW_OPT_AUX_CONNECTOR        CS_OPTION_BIT_2
#define CSPDR_AOHW_OPT_EMONA_FF		        CS_OPTION_BIT_31


// Addon board options that require Special Firmware
#define	CSPDR_AOHW_OPT_FWREQUIRED_MASK				0


#endif	//__CsSpiderOptions__h_

