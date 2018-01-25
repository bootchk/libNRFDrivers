libNRFDrivers


C++ facade to certain Nordics nrf_drv_<foo> modules.

Modules are compatible with Nordic Softdevice (SD.)
(The alternative --use the HAL-- is not compatible with SD.)

Modules for peripherals shared with SD.
See the SD reference manual for list of peripherals shared with SD.
This implements:

     clock (the LF and HF oscillators)
     
(Other peripherals that must use drivers since they are shared with the SD:

     nvic: we always use SD compatible driver
     POWER: ???
     RTC0, RTC1: we don't use them



Library includes compiled sources from Nordic SDK v14.2.
Sources in this project:

    facade classes
    sdk_config.h  (set to compile certain Nordic modules compatibly with SD)
    nrf_drv_<foo>.c 
   
   
Project (the IDE artifact)
-

Eclipse w cmake4eclipse plugin.
Generates ninja scripts (not make scripts.)  Use "sudo apt-get install ninja-build"
CMake as builder.

Incomplete:  currently uses the cmake4eclipse plugin which has no build targets?  
Always builds target "all"

Seems messed up between Neon and Oxygen Eclipse versions

Build
-

Command line build:

mkdir Debug
cmake -E chdir Debug/ cmake -G "Ninja" ../
cmake --build "Debug" --target NRFDrivers

For now, Eclipse project is not configured correctly for building, you must use the command line.


Dependencies
-
	NRF_SDK
	nRF5Cmake (cmake scripts for building on Nordic)
