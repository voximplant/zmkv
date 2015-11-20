//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//

#include <assert.h>
#include <VideoCodecInfoH264.h>

#ifdef _WIN32
	#include <winsock2.h>  // for htonl/htons
#else
	#include <arpa/inet.h> // for htonl/htons
#endif

using namespace ZMKV;

VideoCodecInfoH264::VideoCodecInfoH264(unsigned long width, unsigned long height) : VideoCodecInfo(width,height) {

}

const char *VideoCodecInfoH264::CodecID() const{
    return "V_MPEG4/ISO/AVC";
}

void VideoCodecInfoH264::AddSPS(const unsigned char *data, unsigned long size) {
    if (this->sps.size() == 0){
        this->sps.insert(this->sps.begin(),data,data + size);
        tryToMakeCodecPrivate();
    }
}

void VideoCodecInfoH264::AddPPS(const unsigned char *data, unsigned long size) {
    if (this->pps.size() == 0){
        this->pps.insert(this->pps.begin(),data,data + size);
        tryToMakeCodecPrivate();
    }
}

void VideoCodecInfoH264::tryToMakeCodecPrivate(){

    if (!Completed()){
        return;
    }

    // SPS
    const unsigned char video_private[]={1,
                                         this->sps[1],   // profile_level
                                         0,         // reserved
                                         this->sps[3],
                                         3,         // sizeof NALU len - 1
                                         1};        // NUMBER of SPS-s
    this->codecPrivateData.insert(this->codecPrivateData.end(),video_private,video_private + sizeof(video_private));

    unsigned short sz = htons(this->sps.size());
    this->codecPrivateData.insert(this->codecPrivateData.end(),(const unsigned char*)&sz,((const unsigned char*)&sz) + sizeof(sz));
    this->codecPrivateData.insert(this->codecPrivateData.end(),this->sps.data(),this->sps.data() + this->sps.size());

    // PPS
    this->codecPrivateData.push_back(1); // number of PPS
    sz = htons(this->pps.size());
    this->codecPrivateData.insert(this->codecPrivateData.end(),(const unsigned char*)&sz,((const unsigned char*)&sz) + sizeof(sz));
    this->codecPrivateData.insert(this->codecPrivateData.end(),this->pps.data(),this->pps.data() + this->pps.size());
}

bool VideoCodecInfoH264::Completed(){
    return this->sps.size() > 0 && this->pps.size() > 0;
}
