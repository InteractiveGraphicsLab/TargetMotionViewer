#include "VideoManager.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "../3rdparty/videoloader.h"
#include "../3rdparty/timageloader.h"

#pragma unmanaged
#pragma warning(disable:4996)


std::vector<EVec3f> t_SplistLine(const std::string &line)
{
  std::vector<float> t;
  std::stringstream strstream(line);
  std::string word;

  while( std::getline(strstream, word, ' ') ) 
    t.push_back( (float) atof(word.c_str()) );

  std::vector<EVec3f> results;
  for( int i = 0; i + 2 < t.size(); i += 2)
    results.push_back( EVec3f(t[1+i], t[1+i+1], 0));

  return results;
}



VideoPoseData::VideoPoseData(
    const std::string &fname_video, 
    const std::string &fname_pose)
{
  //1. open video stream
  m_video.openFile( fname_video.c_str() );
  if (!m_video.isLoadingSucess())
  {
    m_loading_success = false;
    std::cout << "!!!!!!!fail to load VIDEO!!!!!!!!!!\n";
    return;
  }

  //2. load pose data
  FILE *fp = fopen(fname_pose.c_str(), "r");
  
  char buf[20000];
  fgets(buf, 20000, fp); //1行目読み捨て

  while ( fgets(buf, 20000, fp) != NULL )
    m_landmarks.push_back(t_SplistLine(std::string(buf)) );


  //3. データの確認 (フレーム数:FrameNum, ランドマーク点数:LM_NUM) 
  for (int i = 0; i < m_landmarks.size(); ++i)
  {
    if(m_landmarks[i].size() != LM_NUM)
    {
      m_landmarks[i].resize(LM_NUM);
      std::cout << "Starange frame exits: ランドマーク点数にエラーあり. (0,0,0)を挿入.\n";
    }
  }
  
  if ( m_video.getFrameNum() != m_landmarks.size() )
  {
    std::cout << "動画と姿勢のフレーム数が違うため自動で姿勢の追加・削除をし調整します\n";
    m_landmarks.resize(m_video.getFrameNum(), std::vector<EVec3f>(LM_NUM));
  }
  m_loading_success = true;
}



VideoManager::VideoManager()
{
  m_focusedVideoIdx = -1;
}


VideoManager::~VideoManager()
{
  for ( int i = 0; i < (int)m_videos.size(); ++i ) delete m_videos[i];
  m_videos.clear();
}


bool VideoManager::LoadVideoAndPose(
    const std::string &fname_video,
    const std::string &fname_pose)
{
  VideoPoseData* p = new VideoPoseData(fname_video, fname_pose);

  if ( !p->m_loading_success ) 
  {
    delete p;
    std::cout << "!!!!!!!!!! fail to open the files !!!!!!!!! \n";
    return false;
  }

  m_videos.push_back(p);
  m_focusedVideoIdx = (int)m_videos.size()-1;
  return true;
}


//-----------------------------------------------------
// FocusVideoInterface
//-----------------------------------------------------
int VideoManager::FocusVideo_GetNumFrame()
{
  if ( m_focusedVideoIdx < 0 || m_videos.size() <= m_focusedVideoIdx ) return -1;
  return m_videos[m_focusedVideoIdx]->m_video.getFrameNum(); 
}

int VideoManager::FocusVideo_GetWidth   ()
{ 
  if ( m_focusedVideoIdx < 0 || m_videos.size() <= m_focusedVideoIdx ) return -1;
  return m_videos[m_focusedVideoIdx]->m_video.getWidth(); 
}

int VideoManager::FocusVideo_GetHeight  ()
{
  if ( m_focusedVideoIdx < 0 || m_videos.size() <= m_focusedVideoIdx ) return -1;
  return m_videos[m_focusedVideoIdx]->m_video.getHeight  (); 
}

float VideoManager::FocusVideo_GetFPS()
{
  if (m_focusedVideoIdx < 0 || m_videos.size() <= m_focusedVideoIdx) return -1;
  return m_videos[m_focusedVideoIdx]->m_video.getFPS();
}


bool VideoManager::FocusVideo_GetFrame(const int frame_idx, byte* bgr)
{
  if ( m_focusedVideoIdx < 0 || m_videos.size() <= m_focusedVideoIdx ) return false;

  if ( frame_idx < 0 || m_videos[m_focusedVideoIdx]->m_video.getFrameNum() <= frame_idx){
    return false;
  }

  m_videos[m_focusedVideoIdx]->m_video.GetFrameBGR(frame_idx, bgr);
  return true;
}

