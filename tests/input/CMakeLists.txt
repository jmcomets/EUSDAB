# EUSDAB input test
set(EUSDAB_INPUT_EXE_NAME "EUSDAB_input")
set(EUSDAB_INPUT_SOURCES main.cpp testinput.cpp testinput.h)
add_executable(${EUSDAB_INPUT_EXE_NAME} ${EUSDAB_INPUT_SOURCES})
target_link_libraries(${EUSDAB_INPUT_EXE_NAME} ${SFML_LIBS})
target_link_libraries(${EUSDAB_INPUT_EXE_NAME} ${EUSDAB_LIB})
