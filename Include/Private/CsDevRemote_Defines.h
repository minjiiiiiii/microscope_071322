#ifndef __CS_SOCKET_COMMANDS_H__
#define __CS_SOCKET_COMMANDS_H__

const short CS_GET_ACQUISITION_SYSTEM_COUNT		= 0;
const short CS_GET_ACQUISITION_SYSTEM_HANDLES	= 1;
const short CS_ACQUISITION_SYSTEM_INIT			= 2;
const short CS_GET_ACQUISITION_SYSTEM_INFO		= 3;
const short CS_GET_BOARDS_INFO					= 4;
const short CS_GET_ACQUISITION_SYSTEM_CAPS		= 5;
const short CS_ACQUISITION_SYSTEM_CLEANUP		= 6;
const short CS_GET_PARAMS						= 7;
const short CS_SET_PARAMS						= 8;
const short CS_VALIDATE_PARAMS					= 9;
const short CS_GET_ACQUISITION_STATUS			= 10;
const short CS_ACTION_DO						= 11;
const short CS_TRANSFER_DATA					= 12;
const short CS_TRANSFER_DATA_EX					= 13;
const short CS_OPEN_SYSTEM_FOR_RM				= 14;
const short CS_CLOSE_SYSTEM_FOR_RM				= 15;
const short CS_SET_SYSTEM_IN_USE				= 16;
const short CS_IS_SYSTEM_IN_USE					= 17;
const short CS_GET_SOCKET_OWNER					= 18;
//const short CS_AUTO_FIRMWARE_UPDATE				= 20;
//const short CS_CFG_AUX_IO						= 21;
//const short CS_GET_BOARD_CAPS					= 22;



const int g_CommandSize = sizeof(short);
const int g_CommandCount = 18;

const int g_MaxBoards = 8;

const int g_isPointer = 0x8000;
const int g_wantReturn = 0x4000;

typedef enum _CSFCITYPE
{
	CS_CHAR, 
	CS_INT8,
	CS_UINT8,
	CS_INT16,
	CS_UINT16,
	CS_INT32,
	CS_UINT32,
	CS_INT64,
	CS_BOOL,
	CS_DRVHANDLE,
	CS_VOID,
	CS_SYSTEMCONFIG,
	CS_SYSTEMINFO,
	CS_BOARDINFO_ARRAY,
	CS_IN_TRANSFERDATA,
	CS_OUT_TRANSFERDATA,
	CS_IN_TRANSFERDATAEX,
	CS_OUT_TRANSFERDATAEX,
	CS_EVENTHANDLE,
	CS_TX_DATARESULT,
	CS_HWOPTIONS_TEXT,
	CS_FWOPTIONS_TEXT
} _CSFCITYPE;

#pragma pack(1)

typedef struct _Preamble
{
	short sCommand;
	WORD  wHeaderSize;
	DWORD dwTotalSize;
} Preamble;

#pragma pack()
#endif // __CS_SOCKET_COMMANDS_H__