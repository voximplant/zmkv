//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#include "MuxerIOWriterCallbackDefault.h"
#include <stdio.h>
#include <assert.h>

using namespace ZMKV;

MuxerIOWriterCallbackDefault::MuxerIOWriterCallbackDefault(const char *path) : file(NULL) {
    this->file = fopen(path, "wb");
    assert(this->file);
}

MuxerIOWriterCallbackDefault::~MuxerIOWriterCallbackDefault() {
    assert(this->file == NULL && "File must be closed by close() method");
}

int MuxerIOWriterCallbackDefault::write(const void *buffer, unsigned int size) {
    assert(this->file && "File must be opened");
    return (int) fwrite(buffer, 1, size, (FILE*)this->file);
}

static int convertMode(MuxerIOWriterCallback::SeekMode mode) {
    switch (mode) {
        case MuxerIOWriterCallback::Begin:
            return SEEK_SET;
        case MuxerIOWriterCallback::Current:
            return SEEK_CUR;
        case MuxerIOWriterCallback::End:
            return SEEK_END;
        default:
            assert(0);
            return -1;
    }
}

void MuxerIOWriterCallbackDefault::seek(long long offset, SeekMode mode) {
    assert(this->file && "File must be opened");
    int res = fseek((FILE*)file, offset, convertMode(mode));
    assert(res == 0);
};

void MuxerIOWriterCallbackDefault::close() {
    assert(this->file && "File must be opened");
    fclose((FILE*)this->file);
    this->file = NULL;
};

