cmake_minimum_required(VERSION 2.8)
project(cweb)

SET(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH})

SET(BLOCKS_CC_FLAGS "-fblocks")
SET(BLOCKS_LINKER_FLAGS "-lBlocksRuntime")

add_definitions(${BLOCKS_CC_FLAGS})

find_package(PkgConfig)
pkg_check_modules(APR apr-1)
pkg_check_modules(R3 r3)
pkg_check_modules(MICROHTTPD libmicrohttpd)

link_directories(${LINK_DIRECTORIES} ${APR_LIBRARY_DIRS} ${R3_LIBRARY_DIRS} ${MICROHTTPD_LIBRARY_DIRS})
include_directories(${LINK_DIRECTORIES} ${APR_INCLUDE_DIRS} ${R3_INCLUDE_DIRS} ${MICROHTTPD_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)

install(FILES include/cweb.h include/cweb_common.h include/cweb_http.h include/cweb_router.h include/cweb_server.h DESTINATION include)

