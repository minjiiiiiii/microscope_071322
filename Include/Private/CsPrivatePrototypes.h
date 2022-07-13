/////////////////////////////////////////////////////////////
//! \file CsPrivatePrototypes.h
//!    \brief Gage Application Programming Interface (API)
//!
/////////////////////////////////////////////////////////////
#ifndef _CS_PRIVATE_PROTOTYPES_H_
#define _CS_PRIVATE_PROTOTYPES_H_

#include "CsPrivateStruct.h"
#pragma once

#ifdef __cplusplus
extern "C"{
#endif

#ifdef __linux__
#define SSM_API
#else
#define SSM_API __stdcall
#endif

//!
//! \ingroup SSM_API
//! \{
//!

int32 SSM_API CsReInitialize(int16 i16Action);
//! \fn int32 SSM_API CsReInitialize(int16 i16Action);
//!	\brief Completely reinitializes the Gage Driver for further processing.
//! \param i16Action	: Action to take. if > 0 the drives are reorganized (i.e master / slave systems may be treated as 2 boards)
//!										  if < 0 the drivers are completely reinitialized
//!	\return
//!		- >= 0					: Number of system available for locking
//!		- CS_SOCKET_NOT_FOUND	: Some socket error
//!		- CS_SOCKET_ERROR		: Unable to communicate with RM
//!
//! \sa CsInitialize
////////////////////////////////////////////////////////////////////

int32 SSM_API CsGetAvailableSystems(void);
//! \fn int32 SSM_API CsGetAvailableSystems(void);
//!	\brief Returns the number of available systems
//!
//!	\return
//!		- >= 0					: Number of available systems.
//!		- CS_NOT_INITIALIZED    : Call to CsInitialize has not been successful.
//!		- CS_SOCKET_ERROR       : Communication error with Resource Manager.
//!
//! \sa CsGetSystem
////////////////////////////////////////////////////////////////////

int32 SSM_API CsLock(CSHANDLE hSystem, BOOL bLock);

// Inter-Process handle functions
int32 SSM_API CsBorrowSystem(CSHANDLE* phSystem, uInt32 u32BoardType, uInt32 u32Channels, uInt32 u32SampleBits, int16 i16Index );
int32 SSM_API CsReleaseSystem(CSHANDLE);

#ifndef __linux__ // for now
// int32 SSM_API CsRegisterCallbackFnc(CSHANDLE hSystem, uInt32 u32Event, LPCsEventCallback pCallBack);
int32 SSM_API CsRegisterStreamingBuffers(CSHANDLE hSystem, uInt8 u8CardIndex, CSFOLIOARRAY* pStmBufferList, HANDLE* phSemaphore, PSTMSTATUS* pStmStatus);
int32 SSM_API CsReleaseStreamingBuffers(CSHANDLE hSystem, uInt8 u8CardIndex);
#endif
// Function to get hardware or firmware option names. i32OptionType can currently be either
// CS_HARDWARE_OPTION_TYPE or CS_FIRMWARE_OPTION_TYPE
int32 SSM_API CsGetOptionText(uInt32 u32BoardType, int32 i32OptionType, PCS_HWOPTIONS_CONVERT2TEXT pOptionText);

int32 SSM_API CsGetFwlCsiInfo(PFWLnCSI_INFO pBuffer, uInt32 *u32BufferSize);

#define CsIsLegacyBoard(u32BoardType ) ( \
		( ((uInt32)u32BoardType == CS8500_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CS82G_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CS12100_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CS1250_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CS1220_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CS1210_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CS14100_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CS1450_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CS1610_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CS1602_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CS3200_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CS85G_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CPCI_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CS1610C_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CS14100C_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CS82GC_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CS85GC_BOARDTYPE ) || \
		  ((uInt32)u32BoardType == CS3200C_BOARDTYPE ) ) ? TRUE : FALSE)


#define CsIsCombineBoard( u32BoardType) ((((uInt32)u32BoardType >= CS_COMBINE_FIRST_BOARD) &&  ((uInt32)u32BoardType <= CS_COMBINE_LAST_BOARD) ) ? TRUE : FALSE)
#define CsIsDemoBoard( u32BoardType) ((((uInt32)u32BoardType >= CSDEMO_BT_FIRST_BOARD) &&  ((uInt32)u32BoardType <= CSDEMO_BT_LAST_BOARD) ) ? TRUE : FALSE)
#define CsIsVirginBoard( u32BoardType) (((uInt32)u32BoardType == PLX_BASED_BOARDTYPE) ? TRUE : FALSE)
#define CsIsBrainBoard( u32BoardType) ( ((uInt32)u32BoardType == CSBRAIN_BOARDTYPE) ? TRUE : FALSE)
#define CsIsBunnyBoard( u32BoardType) ( \
                                      ( ((uInt32)u32BoardType == CS_BASE8_BOARDTYPE)|| \
									    ((uInt32)u32BoardType == CSX11G8_BOARDTYPE) || \
										((uInt32)u32BoardType == CSX21G8_BOARDTYPE) || \
										((uInt32)u32BoardType == CSX22G8_BOARDTYPE) || \
									    ((uInt32)u32BoardType == CSX23G8_BOARDTYPE) || \
										((uInt32)u32BoardType == CSX13G8_BOARDTYPE) || \
										((uInt32)u32BoardType == CSX14G8_BOARDTYPE) ) ? TRUE : FALSE)
