cmake_minimum_required(VERSION 3.13)

# Usar SDK local instalado
set(PICO_SDK_PATH "C:/Program Files/Raspberry Pi/Pico SDK v1.5.1/pico-sdk" CACHE PATH "Path to Pico SDK")

# Adicionar arquivo de importação do SDK
set(PICO_SDK_IMPORT_FILE ${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

include(${PICO_SDK_IMPORT_FILE})

project(monitor_sensores_alerta C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(monitor_sensores_alerta
    src/main.c
    src/display/ssd1306.c
    src/display/font.c
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