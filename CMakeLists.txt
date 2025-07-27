cmake_minimum_required(VERSION 3.13)
include("/opt/pico-sdk/external/pico_sdk_import.cmake")
project(sx1262lib C CXX ASM)
pico_sdk_init()

add_library(sx1262lib
  src/picoboard.c
  src/initialize.c
  src/radio.c
  src/debugging.c
  mylib/ws2812.c
  )

target_include_directories(sx1262lib PUBLIC  ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(sx1262lib PRIVATE ${CMAKE_CURRENT_LIST_DIR}/mylib)
target_include_directories(sx1262lib PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)

target_link_libraries(sx1262lib
  pico_stdlib
  hardware_spi
  hardware_gpio
  hardware_pio
  hardware_clocks
  )

pico_generate_pio_header(sx1262lib ${CMAKE_CURRENT_LIST_DIR}/include/ws2812.pio)

