/////////////////////////////////////////////////////////////
//! \file RmFunctions.h
//!    \brief Programming interface for Resource Manager
//!
/////////////////////////////////////////////////////////////

//! \defgroup RM_API
//! \{
//!

#ifndef __RMFUNCTIONS_H__
#define __RMFUNCTIONS_H__

#include "CsTypes.h"
#include "CsStruct.h"
#include "CsPrivateStruct.h"


#define DllImport
#if defined (_WIN32)
#define DllExport __stdcall
#else
#define DllExport
#endif

#ifdef	__cplusplus
extern "C"	{
#endif

int32 DllExport CsRmInitialize(void);
//! \fn int32 DllExport CsRmInitialize(void);
//! \brief Initializes both the Gage driver and several data structures.
//!
//! \return
//!		- >= 0					: Total number of systems
//!		- CS_SOCKET_NOT_FOUND	: Some socket error
//!		- CS_SOCKET_ERROR		: Unable to communicate with Resource Manager
//!		- CS_NO_SYSTEMS_FOUND	: No available systems were found
//!		- CS_MEMORY_ERROR		: Could not allocate memory in Resource Manager
//!
//!	\warning Must be the first driver function called.
//!
/*************************************************************/

int32 DllExport CsRmReInitialize(int16 i16Action);
//! \fn int32 DllExport CsRmReInitialize(void);
//! \brief Re-initializes both the Gage driver and several data structures.
//!
//! \param i16Action			: 1 means reorganize systems as individual boards and do a hard reinitialize, < 0 is just a hard reinitialize, 0 is just a regular initialize.
//!
//! \return
//!		- >= 0					: Number of system available for locking
//!		- CS_SOCKET_NOT_FOUND	: Some socket error
//!		- CS_SOCKET_ERROR		: Unable to communicate with Resource Manager
//!		- CS_NO_SYSTEMS_FOUND	: No available systems were found
//!		- CS_MEMORY_ERROR		: Could not allocate memory in Resource Manager
//!
//!
//!
/*************************************************************/

int32 DllExport CsRmGetAvailableSystems(void);
//! \fn int32 DllExport CsRmGetAvailableSystems(void);
//! \brief Returns the number of systems available for locking
//!
//! \return
//!	    - >= 0					: The number of systems available for locking
//!		- CS_SOCKET_ERROR		: Unable to communicate with Resource Manager
//!
//! \sa CsRmInitialize, CsRmGetSystem
/*************************************************************/

int32 DllExport CsRmLockSystem(RMHANDLE hSystemHandle);
//! \fn int32 DllExport CsRmLockSystem(RMHANDLE hSystemHandle);
//! \brief Marks a system identified by hSystemHandle as being active.
//!
//! \param hSystemHandle	: Handle of system to be locked, obtained from CsRmGetSystem.
//! \return
//!		- CS_SUCCESS			: Routine succeeded and system is now locked
//!		- CS_SOCKET_ERROR		: Unable to communicate with Resource Manager
//!		- CS_INVALID_HANDLE		: The parameter hSystemHandle does not exist
//!		- CS_HANDLE_IN_USE		: The parameter hSystemHandle is already locked by another process
//!
//!	\warning All systems obtained by CsRmLockSystem must be freed by CsRmFreeSystem.
//!	\warning User programs should use CsRmGetSystem rather then CsRmLockSystem.
//!
//! \sa CsRmGetSystem, CsRmFreeSystem
/*************************************************************/

int32 DllExport CsRmFreeSystem(RMHANDLE hSystemHandle);
//! \fn int32 DllExport CsRmFreeSystem(RMHANDLE hSystemHandle);
//! \brief Deallocate resources of the system and return it to the available pool of systems
//!
//! \param hSystemHandle	: Handle of system to be freed, obtained from CsRmGetSystem.
//!
//! \return
//!	    - CS_SUCCESS			: Routine succeeded and system was released
//!		- CS_INVALID_HANDLE		: The parameter hSystemHandle does not exist
//!		- CS_SOCKET_ERROR		: Unable to communicate with Resource Manager
//!
//!	\warning All systems obtained by CsRmGetSystem must be freed by CsRmFreeSystem.
//!
//! \sa CsRmGetSystem
/*************************************************************/

int32 DllExport CsRmIsSystemHandleValid(RMHANDLE hSystemHandle);
//! \fn int32 DllExport CsRmIsSystemHandleValid(RMHANDLE hSystemHandle);
//! \brief Checks the validity of the system handle, obtained from CsRmGetSystem.
//!
//! \param hSystemHandle	: Handle of system to check.
//!
//! \return
//!	    - CS_SUCCESS			: Handle is either available or being used by the calling process
//!	    - CS_INVALID_HANDLE		: The handle does not exist
//!	    - CS_HANDLE_IN_USE		: The handle is in use by another process
//!		- CS_SOCKET_ERROR		: Unable to communicate with Resource Manager
//!
//! \sa CsRmGetSystem
/*************************************************************/

int32 DllExport CsRmRefreshAllSystemHandles(void);
//! \fn int32 DllExport CsRmRefreshAllSystemHandles(void);
//! \brief Forces a refresh of the internal system list so that any system not in use for a long period is marked available.
//!
//! \return
//!	    - CS_SUCCESS			: Was able to refresh the system list
//!		- CS_FALSE				: Was not able to refresh the system list
//!		- CS_SOCKET_ERROR		: Unable to communicate with Resource Manager
//!
//!
/*************************************************************/

int32 DllExport CsRmGetSystem(uInt32 u32BoardType, uInt32 u32ChannelCount, uInt32 u32SampleBits, RMHANDLE *rmHandle, int16 i16Index = 0);
//! \fn int32 DllExport CsRmGetSystem(int16 i16BoardType, int16 i16ChannelCount, int16 i16SampleBits, RMHANDLE *rmHandle, int16 i16Index = 0);
//! \brief Lock and initialize the system corresponding to the request.
//!
//! \param u32BoardType		: Constant representing system board type, 0 = don't care.
//! \param u32ChannelCount	: Number of channels in desired system, 0 = don't care.
//! \param u32SampleBits	: Sample bits of desired system, 0 = don't care.
//! \param rmHandle			: Handle of locked system corresponding to parameters. NULL implies no system was locked.
//! \param i16Index			: index of system. Default is 0, corresponding to the first matching system.
//!
//! \return
//!	    - CS_SUCCESS				: System succeeded and a valid handle was returned in rmHandle
//!		- CS_NO_AVAILABLE_SYSTEM	: No system matching the specified criteria could be found
//!		- CS_SOCKET_ERROR			: Unable to communicate with Resource Manager
//!
//! \sa CsRmFreeSystem
/*************************************************************/

int32 DllExport CsRmGetNumberOfSystems(void);
//! \fn int32 DllExport CsRmGetNumberOfSystems(void);
//! \brief Returns the total number of systems, both available and in use.
//!
//! \return
//!	    - >= 0				: The total number of systems found.
//!		- CS_SOCKET_ERROR	: Unable to communicate with Resource Manager
//!
//! \sa CsRmGetSystem, CsRmIsHandleValid
/*************************************************************/

int32 DllExport CsRmGetSystemStateByIndex(int16 i16Index, CSSYSTEMSTATE* pSystemState);
//! \fn int32 DllExport CsRmGetSystemStateByIndex(int16 i16Index, CSSYSTEMSTATE* pSystemState);
//! \brief Retrieves information about the state of a system specified by system number rather then by a handle.
//!
//! \param i16Index     : System number of the system. Systems start at 0.
//! \param pSystemState	: pointer to a CSSYSTEMSTATE structure to retrieve the information.
//!
//! \return
//!	    - CS_SUCCESS		: Function succeeded and the information is in pSystemState
//!	    - CS_FALSE			: Function failed.  Index was invalid
//!		- CS_MEMORY_ERROR	: Function failed. pSystemState did not point to valid memory
//!		- CS_SOCKET_ERROR	: Unable to communicate with Resource Manager
//!
//!	\warning This routine is meant to be called by the Instrument Manager.
//!
//! \sa CsRmGetSystemInfo, CsRmGetSystemStateByHandle
/*************************************************************/

int32 DllExport CsRmGetSystemStateByHandle(RMHANDLE hSystemHandle, CSSYSTEMSTATE* pSystemState);
//! \fn int32 DllExport CsRmGetSystemStateByIndex(int16 i16Index, CSSYSTEMSTATE* pSystemState);
//! \brief Retrieves information about the state of a system specified by system number rather then by a handle.
//!
//! \param hSystemHandle: Unique handle that identifies a system.
//! \param pSystemState	: pointer to a CSSYSTEMSTATE structure to retrieve the information.
//!
//! \return
//!	    - CS_SUCCESS		: Function succeeded and the information is in pSystemState
//!	    - CS_INVALID HANDLE : Handle passed to function does not exist.
//!		- CS_MEMORY_ERROR	: Function failed. pSystemState did not point to valid memory
//!		- CS_SOCKET_ERROR	: Unable to communicate with Resource Manager
//!
//!	\warning This routine is meant to be called by the Instrument Manager.
//!
//! \sa CsRmGetSystemInfo, CsRmGetSystemStateByIndex
/*************************************************************/

int32 DllExport CsRmGetSystemInfo(RMHANDLE hSystemHandle, CSSYSTEMINFO* pSystemInfo);
//! \fn int32 DllExport CsRmGetSystemInfo(RMHANDLE hSystemHandle, CSSYSTEMINFO* pSystemInfo);
//! \brief Retrieves static information about the system specified by hSystemHandle.
//!
//! \param hSystemHandle	: Handle that specifies the system to retrieve information about.
//! \param pSystemInfo		: pointer to a CSSYSTEMINFO structure to retrieve the information.
//!
//! \return
//!	    - CS_SUCCESS		: Function succeeded, system information is in pSystemInfo
//!		- CS_INVALID_HANDLE : hSystemHandle is not a valid handle
//!		- CS_MEMORY_ERROR	: pSystemInfo does not point to valid memory
//!		- CS_SOCKET_ERROR	: Unable to communicate with Resource Manager
//!
//! \sa CsRmGetSystem
/*************************************************************/

#ifdef	__cplusplus
}
#endif

#endif // __RMFUNCTIONS_H__

//!
//! \}
//!