std::vector<std::vector<EVec3f>> VideoManager::FocusVideo_GetPoseSequence()
{
  if ( m_focusedVideoIdx < 0 || m_videos.size() <= m_focusedVideoIdx ) 
    return std::vector<std::vector<EVec3f>>();
  
  return m_videos[m_focusedVideoIdx]->m_landmarks;
}



std::vector<EVec3f> VideoManager::FocusVideo_GetLandmarks(const int idx)
{
  if ( m_focusedVideoIdx < 0 || m_videos.size() <= m_focusedVideoIdx ) 
    return std::vector<EVec3f>(LM_NUM, EVec3f(0,0,0));

  if (idx < 0 || m_videos[m_focusedVideoIdx]->m_landmarks.size() -1 <= idx)
    return std::vector<EVec3f>(LM_NUM, EVec3f(0, 0, 0));

  return m_videos[m_focusedVideoIdx]->m_landmarks[idx];
}



void VideoManager::ForcusVideo_SmoothLnadmarks_Gauss()
{
  if ( m_focusedVideoIdx < 0 || m_videos.size() <= m_focusedVideoIdx ) return;
  
  VideoPoseData* vpd = m_videos[m_focusedVideoIdx];
  if ( vpd->m_landmarks.size() == 0 ) return;
  
  const std::vector<std::vector<EVec3f>> &points = vpd->m_landmarks;
  const int frameN    = (int) points.size();
  const int keyPointN = (int) points.front().size();

  std::vector<std::vector<EVec3f>> newPoints = vpd->m_landmarks;
  
  for( int i = 1; i < frameN - 1; ++i)
  {
    for( int j = 0; j < keyPointN; ++j)
    {
      float x = 0.25f * points[i-1][j][0] + 0.5f * points[i][j][0] + 0.25f * points[i+1][j][0];
      float y = 0.25f * points[i-1][j][1] + 0.5f * points[i][j][1] + 0.25f * points[i+1][j][1];
      newPoints[i][j][0] = x;
      newPoints[i][j][1] = y;
    }
  }
  vpd->m_landmarks = newPoints;
}


void VideoManager::ForcusVideo_SmoothLandmarks_Median(int radius)
{
  if ( m_focusedVideoIdx < 0 || m_videos.size() <= m_focusedVideoIdx ) return;
  
  VideoPoseData* vpd = m_videos[m_focusedVideoIdx];
  if ( vpd->m_landmarks.size() == 0 ) return;
  

  const std::vector<std::vector<EVec3f>>& points = vpd->m_landmarks;
  const int frameN    = (int) points.size();
  const int keyPointN = (int) points.front().size();
  
  std::vector<std::vector<EVec3f>> newPoints = vpd->m_landmarks;
  
  for( int i = 0; i < frameN; ++i)
  {
    int sI = std::max(0       , i - radius);
    int eI = std::min(frameN-1, i + radius);

    for (int j = 0; j < keyPointN; ++j)
    {
      std::vector<float> xs, ys;
      for (int k = sI; k <= eI; ++k)
      {
        xs.push_back( points[k][j][0]);
        ys.push_back( points[k][j][1]);
      }      
      std::sort(xs.begin(), xs.end());
      std::sort(ys.begin(), ys.end());
      newPoints[i][j][0] = xs[xs.size() / 2];
      newPoints[i][j][1] = ys[ys.size() / 2];
    }
  }

  vpd->m_landmarks = newPoints;
}


//-----------------------------------------------------------------//
//export clip info ------------------------------------------------//
//-----------------------------------------------------------------//

//clips: EVec3i : (video_idx, start_frame, num_frame)
void VideoManager::ExportClips_AsTheyAre(
    std::string dirpath,
    std::vector<EVec3i> clips)
{
  for ( int ci = 0; ci < clips.size(); ++ci )
  {
    const int video_idx  = clips[ci][0]; 
    const int clip_start = clips[ci][1]; 
    const int clip_len   = clips[ci][2]; 

    VideoPoseData* vpd = m_videos[video_idx];
    const int N = vpd->m_video.getFrameNum();
    const int W = vpd->m_video.getWidth ();
    const int H = vpd->m_video.getHeight();
    std::cout << "size " << W << " " << H << " " << N << "\n";
    
    AVFrame *frame1 = vpd->m_video.getAVFrame(1);

    char fname[2000]; 
    sprintf(fname, "%s/clip_v%d_s%d_n%d.mp4", dirpath.c_str(), video_idx, clip_start, clip_len);
    
    VideoWriterFfmpeg video_writer;
    video_writer.StartEncoding( fname, frame1, vpd->m_video.getTimeBase()); 

    const int clip_end = std::min( N, clip_start + clip_len);
    for (int i = clip_start; i < clip_end; ++i) 
    {
      AVFrame *frame = vpd->m_video.getAVFrame(i);
      video_writer.AddFrame( frame );
      av_frame_free( &frame );
    }
    
    video_writer.FinishEncoding();
    av_frame_free( &frame1 );
  }
}




