#
#
# @description: crtc dc module third party dependency package

cmake_minimum_required(VERSION 3.10)
project(crtc_dc VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(crtc_dc)

# crtc_dc dependencies
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/crtc_dc/include)
link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/deps/crtc_dc/win_x86_debug/libcrtc_x86.dll.lib)

# crtc_dc global complier settings
if(MSVC)
    set(variables CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_CXX_FLAGS_MINSIZEREL)

    foreach(variable ${variables})
        if(${variable} MATCHES "/MT")
            string(REGEX REPLACE "/MT" "/MD" ${variable} "${${variable}}")
        endif()

        if(${variable} MATCHES "/MTd")
            string(REGEX REPLACE "/MTd" "/MDd" ${variable} "${${variable}}")
        endif()
    endforeach()

    add_compile_options(
        $<$<CONFIG:>:/MD> # ---------|
        $<$<CONFIG:Debug>:/MDd> # ---|-- Statically link the runtime libraries
        $<$<CONFIG:Release>:/MD> # --|
        $<$<CONFIG:MinSizeRel>:/MD> # --|
        $<$<CONFIG:RelWithDebInfo>:/MD> # --|
    )
endif()

# crtc_dc global macro settings
if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE)
endif()

if(WIN32)
    add_definitions(-D_UNICODE -DUNICODE -DNOMINMAX)
else()
    add_definitions(-D_POSIX_)
endif()

# crtc_dc sub directory
add_subdirectory(crtc_utils)
add_subdirectory(deps/crtc_dc)

# crtc_dc test
enable_testing()
add_subdirectory(tests)
