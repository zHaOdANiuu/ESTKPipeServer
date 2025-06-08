#pragma once

#include "SPBasic.h"
#include "SoCClient.h"

using SpBasicSuitePtr = SPBasicSuite **;
using GetSPBasicSuite = void (*)(SPBasicSuite **);

void getSpBasicSuite(SPBasicSuite **);
