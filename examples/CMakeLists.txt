SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(server server.c)
add_dependencies(server cweb)
target_link_libraries(server cweb ${LINK_LIBRARIES})
