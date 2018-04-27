libNRFDrivers


C++ facade to certain Nordics nrf_drv_<foo> modules.

"Modules" are compatible with Nordic Softdevice (SD.)
(The alternative --use the HAL-- is not compatible with SD.)

"Coordinated" means:

     - compatible with SD
     - and/or shares resources (GPIO pins) 

SD compatibility strategies
-

Modules for peripherals shared with SD.
See the SD reference manual for list of peripherals shared with SD.

This library implements:

     LF clock (oscillator)
     nvic: SD compatible driver (sic)
     comparator: 
     
Other peripherals that must use drivers since they are shared with the SD:
     
     HF clock (oscillator): ??? 
     POWER: ???
     RTC0, RTC1: we don't use them, instead use RTC2 (only avail on nrf52)

The facade API's are the same as for nRF5x (which uses the HAL and is not SD compatabile.)

The reason the LF clock needs coordination is to keep it on when SD is disabled.
The SD would shut it off unless we coordinate.

The HF clock does not need coordination (can use HAL) because we don't don't need it to stay on,
and we do sequential multiprotocol so we don't access the HF clock when the SD is enabled
and thus the SD's protection of the HF clock registers is disabled then
and the HAL API will work without memory faults.

For the nvic: 
when use case is sequential multiprotocol: use HAL/nvic and simply don't access the nvic while SD is enabled.
when use case: concurrent multiprotocol: use NvicCoordinated 

Sources
-

Library compiles objects from sources from Nordic SDK v14.2 :

    nrf_drv_clock.c
    nrf_drv_comp.c
    nrf_sdh.c
    (SDK file for NvicCoordinated is .../s132/headers/nrf_nvic.h i.e. inline code)

Sources in this project:

    facade classes
         lowFreqClockCoordinated.cpp
         nvicCoordinated.cpp
         comparatorCoordinated.cpp
         hwConfig.h (defines which RTC the nvic affects)
    sdk_config.h  (set to compile certain Nordic modules compatibly with SD)
    
  
   
Project (the IDE artifact)
-

Eclipse w cmake4eclipse plugin.
Generates ninja scripts (not make scripts.)  Use "sudo apt-get install ninja-build"
CMake as builder.

Incomplete:  currently uses the cmake4eclipse plugin which has no build targets?  
Always builds target "all"

Seems messed up between Neon and Oxygen Eclipse versions

Adding a module
-

    Add project source files (.cpp and .h)
    Add Nordic SDK files to CMakeLists (.c)
    Change sdk_config to enable a module

Build
-

Command line build:

    mkdir cmakeBuild
    cd cmakeBuild
    cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=/home/bootch/git/nRF5Cmake/toolchain-gnu-arm.cmake ..
    cmake --build . --target NRFDrivers


For now, Eclipse project is not configured correctly for building, you must use the command line.


Dependencies
-
	NRF_SDK
	nRF5Cmake (cmake scripts for building on Nordic)
