# Versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.12)

# Incluir funciones de SDK de PICO
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Nombre del proyecto y estándares del lenguaje aceptados
project(main C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Inicialización de varios elementos del proyecto
pico_sdk_init()

# Indicarle a CMake los archivos de nuestro programa
add_executable(${PROJECT_NAME} 
    main.c
    events.c
    timer.c
    gpio.c
    keyboard.c
    lcd.c
    eeprom.c
    uart.c
    plantilla.c
)

# Crear archivos de salida
pico_add_extra_outputs(${PROJECT_NAME})

# STDIO: Habilitar salida por USB, deshabilitar salida por UART
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# Enlazar a las librerías requeridas
target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    hardware_gpio
    hardware_i2c
    hardware_uart
    hardware_irq
)