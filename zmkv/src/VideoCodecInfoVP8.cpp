
//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//

#include <VideoCodecInfoVP8.h>

using namespace ZMKV;

VideoCodecInfoVP8::VideoCodecInfoVP8(unsigned long width, unsigned long height) : VideoCodecInfo(width,height) {
}

const char *VideoCodecInfoVP8::CodecID() const{
    return "V_VP8";
}
