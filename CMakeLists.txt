cmake_minimum_required (VERSION 2.6)

project (libNRFDrivers C CXX)

set(CMAKE_MODULE_PATH "/home/bootch/git/nRF5Cmake/")
message(" Module path is ${CMAKE_MODULE_PATH}")


# environment (location of NRF_SDK and other tools)
# i.e. file CMakeEnv.cmake on the MODULE_PATH
include("CMakeEnv")



# configure nRF5CMak scripts
set(NRF_TARGET "nrf52")
set(NRF_SOFTDEVICE "s132")


# scripts specific to nRF5x building
# Defines cmake macros prefixed with "nRF5"
# Sets many cmake vars for tool flags
include("nRF5")


nRF5CheckSetupPreconditions()
nRF5SetBuildOptions()
nRF5SetIncludePaths()

# we don't need to define SDK_SOURCES since we list the SDK sources ourselves
# nRF5SetSDKSourcesBasic()


# sanity: sets a var
message(" Linker script is ${NRF5_LINKER_SCRIPT}")




# library
# source specified later
add_library(NRFDrivers "")


# sources are only the facades and the drivers
# Not: "${SDK_SOURCE_FILES}"
target_sources(
    NRFDrivers
    PUBLIC
       "${CMAKE_CURRENT_LIST_DIR}/lowFreqClockCoordinated.cpp"
       "${NRF5_SDK_PATH}/components/drivers_nrf/common/nrf_drv_common.c"
       "${NRF5_SDK_PATH}/components/drivers_nrf/clock/nrf_drv_clock.c"
    )
    

# test harness
add_executable(testNRFDrivers "")

target_sources(
    testNRFDrivers
    PUBLIC
       testNRFDrivers.cpp
    )


