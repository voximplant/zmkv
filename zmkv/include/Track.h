//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#ifndef ZMG_TRACK_H
#define ZMG_TRACK_H

#include "Muxer.h"

namespace libmatroska {
    class KaxTrackEntry;
}

namespace ZMKV {
    class CodecInfo;

    class Track {
    public:
        Track(Muxer &muxer, const CodecInfo &codecInfo, unsigned int trackNum, unsigned long long trackUUID);

        virtual ~Track() { };
    protected:
        Muxer &muxer;
        libmatroska::KaxTrackEntry &track;

        void AddCodecPrivate(const CodecInfo &codecInfo);
    };
}

#endif //ZMG_TRACK_H
