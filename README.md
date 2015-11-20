# zmkv
Helper library for creating mkv files
Predefined A/V formats: VP8,H264,OPUS,PCM,PCMA,PCMU,G729,SPEEX
Can be easily extended for any new format

# How to use

1. Library located in namespace ZMKV:

    ```cpp
    using namespace ZMKV;
    ```
2. Create file writer, you can use default or make custom writer class derived from: MuxerIOWriterCallback

    ```cpp
    MuxerIOWriterCallbackDefault muxerIOWriterCallbackDefault("./test.mkv");
    ```
3. Create muxer:

    ```cpp
    Muxer muxer(muxerIOWriterCallbackDefault);
    ```
4. Create tracks:
    
    ```cpp
    AudioCodecInfoACM audioCodecInfoACM(8000, 16, 1, ZMKV::wFormatTag::PCM);
    AudioTrack audioTrack(muxer, audioCodecInfoACM, 0, 12345678);

    VideoCodecInfoH264 videoCodecInfoH264(320,240);
    videoCodecInfoH264.AddPPS(sps,sizeof(sps));
    videoCodecInfoH264.AddPPS(pps,sizeof(pps));
      
    VideoTrack videoTrack(muxer,videoCodecInfoH264,1,87654321);
    ```
5. Fill tracks:
  
  ```cpp
  ...
  audioTrack.AddFrame(audioTimeStamp, 0, audio_buf, sizeof(audio_buf));
  videoTrack.AddFrame(videoTimeStamp, isKeyFrame, video_buf, sizeof(video_buf));
  ...
  ```
  
6. Thats all!

# How to build on Ubuntu linux

```bash
apt-get update
apt-get install git cmake gcc g++

apt-get install libmatroska-dev

mkdir work_dir
cd work_dir
git clone https://github.com/voximplant/zmkv.git
mkdir build
cd build
cmake ../zmkv
make -j8

```

