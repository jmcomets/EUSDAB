# The name of our project is "EUSDAB". CMakeLists files in this project can 
# refer to the root source directory of the project as ${EUSDAB_SOURCE_DIR} and 
# to the root binary directory of the project as ${EUSDAB_BINARY_DIR}. 
# minimum version of CMake needed (used version).
cmake_minimum_required(VERSION 2.6)

# Our project name: EUSDAB
project(EUSDAB)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "Building in '${CMAKE_BUILD_TYPE}' mode")

# Compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -std=c++0x -W -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-align -Wconversion -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline -Wunused-parameter")

# Debug flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
endif()

# EUSDAB include directory
include_directories("include")

# EUSDAB sources
file(GLOB_RECURSE EUSDAB_SOURCES ${EUSDAB_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM EUSDAB_SOURCES ${EUSDAB_SOURCE_DIR}/src/main.cpp)
set(EUSDAB_LIB "EUSDAB_lib")
add_library(${EUSDAB_LIB} ${EUSDAB_SOURCES})

# Boost
set(Boost_MIN_VERSION "1.41.0")
find_package(Boost ${Boost_MIN_VERSION} REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost ${Boost_MIN_VERSION} required")
endif()

# SFML
set(SFML_DIR "${PROJECT_SOURCE_DIR}/lib/SFML-2.0-rc")
set(SFML_LIBS sfml-system sfml-window sfml-graphics sfml-audio)
include_directories("${SFML_DIR}/include")
link_directories("${SFML_DIR}/lib")

# EUSDAB main executable
set(EUSDAB_EXE_NAME "EUSDAB")
add_executable(${EUSDAB_EXE_NAME} ${EUSDAB_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${EUSDAB_EXE_NAME} ${SFML_LIBS})
target_link_libraries(${EUSDAB_EXE_NAME} ${EUSDAB_LIB})

# CTags target
set(CTAGS_TARGET_NAME "tags")
set(CTAGS_SCRIPT "ctags.sh")
set(CTAGS_CMD ${CMAKE_CURRENT_SOURCE_DIR}/${CTAGS_SCRIPT})
add_custom_target(
    ${CTAGS_TARGET_NAME}
    COMMAND ${CTAGS_CMD})

# Tests
add_subdirectory("tests")
