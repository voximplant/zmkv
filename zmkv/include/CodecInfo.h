//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#ifndef CODEC_INFO__H
#define CODEC_INFO__H

#include <vector>

namespace ZMKV {
    class CodecInfo {
    public:
        void *CodecPrivate(unsigned int &size) const;
        virtual ~CodecInfo(){};
        virtual const char *CodecID() const = 0;

    protected:
        std::vector<unsigned char> codecPrivateData;
    };
}

#endif
