# List of all tests
set(EUSDAB_TESTS
    "input"
    "animation"
    "hitboxes"
    "painter"
    )

# Add all defined tests
foreach(e ${EUSDAB_TESTS})
    set(e_exe_name "EUSDAB_${e}")
    file(GLOB_RECURSE e_sources "${CMAKE_CURRENT_SOURCE_DIR}/${e}/*.cpp")
    add_executable(${e_exe_name} ${e_sources})
    target_link_libraries(${e_exe_name} ${SFML_LIBS})
    target_link_libraries(${e_exe_name} ${EUSDAB_LIB})
endforeach()
