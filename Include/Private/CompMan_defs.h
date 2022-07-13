#ifndef _CS_COMP_MAN_DEFS_H_
#define _CS_COMP_MAN_DEFS_H_

#ifdef _WIN32
    #pragma once
#endif

#if defined(_WIN32) || defined (_WIN64)
#include "CsSupport.h"
#else
#include "CsLinuxPort.h"
#endif

#include "CsTypes.h"
#include "CsPrivateStruct.h"

#define CS_MAN_STRING(x) (x)
#define CS_MAN_STRINGIFY(x) (#x)

#define BITMASK_CHECKED(x,y)    ( (BITMASK_CHECK(x,y)) == (y) ) /* The mask is the right hand operation (y)*/
#define BITMASK_CHECK(x,y)      ( (x) & (y) )

#define CS_MAN_ONE_KILOBYTE ( 1 << 10 )
#define CS_MAN_ONE_MEGABYTE ( 1 << 20 )
#define CS_MAN_ONE_GIGABYTE ( 1 << 30 )

#define CS_MAN_TIMER_DELAY_500       500   /* Milliseconds */
#define CS_MAN_TIMER_DELAY_1000     1000   /* Milliseconds */
#define CS_MAN_TIMER_DELAY_3000     3000   /* Milliseconds */
#define CS_MAN_TIMER_DELAY_5000     5000   /* Milliseconds */

#define CS_MAN_FILE_OPEN_ERROR      0xfffffffc
#define CS_MAN_FILE_READ_ERROR      0xfffffffd
#define CS_MAN_INVALID_CHECKSUM     0xfffffffe

#define HKLM                    _T("HKEY_LOCAL_MACHINE")
#define DRIVER_KEY              _T("SOFTWARE\\Gage\\Drivers")
#define COMPUSCOPE_MANAGER_KEY  _T("SOFTWARE\\Gage\\CompuScopeManager")
#define GAGE_API                __stdcall
#define GAGE_DIR                CS_MAN_STRING("GageDir")
#define CS_MAX_PATH_LENGTH      256

#ifdef __linux__
    #define GAGE_DIR_LINUX      CS_MAN_STRING("/usr/local/share/Gage/")
#endif

#if defined(_WIN32) && !defined(QT_DLL)

static const UINT UWM_APPLY = ::RegisterWindowMessage(_T("UWM_GAGE_APPLY"));
static const UINT UWM_SYSTEM_RESET = ::RegisterWindowMessage(_T("UWM_GAGE_SYSTEM_RESET"));
static const UINT UWM_UPDATE_FPGA_LIST = ::RegisterWindowMessage(_T("UWM_GAGE_UPDATE_FPGA_LIST"));
static const UINT UWM_STATUS_REPORT = ::RegisterWindowMessage(_T("UWM_GAGE_STATUS_REPORT"));
static const UINT UWM_ENABLE_REMOTE = ::RegisterWindowMessage(_T("UWM_GAGE_ENABLE_REMOTE"));
static const UINT UWM_SECTOR_PROCESSED = ::RegisterWindowMessage(_T("UWM_GAGE_FW_SECTOR_PROCESSED"));
static const UINT UWM_SECTOR_SHOW_PROGRESS = ::RegisterWindowMessage(_T("UWM_GAGE_FW_SECTOR_SHOW_PROGRESS"));
static const UINT UWM_SYSTEM_STATUS_CHANGE = ::RegisterWindowMessage(_T("UWM_GAGE_SYSTEM_STATUS_CHANGE"));

#endif

/* Global Enums */
#ifdef __cplusplus
namespace CsManager {
#endif

enum CS_MAN_FIRMWARE_STATUS
{
    FIRMWARE_OK,
    FIRMWARE_OUTDATED,
    FIRMWARE_UNKNOWN,
    SAFE_BOOT,
    INVALID_CHECKSUM,
    NOT_AVAILABLE,
    VERSION_VALID
};
#ifdef __cplusplus
}
#endif

typedef int (GAGE_API* LPCSINITIALIZE)(void);
typedef int (GAGE_API* LPCSREINITIALIZE)(short);
typedef int32 (GAGE_API* LPRMGETSYSTEMCOUNTPOINTER)(void);
typedef int32 (GAGE_API* LPRMGETSYSTEMSTATEPOINTER)(int16, CSSYSTEMSTATE*);
typedef int32 (GAGE_API* LPRMREFRESHSYSTEMHANDLES)(void);
typedef int32 (GAGE_API* LPCSSETPARAMS) (CSHANDLE, int, void *);
typedef int32 (GAGE_API* LPCSGETPARAMS) (CSHANDLE, int, int, void *);
typedef int32 (GAGE_API* LPCSGETCAPS) (CSHANDLE, uInt32, void *, uInt32 *);
typedef int32 (GAGE_API* LPCSDO) (CSHANDLE, int16);
typedef int32 (GAGE_API* LPCSGETSYSTEM) (CSHANDLE *, uInt32, uInt32, uInt32, int16);
typedef int32 (GAGE_API* LPCSFREESYSTEM) (CSHANDLE);
typedef BOOL (GAGE_API* LPCSQUERYDBRECORD) (LPTSTR, int, long *, long *, long *, long *, LPTSTR, int, BOOL*, LPTSTR, int);

typedef int32 (GAGE_API* LPCSCFGAUXIO) (CSHANDLE);

typedef int32 (GAGE_API* LPRMGETSYSTEMCOUNT)(void);
typedef int32 (GAGE_API* LPRMGETSYSTEMSTATEBYINDEX)(int16, CSSYSTEMSTATE*);
typedef int32 (GAGE_API* LPRMGETSYSTEMSTATEBYHANDLE)(CSHANDLE, CSSYSTEMSTATE*);

typedef int32 (GAGE_API* LPCSGETOPTIONSTEXT)(uInt32, int32, PCS_HWOPTIONS_CONVERT2TEXT);
typedef int32 (GAGE_API* LPCSGETFWLCSIINFO)(PFWLnCSI_INFO, uInt32 *);


typedef int (GAGE_API* LPCSGETERRORSTRING)(int, LPTSTR, int);
typedef int (GAGE_API* LPCSGETSYSTEMINFO)(CSHANDLE, PCSSYSTEMINFO);

#endif //_CS_COMP_MAN_DEFS_H_
