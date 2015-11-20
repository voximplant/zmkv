//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#ifndef ZMG_VIDEOCODECINFO_H
#define ZMG_VIDEOCODECINFO_H

#include "CodecInfo.h"

namespace ZMKV{
    class VideoCodecInfo : public CodecInfo {
    public:
        VideoCodecInfo(unsigned long width, unsigned long height);

        const unsigned int width,height;
    };
}

#endif //ZMG_VIDEOCODECINFO_H
