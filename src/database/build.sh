# Stop on error
set -e

cmake -S . -B build
# build with -Wno-dev to suppress warnings from googletest
cmake --build build
cd build && ctest --verbose
