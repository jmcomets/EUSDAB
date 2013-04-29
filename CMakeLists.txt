# The name of our project is "EUSDAB". CMakeLists files in this project can 
# refer to the root source directory of the project as ${EUSDAB_SOURCE_DIR} and 
# to the root binary directory of the project as ${EUSDAB_BINARY_DIR}. 
# minimum version of CMake needed (used version).
cmake_minimum_required(VERSION 2.6)

# Our project name
project(EUSDAB)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Executable name
set(EXE_NAME "EUSDAB")

# Compile flags
set(CXX_MAIN_FLAGS "-pedantic -std=c++0x")

# Warning flags
set(CXX_WARNING_FLAGS "-W -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-align -Wconversion -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline -Wunused-parameter")

# Finalized compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_MAIN_FLAGS} ${CXX_WARNING_FLAGS}")

# EUSDAB include directory
include_directories("include")

# Executable sources
file(GLOB_RECURSE EUSDAB_SOURCES "src/*.cpp")
add_executable(${EXE_NAME} ${EUSDAB_SOURCES})

# Boost
find_package(Boost 1.41.0 REQUIRED)
if(Boost_FOUND)
   include_directories(${Boost_INCLUDE_DIRS})
endif()

# SFML
set(SFML_DIR "${PROJECT_SOURCE_DIR}/lib/SFML-2.0-rc")
include_directories("${SFML_DIR}/include")
link_directories("${SFML_DIR}/lib")
target_link_libraries(${EXE_NAME} sfml-system sfml-window sfml-graphics sfml-audio)
