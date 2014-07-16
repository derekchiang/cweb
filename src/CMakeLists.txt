aux_source_directory(. C_SOURCES)

add_library(cweb SHARED ${C_SOURCES})

add_library(cweb_static STATIC ${C_SOURCES})
set_target_properties(cweb_static PROPERTIES OUTPUT_NAME cweb)

target_link_libraries(cweb custache)
target_link_libraries(cweb_static custache)

install(TARGETS cweb DESTINATION lib)
install(TARGETS cweb_static DESTINATION lib)
