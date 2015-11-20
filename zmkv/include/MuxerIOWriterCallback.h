//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//

#ifndef ZMG_MUXERIOWRITERCALLBACK_H
#define ZMG_MUXERIOWRITERCALLBACK_H

namespace ZMKV {

    class MuxerIOWriterCallback {
    public:
        virtual ~MuxerIOWriterCallback(){};

        virtual int write(const void *buffer, unsigned int size) = 0;

        enum SeekMode {
            Begin,
            End,
            Current
        };

        virtual void seek(long long offset, SeekMode mode) = 0;

        virtual void close() = 0;
    };
}

#endif //ZMG_MUXERIOWRITERCALLBACK_H