// c1  c_len = 10, c_start = 0, c_align = 4, c_offset = 0 (cliplen_pre-4)
// c2  c_len = 12, c_start = 0, c_align = 3, c_offset = 1 (cliplen_pre-3)
// c3  c_len = 10, c_start = 0, c_align = 1, c_offset = 3 (cliplen_pre-1)
//            |
//    0 1 2 3 4 5 6 7 8 9
//      0 1 2 3 4 5 6 7 8 9 10 11 
//          0 1 2 3 4 5 6 7  8  9
//            |
//   cliplen_pre = 4,  cliplen_post = 9,  clipLen = 13
//

//clips EVec3f: (video_idx, start_frame, num_frame)
void VideoManager::ExportClips_Superimpose( 
    std::string         dirpath  , 
    std::vector<EVec3i> clips    , 
    std::vector<int>    alignidxs)
{
  //get video size (clipW, clipH, clipLen)
  int clipW = 0, clipH = 0;
  int clipLen_pre = 0;
  int clipLen_post = 0;

  for ( int ci = 0; ci < clips.size(); ++ci )
  {
    const int c_vi    = clips[ci][0]; 
    const int c_start = clips[ci][1];
    const int c_len   = clips[ci][2];

    alignidxs[ci] = (c_start <= alignidxs[ci] && alignidxs[ci] < c_start + c_len) ? alignidxs[ci] : c_start;
    const int c_align = alignidxs[ci];

    clipW        = std::max(clipW, m_videos[c_vi]->m_video.getWidth());
    clipH        = std::max(clipH, m_videos[c_vi]->m_video.getHeight());
    clipLen_pre  = std::max(clipLen_pre,  c_align           - c_start);
    clipLen_post = std::max(clipLen_post, (c_start + c_len) - c_align);
  }

  const int clipLen = clipLen_pre + clipLen_post;

  if (clipW == 0 || clipH == 0 || clipLen == 0) {
    std::cout << "strange input!!!!!!!!!!!!!\n ERROR\n";
    return;
  }

  //super impose video 
  std::vector<float*> rgb_seq(clipLen, 0);
  for (int i = 0; i < clipLen; ++i)
  {
    rgb_seq[i] = new float[clipW * clipH * 3];
    memset(rgb_seq[i], 0, sizeof(float) * clipW * clipH * 3);
  }
  
  const int num_clip = (int)clips.size();

  for ( int ci = 0; ci < num_clip; ++ci )
  {
    std::cout << "......... " << ci << "\n";
    const int c_vi    = clips[ci][0];
    const int c_start = clips[ci][1];
    const int c_len   = clips[ci][2];
    const int c_align = alignidxs[ci];
    const int c_ofst  = clipLen_pre - (c_align - c_start);
    std::cout << c_vi    << "\n";
    std::cout << c_start << "\n";
    std::cout << c_len   << "\n";
    std::cout << c_align << "\n";
    std::cout << c_ofst  << "\n";

    VideoManager::GetInst()->SetFocusedVideoIdx(c_vi);
    int N = VideoManager::GetInst()->FocusVideo_GetNumFrame(); 
    int W = VideoManager::GetInst()->FocusVideo_GetWidth   ();
    int H = VideoManager::GetInst()->FocusVideo_GetHeight  ();

    byte *tmpbgr = new byte[W*H*3];

    const int clip_end = std::min( N, c_start + c_len);
    for (int i = 0; i < c_len; ++i)
    {
      if ( c_start + i >= N) break;
      if ( !VideoManager::GetInst()->FocusVideo_GetFrame(c_start+i, tmpbgr) ) continue;

      for ( int y = 0; y < H; ++y )
      {
        for ( int x = 0; x < W; ++x )
        {
          int idx1 = 3 * (x + y * clipW);
          int idx2 = 3 * (x + y * W    );
          rgb_seq[i + c_ofst][idx1+0] += tmpbgr[idx2+0] / (float)num_clip;
          rgb_seq[i + c_ofst][idx1+1] += tmpbgr[idx2+1] / (float)num_clip;
          rgb_seq[i + c_ofst][idx1+2] += tmpbgr[idx2+2] / (float)num_clip;
        }
      }
    }
    std::cout << "......... " << "DONE \n";
    delete[] tmpbgr;
  }

  //export rgb_sequence as video!
  std::cout << "Export Video \n";

  const std::string fname = dirpath + "/superimpose_clip.mp4";
  VideoWriterFfmpeg video_writer;
  AVFrame *frame = m_videos.front()->m_video.getAVFrame( 1 );
  video_writer.StartEncoding(fname.c_str(), frame, m_videos.front()->m_video.getTimeBase());

  SwsContext* ctxYuvToBgr = sws_getContext(clipW, clipH, AV_PIX_FMT_YUV420P,
                                           clipW, clipH, AV_PIX_FMT_BGR24,
                                           SWS_SPLINE, NULL, NULL, NULL);
  SwsContext* ctxBgrToYuv = sws_getContext(clipW, clipH, AV_PIX_FMT_BGR24,
                                           clipW, clipH, AV_PIX_FMT_YUV420P,
                                           SWS_SPLINE, NULL, NULL, NULL);
  AVFrame* tmpFrame = av_frame_alloc();
  byte* tmpBuf = (byte*)av_malloc(avpicture_get_size(AV_PIX_FMT_BGR24, clipW, clipH));
  avpicture_fill((AVPicture*)tmpFrame, tmpBuf, AV_PIX_FMT_BGR24, clipW, clipH);
  sws_scale(ctxYuvToBgr, frame->data, frame->linesize, 0, clipH, tmpFrame->data, tmpFrame->linesize);

  for ( int i = 0; i < clipLen ; ++i)
  {
    // rgb_seq[i] --> tmpFrame --> frame --> video_writer
    for (int j = 0;j < clipW * clipH * 3; ++j) 
      tmpFrame->data[0][j] = (byte)rgb_seq[i][j];
    sws_scale(ctxBgrToYuv, tmpFrame->data, tmpFrame->linesize, 0, clipH, frame->data, frame->linesize); 
    video_writer.AddFrame( frame );
  }

  video_writer.FinishEncoding();

  av_frame_free(&tmpFrame);
  av_free(tmpBuf);
  av_frame_free( &frame );
  sws_freeContext(ctxYuvToBgr);
  sws_freeContext(ctxBgrToYuv);
  for ( int i = 0; i < clipLen; ++i ) delete[] rgb_seq[i];
}



