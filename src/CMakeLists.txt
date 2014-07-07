aux_source_directory(. C_SOURCES)

add_library(cweb SHARED ${C_SOURCES})
install(TARGETS cweb DESTINATION bin)

target_link_libraries(cweb ${LINK_LIBRARIES})
