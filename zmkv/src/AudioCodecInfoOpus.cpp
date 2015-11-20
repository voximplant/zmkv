//
// Created by Andrey Syvrachev on 27.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//

#include <AudioCodecInfoOpus.h>
#include <assert.h>
#include <string.h>

using namespace ZMKV;

#pragma pack(push,1)
class OpusPrivateData {
public:
    OpusPrivateData(unsigned char channels, unsigned short freq, unsigned short pre_skip)
            : version(1), channels(channels), freq(freq), pre_skip(pre_skip) {
        memcpy(this->header, "OpusHead", sizeof(this->header));
        memset(this->padding,0, sizeof(this->padding));
        assert(sizeof(*this) == 19);
    }
private:
    unsigned char header[8];
    unsigned char version;
    unsigned char channels;
    unsigned short pre_skip;
    unsigned short freq;
    unsigned char padding[5];
};
#pragma pack(pop)

AudioCodecInfoOpus::AudioCodecInfoOpus(unsigned int freq, unsigned int bitsPerSample, unsigned int channels, unsigned short pre_skip)
        : AudioCodecInfo(freq, bitsPerSample, channels) {

    OpusPrivateData opusPrivateData((unsigned char) channels,(unsigned short) freq,pre_skip);

    this->codecPrivateData.insert(this->codecPrivateData.end(),
                                  (const unsigned char *) &opusPrivateData,
                                  (const unsigned char *) (&opusPrivateData + 1));
}

const char *AudioCodecInfoOpus::CodecID() const {
    return "A_OPUS";
}
