# CMakeLists files in this project can
# refer to the root source directory of the project as ${CMAKE_SOURCE_DIR} and
# to the root binary directory of the project as ${CMAKE_BINARY_DIR}.
cmake_minimum_required(VERSION 3.9)

# Give your project a name
project(assignment1)

#set(OpenCV_FOUND 1)
find_package(OpenCV REQUIRED)

# General CMake and compiler settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add needed packages (e.g. libraries)
#find_package(OpenCV REQUIRED)
include_directories(
        lib/glm
)
# Continue in subdirectories
add_subdirectory(src)
include_directories(${OpenCV_INCLUDE_DIRS})