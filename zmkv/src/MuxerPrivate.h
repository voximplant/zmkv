//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#ifndef ZMG_MUXERPRIVATE_H
#define ZMG_MUXERPRIVATE_H

#include <ebml/StdIOCallback.h>
#include <ebml/EbmlVoid.h>
#include <matroska/KaxSegment.h>
#include <matroska/KaxTracks.h>
#include <matroska/KaxCluster.h>
#include <matroska/KaxSeekHead.h>
#include <memory>
#include <Muxer.h>

extern const unsigned long long cTimecodeScale;

#define EBML_SET(parent, TField, TValue, value)  {TField &tmp = GetChild<TField>(parent);*(static_cast<TValue *>(&tmp)) = (value);}

namespace ZMKV{
    class MuxerPrivate {
    public:
        MuxerPrivate(IOCallback& file);
        ~MuxerPrivate();

        // used from Muxer.cpp
        libmatroska::KaxTracks *tracks;
        std::unique_ptr<libmatroska::KaxCluster> currentCluster;

        void ProcessClusters(bool video, bool key, unsigned long long ts);

    private:
        void InitFileHeader();
        void InitSegmentInfo();
        void UpdateDuration();

        void CreateNewCluster(unsigned long long ts);
        void CloseCurrentCluster();

        IOCallback& file;
        libmatroska::KaxSegment segment;
        libebml::EbmlVoid dummySeekHead;
        libebml::EbmlVoid dummyTracks;
        libmatroska::KaxDuration * kaxDuration;

        filepos_t segmentSize, segmentInfoSize;

        libmatroska::KaxSeekHead seekHead;
        libmatroska::KaxCues cues;
        uint64 renderedClustersSize;

        uint64 max_ts;
    };
}



#endif //ZMG_MUXERPRIVATE_H
