#pragma once

#include "../3rdparty/tmath.h"
#include "../3rdparty/videoloader.h"
#include <vector>

#pragma unmanaged

// Landmark for media pipe
//  0. NOSE,  
//  1. LEFT_EYE_INNER   2.  LEFT_EYE       3. LEFT_EYE_OUTER,  4. RIGHT_EYE_INNER   5. RIGHT_EYE  6. RIGHT_EYE_OUTER 
//  7, LEFT_EAR         8. RIGHT_EAR,      9. MOUTH_LEFT      10. MOUTH_RIGHT 
// 11. LEFT_SHOULDER   12. RIGHT_SHOULDER 13. LEFT_ELBOW      14. RIGHT_ELBOW 
// 15. LEFT_WRIST      16. RIGHT_WRIST    17. LEFT_PINKY      18. RIGHT_PINKY 
// 19. LEFT_INDEX      20. RIGHT_INDEX    21. LEFT_THUMB      22. RIGHT_THUMB 
// 23. LEFT_HIP        24. RIGHT_HIP      25. LEFT_KNEE       26. RIGHT_KNEE 
// 27. LEFT_ANKLE      28. RIGHT_ANKLE    29. LEFT_HEEL       30. RIGHT_HEEL 
// 31. LEFT_FOOT_INDEX 32. RIGHT_FOOT_INDEX 

#define LM_NUM 33
typedef enum {
  LM_NOSE = 0,
  LM_L_EYEI =  1, LM_L_EYE  =  2, LM_L_EYEO =  3,
  LM_R_EYEI =  4, LM_R_EYE  =  5, LM_R_EYEO =  6,
  LM_L_EAR  =  7, LM_R_EAR  =  8, LM_L_MOUT =  9, LM_R_MOUT = 10,
  LM_L_SHOR = 11, LM_R_SHOR = 12, LM_L_ELBW = 13, LM_R_ELBW = 14, 
  LM_L_WRST = 15, LM_R_WRST = 16, 
  LM_L_PNKY = 17, LM_R_PNKY = 18, LM_L_INDX = 19, LM_R_INDX = 20, LM_L_THMB =21, LM_R_THMB =22,
  LM_L_HIP  = 23, LM_R_HIP  = 24, LM_L_KNEE = 25, LM_R_KNEE = 26,
  LM_L_ANKL = 27, LM_R_ANKL = 28, LM_L_HEEL = 29, LM_R_HEEL = 30,
  LM_L_FIDX = 31, LM_R_FIDX = 32 
} LANRMARKS;


inline bool isLandmarkForDiff(int lm_idx)
{
  if(lm_idx == LM_L_EYEI || lm_idx == LM_R_EYEI || lm_idx == LM_L_EYEO || lm_idx == LM_R_EYEO ||
    lm_idx == LM_L_MOUT || lm_idx == LM_R_MOUT ||
    lm_idx == LM_L_PNKY || lm_idx == LM_R_PNKY || lm_idx == LM_L_INDX || lm_idx == LM_R_INDX ||
    lm_idx == LM_L_THMB || lm_idx == LM_R_THMB || lm_idx == LM_L_FIDX || lm_idx == LM_R_FIDX )
    return false;
  return true;
}


//drag可能なlandmark
inline bool isDragableLandmark(int lm_idx)
{
  if (lm_idx == LM_L_EYEI || lm_idx == LM_R_EYEI || lm_idx == LM_L_EYEO || lm_idx == LM_R_EYEO ||
      lm_idx == LM_L_PNKY || lm_idx == LM_R_PNKY || lm_idx == LM_L_INDX || lm_idx == LM_R_INDX ||
      lm_idx == LM_L_MOUT || lm_idx == LM_R_MOUT ||
      lm_idx == LM_L_THMB || lm_idx == LM_R_THMB || lm_idx == LM_L_FIDX || lm_idx == LM_R_FIDX)
    return false;
  return true;
}




//このクラスはvideo streamを含むのでポインタにて管理する
//vector<VideoPoseData*>とし，コピーコンストラクタやデストラクタが呼ばれないように注意する
class VideoPoseData 
{
public:
  bool m_loading_success; //読み込みが成功したかどうか
  VideoLoaderFfmpeg                m_video;
  std::vector<std::vector<EVec3f>> m_landmarks;

  VideoPoseData(const std::string &fname_video, const std::string &fname_pose );
  VideoPoseData(const VideoPoseData &src)
  {
    std::cout << "エラー!!!!コピーコンストラクタは呼ばれないはず";
  }
  VideoPoseData &operator=(const VideoPoseData &src)
  {
    std::cout << "エラー!!!!コピーコンストラクタは呼ばれないはず";
    return *this;
  }  
};


// VideoManager 
// + 動画の管理 
// + Poseデータの管理
// + 複数データのうち一つがfocusされる (m_focusedVideoIdx) 
class VideoManager
{

private:
  std::vector<VideoPoseData*> m_videos; //pair of videostream & keypoints
  int m_focusedVideoIdx;
  
  VideoManager();
public:
  ~VideoManager();
  
  static VideoManager* GetInst(){
    static VideoManager p;
    return &p;
  }
  
  bool LoadVideoAndPose(const std::string &fname_video, const std::string &fname_pose);

  int  GetFocusedVideoIdx() { return m_focusedVideoIdx; }
  void SetFocusedVideoIdx(int idx) { m_focusedVideoIdx = idx; }

  //focust video index に対する処理
  int   FocusVideo_GetNumFrame();
  int   FocusVideo_GetWidth   ();
  int   FocusVideo_GetHeight  ();
  float FocusVideo_GetFPS     ();
  bool  FocusVideo_GetFrame(const int frame_idx, byte* bgr); //bgr should be allocated byte[W*H*3]
  void  ForcusVideo_SmoothLandmarks_Median(int radius);
  void  ForcusVideo_SmoothLnadmarks_Gauss();
  std::vector<EVec3f>         FocusVideo_GetLandmarks(const int frame_idx);
  std::vector<std::vector<EVec3f>> FocusVideo_GetPoseSequence();
  
  //export clip 
  //clipは、EVec3i(videoid / start_idx / clip_length )で指定する
  void ExportClips_PoseInfo       (std::string dirpath, std::vector<EVec3i> clips);
  void ExportClips_AsTheyAre      (std::string dirpath, std::vector<EVec3i> clips);
  void ExportClips_Superimpose    (std::string dirpath, std::vector<EVec3i> clips, std::vector<int> alignmentidxs);
  void ExportClips_PoseInfo_1stfrm(std::string dirpath, std::vector<EVec3i> clips);

};

#pragma managed
