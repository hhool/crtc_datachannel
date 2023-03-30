/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-27
 * @file libca_jsep.h
 * @brief jsep c api
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_JSEP_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_JSEP_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

typedef struct crtc_sdp_parse_error {
  char* line;
  char* description;
} crtc_sdp_parse_error;

// https://w3c.github.io/webrtc-pc/#dom-rtcsdptype
enum crtc_e_sdp_type {
  // Description must be treated as an SDP offer.
  kOffer,
  // Description must be treated as an SDP answer, but not a final
  // answer.
  kPrAnswer,
  // Description must be treated as an SDP final answer, and the offer-
  // answer exchange must be considered complete after receiving this.
  kAnswer
};

/**
 * @brief Creates a IceCandidateInterface based on SDP string.
 * Returns null if the sdp string can't be parsed.
 * |error| may be null.
 * @param sdp_mid                           sdp_mid
 * @param sdp_mline_index                   sdp_mline_index
 * @param error                             error
 * @return HANDLE                           success：!= NULL，failed：== NULL
 */
CRTC_API HANDLE crtc_jsep_create_ice_candidate(const char* sdp_mid,
                                               int sdp_mline_index,
                                               const char* sdp,
                                               int* error);

/**
 * @brief  get sdp_mid from handle_ic
 * @param handle_ic                         handle_ic
 * @param buffer                            buffer
 * @param length                            length
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_jsep_ic_get_sdp_mid(HANDLE handle_ic,
                                      char* buffer,
                                      int* length);

/**
 * @brief get sdp_mline_index from handle_ic
 * @param handle_ic                         handle_ic
 * @param sdp_mline_index                   sdp_mline_index
 * @return int                             success：== 0，failed：< 0
 */
CRTC_API int crtc_jsep_ic_get_sdp_mline_index(HANDLE handle_ic,
                                              int* sdp_mline_index);

/**
 * @brief get server_url from handle_ic
 * @param handle_ic                         handle_ic
 * @param buffer                            buffer
 * @param length                            length
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_jsep_ic_get_server_url(HANDLE handle_ic,
                                         char* buffer,
                                         int* length);

/**
 * @brief get ic format sdp string
 * @param handle_ic                         handle_ic
 * @param buffer                            buffer
 * @param length                            length
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_jsep_ic_to_string(HANDLE handle_ic,
                                    char* buffer,
                                    int* length);

/**
 * @brief  get size from handle_cc
 * @param handle_cc                         handle_cc
 * @return int                              success：= 0，failed：< 0
 */
CRTC_API int crtc_jsep_cc_get_size(HANDLE handle_cc);

/**
 * @brief exsit ice candidate
 * @param handle_cc                         handle_cc
 * @param handle_ic                         handle_ic
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_jsep_cc_has_ice_candidate(HANDLE handle_cc, HANDLE handle_ic);

/**
 * @brief get ice candidate from handle_cc
 * @param handle_cc                         handle_cc
 * @param pos                               pos
 * @return HANDLE                           success：!= NULL，failed：== NULL
 */
CRTC_API HANDLE crtc_jsep_cc_get_ice_candidate(HANDLE handle_cc, int pos);

/**
 * @brief Creates a SessionDescriptionInterface based on the SDP string and the
 type. Returns null if the sdp string can't be parsed or the type is
 unsupported. |error| may be null.
 * @param type                              type
 * @param sdp                               sdp
 * @param error                             error
 * @return HANDLE                           success：!= NULL，failed：== NULL
 */
CRTC_API HANDLE crtc_jsep_create_session_description(crtc_e_sdp_type type,
                                                     const char* sdp,
                                                     int* error);

CRTC_API void crtc_jsep_destory(HANDLE handle_sdp);

/**
 * @brief get sdp format handle_sdp
 * @param handle_sdp                        handle_sdp
 * @return char*                            success：!= NULL，failed：== NULL
 */
CRTC_API const char* crtc_jsep_sdp_get_session_id(HANDLE handle_sdp);

/**
 * @brief get sdp version from handle_sdp
 * @param handle_sdp                        handle_sdp
 * @return char*                            success：!= NULL，failed：== NULL
 */
CRTC_API const char* crtc_jsep_sdp_get_session_version(HANDLE handle_sdp);

/**
 * @brief get sdp type from handle_sdp
 * @param handle_sdp                        handle_sdp
 * @return crtc_e_sdp_type
 */
CRTC_API crtc_e_sdp_type crtc_jsep_sdp_get_type(HANDLE handle_sdp);

/**
 * @brief add ice candidate to handle_sdp
 * @param handle_sdp                        handle_sdp
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_jsep_sdp_add_candidate(HANDLE handle_sdp, HANDLE handle_ic);

/**
 * @brief remove ice candidate from handle_sdp
 * @param handle_sdp                        handle_sdp
 * @param handle_ic                         handle_ic
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_jsep_sdp_remove_candidate(HANDLE handle_sdp,
                                            HANDLE handle_ic);

/**
 * @brief Returns the number of m= sections in the session description.
 * @param handle_sdp                        handle_sdp
 * @param handle_ic                         handle_ic
 * @param number_of_mediasections           pointer to number of m= sections
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_jsep_sdp_number_of_mediasections(
    HANDLE handle_sdp,
    HANDLE handle_ic,
    int* number_of_mediasections);

/**
 * @brief get ice candidate from handle_sdp by mediasection_index
 * @param handle_sdp                        handle_sdp
 * @param mediasection_index                mediasection_index
 * @return int
 */
CRTC_API int crtc_jsep_sdp_get_candidates(HANDLE handle_sdp,
                                          int mediasection_index);

/**
 * @brief convert handle_sdp to string
 * @param handle_sdp                        handle_sdp
 * @param buffer                            buffer
 * @return int
 */
CRTC_API int crtc_jsep_sdp_to_string(HANDLE handle_sdp,
                                     char* buffer,
                                     int* length);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_JSEP_H_
