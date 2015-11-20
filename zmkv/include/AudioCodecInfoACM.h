//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//

#ifndef ZMG_AUDIOCODECINFOPCMU_H
#define ZMG_AUDIOCODECINFOPCMU_H

#include "AudioCodecInfo.h"



namespace ZMKV {

    namespace wFormatTag{
        enum {
            PCM  = 0x0001,
            PCMA = 0x0006,
            PCMU = 0x0007,
            G729 = 0x0083,
            Speex = 0xa109
        };
    }

    class AudioCodecInfoACM : public AudioCodecInfo {
    public:
        AudioCodecInfoACM(unsigned int freq, unsigned int bitsPerSample, unsigned int channels, unsigned short wFormatTag);

        virtual const char *CodecID() const;
    };
}

#endif //ZMG_AUDIOCODECINFOPCMU_H
