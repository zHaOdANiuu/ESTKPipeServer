#pragma once

#include "AEConfig.h"
#include "SoSharedLibDefs.h"

#ifdef AE_OS_WIN
#include <Windows.h>
#define exports __declspec(dllexport)
#define strdup _strdup
#elif defined AE_OS_MAC
#include <dlfcn.h>
#define exports (__APPLE__) __attribute__((visibility("default")))
#endif

extern "C" exports char *ESInitialize(TaggedData **, long);
