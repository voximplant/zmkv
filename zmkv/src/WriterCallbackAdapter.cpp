//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#include <MuxerIOWriterCallback.h>
#include "WriterCallbackAdapter.h"

using namespace ZMKV;
using namespace libebml;

WriterCallbackAdapter::WriterCallbackAdapter(MuxerIOWriterCallback &muxerIOWriterCalback) : muxerIOWriterCalback(muxerIOWriterCalback), position(0) {
}

uint32 WriterCallbackAdapter::read(void *, size_t ) {
    assert(0);
    return uint32(-1);
}

void WriterCallbackAdapter::setFilePointer(int64 offset, seek_mode mode) {

    MuxerIOWriterCallback::SeekMode seekMode = MuxerIOWriterCallback::Begin;

    switch (mode) {
        case seek_beginning:
            this->position = (uint64) offset;
            seekMode = MuxerIOWriterCallback::Begin;
            break;
        case seek_current:
            this->position += offset;
            seekMode = MuxerIOWriterCallback::Current;
        case seek_end:
            assert(!"Unhandled seek mode");
            break;
    }

    muxerIOWriterCalback.seek(offset, seekMode);
}

size_t WriterCallbackAdapter::write(const void *buffer, size_t size) {
    int ret_size = muxerIOWriterCalback.write(buffer, (unsigned int) size);
    assert(ret_size == size);
    this->position += ret_size;
    return (size_t) ret_size;
}

uint64 WriterCallbackAdapter::getFilePointer() {
    return this->position;
}

void WriterCallbackAdapter::close() {
    muxerIOWriterCalback.close();
}
