//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#include <CodecInfo.h>
#include <assert.h>

using namespace ZMKV;

void *CodecInfo::CodecPrivate(unsigned int &size) const {
    size = (unsigned int) this->codecPrivateData.size();
    return (void*)this->codecPrivateData.data();
}
