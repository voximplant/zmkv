//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#ifndef ZMG_AUDIOCODECINFOOPUS_H
#define ZMG_AUDIOCODECINFOOPUS_H

#include "AudioCodecInfo.h"

namespace ZMKV{
    class AudioCodecInfoOpus: public AudioCodecInfo {
    public:
        // TODO: add pre-skip parameter used in opus header
        AudioCodecInfoOpus(unsigned int freq, unsigned int bitsPerSample, unsigned int channels,unsigned short pre_skip = 312);

        virtual const char *CodecID() const;
    };
}



#endif //ZMG_AUDIOCODECINFOOPUS_H
