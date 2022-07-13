// CsRabbitOptions.h
//
// Hardware and Firmware (non-Expert) options for Rabbit cards
//
// For Expert Firmware options, see CsExpert.h
//

#ifndef __CsRabbitOptions__h_
#define __CsRabbitOptions__h_


#include "CsDrvConst.h"


//
// Base board Hardware options
//

//#define	CSRB_BBHW_OPTION_STANDALONE		CS_OPTION_BIT_0		// Stand alone Rabbit base board

// Cobra  PCI-E cards only
#define	CSRB_BASEBOARD_HW_OPTION_UTEXPE		CS_OPTION_BIT_0			// UTEX board
#define	CSRB_BASEBOARD_HW_OPTION_SONOSCAN   CS_OPTION_BIT_1 		// Sonoscan board


// Base board options that require Special Firmware
#define	CSRB_BBHW_OPT_FWREQUIRED_MASK		0
#define	CSCOBRAMAX_BBHW_OPT_FWREQUIRED_MASK				(CSRB_ADDON_HW_OPTION_UTEXPE|CSRB_BASEBOARD_HW_OPTION_SONOSCAN)	



//
// Addon Hardware options
//

// Cobra  PCI and PCIE cards
#define	CSRB_ADDON_HW_OPTION_1CHANNEL	CS_OPTION_BIT_0			// 1 Channel cards
#define	CSRB_ADDON_HW_OPTION_500OSC		CS_OPTION_BIT_1			// 500 Osciillator
#define	CSRB_ADDON_HW_OPTION_HIGHBW		CS_OPTION_BIT_2			// High	Bandwith

// Cobra  PCI cards only
#define	CSRB_ADDON_HW_OPTION_1500OSC	CS_OPTION_BIT_3			// 1500 Oscillator
#define	CSRB_ADDON_HW_OPTION_ECO10      CS_OPTION_BIT_4 		// ECO 10
#define	CSRB_ADDON_HW_OPTION_LAB11G     CS_OPTION_BIT_5 		// Lab11G card (Chan2 is used as Ext Trigger input)

// Cobra  PCI-E cards only
#define	CSRB_ADDON_HW_OPTION_UTEXPE		CS_OPTION_BIT_3			// UTEX board
#define	CSRB_ADDON_HW_OPTION_SONOSCAN   CS_OPTION_BIT_4 		// Sonoscan board


// Addon board options that require Special Firmware
#define	CSRB_AOHW_OPT_FWREQUIRED_MASK				0

// Addon board options that require Special Firmware (CobraMax PCIe)
#define	CSCOBRAMAX_AOHW_OPT_FWREQUIRED_MASK				(CSRB_ADDON_HW_OPTION_1CHANNEL|CSRB_ADDON_HW_OPTION_UTEXPE|CSRB_BASEBOARD_HW_OPTION_SONOSCAN)	



#endif	//__CsRabbitOptions__h_

