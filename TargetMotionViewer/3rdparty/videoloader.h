#pragma once

#pragma unmanaged

#pragma warning(disable:4996)
#pragma warning(disable:4819)

#include "tmath.h"
#include <vector>
#include <string>
#include <iostream>
#include <deque>


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/avutil.h"
#include "libavutil/pixfmt.h"

}
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "swscale.lib")

#define INBUF_SIZE 4096



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*
inline void t_testLoading(const char* fname, int &width, int &height, std::vector<byte*> &imgs)
{  
  std::cout << "t_testLoading\n";
  av_register_all();  // open file
  AVFormatContext* format_context = nullptr;
  if (avformat_open_input(&format_context, fname, nullptr, nullptr) != 0) {
    printf("avformat_open_input failed\n");
  }  // get stream info
  if (avformat_find_stream_info(format_context, nullptr) < 0) {
    printf("avformat_find_stream_info failed\n");
  }  // find video stream
  int       stream_idx = -1;
  AVStream* video_stream = nullptr;
  for (int i = 0; i < (int)format_context->nb_streams; ++i) {
    if (format_context->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
      video_stream = format_context->streams[i];
      stream_idx = i;
      break;
    }
  }
  if (video_stream == nullptr) {
    printf("No video stream ...\n");
  }  // find decoder
  AVCodec* codec = avcodec_find_decoder(video_stream->codecpar->codec_id);
  if (codec == nullptr) {
    printf("No supported decoder ...\n");
  }  // alloc codec context
  AVCodecContext* codec_context = avcodec_alloc_context3(codec);
  if (codec_context == nullptr) {
    printf("avcodec_alloc_context3 failed\n");
  }  // open codec
  if (avcodec_parameters_to_context(codec_context, video_stream->codecpar) < 0) {
    printf("avcodec_parameters_to_context failed\n");
  }
  if (avcodec_open2(codec_context, codec, nullptr) != 0) {
    printf("avcodec_open2 failed\n");
  }  std::cout << "size " << codec_context->width
            << " "     << codec_context->height
            << " "     << video_stream->nb_frames
            << " "     << video_stream->duration << "\n";  const int W = codec_context->width;
  const int H = codec_context->height;
  const int frame_n =(int) video_stream->nb_frames ;
  const int dure    =(int) video_stream->duration ;
  width = W;
  height = H;  int trgttime = (int) (200 / (double) frame_n * dure);
  int ret = av_seek_frame( format_context, stream_idx, trgttime, AVSEEK_FLAG_ANY );  int counter = 0;  // decode frames
  AVFrame* frame = av_frame_alloc();
  AVFrame *pFrameBGR = av_frame_alloc();
  byte    *bufferBGR = (byte *) av_malloc( avpicture_get_size( AV_PIX_FMT_BGR24, W, H) );
  avpicture_fill((AVPicture*)pFrameBGR, bufferBGR, AV_PIX_FMT_BGR24, W, H );  SwsContext *pConvertCtx =
      sws_getContext( W, H, codec_context->pix_fmt, W, H, AV_PIX_FMT_BGR24, SWS_SPLINE, NULL, NULL, NULL);  AVPacket packet = AVPacket();
  while (av_read_frame(format_context, &packet) == 0)
  {
    if (packet.stream_index == video_stream->index)
    {
      if (avcodec_send_packet(codec_context, &packet) != 0)
      {
        printf("avcodec_send_packet failed\n");
      }
      while (avcodec_receive_frame(codec_context, frame) == 0)
      {        sws_scale( pConvertCtx, (const byte* const*) frame->data, frame->linesize, 0,
          codec_context->height, pFrameBGR->data, pFrameBGR->linesize);        byte *bgr = new byte[W*H*3];
        memcpy(bgr, pFrameBGR->data[0], W * H * sizeof(byte) * 3);
        imgs.push_back( bgr );
        std::cout << " " << counter << " ";
        ++counter;
      }
    }
    av_packet_unref(&packet);
  }  // flush decoder
  if (avcodec_send_packet(codec_context, nullptr) != 0) {
    printf("avcodec_send_packet failed");
  }
  while (avcodec_receive_frame(codec_context, frame) == 0) {
    std::cout << " " << counter << " final flush ";
    ++counter;
  }  // clean up
  av_frame_free(&frame);
  av_frame_free(&pFrameBGR);
  avcodec_free_context(&codec_context);
  avformat_close_input(&format_context);  std::cout << "DONE\n";
}


