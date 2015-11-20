//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#ifndef ZMG_VIDEOCODECINFO_H264_H
#define ZMG_VIDEOCODECINFO_H264_H

#include "VideoCodecInfo.h"

namespace ZMKV {
    class VideoCodecInfoH264 : public VideoCodecInfo {
    public:
        VideoCodecInfoH264(unsigned long width, unsigned long height);

        virtual const char *CodecID() const;

        void AddSPS(const unsigned char *data, unsigned long size);
        void AddPPS(const unsigned char *data, unsigned long size);

        bool Completed();

    private:
        std::vector<unsigned char> sps;
        std::vector<unsigned char> pps;

        void tryToMakeCodecPrivate();
    };
}



#endif //ZMG_VIDEOCODECINFO_H
