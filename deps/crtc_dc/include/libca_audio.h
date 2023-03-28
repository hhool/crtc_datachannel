/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-28
 * @file libca_audio.h
 * @description 音频输入 音频输出 声音效果相关函数定义.
 * @音频输入支持 单声道 采样率 [8000 16000 32000 44100 48000] 位深16bits.
 * @音频输出支持 [单声道 双声道] 采样率 [8000 16000 32000 44100 48000]
 * 位深16bits.
 */
#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_AUDIO_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_AUDIO_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

typedef enum crtc_e_channel {
  crtc_e_channel_mono = 0x1,
  crtc_e_channel_stereo = 0x2,
} crtc_e_channel;

typedef enum crtc_e_sample_rate {
  crtc_e_sample_rate_8000hz = 8000,
  crtc_e_sample_rate_16000hz = 16000,
  crtc_e_sample_rate_32000hz = 32000,
  crtc_e_sample_rate_44100hz = 44100,
  crtc_e_sample_rate_48000hz = 48000,
} crtc_e_sample_rate;

/* @void crtc_audio_set_process_info(HANDLE handle_crtc, bool aec, bool ns, bool
 * vad)
 * 回声消除,降噪,语音检测 此接口是全局接口,在sdk初始化后设置一直有效
 * @param[in] handle_crtc                   crtc_init 生成的引擎句柄
 * @param[in] aec                           true 启用回音消除功能,false
 *                                          关闭
 * @param[in] ns                            true 启用降噪功能, false 关闭
 * @param[in] vad                           true 启用语音检测功能, false
 *                                          关闭
 * @return int                              成功:==0 失败:<0
 */
CRTC_API int crtc_audio_set_process_info(HANDLE handle_crtc,
                                         bool aec,
                                         bool ns,
                                         bool vad);

/* @void crtc_audio_set_input_record_delay(HANDLE handle_crtc, int time_ms)
 * 回声消除扬声器外放到再次被麦克风录入时间时长间隔
 * 此接口是全局接口,在sdk初始化后设置一直有效
 * @param[in] handle_crtc                   crtc_init 生成的引擎句柄
 * @param[in] time_ms                       单位毫秒
 * @return int                              成功:==0, 失败:<0
 */
CRTC_API int crtc_audio_set_input_record_delay(HANDLE handle_crtc, int time_ms);

/* @int crtc_pcm_speaker_out_set_info(HANDLE handle_crtc,
                                             crtc_e_channel channels,
                                             crtc_e_sample_rate sample_rate,
                                             int sample_bits)
* 设置模拟扬声器的pcm属性,
* 输出音频通道,通道个数[1,2],采样频率[8000,16000,32000,44100,48000],采样位深[16]
* @param[in] handle_crtc                    crtc_init 生成的引擎句柄
* @param[in] channels                       通道个数
* @param[in] sample_rate                    采样频率
* @param[in] sample_bits                    采样位深
* @return int                               成功:==0 失败:<0
*/
CRTC_API int crtc_pcm_speaker_out_set_info(HANDLE handle_crtc,
                                           crtc_e_channel channels,
                                           crtc_e_sample_rate sample_rate,
                                           int sample_bits);

/* @typedef void (*crtc_pcm_speaker_out_data_cb_func)(const uint8_t* data,
                                                   uint32_t size,
                                                   crtc_e_channel channels,
                                                   crtc_e_sample_rate
 sample_rate, void* reserve)
 * crtc_pcm_speaker_out_set_cb 函数设置的回调函数类型
 * @param[in] data                          音频数据pcm格式
 * @param[in] size                          data的数据长度
 * @param[in] reserve                       保留字段
 * @return void                             无
 */
typedef void (*crtc_pcm_speaker_out_data_cb_func)(const uint8_t* data,
                                                  uint32_t size,
                                                  int channels,
                                                  int sample_rate,
                                                  void* context);

/* @int crtc_pcm_speaker_out_set_cb(HANDLE handle_crtc,
 * rcrtc_pcm_speaker_out_data_cb_func cb) 设置声音处理完毕后的回调函数,
 * @param[in] cb                            声音处理后的回调函数指针
 * @param[in] context                       上下文
 * @return int                              成功:==0 失败:<0
 */
