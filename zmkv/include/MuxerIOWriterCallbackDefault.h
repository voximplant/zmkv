//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#ifndef ZMG_MUXERIOWRITERCALLBACKDEFAULT_H
#define ZMG_MUXERIOWRITERCALLBACKDEFAULT_H

#include "MuxerIOWriterCallback.h"

namespace ZMKV {

    class MuxerIOWriterCallbackDefault : public MuxerIOWriterCallback {
    public:
        MuxerIOWriterCallbackDefault(const char *path);

        ~MuxerIOWriterCallbackDefault();

        virtual int write(const void *buffer, unsigned int size);

        virtual void seek(long long offset, SeekMode mode);

        virtual void close();

    private:
        void *file;
    };
}


#endif //ZMG_MUXERIOWRITERCALLBACKDEFAULT_H
