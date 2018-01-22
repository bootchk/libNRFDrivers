libNRFDrivers

status: work in progress


C++ facade to certain Nordics nrf_drv_<foo> modules.

Modules are compatible with Nordic Softdevice (SD.)

Modules for peripherals shared with SD.

Library includes compiled sources from Nordic SDK v14.2.

Sources in this project:
   facade classes
   sdk_config.h  (set to compile certain Nordic modules compatibly with SD)
   
   
Project
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


