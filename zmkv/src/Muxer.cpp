//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#include <Muxer.h>
#include "MuxerPrivate.h"
#include "WriterCallbackAdapter.h"

using namespace ZMKV;

Muxer::Muxer(MuxerIOWriterCallback &callback) : callbackAdapter(new WriterCallbackAdapter(callback)), priv(new MuxerPrivate(*callbackAdapter)) {
}

libmatroska::KaxTracks &Muxer::getTracks() {
    return *this->priv->tracks;
}

libmatroska::KaxCluster &Muxer::getCurrentCluster() {
    return *this->priv->currentCluster;
}

void Muxer::ProcessClusters(bool video, bool key, unsigned long long ts)
{
    this->priv->ProcessClusters(video, key, ts);
}
