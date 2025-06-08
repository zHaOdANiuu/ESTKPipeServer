#include "eval.hpp"
#include "AE_Macros.h"

int eval(AEGP_SuiteHandler &suite, const char *code, void **result) {
  int                err         = 0;
  AEGP_MemSize       size        = 0;
  AEGP_MemHandle     outResult   = NULL;
  AEGP_MemHandle     outError    = NULL;
  AEGP_MemorySuite1 *MemorySuite = suite.MemorySuite1();

  err = suite.UtilitySuite4()->AEGP_ExecuteScript(0, code, false, &outResult, &outError);
  if (outError) {
    ERR(MemorySuite->AEGP_LockMemHandle(outError, result));
    ERR(MemorySuite->AEGP_UnlockMemHandle(outError));
    ERR(MemorySuite->AEGP_FreeMemHandle(outError));
  }
  if (outResult) {
    ERR(MemorySuite->AEGP_LockMemHandle(outResult, result));
    ERR(MemorySuite->AEGP_UnlockMemHandle(outResult));
    ERR(MemorySuite->AEGP_FreeMemHandle(outResult));
  }

  return err;
}
