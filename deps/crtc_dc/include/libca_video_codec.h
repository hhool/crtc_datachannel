/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-20
 * @file libca_video_codec.h
 * @description video codec c api
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_VIDEO_CODEC_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_VIDEO_CODEC_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

enum crtc_e_video_error {
  kVideoCodecErrorOkRequstKeyframe = 4,
  kVideoCodecErrorNoOutput = 1,
  kVideoCodecErrorOK = 0,
  kVideoCodecError = -1,
  kVideoCodecErrorMemory = -3,
  kVideoCodecErrorParameter = -4,
  kVideoCodecErrorUninitialized = -7,
  kVideoCodecErrorFallbackSoftware = -13,
  kVideoCodecErrorTargetBitrateOvershoot = -14,
  kVideoCodecErrorSimulcastParameterUnSupported = -15,
};

enum crtc_e_video_codec_type {
  kVideoCodecGeneric = 0,
  kVideoCodecVP8,
  kVideoCodecVP9,
  kVideoCodecAV1,
  kVideoCodecH264,
  kVideoCodecMultiplex,
};

enum crtc_e_h264_profile {
  kProfileConstrainedBaseline,
  kProfileBaseline,
  kProfileMain,
  kProfileConstrainedHigh,
  kProfileHigh,
};

enum crtc_e_video_codec_mode { kRealtimeVideo, kScreensharing };

struct crtc_video_codec {
  crtc_e_video_codec_type codecType;
  unsigned char plType;

  uint16_t width;
  uint16_t height;

  unsigned int startBitrate;  // kilobits/sec.
  unsigned int maxBitrate;    // kilobits/sec.
  unsigned int minBitrate;    // kilobits/sec.

  uint32_t maxFramerate;
  crtc_e_video_codec_mode mode;
};

enum crtc_e_frame_type {
  kFrameType_EmptyFrame = 0,
  kFrameType_AudioFrameSpeech = 1,
  kFrameType_AudioFrameCN = 2,
  kFrameType_VideoFrameKey = 3,
  kFrameType_VideoFrameDelta = 4,
};

struct crtc_video_sdp_format {
  char name[256];
};

struct crtc_frame_buffer {
  const uint8_t* Y_;
  int Y_Stride_;
  const uint8_t* U_;
  int U_Stride_;
  const uint8_t* V_;
  int V_Stride_;
  int width_;
  int height_;
};

struct crtc_video_frame {
  crtc_frame_buffer frame_buffer;
  uint32_t timestamp_rtp_;
  int64_t ntp_time_ms_;
  int64_t timestamp_us_;
};

struct crtc_encoded_buffer {
  uint8_t* data_;
  uint32_t length_;
};

struct crtc_encoded_frame {
  crtc_encoded_buffer buffer_;
  crtc_e_frame_type frame_type_;
  uint32_t width_;
  uint32_t height_;
  uint32_t timestamp_rtp_;
  int64_t ntp_time_ms_;
  int64_t timestamp_us_;
};

typedef int32_t (*ENCODE_INIT)(HANDLE handle,
                               const crtc_video_codec* codec_settings,
                               int32_t number_of_cores,
                               size_t max_payload_size);

typedef int32_t (*ENCODE_RELEASE)(HANDLE handle);

typedef void (*ENCODE_DISPOSE)(HANDLE handle);

typedef int32_t (*ENCODE_ENCODE)(HANDLE handle,
                                 const ::crtc_video_frame* frame,
                                 const bool request_key_frame,
                                 HANDLE context);

typedef int32_t (*ENCODE_SET_RATE)(HANDLE context,
                                   uint32_t bitrate,
                                   uint32_t framerate);

struct crtc_video_encoder_adapt {
  ENCODE_INIT Method_InitEncode;
  ENCODE_RELEASE Method_Release;
  ENCODE_DISPOSE Method_Dispose;
  ENCODE_ENCODE Method_Encode;
  ENCODE_SET_RATE Method_Set_Rate;
  void* Extral_Context_;
};

typedef int32_t (*ENCODE_SUPPORTED_FORMAT)(crtc_video_sdp_format* formats,
                                           int count);
typedef int32_t (*ENCODE_CREATE)(crtc_video_sdp_format format,
                                 HANDLE* context,
                                 crtc_video_encoder_adapt* adpat);
struct crtc_video_encoder_adapt_factory {
  ENCODE_SUPPORTED_FORMAT Method_Supported_Format;
  ENCODE_CREATE Method_Create_Encoder;
};

CRTC_API int crtc_video_encode_deliver_encoded_frame(
    HANDLE context,
    const crtc_encoded_frame* frame);

struct crtc_encodec_image {
  crtc_encoded_buffer buffer_;
  uint32_t timestamp_rtp_;
  int64_t ntp_time_ms_;
};

typedef int32_t (*DECODE_INIT)(HANDLE handle_decoder,
                               const crtc_video_codec* codec_settings,
                               int32_t number_of_cores);

typedef int32_t (*DECODE_DECODE)(HANDLE handle_decoder,
                                 const crtc_encodec_image* input_image,
                                 bool missing_frames,
                                 int64_t render_time_ms,
                                 HANDLE decoded_handle);

typedef int32_t (*DECODE_RELEASE)(HANDLE handle_decoder);

typedef int (*DECODE_PREFERS_LATE_DECODING)(HANDLE handle_decoder);

typedef const char* (*DECODE_IMPLEMENTATION_NAME)(HANDLE handle_decoder);

struct crtc_video_decoder_adapt {
  DECODE_INIT Method_InitDecode;
  DECODE_DECODE Method_Decode;
  DECODE_RELEASE Method_Release;
  ENCODE_DISPOSE Method_Dispose;
  DECODE_PREFERS_LATE_DECODING Method_PrefersLateDecoding;
  DECODE_IMPLEMENTATION_NAME Method_ImplementationName;
};

typedef int32_t (*DECODE_SUPPORTED_FORMAT)(crtc_video_sdp_format* formats,
                                           int count);

typedef int32_t (*DECODER_CREATE)(crtc_video_sdp_format format,
                                  HANDLE* context,
                                  crtc_video_decoder_adapt* adapt);

struct crtc_video_decoder_adapt_factory {
  DECODE_SUPPORTED_FORMAT Method_Supported_Format;
  DECODER_CREATE Method_Create_Decoder;
};

CRTC_API int crtc_video_decode_deliver_image_frame(
    HANDLE handle,
    const crtc_video_frame* video_frame);
#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_VIDEO_CODEC_H_
