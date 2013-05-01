# EUSDAB input test
set(EUSDAB_ANIMATION_EXE_NAME "EUSDAB_animation")
set(EUSDAB_ANIMATION_SOURCES main.cpp testanimation.cpp testanimation.h)
add_executable(${EUSDAB_ANIMATION_EXE_NAME} ${EUSDAB_ANIMATION_SOURCES})
target_link_libraries(${EUSDAB_ANIMATION_EXE_NAME} ${SFML_LIBS})
target_link_libraries(${EUSDAB_ANIMATION_EXE_NAME} ${EUSDAB_LIB})
