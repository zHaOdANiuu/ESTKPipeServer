#pragma once

#include <Windows.h>

#define PIPE_BUFFER_SIZE 1024

using PipeCallback = const char8_t *(struct SPBasicSuite *, const char8_t *);

int pipeServer(
  const char16_t      *pipeName,
  struct SPBasicSuite *pica,
  PipeCallback         callback
);