*/





//参考 URL https://ffmpeg.zeranoe.com/forum/viewtopic.php?t=736
//av_register_all           : Initialize libavformat and register all the muxers (一度だけでOK?)
//avformat_open_input       : Open an input stream and read the header
//avformat_find_stream_info : Read packets of a media file to get stream information
//av_dump_format            : Print detailed information about the input or output format
//avcodec_find_decoder      : Find a registered decoder with a matching codec ID
//avcodec_open2             : Initialize the AVCodecContext to use the given AVCodec.
//av_frame_alloc            : Allocate an AVFrame and set its fields to default values
//av_seek_frame             : Seek to the keyframe at timestamp.
// pFrame->data[0,1,2] : それぞれがYUVに対応するっぽい

// This class is for loading mpeg movie 
//  1. set file name  by calling openFile(file name )
//  2. get frame (bgr) by calling getFrame(frame idx, bgr point)
//  3. close file stream (do nothing)

class VideoLoaderFfmpeg
{
private:
  bool m_bOpenSuccessed;
  int  m_W, m_H, m_num_frames, m_duration;
  int m_stream_idx;
  int m_prev_frame_idx;
  AVFormatContext* m_format_context;
  AVCodecContext*  m_codec_context;
  AVStream   *m_video_stream;
  AVCodec    *m_codec; 
	AVFrame    *m_frame   ;
  AVFrame    *m_frame_bgr;
  byte       *m_buffer_bgr;
  SwsContext *m_cvt_context;

  AVRational  m_timebase;



public: 
  VideoLoaderFfmpeg()
  {
    
    m_W =  m_H = 0;
    m_bOpenSuccessed = false;
    m_num_frames = m_duration = 0;
    m_stream_idx = -1;
    m_prev_frame_idx = -1;
    m_format_context = 0;
    m_codec_context  = 0;
    m_video_stream   = 0;
    m_codec       = 0; 
	  m_frame       = 0;
    m_frame_bgr   = 0;
    m_buffer_bgr  = 0;
    m_cvt_context = 0;
  }
  
  ~VideoLoaderFfmpeg(){
    clear();
  }

  void clear()
  {
    m_bOpenSuccessed = false;
		if( m_frame          != 0 ) av_frame_free  ( &m_frame        );
		if( m_frame_bgr      != 0 ) av_frame_free  ( &m_frame_bgr    );
		if( m_buffer_bgr     != 0 ) av_free        ( m_buffer_bgr    );
    if( m_cvt_context    != 0 ) sws_freeContext( m_cvt_context   );
	  if( m_codec_context  != 0 ) avcodec_close  ( m_codec_context );
		if( m_format_context != 0 ) avformat_close_input(&m_format_context);

    m_W =  m_H = 0;
    m_bOpenSuccessed = false;
    m_num_frames = m_duration = 0;
    m_stream_idx = -1;

    m_format_context = 0;
    m_codec_context  = 0;
    m_video_stream   = 0;
    m_codec       = 0; 
	  m_frame       = 0;
    m_frame_bgr   = 0;
    m_buffer_bgr  = 0;
    m_cvt_context = 0;
    m_prev_frame_idx = 0;
  }

  bool isLoadingSucess(){ return m_bOpenSuccessed; }
  AVRational getTimeBase () { return m_timebase;}
  int getWidth   () { return m_W; }
  int getHeight  () { return m_H; }
  int getFrameNum() { return m_num_frames; }
  float getFPS     () 
  {
    if ( !m_bOpenSuccessed ) return 0;
       
    return (float)m_format_context->streams[m_stream_idx]->avg_frame_rate.num / 
                  m_format_context->streams[m_stream_idx]->avg_frame_rate.den;
  }





