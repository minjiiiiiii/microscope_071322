/////////////////////////////////////////////////////////////
//! \file CsSsmDebug.h
//!    \brief Debug stub for SSM library
//!
/////////////////////////////////////////////////////////////


#pragma once

#ifdef __cplusplus
extern "C"{
#endif

//! \defgroup SSM_DEBUG_API
//! \{
//!

int32 SSM_API CsDebugRetrieveStateName(CSHANDLE hSystem, LPTSTR szStateName, int16 i16Length);
//! \fn int32 SSM_API CsDebugRetrieveStateName(CSHANDLE hSystem, LPTSTR szStateName, int16 i16Length)
//! \brief Retrieve the current state name
//!
//! \param hSystem : Handle of valid system
//! \param pBuffer : Output buffer to receive the state name
//! \param i16Size : Size of allocated buffer
//!
//! \return
//!	    - Number of bytes copied to the buffer
//!
/*************************************************************/

int32 SSM_API CsDebugSetTrace(CSHANDLE hSystem, int8 bEnable, ostream& debug_stream);
//! \fn int32 SSM_API CsDebugSetTrace(CSHANDLE hSystem, int8 bEnable, ostream& debug_stream)
//! \brief Change the stream buffer used by internal SSM for tracing
//!
//! \param hSystem : Handle of valid system
//! \param bEnable : Enable the tracing mechanism for internal SSM
//! \param debug_stream : New output stream
//!
//! \return
//!	    - Always TRUE
//!
/*************************************************************/

bool  SSM_API CsDebugPerformTransition(CSHANDLE hSystem, int16 i16Transition);
//! \fn bool  SSM_API CsDebugPerformTransition(CSHANDLE hSystem, int16 i16Transition);
//! \brief Perform the requested transition manually. 
//!
//! \param hSystem : Handle of valid system
//! \param i16Transition : Transition to perfrom
//!
//! \return
//!	    - true: Transition was performed successfully
//!	    - false: Invalid transition or system is not initialized
//!
/*************************************************************/

int32 SSM_API CsTraceConfiguration_Acquisition(CSACQUISITIONCONFIG& configAcquisition);
//! \fn int32 SSM_API CsTraceConfiguration_Acquisition(CSACQUISITIONCONFIG& configAcquisition)
//! \brief Trace all the elements of the structure  
//!
//! \param configAcquisition : Acquisition Configuration
//!
//! \return
//!	    - CS_SUCCESS: Trace was performed
//!	    - else: Error code
//!
/*************************************************************/

int32 SSM_API CsTraceConfiguration_Channels(PARRAY_CHANNELCONFIG& arrayChannels);
//! \fn int32 SSM_API CsTraceConfiguration_Channel(PARRAY_CHANNELCONFIG& arrayChannels)
//! \brief Trace all the elements of the structure  
//!
//! \param arrayChannels : Configuration for all channels
//!
//! \return
//!	    - CS_SUCCESS: Trace was performed
//!	    - else: Error code
//!
/*************************************************************/

int32 SSM_API CsTraceConfiguration_Triggers(PARRAY_TRIGGERCONFIG& arrayTriggers);
//! \fn int32 SSM_API CsTraceConfiguration_Trigger(PARRAY_TRIGGERCONFIG& arrayTriggers)
//! \brief Trace all the elements of the structure  
//!
//! \param arrayTriggers : Configuration for all triggers
//!
//! \return
//!	    - CS_SUCCESS: Trace was performed
//!	    - else: Error code
//!
/*************************************************************/

//!
//! \}
//!

#ifdef __cplusplus
}
#endif