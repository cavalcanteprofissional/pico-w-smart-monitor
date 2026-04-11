cmake_minimum_required(VERSION 3.13)

# Fetch Pico SDK from Git if not available
if(NOT PICO_SDK_PATH)
    include(FetchContent)
    FetchContent_Declare(
        pico_sdk
        GIT_REPOSITORY https://github.com/raspberrypi/pico-sdk.git
        GIT_TAG 1.5.1
    )
    FetchContent_MakeAvailable(pico_sdk)
endif()

project(monitor_sensores_alerta C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(monitor_sensores_alerta
    src/main.c
    src/display/ssd1306.c
    src/sensors/joystick.c
    src/utils/uart_log.c
)

target_include_directories(monitor_sensores_alerta PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/display
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sensors
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
)

target_link_libraries(monitor_sensores_alerta
    pico_stdlib
    hardware_i2c
    hardware_adc
    hardware_gpio
    hardware_pwm
)

pico_enable_stdio_usb(monitor_sensores_alerta 0)
pico_enable_stdio_uart(monitor_sensores_alerta 1)

pico_add_extra_outputs(monitor_sensores_alerta)