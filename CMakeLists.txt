cmake_minimum_required(VERSION 3.13)
project(CHASE VERSION 1.0.0 LANGUAGES C CXX)

include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime.cmake")
# NOTE: register custom targets between these two lines
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime-Code.cmake")

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Util/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Ports/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/SignalProcessing/")
