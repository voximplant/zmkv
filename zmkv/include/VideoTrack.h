//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#ifndef ZMG_VIDEOTRACK_H
#define ZMG_VIDEOTRACK_H

#include "Track.h"

namespace ZMKV {
    class VideoCodecInfo;
    class VideoTrack : public Track {
    public:
        VideoTrack(Muxer &muxer, const VideoCodecInfo &codecInfo,unsigned int trackNum, unsigned long long trackUUID);

        void AddFrame(unsigned long long ts, bool key, const unsigned char *data, unsigned long long size);
    };
}


#endif //ZMG_VIDEOTRACK_H
