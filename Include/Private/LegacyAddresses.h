#ifndef __LEGACY_ADDRESSES_H__
#define __LEGACY_ADDRESSES_H__

#include "gage_drv.h"

int32 GAGEAPI	CalculateMrFileAddresses (int32 group, int16 board_type, int32 depth, int32 in_memory, int16 chan, int16 op_mode, float tbs, int32 far *trig, int32 far *start, int32 far *end);
int32 GAGEAPI	CalculateMraFileAddresses (int16 board_type, uInt16 version, int16 channel, int16 op_mode, float tbs, int32 far *trig, int32 far *start, int32 far *end, int16 data);


#endif // __LEGACY_ADDRESSES_H__