void VideoManager::ExportClips_PoseInfo( 
    std::string dirpath,
    std::vector<EVec3i> clips)
{
  for ( int ci = 0; ci < clips.size(); ++ci )
  {
    const int video_idx  = clips[ci][0]; 
    const int clip_start = clips[ci][1]; 
    const int clip_len   = clips[ci][2]; 

    VideoPoseData* vpd = m_videos[video_idx];
    const int N = vpd->m_video.getFrameNum();
    const int clip_end = std::min( N, clip_start+clip_len);


    char fname[2000]; 
    sprintf(fname, "%s/clip_v%d_s%d_n%d.csv", dirpath.c_str(), video_idx, clip_start, clip_len);
  
    std::ofstream out_fstream(fname);
    
    //1行目 
    out_fstream << "NOSE_x, NOSE_y,"; 
    out_fstream << "LEFT_EYE_INNER_x, LEFT_EYE_INNER_y, LEFT_EYE_x, LEFT_EYE_y, LEFT_EYE_OUTER_x, LEFT_EYE_OUTER_y, ";
    out_fstream << "RIGHT_EYE_INNER_x, RIGHT_EYE_INNER_y, RIGHT_EYE_x, RIGHT_EYE_y, RIGHT_EYE_OUTER_x, RIGHT_EYE_OUTER_y, ";
    out_fstream << "LEFT_EAR_x, LEFT_EAR_y, RIGHT_EAR_x, RIGHT_EAR_y, MOUTH_LEFT_x, MOUTH_LEFT_y, MOUTH_RIGHT_x, MOUTH_RIGHT_y, ";
    out_fstream << "LEFT_SHOULDER_x, LEFT_SHOULDER_y, RIGHT_SHOULDER_x, RIGHT_SHOULDER_y, LEFT_ELBOW_x, LEFT_ELBOW_y, RIGHT_ELBOW_x, RIGHT_ELBOW_y, ";
    out_fstream << "LEFT_WRIST_x, LEFT_WRIST_y, RIGHT_WRIST_x, RIGHT_WRIST_y, LEFT_PINKY_x, LEFT_PINKY_y, RIGHT_PINKY_x, RIGHT_PINKY_y, ";
    out_fstream << "LEFT_INDEX_x, LEFT_INDEX_y, RIGHT_INDEX_x, RIGHT_INDEX_y, LEFT_THUMB_x, LEFT_THUMB_y, RIGHT_THUMB_x, RIGHT_THUMB_y, ";
    out_fstream << "LEFT_HIP_x, LEFT_HIP_y, RIGHT_HIP_x, RIGHT_HIP_y, LEFT_KNEE_x, LEFT_KNEE_y, RIGHT_KNEE_x, RIGHT_KNEE_y, ";
    out_fstream << "LEFT_ANKLE_x, LEFT_ANKLE_y, RIGHT_ANKLE_x, RIGHT_ANKLE_y, LEFT_HEEL_x, LEFT_HEEL_y, RIGHT_HEEL_x, RIGHT_HEEL_y, ";
    out_fstream << "LEFT_FOOT_INDEX_x, LEFT_FOOT_INDEX_y, RIGHT_FOOT_INDEX_x, RIGHT_FOOT_INDEX_y\n";

    for (int i = clip_start; i < clip_end; ++i) 
    {
      const std::vector<EVec3f> &p = vpd->m_landmarks[i];
      for( int j = 0; j < (int) p.size(); ++j)
        out_fstream << p[j][0] << "," << p[j][1] << ",";

      out_fstream << "\n";
    }
    out_fstream.close();
  }
}


