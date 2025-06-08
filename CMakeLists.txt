cmake_minimum_required(VERSION 3.20.0)
project(es)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(AE_SDK ../SDK)
set(
  SOURCES
  ${AE_SDK}/Util/AEGP_SuiteHandler.cpp
  ${AE_SDK}/Util/MissingSuiteError.cpp
  ${AE_SDK}/Util/Smart_Utils.cpp
  backend/src/eval.cpp
  backend/src/getSpBasicSuite.cpp
  backend/src/pipeServer.cpp
  backend/main.cpp
)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_library(${PROJECT_NAME} MODULE ${SOURCES})
target_include_directories(
   ${PROJECT_NAME}
   PRIVATE
   ${AE_SDK}/External
   ${AE_SDK}/Headers
   ${AE_SDK}/Headers/SP
   ${AE_SDK}/Resources
   ${AE_SDK}/Util
   ${CMAKE_SOURCE_DIR}/backend/src
   ${CMAKE_SOURCE_DIR}/backend
)
