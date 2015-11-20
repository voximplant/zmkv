//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#include <iostream>
#include <MuxerIOWriterCallbackDefault.h>
#include <Muxer.h>
#include <AudioCodecInfoACM.h>
#include <AudioTrack.h>
#include <VideoCodecInfoVP8.h>
#include <VideoCodecInfoH264.h>
#include <VideoTrack.h>

using namespace std;

int main() {
    ZMKV::MuxerIOWriterCallbackDefault muxerIOWriterCallbackDefault("./test.mkv");

    ZMKV::Muxer muxer(muxerIOWriterCallbackDefault);
    ZMKV::AudioCodecInfoACM audioCodecInfoACM(8000, 16, 1, ZMKV::wFormatTag::PCM);
    ZMKV::AudioTrack audioTrack(muxer, audioCodecInfoACM, 0, 12345678);

    ZMKV::VideoCodecInfoH264 videoCodecInfoH264(320,240);

    // сконвертить реальный файл h264_pcmu.rtp -> в подходящий для теста и содать с помощью библиотеки файл

//    unsigned char sps[]={1,2,3,4};
//    unsigned char pps[]={1,2,3,4,5,6,7,8,9,0};
//    videoCodecInfoH264.AddPPS(sps,sizeof(sps));
//    videoCodecInfoH264.AddPPS(pps,sizeof(pps));
//    ZMKV::VideoTrack videoTrack(muxer,videoCodecInfoH264,1,87654321);

    short pcm_buf[160];
    for (auto i = 0; i < sizeof(pcm_buf) / sizeof(pcm_buf[0]); i++) {
        pcm_buf[i] = (i & 2) == 0 ? -32700 : +32700;
    }

    unsigned long long ts = 0;
    for (auto i = 0; i < 1000; i++) {

        audioTrack.AddFrame(ts, 0, (const unsigned char *) pcm_buf, sizeof(pcm_buf));
      //  videoTrack.AddFrame(ts,true,(const unsigned char *) video_buf,sizeof(video_buf));
        ts += 20000000;
    }

    return 0;
}