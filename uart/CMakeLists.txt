cmake_minimum_required(VERSION 3.13)
include("/opt/pico-sdk/external/pico_sdk_import.cmake")
add_subdirectory(.. sx1262)
project(transmit C CXX ASM)
pico_sdk_init()
add_executable(uart uart.c)
target_compile_definitions(uart PRIVATE TX_PIN=4 RX_PIN=5)
target_link_libraries(uart
  pico_stdlib
  pico_stdio_uart
  sx1262lib
  hardware_uart
  hardware_irq
  )
pico_enable_stdio_uart(uart 1)
#pico_enable_stdio_usb(uart 1)
pico_add_extra_outputs(uart)
