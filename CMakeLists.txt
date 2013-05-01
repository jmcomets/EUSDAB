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
set(EUSDAB_EXE_NAME "EUSDAB")

# Compile flags
set(CXX_MAIN_FLAGS "-pedantic -std=c++0x")

# Warning flags
set(CXX_WARNING_FLAGS "-W -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-align -Wconversion -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline -Wunused-parameter")

# Finalized compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_MAIN_FLAGS} ${CXX_WARNING_FLAGS}")

# EUSDAB include directory
include_directories("include")

# EUSDAB sources
set(EUSDAB_SOURCES 
    ${EUSDAB_SOURCE_DIR}/src/state.cpp
    ${EUSDAB_SOURCE_DIR}/src/movement.cpp
    ${EUSDAB_SOURCE_DIR}/src/entity.cpp
    ${EUSDAB_SOURCE_DIR}/src/physics/controller.cpp
    ${EUSDAB_SOURCE_DIR}/src/animation.cpp
    ${EUSDAB_SOURCE_DIR}/src/input/controller.cpp
    ${EUSDAB_SOURCE_DIR}/src/input/event.cpp
    ${EUSDAB_SOURCE_DIR}/src/input/listener.cpp
    ${EUSDAB_SOURCE_DIR}/src/input/speaker.cpp
    ${EUSDAB_SOURCE_DIR}/src/entitywithmask.cpp
    ${EUSDAB_SOURCE_DIR}/src/application.cpp
    ${EUSDAB_SOURCE_DIR}/src/textureManager.cpp
    ${EUSDAB_SOURCE_DIR}/src/entityparser.cpp
    ${EUSDAB_SOURCE_DIR}/src/states/idle.cpp
    )
set(EUSDAB_LIB "EUSDAB_lib")
add_library(${EUSDAB_LIB} ${EUSDAB_SOURCES})

# EUSDAB main executable
add_executable(${EUSDAB_EXE_NAME} ${EUSDAB_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${EUSDAB_EXE_NAME} ${EUSDAB_LIB})

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
target_link_libraries(${EUSDAB_EXE_NAME} ${SFML_LIBS})

# Tests
add_subdirectory("tests")
