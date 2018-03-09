cmake_minimum_required (VERSION 2.6)

project (libNRFDrivers C CXX)

set(CMAKE_MODULE_PATH "/home/bootch/git/nRF5Cmake/")
message(" Module path is ${CMAKE_MODULE_PATH}")


# environment (location of NRF_SDK and other tools)
# i.e. file CMakeEnv.cmake on the MODULE_PATH
include("CMakeEnv")



# configure nRF5CMake scripts
set(NRF_FAMILY "nrf52")


set(SOFTDEVICE "s112")
set(CHIP "nrf52810")


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

nRF5SetSoftdeviceIncludePaths( "NRFDrivers" ${SOFTDEVICE})
nRF5SetSoftdeviceDefinitions( "NRFDrivers" ${SOFTDEVICE})
nRF5SetChipCompileDefinitions( "NRFDrivers" ${CHIP})

# sources are only the facades and the drivers
# there is no drive for the nvic: just separate .h implementation
# Not: "${SDK_SOURCE_FILES}"
# Dependency:  
#   drv_clock -> drv_common.c
#   drv_clock -> sdh.c (nrf_sdh_is_enabled())
#   nrf_sdh.c -> nrf_section_iter.c
target_sources(
    NRFDrivers
    PUBLIC
       "${CMAKE_CURRENT_LIST_DIR}/lowFreqClockCoordinated.cpp"
       "${CMAKE_CURRENT_LIST_DIR}/nvicCoordinated.cpp"
       "${NRF5_SDK_PATH}/components/drivers_nrf/common/nrf_drv_common.c"
       "${NRF5_SDK_PATH}/components/drivers_nrf/clock/nrf_drv_clock.c"
       "${NRF5_SDK_PATH}/components/softdevice/common/nrf_sdh.c"
       "${NRF5_SDK_PATH}/components/libraries/experimental_section_vars/nrf_section_iter.c"
    )
    

# test harness
add_executable(testNRFDrivers "")

target_sources(
    testNRFDrivers
    PUBLIC
       testNRFDrivers.cpp
    )


