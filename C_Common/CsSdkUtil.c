#ifndef _WIN32
#include "CsSdkUtil.h"


uInt32 GetTickCount()
{
	struct timespec ts = {0};
	unsigned TickResult  = 0U;
	clock_gettime( CLOCK_REALTIME, &ts );
	TickResult = ts.tv_nsec / 1000000;
	TickResult += ts.tv_sec * 1000;
	return(TickResult);
}

LONGLONG GetTickCountEx()
{
	struct timeval _tstart;
	struct timezone tz;
	double dMicroseconds;

	gettimeofday(&_tstart, &tz);
	dMicroseconds = (double)(_tstart.tv_sec * 1000000.0) + (double)(_tstart.tv_usec);
	return (LONGLONG)dMicroseconds;
}


void	QueryPerformanceCounter(LARGE_INTEGER *TickCount)
{
	TickCount->QuadPart = GetTickCountEx();
}

void	QueryPerformanceFrequency(LARGE_INTEGER *Frq)
{
	Frq->QuadPart = 1000000;
}

void	strcat_s(char *Dest, size_t Size, char *Str)
{
	strcat(Dest, Str);
}

#endif