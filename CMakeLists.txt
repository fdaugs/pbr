# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required(VERSION 3.9)

# Give your project a name
project(assignment1)

# General CMake and compiler settings
set(CMAKE_CXX_STANDARD 17)

# Add needed packages (e.g. libraries)
# find_package(OpenCV REQUIRED)

# Continue in subdirectories
add_subdirectory(src)