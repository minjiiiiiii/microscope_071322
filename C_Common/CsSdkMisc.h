#ifndef __CS_SDK_MISC_H__
#define __CS_SDK_MISC_H__


#ifdef __cplusplus
extern "C"{
#endif

void DisplayErrorString(const int32 i32Status);
void DisplayFinishString(const int32 i32FileFormat);
BOOL DataCaptureComplete(const CSHANDLE hSystem);

#ifdef __cplusplus
}
#endif

#endif // __CS_SDK_MISC_H__
