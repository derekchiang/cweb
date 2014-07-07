cmake_minimum_required(VERSION 2.8)
project(cweb)

SET(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH})

SET(BLOCKS_CC_FLAGS "-fblocks")
SET(BLOCKS_LINKER_FLAGS "-lBlocksRuntime")

add_definitions(${BLOCKS_CC_FLAGS})
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${BLOCKS_LINKER_FLAGS}")
add_definitions(${BLOCKS_LINKER_FLAGS})

find_package(PkgConfig)
pkg_check_modules(APR apr-1)
pkg_check_modules(R3 r3)
pkg_check_modules(MICROHTTPD libmicrohttpd)

link_directories(${LINK_DIRECTORIES} ${APR_LIBRARY_DIRS} ${R3_LIBRARY_DIRS} ${MICROHTTPD_LIBRARY_DIRS})
include_directories(${INCLUDE_DIRECTORIES} ${APR_INCLUDE_DIRS} ${R3_INCLUDE_DIRS} ${MICROHTTPD_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)
link_libraries(${LINK_LIBRARIES} ${APR_STATIC_LIBRARIES} ${R3_STATIC_LIBRARIES} ${MICROHTTPD_STATIC_LIBRARIES})

file(GLOB HEADERS "include/*.h")
install(FILES ${HEADERS} DESTINATION include)

add_subdirectory(src)
add_subdirectory(examples)
