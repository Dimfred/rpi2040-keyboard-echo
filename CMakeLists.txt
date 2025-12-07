cmake_minimum_required(VERSION 3.13)

include(./dependencies/pico-sdk/pico_sdk_init.cmake)

project(usb_keyboard_echo C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(usb_keyboard_echo
  src/main.cpp
  src/usb_descriptors.c
)
target_include_directories(usb_keyboard_echo PRIVATE include/)
pico_enable_stdio_usb(usb_keyboard_echo 1)
pico_enable_stdio_uart(usb_keyboard_echo 0)
target_link_libraries(usb_keyboard_echo
    pico_stdlib
    tinyusb_device
    tinyusb_board
)

pico_add_extra_outputs(usb_keyboard_echo)
