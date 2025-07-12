cmake_minimum_required(VERSION 3.13)
include("/opt/pico-sdk/external/pico_sdk_import.cmake")
add_subdirectory(.. sx1262)
project(transmit C CXX ASM)
pico_sdk_init()
add_executable(transmit transmit.c)
target_link_libraries(transmit
  pico_stdlib
  sx1262lib
  )
pico_enable_stdio_usb(transmit 1)
pico_add_extra_outputs(transmit)
