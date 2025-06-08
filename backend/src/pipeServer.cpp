#include "pipeServer.hpp"
#include <cstddef>

#define CLEAR_PIPE_RESOURCE(hPipe) \
  do {                             \
    FlushFileBuffers(hPipe);       \
    DisconnectNamedPipe(hPipe);    \
    CloseHandle(hPipe);            \
  } while (0)

#define PROCESS_ERROR(hPipe, errCode) \
  do {                                \
    CLEAR_PIPE_RESOURCE(hPipe);       \
    return (errCode);                 \
  } while (0)

int pipeServer(
  const char16_t      *pipeName,
  struct SPBasicSuite *pica,
  PipeCallback         callback
) {
  HANDLE hPipe = CreateNamedPipeW(
    reinterpret_cast<LPCWSTR>(pipeName),
    PIPE_ACCESS_DUPLEX,
    PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
    1,
    PIPE_BUFFER_SIZE,
    PIPE_BUFFER_SIZE,
    NMPWAIT_USE_DEFAULT_WAIT,
    NULL
  );

  if (hPipe == INVALID_HANDLE_VALUE)
    return GetLastError();

  BOOL connected = ConnectNamedPipe(hPipe, NULL) ? TRUE : GetLastError() == ERROR_PIPE_CONNECTED;

  if (!connected)
    PROCESS_ERROR(hPipe, GetLastError());

  while (true) {
    DWORD   bytesRead                = 0;
    char8_t buffer[PIPE_BUFFER_SIZE] = {0};

    if (!ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL) || bytesRead == 0) {
      DWORD err = GetLastError();
      if (err == ERROR_BROKEN_PIPE)
        break;
      PROCESS_ERROR(hPipe, err);
    }

    buffer[bytesRead] = u8'\0';

    const char8_t *resultBuffer = callback(pica, buffer);

    if (
      !WriteFile(
        hPipe,
        resultBuffer,
        strlen(reinterpret_cast<const char *>(resultBuffer)) + 1,
        NULL,
        NULL
      )
    ) {
      DWORD err = GetLastError();
      if (err != ERROR_BROKEN_PIPE) {
        PROCESS_ERROR(hPipe, err);
      }
      break;
    }
  }

  CLEAR_PIPE_RESOURCE(hPipe);
  return 0;
}
