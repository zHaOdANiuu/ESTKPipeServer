#include "AEConfig.h"
#include "getSpBasicSuite.hpp"

#include <string>

#ifdef AE_OS_WIN
#include <Windows.h>
#elif defined AE_OS_MAC
#include <dlfcn.h>
#endif

namespace {
GetSPBasicSuite loadLib(const char *libPath, const char *funcName) {
  std::string tmp = libPath;
#ifdef AE_OS_WIN
  tmp += ".dll";
  auto hModule = GetModuleHandleA(tmp.c_str());
#else
  tmp += ".dylib";
  auto hModule = dlopen(tmp.c_str(), RTLD_LAZY);
#endif
  if (hModule == nullptr)
    return nullptr;
#ifdef AE_OS_WIN
  return reinterpret_cast<GetSPBasicSuite>(GetProcAddress(hModule, funcName));
#else
  return reinterpret_cast<GetSPBasicSuite>(dlsym(hModule, funcName));
#endif
}
} // namespace

void getSpBasicSuite(SPBasicSuite **r) {
  GetSPBasicSuite getSPBasicSuite = ::loadLib("PLUG", "PLUG_GetSPBasicSuite");
  if (getSPBasicSuite == nullptr)
    getSPBasicSuite = ::loadLib("U", "U_SP_GetSPBasicSuite");
  if (getSPBasicSuite != nullptr)
    getSPBasicSuite(r);
}
