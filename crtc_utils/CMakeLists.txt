cmake_minimum_required(VERSION 3.16.0)

project(crtc_utils)

set(SRC_LIST
    libca_crtc_utils_api.h
    libca_crtc_utils_api.cc
    libca_crtc_utils_thread.h
    libca_crtc_utils_thread.cc
    libca_crtc_utils_log.h
    libca_crtc_utils_log.cc
    libca_crtc_utils_sdp.h
    libca_crtc_utils_sdp.cc)

add_library(crtc_utils_static STATIC ${SRC_LIST})