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

# Source files
add_subdirectory("src")

# Tags
#set_source_files_properties(tags PROPERTIES GENERATED true)
#add_custom_command(OUTPUT tags
    #COMMAND ctags -R --sort=yes --c++-kinds=+px-d --fields=+iaS --extra=+q "${PROJECT_SOURCE_DIR}/include"
    #WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
#add_dependencies(${EXE_NAME} tags)
