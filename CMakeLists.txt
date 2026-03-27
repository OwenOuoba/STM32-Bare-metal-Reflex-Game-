cmake_minimum_required(VERSION 3.22)

# Set system properties for cross-compilation
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# For bare-metal toolchains, avoid linking test executables during compiler checks.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(Reflex_game C ASM)

set(CMAKE_EXECUTABLE_SUFFIX ".elf")

# Standard C settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# CPU specifications for STM32F401RE
add_compile_options(
        -mcpu=cortex-m4
        -mthumb
        -mfloat-abi=hard
        -mfpu=fpv4-sp-d16
        -fdata-sections
        -ffunction-sections
        -Wall
)

# Linker script and options
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F401XX_FLASH.ld)
add_link_options(
        -mcpu=cortex-m4
        -mthumb
        -mfloat-abi=hard
        -mfpu=fpv4-sp-d16
        --specs=nosys.specs
        -Wl,--gc-sections
        -T${LINKER_SCRIPT}
)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Linker script: ${LINKER_SCRIPT}")

# Create the executable
add_executable(${CMAKE_PROJECT_NAME})

# Include the STM32CubeMX configuration
add_subdirectory(cmake/stm32cubemx)

# Link libraries from the CubeMX configuration
target_link_libraries(${CMAKE_PROJECT_NAME}
        stm32cubemx
)

# Create .hex and .bin files from the .elf executable
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.hex
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
        COMMENT "Generating .hex and .bin files"
)


# Flash target
add_custom_target(flash
        COMMAND STM32_Programmer_CLI -c port=SWD -w ${CMAKE_PROJECT_NAME}.bin 0x08000000 -rst
        DEPENDS ${CMAKE_PROJECT_NAME}
        COMMENT "Flashing to STM32F401RE..."
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)