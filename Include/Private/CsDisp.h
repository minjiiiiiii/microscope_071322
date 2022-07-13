/////////////////////////////////////////////////////////////
//! \file CsDisp.h
//!    \brief Low level drivers exported function
//!
/////////////////////////////////////////////////////////////

#ifndef _CSDISP_H_
#define _CSDISP_H_

#include "CsErrors.h"
#include "CsTypes.h"
#include "CsStruct.h"
#include "CsPrivateStruct.h"

#ifdef __cplusplus
	extern "C"
	{
#endif

#ifdef __linux__
	void __attribute__((constructor)) init_Disp(void);
	void __attribute__ ((destructor)) cleanup_Disp(void);
#endif

// Private functions
BOOL	GetSharedSection(BOOL bUsingCsRm);
void	DeleteSharedSection();
uInt32	InitializationGlobal();
int32	InitializationPerProcess();
uInt16	GetNumberOfDrivers();
uInt32	GetDrvDllFileNames();
void	CleanupGlobal();
void	CleanupPerProcess();
void	GetHwDllFunctionPointers();

// Exported functions

//! \defgroup HWDLL_API CsDrv (Dispatch) API
//! \{
//!

int32 CsDrvAutoFirmwareUpdate();
//! \fn uInt32 CsDrvAutoFirmwareUpdate()
//! \brief Request Kernel Driver for updating FPGA firmware.
//!
//! Request Kernel Driver for updating FPGA firmware.
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!


int32 CsDrvGetAcquisitionSystemCount( uInt16 bForceIndependantMode, uInt16* pu16SystemFound );
//! \fn uInt32 CsDrvGetAcquisitionSystemCount( uInt16 bForceIndependentMode, uInt16* pu16SystemFound )
//! \brief Get the number of acquisition system.
//!
//! Get the number of acquisition system.
//!
//! \param bForceIndependentMode	: Configuration mode
//! \param pu16SystemFound	: pointer to variable that receive number of system found
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!
//! \sa CsDrvGetAcquisitionSystemHandles
//!

uInt32 CsDrvGetAcquisitionSystemHandles( PDRVHANDLE pDrvHdl, uInt32 u32Size );
//! \fn uInt32 CsDrvGetAcquisitionSystemHandles( PDRVHANDLE pDrvHdl, uInt32 u32Size )
//! \brief Get the table of drivers handles for acquisition systems.
//!
//! Get the table of drivers handles for acquisition systems.  Each drivers handle identifies one acquisition system
//!
//! \param pDrvHdl	: Pointer to the buffer allocated by callers
//! \param u32Size	: The buffer size
//!
//! \return
//!	    - The number of drivers handles copied to the buffer
//!



int32 CsDrvGetAcquisitionSystemInfo(CSHANDLE CsHandle, PCSSYSTEMINFO pSysInfo);
//! \fn int32 CsDrvGetAcquisitionSystemInfo(CSHANDLE CsHandle, PCSSYSTEMINFO pSysInfo)
//!	\brief Retrieves the static information  about the CompuScope system
//!
//! This method queries static or unchangeable information about the CompuScope system, such as sample resolution
//! and memory size. To query for dynamic parameters settings the CsDrvGetParams method should be used.
//!
//! \param CsHandle	: Driver handle
//! \param pSysInfo	:	pointer to the structure CSSYSTEMINFO.
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!
//! \sa CsDrvGetAcquisitionSystemCaps
/*************************************************************/

int32 CsDrvGetAcquisitionSystemCaps(CSHANDLE CsHandle, uInt32 CapsId, PCSSYSTEMCONFIG pSysCfg, void *pBuffer, uInt32 *BufferSize);
//! \fn int32 CsDrvGetAcquisitionSystemCaps(CSHANDLE CsHandle, uInt32 CapsId, PCSSYSTEMCONFIG pSysCfg, void *pBuffer, uInt32 *BufferSize);
//!	\brief Retrieves the capabilities of the CompuScope system in its current configuration
//!
//! This method is designed to dynamically query capabilities of the CompuScope hardware. The returned parameters are valid for
//! current CompuScope configuration. Usually, this method is called twice.
//! On the first call the pBuffer parameter is passed as NULL and method assigns *pBufferSize the size of the buffer
//! required to hold the requested data. The calling process can then allocate a sufficient buffer and pass its address to the method
//! on the second call. The user may query different capabilities by using different CapsId .
//!
//! \param CsHandle		: CsHandle of acquisition system.
//! \param CapsId		: Can be one of followings CAPS_SAMPLE_RATES,CAPS_INPUT_RANGES,,CAPS_IMPEDANCES, CAPS_COUPLINGS
//! \param pSysCfg		: Pointer to CSSYSTEMCONFIG structure filled by the caller with the current configuration
//! \param pBuffer		: Pointer to buffer allocated by caller
//! \param BufferSize	: buffer size
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!

int32 CsDrvGetBoardsInfo(CSHANDLE CsHandle, PARRAY_BOARDINFO pBoardInfo);
//! \fn int32 CsDrvGetBoardsInfo(CSHANDLE CsHandle, PARRAY_BOARDINFO pBoardInfo);
//! \brief Get information about the CompuScope system
//!
//! Get information about the CompuScope system
//!
//! \param CsHandle		: CsHandle of acquisition system.
//! \param pBoardInfo	: pointer to structure ARRAY_BOARDINFO
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!
//! \sa CsDrvGetSystemInfo
/*************************************************************/

int32 CsDrvAcquisitionSystemInit( CSHANDLE	CsHandle, BOOL bSystemDefaultSetting );
//! \fn int32 CsDrvAcquisitionSystemInit( CSHANDLE	CsHandle, BOOL bSystemDefaultSetting )
//! \brief Initialization of the system
//!
//! This function should be called before using any other functions with CSHANDLE as
//! the first parameter Dll's internal variables related to system will be initialized.
//!
//! \param CsHandle				 : CsHandle of acquisition system.
//! \param bSystemDefaultSetting : Reset to the default setting. Calibration will be done if necessary
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!
//! \sa CsDrvAcquisitionSystemCleanup
/*************************************************************/

int32 CsDrvAcquisitionSystemCleanup(CSHANDLE CsHandle);
//! \fn int32 CsDrvAcquisitionSystemCleanup(CSHANDLE CsHandle)
//! \brief This function should be called when the acquisition system is no longer used.
//!
//! This function should be called when the acquisition system is no longer used.
//!
//! \param CsHandle    : CsHandle of acquisition system.
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!
//! \sa CsDrvAcquisitionSystemInit
/*************************************************************/

int32 CsDrvGetAcquisitionStatus(CSHANDLE CsHandle, uInt32* pu32Status);
//! \fn int32 CsDrvGetAcquisitionStatus(CSHANDLE CsHandle, uInt32* pu32Status);
//! \brief Queries the status of the CompuScope system
//!
//! Queries the status of the CompuScope system
//!
//! \param CsHandle	   : CsHandle of acquisition system.
//! \param pu32Status  : pointer to variable that receive the current status
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!
//! \sa CsDrvDo
/*************************************************************/

int32 CsDrvUpdateLookupTable(DRVHANDLE DrvHdl, CSHANDLE CsHandle);
//! \fn int32 CsDrvUpdateLookupTable(DRVHANDLE DrvHdl, CSHANDLE CsHandle);
//! Create an alias for the driver handle.
//!
//! Create an alias for the driver handle.
//!
//! \param DrvHdl : Driver handle
//! \param CsHandle  : New alias (CsHandle of acquisition system)
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!
//! \sa  CsDrvAcquisitionSystemInit
/*************************************************************/

int32 CsDrvGetParams(CSHANDLE CsHandle, uInt32 ParamID, void *Parambuffer);
//! \fn int32 CsDrvGetParams(CSHANDLE, uInt32 ParamID, void *Parambuffer);
//! \brief Get the current configuration parameters of acquisition system.
//!
//! \param CsHandle    : CsHandle of acquisition system.
//! \param ParamID     : Constant that identifies the Cs parameters requested.
//! \param Parambuffer : Pointer to buffer allocated and initialized by caller.
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!
//! \sa CsDrvValidateParams, CsDrvSetParams
/*************************************************************/

int32 CsDrvSetParams(CSHANDLE CsHandle, uInt32 ParamID, void *Parambuffer);
//! \fn int32 CsDrvSetParams(CSHANDLE, uInt32 ParamID, void *Parambuffer);
//! \brief Set the new configuration parameters of acquisition system.
//!
//! \param CsHandle    : CsHandle of acquisition system.
//! \param ParamID     : Constant that identifies the Cs parameters requested.
//! \param Parambuffer : Pointer to buffer allocated and initialized by caller.
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!
//! \sa CsDrvValidateParams, CsDrvGetParams
/*************************************************************/

int32 CsDrvValidateParams(CSHANDLE CsHandle, uInt32 ParamID, uInt32 Coerce, void *Parambuffer);
//! \fn int32 CsDrvValidateParams(CSHANDLE, uInt32 ParamID, uInt32 Coerce, void *Parambuffer)
//!
//! \brief Validation of the configuration parameters of acquisition system.
//!
//! Validation of the configuration parameters of acquisition system.
//! If no coerce is used, function will return error if there is any
//!	parameters that do not match the capacity of acquisition system.
//! If coerce is used and if there is any parameters that do not match the capacity
//! of acquisition system, this function will use a predefined auto correction to
//! correct the error.
//!
//! \param CsHandle    : CsHandle of acquisition system.
//! \param ParamID     : Constant that identifies the Cs parameters to be validated
//! \param Coerce      : If no coerce is used, function will return error if there is any
//!						 parameters that de
//! \param Parambuffer : Pointer to buffer allocated and initialized by caller with parameters to be validated.
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!
//! \sa CsDrvSetParams, CsDrvGetParams
/*************************************************************/

int32 CsDrvDo(CSHANDLE CsHandle, uInt32 ActionID, void* pActionBuffer);
//! \fn int32 CsDrvDo(CSHANDLE, uInt32 ActionID, void* pActionBuffer );
//! \brief Performs an operation on the CompuScope system
//!
//! \param CsHandle      : CsHandle of acquisition system.
//! \param ActionID      : Constant that defines the action (ACTION_START, ACTION_STOP ...)
//! \param pActionBuffer : Pointer to buffer allocated and initialized by caller with parameters to be validated.
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!
//! \sa CsDrvSetParams, CsDrvGetParams
/*************************************************************/


int32 CsDrvTransferData(CSHANDLE CsHandle, IN_PARAMS_TRANSFERDATA inParams, POUT_PARAMS_TRANSFERDATA pOutParams );

//! \fn int32 int32 CsDrvTransferData(CSHANDLE CsHandle, IN_PARAMS_TRANSFERDATA inParams, POUT_PARAMS_TRANSFERDATA pOutParams )
//! \brief Transfer data from acquisition system memory to user allocated buffer.
//!
//! Transfer data from acquisition system memory to user allocated buffer.
//! This function can run in both synchronous or asynchronous mode.
//! If hTransferEvent parameters is NULL, this function will return only when data transfer is  completed.
//! If hTransferEvent parameters is not NULL, this function will return right after data transfer is
//! initiated. The caller should check on the Event for completion of data transfer.
//!
//! \param CsHandle   : CsHandle of acquisition system.
//! \param inParams	  : Pointer to the IN_PARAMS_TRANSFERDATA structure containing requested data transfer settings and data buffer pointer
//! \param pOutParams : Pointer to the OUT_PARAMS_TRANSFERDATA structure that is filled with actual data transfer settings
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!
//! \sa CsDrvDo
/*************************************************************/

int32 CsDrvTransferDataEx(CSHANDLE CsHandle, PIN_PARAMS_TRANSFERDATA_EX pInParams, POUT_PARAMS_TRANSFERDATA_EX pOutParams );

//! \fn int32 int32 CsDrvTransferDataEx(CSHANDLE CsHandle, PIN_PARAMS_TRANSFERDATA_EX pInParams, POUT_PARAMS_TRANSFERDATA pOutParams )
//! \brief Transfer data from acquisition system memory to user allocated buffer.
//!
//! Transfer data from acquisition system memory to user allocated buffer.
//! This function can run in both synchronous or asynchronous mode.
//! If hTransferEvent parameters is NULL, this function will return only when data transfer is  completed.
//! If hTransferEvent parameters is not NULL, this function will return right after data transfer is
//! initiated. The caller should check on the Event for completion of data transfer.
//!
//! \param CsHandle   : CsHandle of acquisition system.
//! \param inParams	  : Pointer to the IN_PARAMS_TRANSFERDATA_EX structure containing requested data transfer settings and data buffer pointer
//! \param pOutParams : Pointer to the OUT_PARAMS_TRANSFERDATA_EX structure that is filled with actual data transfer settings
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!
//! \sa CsDrvDo
/*************************************************************/

int32 CsDrvGetAsyncTransferDataResult(CSHANDLE CsHandle, uInt8 u8Token, CSTRANSFERDATARESULT *pTxDataResult, BOOL bWait );
//! \fn int32 int32 CsDrvGetAsyncTransferDataResult(CSHANDLE CsHandle, uInt8 u8Token, CSTRANSFERDATARESULT *pTxDataResult, BOOL bWait )
//! \brief Query the result of the transfer specified by the i32Token
//!
//! This method is used to  query the result of an asynchronous transfer initiated by a call
//! to the CsGetTransferAS API method.
//!
//! \param CsHandle	     : Handle of the CompuScope system to be addressed.
//! \param u8Token	     : Token specifying the transfer to be queried
//! \param pTxDataResult : Pointer to the CSTRANSFERDATARESULT variable that is filled with the number of bytes already transferred and status of the transfer
//! \param bWait         : Wait for the transfer completion
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!


int32 CsDrvRegisterEventHandle(CSHANDLE CsHandle, uInt32 EventType, /*EVENT_HANDLE*/ HANDLE *EventHandle);
//! \fn int32 CsDrvRegisterEventHandle(CSHANDLE, uInt32 EventType, HANDLE *EventHandle);
//! \brief Register an event handle for either TRIGGERED event or END_OF_ACQUISITION event.
//!
//! Register an event handle for either TRIGGERED event or END_OF_ACQUISITION event.
//!
//! \param CsHandle		: CsHandle of acquisition system
//! \param EventType    : Can be either ACQ_EVENT_TRIGGERD or ACQ_EVENT_END_BUSY
//! \param EventHandle	: Pointer to the event created by the caller.
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!
/*************************************************************/

int32 CsDrvExpertCall( CSHANDLE CsHandle,  void *FuncParams );
//! \fn int32 CsDrvExpertCall( CSHANDLE CsHandle,  void *FuncParams )
//! \brief Generic call for extended functionality of the eXpert line
//!
//!Generic call for extended functionality of the eXpert line
//!
//! \param CsHandle    : CsHandle of acquisition system.
//! \param FuncParams  : Pointer to buffer allocated and initialized by the caller.
//!
//! \return
//!	    - CS_SUCCESS (0) indicates success. Otherwise return error code < 0
//!
//! \sa CsDrvDo
/*************************************************************/

//! \}

#ifndef __linux__ // for now
int32 CsDrvRegisterStreamingBuffers(CSHANDLE, uInt8, CSFOLIOARRAY *, HANDLE *, PSTMSTATUS *);
int32 CsDrvReleaseStreamingBuffers(CSHANDLE, uInt8 );
#endif

int32 CsDrvCfgAuxIo(CSHANDLE CsHandle);
int32 CsDrvOpenSystemForRm( DRVHANDLE	DrvHdl );
int32 CsDrvCloseSystemForRm( DRVHANDLE	DrvHdl );
int32 _CsDrvGetHwOptionText(uInt32 u32BoardType, PCS_HWOPTIONS_CONVERT2TEXT pHwOptionsText);
int32 _CsDrvGetFwOptionText(uInt32 u32BoardType, PCS_FWOPTIONS_CONVERT2TEXT pFwOptionsText);
int32 _CsDrvGetFwlCsiInfo( PFWLnCSI_INFO pBuffer, uInt32 *u32BufferSize );
int32 _CsDrvGetBoardCaps(uInt32	u32ProductId, uInt32 CapsId, void *pBuffer, uInt32 *BufferSize);
uInt32 CsDrvGetAcquisitionSystemHandlesDbg( PDRVHANDLE pDrvHdl, uInt32 u32Size );

int32	CsDrvStmAllocateBuffer( CSHANDLE CsHandle, int32 nCardIndex, uInt32 u32BufferSize, PVOID *pVa );
int32	CsDrvStmFreeBuffer( CSHANDLE CsHandle, int32 nCardIndex, PVOID pVa );
int32	CsDrvStmTransferToBuffer( CSHANDLE CsHandle, int32 nCardIndex, PVOID pBuffer, uInt32 u32TransferSize );
int32	CsDrvStmGetTransferStatus( CSHANDLE CsHandle, int32 nCardIndex, uInt32 u32TimeoutMs, uInt32 *u32ErrorFlag, uInt32 *u32ActualSize, PVOID Reserved );
int32	CsDrvSetRemoteSystemInUse( CSHANDLE CsHandle, BOOL bSet ); // bSet = 1 or 0 to mark as in use or not
int32	CsDrvIsRemoteSystemInUse( CSHANDLE CsHandle, BOOL* bSet ); // returns TRUE is remote system is being used
int32	CsDrvGetRemoteUser( CSHANDLE CsHandle, TCHAR* lpUser ); // returns the ip address of the owner of the remote handle
#ifdef __cplusplus
}
#endif

#endif   // _GAGEDISP_H_
