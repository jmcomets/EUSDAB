# Executable sources
file(GLOB_RECURSE EUSDAB_SOURCES *.cpp)
add_executable(${EXE_NAME} ${EUSDAB_SOURCES})

# SFML
set(SFML_DIR "${PROJECT_SOURCE_DIR}/lib/SFML-2.0-rc")
include_directories("${SFML_DIR}/include")
link_directories("${SFML_DIR}/lib")
target_link_libraries(${EXE_NAME} sfml-system sfml-window sfml-graphics sfml-audio)

# Boost
find_package(Boost 1.41.0 REQUIRED)
if(Boost_FOUND)
   include_directories(${Boost_INCLUDE_DIRS})
endif()
