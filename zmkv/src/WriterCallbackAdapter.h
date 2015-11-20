//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#ifndef ZMG_WRITERCALLBACKADAPTER_H
#define ZMG_WRITERCALLBACKADAPTER_H

#include <ebml/IOCallback.h>

namespace ZMKV {
    class MuxerIOWriterCallback;

    class WriterCallbackAdapter : public libebml::IOCallback {
    public:
        WriterCallbackAdapter(MuxerIOWriterCallback &muxerIOWriterCalback);

        virtual uint32 read(void *buffer, size_t size);

        virtual void setFilePointer(int64 offset, libebml::seek_mode mode = libebml::seek_beginning);

        virtual size_t write(const void *buffer, size_t Size);

        virtual uint64 getFilePointer();

        virtual void close();

    private:
        MuxerIOWriterCallback &muxerIOWriterCalback;
        uint64 position;
    };
}

#endif //ZMG_WRITERCALLBACKADAPTER_H
