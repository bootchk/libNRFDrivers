cmake_minimum_required (VERSION 2.6)

project (libNRFDrivers C CXX)

set(CMAKE_MODULE_PATH "/home/bootch/git/nRF5Cmake/")
message(" Module path is ${CMAKE_MODULE_PATH}")


# environment (location of NRF_SDK and other tools)
# i.e. file CMakeEnv.cmake on the MODULE_PATH
include("CMakeEnv")


# scripts specific to nRF5x building
# Defines cmake macros prefixed with "nRF5"
# Sets many cmake vars for tool flags
include("nRF5")


nRF5CheckSetupPreconditions()
nRF5SetBuildOptions()
nRF5SetIncludePaths()

# we don't need to define SDK_SOURCES since we list the SDK sources ourselves
# nRF5SetSDKSourcesBasic()


# library
# source specified later
add_library(NRFDrivers "")

set_target_properties( NRFDrivers
    PROPERTIES
       CHIP "nrf52810e"
       SOFTDEVICE "s112"
       FLOAT_ABI "soft"
    )
nRF5CheckTargetProperties(NRFDrivers)
nRF5ConfigTargetByProperties(NRFDrivers)


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
       "${CMAKE_CURRENT_LIST_DIR}/comparatorCoordinated.cpp"
       "${NRF5_SDK_PATH}/components/drivers_nrf/common/nrf_drv_common.c"
       "${NRF5_SDK_PATH}/components/drivers_nrf/clock/nrf_drv_clock.c"
       "${NRF5_SDK_PATH}/components/drivers_nrf/comp/nrf_drv_comp.c"
       "${NRF5_SDK_PATH}/components/softdevice/common/nrf_sdh.c"
       "${NRF5_SDK_PATH}/components/libraries/experimental_section_vars/nrf_section_iter.c"
    )
    

# test harness
add_executable(testNRFDrivers "")

set_target_properties( testNRFDrivers
    PROPERTIES
       CHIP "nrf52810e"
       SOFTDEVICE "s112"
       FLOAT_ABI "soft"
    )
nRF5CheckTargetProperties(testNRFDrivers)
nRF5ConfigTargetByProperties(testNRFDrivers)
nRF5SetTargetStartupSources(testNRFDrivers)
# TODO need fix this nRF5SetTargetsLinkerScript(testNRFDrivers "${CMAKE_SOURCE_DIR}/linkerScripts/nrf52810SD.ld")

target_sources(
    testNRFDrivers
    PUBLIC
       testNRFDrivers.cpp
    )