//引数は vector<videoid / start_idx / clip_length >

void VideoManager::ExportClips_PoseInfo_1stfrm(
    std::string dirpath, 
    std::vector<EVec3i> clips)
{
  char fname[2000];
  sprintf(fname, "%s/thumbnail_poses.csv", dirpath.c_str());

  std::ofstream out_fstream(fname);

  //1行目 
  out_fstream << "NOSE_x, NOSE_y,";
  out_fstream << "LEFT_EYE_INNER_x, LEFT_EYE_INNER_y, LEFT_EYE_x, LEFT_EYE_y, LEFT_EYE_OUTER_x, LEFT_EYE_OUTER_y, ";
  out_fstream << "RIGHT_EYE_INNER_x, RIGHT_EYE_INNER_y, RIGHT_EYE_x, RIGHT_EYE_y, RIGHT_EYE_OUTER_x, RIGHT_EYE_OUTER_y, ";
  out_fstream << "LEFT_EAR_x, LEFT_EAR_y, RIGHT_EAR_x, RIGHT_EAR_y, MOUTH_LEFT_x, MOUTH_LEFT_y, MOUTH_RIGHT_x, MOUTH_RIGHT_y, ";
  out_fstream << "LEFT_SHOULDER_x, LEFT_SHOULDER_y, RIGHT_SHOULDER_x, RIGHT_SHOULDER_y, LEFT_ELBOW_x, LEFT_ELBOW_y, RIGHT_ELBOW_x, RIGHT_ELBOW_y, ";
  out_fstream << "LEFT_WRIST_x, LEFT_WRIST_y, RIGHT_WRIST_x, RIGHT_WRIST_y, LEFT_PINKY_x, LEFT_PINKY_y, RIGHT_PINKY_x, RIGHT_PINKY_y, ";
  out_fstream << "LEFT_INDEX_x, LEFT_INDEX_y, RIGHT_INDEX_x, RIGHT_INDEX_y, LEFT_THUMB_x, LEFT_THUMB_y, RIGHT_THUMB_x, RIGHT_THUMB_y, ";
  out_fstream << "LEFT_HIP_x, LEFT_HIP_y, RIGHT_HIP_x, RIGHT_HIP_y, LEFT_KNEE_x, LEFT_KNEE_y, RIGHT_KNEE_x, RIGHT_KNEE_y, ";
  out_fstream << "LEFT_ANKLE_x, LEFT_ANKLE_y, RIGHT_ANKLE_x, RIGHT_ANKLE_y, LEFT_HEEL_x, LEFT_HEEL_y, RIGHT_HEEL_x, RIGHT_HEEL_y, ";
  out_fstream << "LEFT_FOOT_INDEX_x, LEFT_FOOT_INDEX_y, RIGHT_FOOT_INDEX_x, RIGHT_FOOT_INDEX_y\n";

  for (int ci = 0; ci < clips.size(); ++ci)
  {
    const int video_idx  = clips[ci][0];
    const int clip_start = clips[ci][1];

    VideoPoseData* vpd = m_videos[video_idx];
    const std::vector<EVec3f> &p = vpd->m_landmarks[clip_start];
    for (int j = 0; j < (int)p.size(); ++j) 
    {
      out_fstream << p[j][0] << "," << p[j][1] << ",";
    }
    out_fstream << "\n";
  }
  out_fstream.close();
}

#pragma warning(default:4996)

#pragma managed
