@echo off
::rd build /s /q
mkdir build
cd build
::cmake .. -G "MinGW Makefiles"
cmake ..
::cmake --build . --target %*
cmake --build .
cd ..
::pause