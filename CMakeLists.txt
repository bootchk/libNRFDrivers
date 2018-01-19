cmake_minimum_required (VERSION 2.6)

project (libNRFDrivers)

# cmake includes modules from here
# !!! only for simple names without the .cmake suffix
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMakeScripts/")
message(" Module path is ${CMAKE_MODULE_PATH}")


# environment (location of NRF_SDK and other tools)
# i.e. file CMakeEnv.cmake on the MODULE_PATH
include("CMakeEnv")



# var configures CMake_nRF5x to chip family nrf52
set(NRF_TARGET "nrf52")

# scripts specific to nRF5x building
# Defines cmake macros prefixed with "nRF5x"
# Sets many cmake vars for tool flags
include("CMake_nRF5x")
nRF5x_setup()

# sanity: sets a var
message(" Linker script is ${NRF5_LINKER_SCRIPT}")




# target is library
# source specified later
add_library(NRFDrivers "")

target_sources(
    NRFDrivers
    PUBLIC
       "${CMAKE_CURRENT_LIST_DIR}/lowFreqClockCoordinated.cpp"
       "${SDK_SOURCE_FILES}"
    )



