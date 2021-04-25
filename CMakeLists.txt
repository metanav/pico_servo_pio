cmake_minimum_required(VERSION 3.19)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "~/pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_pio_pwm C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()
add_executable(pico_pio_pwm)

pico_generate_pio_header(pico_pio_pwm ${CMAKE_CURRENT_LIST_DIR}/pico_servo.pio)

target_sources(pico_pio_pwm PRIVATE main.c)

target_link_libraries(pico_pio_pwm PRIVATE
  pico_stdlib
  hardware_pio
  pico_stdlib 
  hardware_pwm
)

# enable usb output, disable uart output
pico_enable_stdio_usb(pico_pio_pwm 1)
pico_enable_stdio_uart(pico_pio_pwm 0)

pico_add_extra_outputs(pico_pio_pwm)
