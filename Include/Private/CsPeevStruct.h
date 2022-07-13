#ifndef _PEEVSTRUCT_H_
#define _PEEVSTRUCT_H_

#include "CsTypes.h"




#define		CS_PEEVADAPTOR_INVALID_CONFIG			-500000
#define		CS_PEEVADAPTOR_NOT_INIT					-500001


#define	PEEV_CTRLBITS	19			// Number of controls bits in PVADAPTORCONFIG struct

typedef union _PVADAPTORCONFIG
{
	uInt32	u32RegVal;

	struct
	{
		// 1
		unsigned int	uCtrlChan1 : 1;		// 0:Aux Input, 1:Dc Accuracy Input
		// 2
		unsigned int	uCtrlChan2 : 1;		// 0:Aux Input, 1:Dc Accuracy Input
		// 3
		unsigned int	uCtrlChan3 : 1;		// 0:Aux Input, 1:Dc Accuracy Input
		// 4
		unsigned int	uCtrlChan4 : 1;		// 0:Aux Input, 1:Dc Accuracy Input
		// 5
		unsigned int	uCtrlChan5 : 1;		// 0:Aux Input, 1:Dc Accuracy Input
		// 6
		unsigned int	uCtrlChan6 : 1;		// 0:Aux Input, 1:Dc Accuracy Input
		// 7
		unsigned int	uCtrlChan7 : 1;		// 0:Aux Input, 1:Dc Accuracy Input
		// 8
		unsigned int	uCtrlChan8 : 1;		// 0:Aux Input, 1:Dc Accuracy Input


		// 9
		unsigned int	uCtrlClkIn		:1;	// 0:Pass-thru, 1:Aux Src
		// 10
		unsigned int	uCtrlTrigIn		:1;	// 0:Pass-thru, 1:Aux Src

		// 11
		unsigned int	uCtrlClkOut		:1;	// 0:Pass-thru, 1:Feedback path
		// 12
		unsigned int	uCtrlTrigOut	:1;	// 0:Pass-thru, 1:Feedback path


		// 13
		unsigned int	uCtrlAuxSrc		:1;	// 0:TrigOut or ClkOut or GnD Path selected
											// 1:Aux source selected
		// 14
		unsigned int	uCtrlClkOutTrigOut	:1;		// 0: TriggerOut Selected for feedback path
													// 1: Secondary External instrument selected
		// 15
		unsigned int	uInputFeedBack	:1;			// 0: Input feedback path disabled
													// 1: Input feedback path enabled
		// 16
		unsigned int	uCtrlGndOn		:1;	// 0:Aux Src not-grounded, 1:Aux Src grounded.

		// 17
		unsigned int	uctrlLoopDc		:1;	// 0: OFF, 1: ON

		// 18
		unsigned int	uctrlLoopAux	:1;	// 0: OFF, 1: ON
		
		// 19
		unsigned int	uctrlAuxFilter	:1;	// 0: OFF, 1: ON
	} Bits;

} PVADAPTORCONFIG, *PPVADAPTORCONFIG;

typedef union _PVADAPTORCONFIG_BUNNY
{
	uInt32	u32RegVal;

	struct
	{
		// 1
		unsigned int	uCtrlChan1 : 1;		// 0:Aux Input, 1:Dc Accuracy Input
		// 2
		unsigned int	uCtrlChan2 : 1;		// 0:Aux Input, 1:Dc Accuracy Input
		// 3
		unsigned int	uCtrlAuxSrcSel	:1;	// 0:Trig Clk Out, 1:Aux Src
		// 4
		unsigned int	uCtrlAuxRouting	:1;	// 0:Trig Clk In, 1:Channels control
		// 5
		unsigned int	uCtrlAuxFilter	:1;	// 0:Pass-thru, 1:Ext filter
		// 6
		unsigned int	uCtrlClkTrig	:1;	// 0:Trig In/Out, 1:Clk In/Out
		// 7
		unsigned int	uCtrlTrigSel	:1;	// 0:Ext Trig, 1:Aux src
		// 8
		unsigned int	uCtrlClkSel	:1;	// 0:Ext Clk, 1:Aux src

	} Bits;

} PVADAPTORCONFIG_BUNNY, *PPVADAPTORCONFIG_BUNNY;


#endif

