//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#include <VideoTrack.h>
#include "VideoCodecInfo.h"
#include "MuxerPrivate.h"


using namespace ZMKV;
using namespace libmatroska;

VideoTrack::VideoTrack(Muxer &muxer, const VideoCodecInfo &codecInfo, unsigned int trackNum, unsigned long long trackUUID)
        : Track(muxer, codecInfo, trackNum, trackUUID) {

    EBML_SET(this->track, KaxTrackType, EbmlUInteger, track_video);

    AddCodecPrivate(codecInfo);

    // video specific params
    KaxTrackVideo &videoTrackInfo = GetChild<KaxTrackVideo>(this->track);
    EBML_SET(videoTrackInfo, KaxVideoPixelWidth, EbmlUInteger, codecInfo.width);
    EBML_SET(videoTrackInfo, KaxVideoPixelHeight, EbmlUInteger, codecInfo.height);
}

void VideoTrack::AddFrame(unsigned long long ts, bool key, const unsigned char *data, unsigned long long size) {

    muxer.ProcessClusters(true, key, ts);

    KaxSimpleBlock &simpleBlock = AddNewChild<KaxSimpleBlock>(this->muxer.getCurrentCluster());
    simpleBlock.SetParent(this->muxer.getCurrentCluster());
    simpleBlock.SetKeyframe(key);

    // TODO: think about minimize copy!, now packets are copied to new buf
    DataBuffer *buf = new DataBuffer((binary *) data, (uint32) size, NULL, true);
    simpleBlock.AddFrame(this->track, ts, *buf, LACING_EBML, false);
}