//
// Created by Andrey Syvrachev on 27.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//

#include "AudioCodecInfoACM.h"
#include <matroska/KaxTypes.h>
#include <assert.h>

#pragma pack (push,1)
typedef struct {
    uint16 wFormatTag;
    uint16 nChannels;
    uint32 nSamplesPerSec;
    uint32 nAvgBytesPerSec;
    uint16 nBlockAlign;
    uint16 wBitsPerSample;
    uint16 cbSize;
} WAVEFORMATEX;
#pragma pack(pop)


using namespace ZMKV;

AudioCodecInfoACM::AudioCodecInfoACM(unsigned int freq, unsigned int bitsPerSample, unsigned int channels, unsigned short wFormatTag)
        : AudioCodecInfo(freq, bitsPerSample, channels) {
    assert(sizeof(WAVEFORMATEX) == 18);

    this->codecPrivateData.resize(sizeof(WAVEFORMATEX));

    WAVEFORMATEX *waveFormat = (WAVEFORMATEX *) this->codecPrivateData.data();
    waveFormat->wFormatTag = wFormatTag;
    waveFormat->nChannels = (uint16) channels;
    waveFormat->nSamplesPerSec = freq;
    waveFormat->wBitsPerSample = (uint16) bitsPerSample;
    waveFormat->nBlockAlign = 2;
    waveFormat->nAvgBytesPerSec = waveFormat->nChannels * waveFormat->wBitsPerSample / 8 * waveFormat->nSamplesPerSec;
    waveFormat->cbSize = 0;
}

const char *AudioCodecInfoACM::CodecID() const {
    return "A_MS/ACM";
}
