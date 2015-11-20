# zmkv
Helper library for creating mkv files

# How to use

using namespace ZMKV;

1. Create file writer, you can use default or make custom writer class derived from: MuxerIOWriterCallback

    ```cpp
    MuxerIOWriterCallbackDefault muxerIOWriterCallbackDefault("./test.mkv");
    ```
2. Create muxer:
    ```cpp
    Muxer muxer(muxerIOWriterCallbackDefault);
    ```
3. Create tracks:
    
    ```cpp
    AudioCodecInfoACM audioCodecInfoACM(8000, 16, 1, ZMKV::wFormatTag::PCM);
    AudioTrack audioTrack(muxer, audioCodecInfoACM, 0, 12345678);

    VideoCodecInfoH264 videoCodecInfoH264(320,240);
    videoCodecInfoH264.AddPPS(sps,sizeof(sps));
    videoCodecInfoH264.AddPPS(pps,sizeof(pps));
      
    VideoTrack videoTrack(muxer,videoCodecInfoH264,1,87654321);
    ```
4. Fill tracks:
  
  ```cpp
  ...
  audioTrack.AddFrame(audioTimeStamp, 0, audio_buf, sizeof(audio_buf));
  videoTrack.AddFrame(videoTimeStamp, isKeyFrame, video_buf, sizeof(video_buf));
  ...
  ```
  
5. Thats all!
