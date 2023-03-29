# CMakeLists.txt demo

cmake_minimum_required(VERSION 3.15)
project(tests)

# add GTest dependency to the project
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

# add crtc_dc_test project
add_executable(crtc_dc_test main.cc
        libca_crtc_dc_unittest.h
        libca_crtc_dc_unittest.cc)

target_include_directories(crtc_dc_test PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}/../deps/crtc_dc/include)

set(CRTC_SO_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../deps/crtc_dc)
set(CRTC_SO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../deps/crtc_dc)
set(CRTC_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../deps/crtc_dc)

if(${CMAKE_SIZEOF_VOID_P} EQUAL "8")
        set(PROJECTNAME_ARCHITECTURE "x64")
else()
        set(PROJECTNAME_ARCHITECTURE "x86")
endif()

message(STATUS "PROJECTNAME_ARCHITECTURE: ${PROJECTNAME_ARCHITECTURE}")

if(MSVC)
        if("${CMAKE_BUILD_TYPE}" EQUAL "Release")
                if(CMAKE_CL_64 OR ${PROJECTNAME_ARCHITECTURE} MATCHES "x64")
                        string(APPEND CRTC_LIB_PATH /win_x64_release)
                        string(APPEND CRTC_SO_PATH /win_x64_release)
                        target_link_libraries(crtc_dc_test
                                PRIVATE ${CRTC_LIB_PATH}/libcrtc_x64.dll.lib)
                else()
                        string(APPEND CRTC_LIB_PATH /win_x86_release)
                        string(APPEND CRTC_SO_PATH /win_x86_release)
                        target_link_libraries(crtc_dc_test
                                PRIVATE ${CRTC_LIB_PATH}/libcrtc_x86.dll.lib)
                endif()
        else()
                if(CMAKE_CL_64 OR ${PROJECTNAME_ARCHITECTURE} MATCHES "x64")
                        string(APPEND CRTC_LIB_PATH /win_x64_debug/)
                        string(APPEND CRTC_SO_PATH /win_x64_debug/)
                        target_link_libraries(crtc_dc_test
                                PRIVATE ${CRTC_LIB_PATH}/libcrtc_x64.dll.lib)
                else()
                        string(APPEND CRTC_LIB_PATH /win_x86_debug)
                        string(APPEND CRTC_SO_PATH /win_x86_debug)
                        target_link_libraries(crtc_dc_test
                                PRIVATE ${CRTC_LIB_PATH}/libcrtc_x86.dll.lib)
                endif()
        endif()
endif()

if(APPLE)
        message(STATUS "Check if the CPU is ARM")

        if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm.*" OR ${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64.*")
                set(IS_ARM_ISA TRUE)
                message(STATUS "Check if the CPU is ARM - TRUE" )
        else()
                set(IS_ARM_ISA FALSE)
                message(STATUS "Check if the CPU is ARM - FALSE")
        ENDIF()

        message(STATUS "CMAKE_OSX_ARCHITECTURES:${CMAKE_OSX_ARCHITECTURES}")

        if(${CMAKE_OSX_ARCHITECTURES} MATCHES "x86_64")
                set(IS_ARM_ISA false)
        elseif(${CMAKE_OSX_ARCHITECTURES} MATCHES "arm64")
                set(IS_ARM_ISA true)
        endif()
        if(NOT IS_ARM_ISA)
                string(APPEND CRTC_LIB_PATH /mac_x64_debug)
                string(APPEND CRTC_SO_PATH /mac_x64_debug)
                target_link_libraries(crtc_dc_test
                        PRIVATE ${CRTC_LIB_PATH}/libcrtc_x64.so)
                message(STATUS "x64 target")
        else()
                string(APPEND CRTC_LIB_PATH /mac_arm64_debu)
                string(APPEND CRTC_SO_PATH /mac_arm64_debug)
                target_link_libraries(crtc_dc_test
                        PRIVATE ${CRTC_LIB_PATH}/libcrtc_arm64.so)
                message(STATUS "arm64 target")
        endif()
endif()

target_link_libraries(crtc_dc_test PRIVATE crtc_utils_static GTest::GTest)

add_test(tests crtc_dc_test)

# set environment variable for crtc_dc_test running
if(MSVC)
        set_target_properties(crtc_dc_test PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${CRTC_SO_PATH}")
endif()
