//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#ifndef ZMG_AUDIOCODECINFO_H
#define ZMG_AUDIOCODECINFO_H

#include "CodecInfo.h"

namespace ZMKV {
    class AudioCodecInfo : public CodecInfo {
    public:
        AudioCodecInfo(unsigned int freq, unsigned int bitsPerSample, unsigned int channels);

        const unsigned int freq;
        const unsigned int bitsPerSample;
        const unsigned int channels;
    };
}

#endif //ZMG_AUDIOCODECINFO_H
