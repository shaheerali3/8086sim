@echo off
mkdir..\build
pushd..\build
gcc ..\8086\8086.cpp -o 8086
popd 
..\build\8086.exe