cmake_minimum_required(VERSION 3.10)
project(libcrtc_dc)

add_library(libcrtc_dc INTERFACE)

target_include_directories(libcrtc_dc INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(libcrtc_dc INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/win_x86_debug/libcrtc_dc.lib
)
