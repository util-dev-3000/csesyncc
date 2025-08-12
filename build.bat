mkdir build 2>nul
cmake -S . -B build -G "MinGW Makefiles"
mingw32-make build
