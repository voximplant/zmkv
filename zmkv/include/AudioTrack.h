//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#ifndef ZMG_AUDIOTRACK_H
#define ZMG_AUDIOTRACK_H

#include "Track.h"


namespace ZMKV {
    class AudioCodecInfo;
    class AudioTrack : public Track {
    public:
        AudioTrack(Muxer &muxer, const AudioCodecInfo &codecInfo,unsigned int trackNum, unsigned long long trackUUID);

        void AddFrame(unsigned long long ts, unsigned long long duration, const unsigned char *data, unsigned long long size);
    };
}


#endif //ZMG_AUDIOTRACK_H
