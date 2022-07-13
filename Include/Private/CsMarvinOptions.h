// CsMarvinOptions.h
//
// Hardware and Firmware (non-Expert) options for Combine cards
//
// For Expert Firmware options, see CsExpert.h
//

#ifndef __CsMarvinOptions__h_
#define __CsMarvinOptions__h_


#include "CsDrvConst.h"

#define	CSMV_TRIGGER_RES		4
//
// Base board Hardware options
//
#define	CVMV_BBHARDWARE_OPTION_SLOW_NIOS		CS_OPTION_BIT_0		// Slow Nios (for Memory > 1G Samples)
#define	CVMV_BBHARDWARE_OPTION_NO_SODIMM		CS_OPTION_BIT_1		// DPRAM removed


// Options that require Special Firmware
#define	CSMV_BBHW_OPT_FWREQUIRED_MASK			CVMV_BBHARDWARE_OPTION_NO_SODIMM




//
// Addon Hardware options
//
#define	CSMV_AOHW_OPTIONS_STANDARD					CS_OPTION_BIT_0		// Standard options. Must be set.


// Resistors removed => no connectivity between channel front end and trigger circutry
// therefore there is no analog channel trigger
#define	CSMV_AOHW_OPTIONS_NOANALOG_TRIGGER			CS_OPTION_BIT_1		// No channel analog trigger circuitry
#define	CSMV_AOHW_OPTIONS_NOREFERNCE_CLOCK			CS_OPTION_BIT_2		// No reference clock available
#define	CSMV_AOHW_OPTIONS_CS12380					CS_OPTION_BIT_3		// Cs12380 card (190 MHz OScillator)
#define	CSMV_AOHW_OPTIONS_NOOSC1					CS_OPTION_BIT_4		// No first oscilator
#define	CSMV_AOHW_OPTIONS_NOOSC2					CS_OPTION_BIT_5		// No second oscilator


// Options that require Special Firmware
#define	CSMV_AOHW_OPT_FWREQUIRED_MASK				0



//
// Addon Firmware options
//
#define	CSMV_AOFW_OPTION_DIGITAL_TRIG				CS_OPTION_BIT_0		// Digital trigger


#endif	// __CsIoctl__h_
