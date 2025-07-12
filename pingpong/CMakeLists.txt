cmake_minimum_required(VERSION 3.13)
include("/opt/pico-sdk/external/pico_sdk_import.cmake")
add_subdirectory(.. sx1262)
project(pingpong C CXX ASM)
pico_sdk_init()
add_executable(pingpong pingpong.c)
target_link_libraries(pingpong
  pico_stdlib
  pico_rand
  sx1262lib
  )
pico_enable_stdio_usb(pingpong 1)
pico_add_extra_outputs(pingpong)
