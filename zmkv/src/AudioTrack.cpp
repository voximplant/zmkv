//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//

#include <AudioTrack.h>
#include <AudioCodecInfo.h>
#include "MuxerPrivate.h"

using namespace libmatroska;
using namespace ZMKV;


AudioTrack::AudioTrack(Muxer &muxer, const AudioCodecInfo &codecInfo,unsigned int trackNum, unsigned long long trackUUID)
        : Track(muxer,codecInfo,trackNum,trackUUID) {

    EBML_SET(this->track, KaxTrackType, EbmlUInteger, track_audio);

    AddCodecPrivate(codecInfo);

    KaxTrackAudio &audioTrackInfo = GetChild<KaxTrackAudio>(track);

    EBML_SET(audioTrackInfo, KaxAudioSamplingFreq, EbmlFloat, codecInfo.freq);
    EBML_SET(audioTrackInfo, KaxAudioBitDepth, EbmlUInteger, codecInfo.bitsPerSample);
    EBML_SET(audioTrackInfo, KaxAudioChannels, EbmlUInteger, codecInfo.channels);
}

void AudioTrack::AddFrame(unsigned long long ts, unsigned long long , const unsigned char *data, unsigned long long size) {

    muxer.ProcessClusters(false, false, ts);

    KaxSimpleBlock & simpleBlock = AddNewChild<KaxSimpleBlock>(this->muxer.getCurrentCluster());
    simpleBlock.SetParent(this->muxer.getCurrentCluster());

    // TODO: think about minimize copy!, now packets are copied to new buf
    DataBuffer *buf = new DataBuffer((binary *)data, (uint32) size,NULL,true);
    simpleBlock.AddFrame(this->track,ts,*buf,LACING_EBML, false);

//    KaxBlockBlob *Blob1 = new KaxBlockBlob(BLOCK_BLOB_NO_SIMPLE);
 //   Blob1->SetParent(this->muxer.getCurrentCluster());
  //  KaxCuePoint& cuePoint = AddNewChild<KaxCuePoint>(this->muxer.getCues());
}