#define CsIsDeereBoard(u32BoardType)  ( \
                                      ( ((uInt32)u32BoardType == CS12500_BOARDTYPE) || \
                                        ((uInt32)u32BoardType == CS121G_BOARDTYPE ) || \
                                        ((uInt32)u32BoardType == CS122G_BOARDTYPE ) || \
                                        ((uInt32)u32BoardType == CS14250_BOARDTYPE) || \
                                        ((uInt32)u32BoardType == CS14500_BOARDTYPE) || \
                                        ((uInt32)u32BoardType == CS141G_BOARDTYPE ) ) ? TRUE : FALSE)
#define CsIsUsbBoard( u32BoardType) ( ((uInt32)u32BoardType == CSUSB_BOARDTYPE) ? TRUE : FALSE)

#define CsIsBunnyPciEx( u32BoardType) ( ( ((uInt32)u32BoardType == (CSNUCLEONBASE_BOARDTYPE|CSX14G8_BOARDTYPE) )|| \
										((uInt32)u32BoardType == (CSNUCLEONBASE_BOARDTYPE|CSX24G8_BOARDTYPE) ) ) ? TRUE : FALSE)

#define CsIsRabbitPci(u32BoardType) ((((uInt32)u32BoardType >= CS22G8_BOARDTYPE) &&  ((uInt32)u32BoardType <= CS11G8_BOARDTYPE) ) ? TRUE : FALSE)
#define CsIsRabbitPciEx(u32BoardType) ( CsIsBunnyPciEx( u32BoardType) || \
										(((uInt32)u32BoardType >= (CSNUCLEONBASE_BOARDTYPE|CSxyG8_FIRST_BOARD)) &&  ((uInt32)u32BoardType <= (CSNUCLEONBASE_BOARDTYPE|CSxyG8_LAST_BOARD)) ) ? TRUE : FALSE)
#define CsIsRabbitBoard(u32BoardType) ( CsIsRabbitPci(u32BoardType) || CsIsRabbitPciEx(u32BoardType) )

#define CsIsSpiderPci(u32BoardType) ((((uInt32)u32BoardType >= CS8_BT_FIRST_BOARD) &&  ((uInt32)u32BoardType <= CS8_BT_LAST_BOARD) ) ? TRUE : FALSE)
#define CsIsSpiderPciEx(u32BoardType) ((((uInt32)u32BoardType >= (CSNUCLEONBASE_BOARDTYPE|CS8_BT_FIRST_BOARD)) &&  ((uInt32)u32BoardType <= (CSNUCLEONBASE_BOARDTYPE|CS8_BT_LAST_BOARD)) ) ? TRUE : FALSE)
#define CsIsSpiderBoard(u32BoardType) ( CsIsSpiderPci(u32BoardType) || CsIsSpiderPciEx(u32BoardType) )

#define CsIsSplendaPci( u32BoardType) ((((uInt32)u32BoardType >= CS16xyy_BT_FIRST_BOARD) &&  ((uInt32)u32BoardType <= CS16xyy_LAST_BOARD) ) ? TRUE : FALSE)
#define CsIsSplendaPciEx( u32BoardType) ((((uInt32)u32BoardType >= (CSNUCLEONBASE_BOARDTYPE|CS16xyy_BT_FIRST_BOARD)) &&  ((uInt32)u32BoardType <= (CSNUCLEONBASE_BOARDTYPE|CS16xyy_LAST_BOARD)) ) ? TRUE : FALSE)
#define CsIsSplendaBoard(u32BoardType) ( CsIsSplendaPci(u32BoardType) || CsIsSplendaPciEx(u32BoardType) )

#define CsIsOscarBoard(u32BoardType) ((((uInt32)u32BoardType >= CSE4abc_FIRST_BOARD) &&  ((uInt32)u32BoardType <= CSE4abc_LAST_BOARD) ) ? TRUE : FALSE)

#define CsIsNucleon(u32BoardType) ( 0 != (CSNUCLEONBASE_BOARDTYPE & u32BoardType) )
#define CsIsFciDevice(u32BoardType) ( 0 != (FCI_BOARDTYPE & u32BoardType) )

#define CsIsDecadeBoard(u32BoardType) ((((uInt32)u32BoardType >= CSDECADE_FIRST_BOARD) &&  ((uInt32)u32BoardType <= CSDECADE_LAST_BOARD) ) ? TRUE : FALSE)
#define CsIsHexagonBoard(u32BoardType) ((((uInt32)u32BoardType >= CSHEXAGON_FIRST_BOARD) &&  ((uInt32)u32BoardType <= CSHEXAGON_LAST_BOARD) ) ? TRUE : FALSE)

#define CsIsPciExpress(u32BoardType) ((CsIsNucleon(u32BoardType) || CsIsDecadeBoard(u32BoardType) || CsIsDecadeBoard(u32BoardType) || CsIsHexagonBoard(u32BoardType)) ? TRUE : FALSE)

#ifdef __cplusplus
}
#endif

#endif
