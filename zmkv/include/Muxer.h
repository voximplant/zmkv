//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#ifndef ZMG_MUXER_H
#define ZMG_MUXER_H

#include <memory>


namespace libmatroska {
    class KaxTracks;
    class KaxCluster;
}

namespace ZMKV {

    class Track;

    class MuxerPrivate;

    class MuxerIOWriterCallback;
    class WriterCallbackAdapter;
    class Muxer {
    public:
        Muxer(MuxerIOWriterCallback &callback);

        libmatroska::KaxTracks &getTracks();

        libmatroska::KaxCluster &getCurrentCluster();

        void ProcessClusters(bool video, bool key, unsigned long long ts);

    private:
        std::shared_ptr<WriterCallbackAdapter> callbackAdapter;
        std::shared_ptr<MuxerPrivate> priv;
    };
}


#endif //ZMG_MUXER_H
