#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef _WIN32
#include "windows.h"

typedef HWND	HWND;
typedef HDC		HDC;

#include <string>
typedef   signed __int64  int64;
typedef unsigned __int64 uint64;

#endif



#ifdef BUILD_ENGINE
#define DLL_API _declspec(dllexport)
#else
#define DLL_API _declspec(dllimport)
#endif

#endif
