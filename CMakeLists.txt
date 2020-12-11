# CMakeList.txt : CMake project for splitter, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("splitter")

# Add source to this project's executable.
add_executable (splitter "splitter.cpp" "splitter.h")

# TODO: Add tests and install targets if needed.
