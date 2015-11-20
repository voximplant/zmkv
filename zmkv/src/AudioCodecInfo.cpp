//
// Created by Andrey Syvrachev on 24.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//

#include "AudioCodecInfo.h"

using namespace ZMKV;

AudioCodecInfo::AudioCodecInfo(unsigned int freq, unsigned int bitsPerSample, unsigned int channels)
        : freq(freq),
          bitsPerSample(bitsPerSample),
          channels(channels) {
}
