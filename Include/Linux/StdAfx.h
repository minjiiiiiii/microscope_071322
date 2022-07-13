// This file is only for linux in order to keep source code compatible with WINDOWS

#ifdef __linux__
	#include <cstdio>
	#include <stdint.h>
	#include <string>

	#include <iostream>
	#include <assert.h>
	#include <string.h> // def. for  memset
	#include <dlfcn.h>
	#include <fcntl.h>
	#include <sys/ioctl.h>

	#include <limits.h>

	using std::cerr;
	using namespace std;

	#include <misc.h>

	#define TEXT(x)			(x)
	#define	ASSERT(x)

	#define		RtlCopyMemory			memcpy
	#define		RtlZeroMemory(x, y)		memset(x, 0, y)
	#define		RtlEqualMemory			!memcmp
	#define		RtlMoveMemory			memmove

#endif
