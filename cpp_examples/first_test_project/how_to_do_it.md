# How to use the CMakeLists.txt 


## make the build folder and files
cmake -G "MinGW Makefiles" -B build

## build the main.exe 
cmake --build build


## can be done together
- In Powershell this will be done with ; 

cmake -G "MinGW Makefiles" -B build ; cmake --build build
