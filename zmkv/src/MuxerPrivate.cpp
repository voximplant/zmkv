//
// Created by Andrey Syvrachev on 23.07.15.
// asyvrachev@zingaya.com
// www.voximplant.com
//


#include "MuxerPrivate.h"
#include <ebml/EbmlHead.h>

using namespace libebml;
using namespace libmatroska;
using namespace ZMKV;

const auto cMaxSeekHeadSizeOctets = 3000;
const auto cMaxTracksSizeOctets = 300;
const unsigned long long cTimecodeScale = 1000000;

const auto cbWithDefault = true;


MuxerPrivate::MuxerPrivate(IOCallback &file) : file(file), max_ts(0), kaxDuration(NULL), renderedClustersSize(0) {

    InitFileHeader();

    this->segmentSize = this->segment.WriteHead(this->file, 5, cbWithDefault);

    // reserve some space for the Meta Seek written at the end
    this->dummySeekHead.SetSize(cMaxSeekHeadSizeOctets);
    this->dummySeekHead.Render(this->file);

    InitSegmentInfo();

    this->tracks = &GetChild<KaxTracks>(this->segment);

    // reserve space for track information written at the end
    this->dummyTracks.SetSize(cMaxTracksSizeOctets);
    this->dummyTracks.Render(this->file);

    this->cues.SetGlobalTimecodeScale(cTimecodeScale);

    CreateNewCluster(0);
}


MuxerPrivate::~MuxerPrivate() {
    CloseCurrentCluster();

    filepos_t cueSize = this->cues.Render(this->file, false);

    this->seekHead.IndexThis(this->cues, this->segment);

    uint64 TrackSize = 0;
    if (this->tracks->GetElementList().size() > 0){
        TrackSize = this->dummyTracks.ReplaceWith(*this->tracks, this->file);
        assert(TrackSize);
    }

    filepos_t seekHeadSize = dummySeekHead.ReplaceWith(this->seekHead, this->file);
    assert(seekHeadSize); // TODO: think about very big files!, must have workaround!

    UpdateDuration();


    if (this->segment.ForceSize(this->segmentSize
                                - this->segment.HeadSize()
                                + seekHeadSize
                                + TrackSize
                                + this->renderedClustersSize
                                + cueSize
                                + this->segmentInfoSize)) {
        this->segment.OverwriteHead(this->file);
    }

    file.close();
}

void MuxerPrivate::InitFileHeader() {
    EbmlHead FileHead;
//  EBML_SET(FileHead,EDocType,EbmlString,"webm");
//  EBML_SET(FileHead,EDocTypeVersion,EbmlUInteger,MATROSKA_VERSION);
//  EBML_SET(FileHead,EDocTypeReadVersion,EbmlUInteger,MATROSKA_VERSION);
    FileHead.Render(this->file, cbWithDefault);
}

void MuxerPrivate::InitSegmentInfo() {
    // update duration
    KaxInfo &segmentInfo = GetChild<KaxInfo>(this->segment);
    EBML_SET(segmentInfo, KaxTimecodeScale, EbmlUInteger, cTimecodeScale);

    this->kaxDuration = &GetChild<KaxDuration>(segmentInfo);
    *(static_cast<EbmlFloat *>(this->kaxDuration)) = 0;

    EBML_SET(segmentInfo, KaxMuxingApp, EbmlUnicodeString, L"Zingaya RTP MKV");
    EBML_SET(segmentInfo, KaxWritingApp, EbmlUnicodeString, L"Voximplant Media Server");

    this->segmentInfoSize = segmentInfo.Render(this->file);
}

void MuxerPrivate::CreateNewCluster(unsigned long long ts) {
//    printf("CreateNewCluster(ts = %llu)\n", ts);
    this->currentCluster.reset(new KaxCluster);

    this->currentCluster->SetParent(this->segment);
    this->currentCluster->InitTimecode(ts / cTimecodeScale, cTimecodeScale);
    this->currentCluster->SetGlobalTimecodeScale(cTimecodeScale);
    this->currentCluster->EnableChecksum();
    EBML_SET(*this->currentCluster, KaxClusterTimecode, EbmlUInteger, 0);
}

void MuxerPrivate::CloseCurrentCluster() {
//    printf("Render cluster timecode = %llu ...\n", this->currentCluster->GlobalTimecode());
    this->renderedClustersSize += this->currentCluster->Render(this->file, this->cues);
    this->currentCluster->ReleaseFrames();
    this->seekHead.IndexThis(*this->currentCluster, segment);
    this->currentCluster.reset(); // free Cluster object here
}

void MuxerPrivate::ProcessClusters(bool , bool , unsigned long long ts) {
    int64 delta = ts - this->max_ts;
    if (delta > 0) {
        this->max_ts = ts;
    }
    assert(this->currentCluster);
    int64 TimecodeDelay = (int64(ts) - int64(this->currentCluster->GlobalTimecode())) / cTimecodeScale;

    if (TimecodeDelay > 32767) {

        CloseCurrentCluster();
        CreateNewCluster(ts);
    }
}

void MuxerPrivate::UpdateDuration() {

    assert(this->kaxDuration);
    uint64 kaxDurationPos = this->kaxDuration->GetElementPosition();
    uint64 prev = this->file.getFilePointer();
    this->file.setFilePointer(kaxDurationPos, seek_beginning);

    float duration = this->max_ts / cTimecodeScale;
    *(static_cast<EbmlFloat *>(this->kaxDuration)) = duration;

    this->kaxDuration->Render(this->file, false, true);
    this->file.setFilePointer(prev, seek_beginning);
}
