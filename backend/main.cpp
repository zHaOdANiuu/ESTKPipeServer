#include "main.hpp"
#include "AEGP_SuiteHandler.h"
#include "getSpBasicSuite.hpp"
#include "eval.hpp"
#include "pipeServer.hpp"

#include <thread>

#define PIPE_NAME u"\\\\.\\pipe\\ExtendScriptPipeServer"

const char8_t *callback(SPBasicSuite *pica, const char8_t *mes) {
  void             *rPtr  = nullptr;
  AEGP_SuiteHandler suite = AEGP_SuiteHandler(pica);
  if (eval(suite, reinterpret_cast<const char *>(mes), &rPtr))
    suite.UtilitySuite1()->AEGP_ReportInfo(0, "Error: Failed to evaluate script");
  return reinterpret_cast<const char8_t *>(rPtr);
}

void server(SPBasicSuite *pica) {
  while (true) {
    std::this_thread::yield();
    int err = pipeServer(PIPE_NAME, pica, callback);
    if (err)
      printf("Error: Failed to start pipe server: %d\n", err);
    Sleep(200);
  }
}

char *ESInitialize(TaggedData **, long) {
  SPBasicSuite *pica = nullptr;
  getSpBasicSuite(&pica);
  std::thread(server, pica).detach();
  static char s[] = "\0";
  return s;
}