  void openFile(const char* fname)
  {
    std::cout << "openFile " << fname << "\n";
    clear();

    // ffmpeg初期化
    av_register_all(); 
        
    if (avformat_open_input(&m_format_context, fname, nullptr, nullptr) != 0) 
    {
      std::cout << "error avformat_open_input \n";
      return;
    } 
 
    if ( avformat_find_stream_info(m_format_context, nullptr) < 0) 
    {
      std::cout << "error avformat_find_stream_info \n";
      return;
    }  

    // find video stream
    for (int i = 0; i < (int)m_format_context->nb_streams; ++i) 
    {
      if (m_format_context->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) 
      {
        m_video_stream = m_format_context->streams[i];
        m_stream_idx = i;
        break;
      }
    }

    if (m_video_stream == nullptr) 
    {
      std::cout << "error find video stream\n";
      return;
    }

    m_codec = avcodec_find_decoder( m_video_stream->codecpar->codec_id );
    if ( m_codec == nullptr) 
    {
      std::cout << "error avcodec_find_decoder\n";
      return;
    }  

    m_codec_context = avcodec_alloc_context3( m_codec );
    if ( m_codec_context == nullptr) 
    {
      std::cout << "error avcodec_alloc_context3\n";
      return;
    }  

    if ( avcodec_parameters_to_context(m_codec_context, m_video_stream->codecpar) < 0)
    {
      std::cout << "error avcodec_parameters_to_context\n";
      return;
    }

    if ( avcodec_open2( m_codec_context, m_codec, nullptr) != 0) 
    {
      std::cout << "error avcodec_open2\n";
      return;
    } 
    m_W = m_codec_context->width ;
    m_H = m_codec_context->height;
    m_num_frames   = (int) m_video_stream->nb_frames;
    m_duration = (int) m_video_stream->duration ;
    m_timebase = m_video_stream->time_base;

    std::cout << "sucess open video (" << m_W << ", " << m_H << ")\n";
    std::cout << "frame: " << m_num_frames << " " << m_duration << "\n";


	  m_frame     = av_frame_alloc(); 
    m_frame_bgr = av_frame_alloc();
    m_buffer_bgr  = (byte *) av_malloc( avpicture_get_size( AV_PIX_FMT_BGR24, m_W, m_H) );
    avpicture_fill((AVPicture*)m_frame_bgr, m_buffer_bgr , AV_PIX_FMT_BGR24, m_W, m_H );

    //5 YUV --> RGB 変換コンテキスト生成
    m_cvt_context = sws_getContext( m_W, m_H, m_codec_context->pix_fmt, 
                                    m_W, m_H, AV_PIX_FMT_BGR24, 
                                    SWS_SPLINE, NULL, NULL, NULL);
    m_bOpenSuccessed = true;
  }



  //現在、10フレーム以上遠いときはseekしているが、本来はkeyframe intervalを利用して計算すべき
  //rgb shoud be allocated [W*H*3]
  bool GetFrameBGR( int frame_idx, byte* bgr )
  {
    if( !m_bOpenSuccessed ) return false;

    int trgttime = (int) (frame_idx / (double) m_num_frames * m_duration); 

    //一度encodeしたframeを保持 --> m_prev_frame_idx
    //対象frameが m_prev_frame_idx より遠いとき or より手前の時 or 同じ時、  
    // --> trgttime に一番近い（手前の）キーフレームまでseekする 
    if (frame_idx > m_prev_frame_idx + 10 || frame_idx <= m_prev_frame_idx)
    {
      av_seek_frame(m_format_context, m_stream_idx, trgttime, AVSEEK_FLAG_BACKWARD);
    }
    m_prev_frame_idx = frame_idx;

	  AVPacket packet;
    //std::cout << "trgttime " << trgttime << " " << frame_idx << " " << m_stream_idx << "\n";

    while (av_read_frame( m_format_context, &packet) == 0)
    {
      if ( packet.stream_index == m_stream_idx )
      {
        if ( avcodec_send_packet( m_codec_context, &packet) != 0 )
          std::cout << "avcodec_send_packet failed\n";
        
        //packet.dts が decodeした timestamp．trgttimeまでdecodeする
        
        if ( avcodec_receive_frame( m_codec_context, m_frame) == 0 && packet.dts >= trgttime)
        {
          sws_scale( m_cvt_context, 
                    (const byte* const*) m_frame->data,  m_frame->linesize, 
                     0, m_codec_context->height, 
                     m_frame_bgr->data, m_frame_bgr->linesize);

          memcpy( bgr, m_frame_bgr->data[0], m_W * m_H * sizeof(byte) * 3);
          av_packet_unref(&packet);
          return true;
        }
      }
      av_packet_unref(&packet);
      //avcodec_flush_buffers(m_codec_context);
    }

    return false;
  }


