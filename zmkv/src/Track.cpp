//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//

#include <Track.h>
#include <CodecInfo.h>
#include "MuxerPrivate.h"

using namespace ZMKV;
using namespace libmatroska;

Track::Track(Muxer &muxer, const CodecInfo &codecInfo, unsigned int trackNum, unsigned long long trackUUID)
        : muxer(muxer),
          track(AddNewChild<KaxTrackEntry>(muxer.getTracks())) {

    this->track.SetGlobalTimecodeScale(cTimecodeScale);
    EBML_SET(this->track, KaxTrackNumber, EbmlUInteger, trackNum);
    EBML_SET(this->track, KaxTrackUID, EbmlUInteger, trackUUID);
    EBML_SET(this->track, KaxCodecID, EbmlString, codecInfo.CodecID());

    this->track.EnableLacing(false);
}

void Track::AddCodecPrivate(const CodecInfo &codecInfo) {
    KaxCodecPrivate &codecPrivate = GetChild<KaxCodecPrivate>(this->track);
    unsigned int codecPrivateDataSize;
    const binary *codecPrivateData = (const binary *) codecInfo.CodecPrivate(codecPrivateDataSize);
    codecPrivate.CopyBuffer(codecPrivateData, codecPrivateDataSize);
}

