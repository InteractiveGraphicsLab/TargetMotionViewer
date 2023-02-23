#pragma once

#include <vector>
#include "../3rdparty/tmath.h"

class AnalysisManager
{

private:
  AnalysisManager(){
    m_prev_start_idx = -1;
    m_prev_end_idx = -1;
    m_prev_winsize = -1;
  }
  ~AnalysisManager(){}
   
  //�T��query�ƒT�����ʂ̋L�^�i�ƍė��p�j
  int m_prev_start_idx;
  int m_prev_end_idx  ;
  int m_prev_winsize  ;
  std::vector<float> m_prev_diff_sequence;

public:

  static AnalysisManager* getInst() {
    static AnalysisManager p;
    return &p;
  }

   //idx���N�G���ɂ���ꍇ
  void SearchSimilarPoseClip(
    const std::vector< std::vector<EVec3f> > &_pose_sequence,
    const int clip_start_idx  ,
    const int clip_end_idx    ,
    const int threshold       , 
    const int localmin_winsize,

    std::vector<float> &diff_sequence,
    std::vector<int>   &found_clip_idx
  );

  //pose���N�G���ɂ���ꍇ(aliment�����Ɏg��)
  static int SearchBestMatchPoseIdx(
    const std::vector< std::vector<EVec3f> > &trgt_pose_seq,
    const std::vector< std::vector<EVec3f> > &query_pose_seq);
};