  /*
  //rgb shoud be allocated [W*H*3]
  bool GetFrameBGR_old(int frame_idx, byte* bgr)
  {
    if (!m_bOpenSuccessed) return false;
    //std::cout <<  "GetFrameBGR\n";

    int trgttime = (int)(frame_idx / (double)m_num_frames * m_duration);

    if (frame_idx >= m_prev_frame_idx) {
      av_seek_frame(m_format_context, m_stream_idx, trgttime, AVSEEK_FLAG_ANY);
    }
    else
    {
      av_seek_frame(m_format_context, m_stream_idx, trgttime, AVSEEK_FLAG_BACKWARD);

    }
    m_prev_frame_idx = frame_idx;
    AVPacket packet;

    while (av_read_frame(m_format_context, &packet) == 0)
    {
      //packet.dts が decodeした time だと思われる
      if (packet.stream_index == m_stream_idx)
      {
        if (avcodec_send_packet(m_codec_context, &packet) != 0)
          std::cout << "avcodec_send_packet failed\n";

        if (avcodec_receive_frame(m_codec_context, m_frame) == 0)
        {
          sws_scale(m_cvt_context,
            (const byte* const*)m_frame->data, m_frame->linesize,
            0, m_codec_context->height,
            m_frame_bgr->data, m_frame_bgr->linesize);

          memcpy(bgr, m_frame_bgr->data[0], m_W * m_H * sizeof(byte) * 3);
          av_packet_unref(&packet);
          return true;
        }
      }
      av_packet_unref(&packet);
    }

    return false;
  }
  */




  //retrn AVFrame which should be av_frame_free()
  AVFrame *getAVFrame(int frame_idx)
  {
    if (!m_bOpenSuccessed) return false;
    int trgttime = (int)(frame_idx / (double)m_num_frames * m_duration);

    if (frame_idx > m_prev_frame_idx + 10 || frame_idx <= m_prev_frame_idx)
    {
      av_seek_frame(m_format_context, m_stream_idx, trgttime, AVSEEK_FLAG_BACKWARD);
    }
    m_prev_frame_idx = frame_idx;

   
    AVFrame *frame = av_frame_alloc();
    AVPacket packet;
    while ( av_read_frame( m_format_context, &packet) >= 0)
    {
      if ( packet.stream_index == m_stream_idx )
      {
        if ( avcodec_send_packet( m_codec_context, &packet) != 0 )
          std::cout << "avcodec_send_packet failed\n";

        if ( avcodec_receive_frame( m_codec_context, frame) == 0 && packet.dts >= trgttime)
        {
          std::cout << frame;
          av_free_packet(&packet);
          return frame;
        }
      }
    }
    std::cout << "getAVFrame error\n";
    return frame;
  }
};






// VideoWriterFfmpeg
// This class is for loading mpeg movie 
//  1. set file name  by calling openFile ( file name )
//  2. set frames (bgr) by calling setFrame( vector<bgr pointer> )
//  3. close file stream (do nothing)

class VideoWriterFfmpeg 
{
  AVIOContext*     m_io_context;
  AVFormatContext* m_format_context;
  AVCodec*         m_codec;
  AVCodecContext*  m_codec_context;
  AVStream*        m_stream;
  int m_frame_count;

public:
  VideoWriterFfmpeg() 
  {
    m_io_context     = 0;
    m_format_context = 0;
    m_codec          = 0;
    m_codec_context  = 0;
    m_stream         = 0;
    m_frame_count    = 0;
  }

  ~VideoWriterFfmpeg() {
  }

  //参考
  //http://proc-cpuinfo.fixstars.com/2017/09/ffmpeg-api-encode/