CRTC_API int crtc_pcm_speaker_out_set_cb(HANDLE handle_crtc,
                                         crtc_pcm_speaker_out_data_cb_func cb,
                                         void* context);

/* @int crtc_pcm_mic_in_set_info(HANDLE handle_crtc, int channels, int
 * sample_rate, int sample_bits)
 * 设置模拟mic输入的pcm声音信息,
 * 输入音频通道,通道个数[1],采样频率[8000,16000,32000, 44100,
 * 48000],采样位深[16]
 * @param[in] handle_crtc                   crtc_init 生成的引擎句柄
 * @param[in] channels                      通道个数
 * @param[in] sample_rate                   采样频率
 * @param[in] sample_bits                   采样位深
 * @return int                              成功:==0 失败:<0
 */
CRTC_API int crtc_pcm_mic_in_set_info(HANDLE handle_crtc,
                                      crtc_e_channel channels,
                                      crtc_e_sample_rate sample_rate,
                                      int sample_bits);

/* @int crtc_pcm_mic_in_write(const char* data, uint32_t size, int64_t time_ms)
 * int sample_bits)
 * 写入模拟mic输入的pcm声音数据,
 * 输入音频通道,通道个数[1],采样频率[8000,16000,32000,44100,48000],采样位深[16]
 * @param[in] handle_crtc                   crtc_init 生成的引擎句柄
 * @param[in] data                          pcm 数据
 * @param[in] size                          pcm 数据字节长度
 * @param[in] time_ms                       采样从设备采集到的时刻单位毫秒
 * @return int                              成功:==数据字节长度 失败:<0
 */
CRTC_API int crtc_pcm_mic_in_write(HANDLE handle_crtc,
                                   const uint8_t* data,
                                   uint32_t size,
                                   int64_t time_ms);

/* @typedef void (*crtc_pcm_audio_data_cb_func)uint8_t* data,
                                             uint32_t size,
                                             uint32_t sample_rate,
                                             uint32_t sample_bits,
                                             uint32_t channels)
 * crtc_pcm_register_recording_data_callback和crtc_pcm_register_play_data_callback
 函数设置的回调函数类型
 * @param[in] data                       音频数据
 * @param[in] size                       音频数据字节长度
 * @param[in] sample_rate                音频数据的采样率
 * @param[in] sample_bits                音频数据采样点数据大小（目前是2字节）
 * @param[in] channels                   音频数据的通道数
 * @return void                          无
 */
typedef void (*crtc_pcm_audio_data_cb_func)(uint8_t* data,
                                            uint32_t size,
                                            uint32_t sample_rate,
                                            uint32_t sample_bits,
                                            uint32_t channels);

// TODO(hhool):
/* @int crtc_pcm_register_recording_data_callback(HANDLE handle_crtc,
 * crtc_pcm_audio_data_cb_func cbRecording) 注册获取麦克风采集pcm数据的回调函数,
 * @param[in] handle_crtc                   crtc_init 生成的引擎句柄
 * @param[in] cbRecording                   获取麦克风数据的回调函数指针
 * @return int                              成功:==0 失败:<0
 */
CRTC_API int crtc_pcm_register_recording_data_callback(
    HANDLE handle_crtc,
    crtc_pcm_audio_data_cb_func cbRecording);

// TODO(hhool):
/* @int crtc_pcm_register_play_data_callback(HANDLE handle_crtc,
 * crtc_pcm_audio_data_cb_func cbPlay) 注册获取扬声器播放pcm数据的回调函数,
 * @param[in] handle_crtc                  crtc_init 生成的引擎句柄
 * @param[in] cbPlay                       获取扬声器数据的回调函数指针
 * @return int                             成功:==0 失败:<0
 */
CRTC_API int crtc_pcm_register_play_data_callback(
    HANDLE handle_crtc,
    crtc_pcm_audio_data_cb_func cbPlay);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_AUDIO_H_
