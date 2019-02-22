cmake_minimum_required(VERSION 2.6)

project(EUSDAB)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "Building in '${CMAKE_BUILD_TYPE}' mode")

# Compile flags
set(WARNINGS "-W -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-align -Wconversion -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline -Wunused-parameter")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -std=c++11 ${WARNINGS} -Werror")

# Debug flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
endif()

# Boost
set(Boost_MIN_VERSION "1.41.0")
find_package(Boost ${Boost_MIN_VERSION} REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(SRC src)
set(SFML_MIN_VERSION "2.0.0")
set(SFML_COMPONENTS graphics audio window system)
set(SFML_LIBS sfml-graphics sfml-audio sfml-window sfml-system)
find_package(SFML ${SFML_MIN_VERSION} COMPONENTS ${SFML_COMPONENTS} REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})

# EUSDAB include directory
include_directories("include")

# EUSDAB library
set(EUSDAB_LIB "eusdab")
add_library(${EUSDAB_LIB}
    ${SRC}/animation.cpp
    ${SRC}/animationparser.cpp
    ${SRC}/application.cpp
    ${SRC}/attack.cpp
    ${SRC}/entity.cpp
    ${SRC}/entitycontroller.cpp
    ${SRC}/entityparser.cpp
    ${SRC}/graphics/controller.cpp
    ${SRC}/graphics/texturemanager.cpp
    ${SRC}/infiniteLife.cpp
    ${SRC}/input/controller.cpp
    ${SRC}/input/event.cpp
    ${SRC}/input/joystickmapping.cpp
    ${SRC}/input/keyboardmapping.cpp
    ${SRC}/input/listener.cpp
    ${SRC}/input/speaker.cpp
    ${SRC}/life.cpp
    ${SRC}/map.cpp
    ${SRC}/movement.cpp
    ${SRC}/percentageLife.cpp
    ${SRC}/physics/controller.cpp
    ${SRC}/physics/transform.cpp
    ${SRC}/physics/world.cpp
    ${SRC}/soundmanager.cpp
    ${SRC}/state.cpp
    ${SRC}/states/aerialAttack.cpp
    ${SRC}/states/aerialDodge.cpp
    ${SRC}/states/aerialHit.cpp
    ${SRC}/states/attack.cpp
    ${SRC}/states/crouch.cpp
    ${SRC}/states/dodge.cpp
    ${SRC}/states/falling.cpp
    ${SRC}/states/guard.cpp
    ${SRC}/states/haul.cpp
    ${SRC}/states/hit.cpp
    ${SRC}/states/idle.cpp
    ${SRC}/states/jump.cpp
    ${SRC}/states/motion.cpp
    ${SRC}/states/run.cpp
    ${SRC}/states/shield.cpp
    ${SRC}/states/special.cpp
    ${SRC}/states/wait.cpp
    ${SRC}/states/walk.cpp
    ${SRC}/util/filename.cpp
    ${SRC}/util/string.cpp
    ${SRC}/HPLife.cpp
    )

# Main
set(EUSDAB_MAIN "eusdab-main")
add_executable(${EUSDAB_MAIN}
    ${SRC}/main.cpp
    ${SRC}/main_application.cpp
    )
target_link_libraries(${EUSDAB_MAIN} ${SFML_LIBS} pthread)
target_link_libraries(${EUSDAB_MAIN} ${EUSDAB_LIB})

# Tests
#add_subdirectory("tests")