  bool StartEncoding( const char *fname, AVFrame *ref_frame, AVRational time_base)
  {

    if (avio_open(& m_io_context, fname, AVIO_FLAG_WRITE) < 0) 
    {
      std::cout << "error avio_open\n";
      return false;
    }

    if (avformat_alloc_output_context2( &m_format_context, nullptr, "mp4", nullptr) < 0) 
    {
      std::cout << "error avformat_alloc_output_context2\n";
      return false;
    }

    m_format_context->pb = m_io_context;
    m_codec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (m_codec == nullptr) 
    {
      std::cout << "encoder not found ...\n";
      return false;
    }

    m_codec_context = avcodec_alloc_context3(m_codec);
    if ( m_codec_context  == nullptr) 
    {
      std::cout << " error avcodec_alloc_context3\n";
      return false;
    }

    // set picture properties
    m_codec_context->pix_fmt         = (AVPixelFormat)ref_frame->format;
    m_codec_context->width           = ref_frame->width;
    m_codec_context->height          = ref_frame->height;
    m_codec_context->field_order     = AV_FIELD_PROGRESSIVE;
    m_codec_context->color_range     = ref_frame->color_range;
    m_codec_context->color_primaries = ref_frame->color_primaries;
    m_codec_context->color_trc       = ref_frame->color_trc;
    m_codec_context->colorspace      = ref_frame->colorspace;
    m_codec_context->chroma_sample_location = ref_frame->chroma_location;
    m_codec_context->sample_aspect_ratio = ref_frame->sample_aspect_ratio;

    std::cout << "encodding !!!!!!" << ref_frame->width << " " << ref_frame->height << "\n\n\n";    

    // set timebase
    m_codec_context->time_base = time_base;

    // generate global header when the format requires it
    if ( m_format_context->oformat->flags & AVFMT_GLOBALHEADER ) 
    {
      m_codec_context->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    }
    // make codec options
    AVDictionary* codec_options = nullptr;
    av_dict_set(&codec_options, "preset", "medium", 0);
    av_dict_set(&codec_options, "crf", "22", 0);
    av_dict_set(&codec_options, "profile", "high", 0);
    av_dict_set(&codec_options, "level", "4.0", 0);

    if (avcodec_open2( m_codec_context, m_codec_context->codec, &codec_options) != 0) 
    {
      std::cout << "avcodec_open2 failed\n";
    }

    m_stream = avformat_new_stream( m_format_context, m_codec);
    if ( m_stream == NULL) {
      printf("avformat_new_stream failed");
    }

    m_stream->sample_aspect_ratio = m_codec_context->sample_aspect_ratio;
    m_stream->time_base = m_codec_context->time_base;
    if (avcodec_parameters_from_context( m_stream->codecpar, m_codec_context) < 0) 
    {
      std::cout << "avcodec_parameters_from_context failed";
    }

    if ( avformat_write_header( m_format_context, nullptr) < 0) 
    {
      std::cout << "avformat_write_header failed\n";
    }
    return true;
  }

  //この関数はframeを av_frame_freeしないので注意
  void AddFrame(AVFrame *frame)
  {
    AVRational time_base = av_make_q(1000, 30000);

    frame->pts = av_rescale_q( m_frame_count++, time_base, m_codec_context->time_base);
    frame->key_frame = 0;

    if ( avcodec_send_frame( m_codec_context, frame) != 0) 
    {
      std::cout << "avcodec_send_frame failed";
    }
    
    AVPacket packet = AVPacket();
    while ( avcodec_receive_packet( m_codec_context, &packet) == 0) 
    {
      packet.stream_index = 0;
      av_packet_rescale_ts(&packet, m_codec_context->time_base, m_stream->time_base);
      if (av_interleaved_write_frame( m_format_context, &packet) != 0) 
      {
        std::cout << " error  av_interleaved_write_frame\n";
      }
    }
  }

  void FinishEncoding()
  {
    // flush encoder
    if ( avcodec_send_frame( m_codec_context, nullptr) != 0) 
    {
      std::cout << "avcodec_send_frame failed\n";
    }

    AVPacket packet = AVPacket();
    while ( avcodec_receive_packet( m_codec_context, &packet) == 0) 
    {
      packet.stream_index = 0;
      av_packet_rescale_ts(&packet, m_codec_context->time_base, m_stream->time_base);
      if ( av_interleaved_write_frame( m_format_context, &packet) != 0) 
      {
        std::cout << "av_interleaved_write_frame failed\n";
      }
    }

    if ( av_write_trailer( m_format_context) != 0) 
    {
      std::cout << "av_write_trailer failed\n";
    }

    avcodec_free_context ( &m_codec_context);
    avformat_free_context( m_format_context);
    avio_closep(&m_io_context);
  }

};

  
#pragma warning(default:4996)
#pragma warning(default:4819)


#pragma managed
