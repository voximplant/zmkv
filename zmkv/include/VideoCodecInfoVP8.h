//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#ifndef ZMG_VIDEOCODECINFOVP8_H
#define ZMG_VIDEOCODECINFOVP8_H

#include "VideoCodecInfo.h"

namespace ZMKV {
    class VideoCodecInfoVP8 : public VideoCodecInfo {
    public:
        VideoCodecInfoVP8(unsigned long width, unsigned long height);

        virtual const char *CodecID() const;
    };
}

#endif //ZMG_VIDEOCODECINFOVP8_H
