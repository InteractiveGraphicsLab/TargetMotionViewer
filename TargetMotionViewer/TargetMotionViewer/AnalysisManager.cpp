#include "AnalysisManager.h"

#include <vector>
#include <algorithm>
#include<iostream>
#include<fstream>


static float t_DiffOfTwoPoses(
    const std::vector<EVec3f> &points1, 
    const std::vector<EVec3f> &points2)
{
  const int N = (int)points1.size();

  float dis = 0;
  for ( int i = 0; i < N; ++i) 
  {
    float dx = points1[i][0] - points2[i][0];
    float dy = points1[i][1] - points2[i][1];
    dis += sqrt(dx * dx + dy * dy);
  }
  return dis / N;
}


//現状，重心を原点にするだけ
//スケール正規化は検討中
static void t_NormalizePose( std::vector<EVec3f> &points)
{
  const int N = (int)points.size();
  float cx = 0, cy = 0;

  for (int i = 0; i < N; ++i) {
    cx += points[i][0];
    cy += points[i][1];
  }
  cx = cx / N;
  cy = cy / N;

  for (int i = 0; i < N; ++i) 
  {
    points[i][0] -= cx;
    points[i][1] -= cy;
  }
}

static void t_SearchLocalMinima(
    const std::vector<float> &diff_sequence,
    const int threshold,
    const int winsize,

    std::vector<int> &found_idx
)
{
  found_idx.clear();

  std::ofstream outputfile2("localMinIdx.csv");

  for (int piv_i = 0; piv_i < (int)diff_sequence.size(); ++piv_i)
  {
    if (diff_sequence[piv_i] >= threshold) continue;

    const int win_s = (std::max)(piv_i - winsize / 2, 0);
    const int win_e = (std::min)(piv_i + winsize / 2, (int)diff_sequence.size());

    bool isLocalMin = true;
    for (int k = win_s; k < win_e; ++k)
    {
      if (diff_sequence[piv_i] > diff_sequence[k])
      {
        isLocalMin = false;
        break;
      }
    }

    if (isLocalMin)
    {
      found_idx.push_back(piv_i);
      outputfile2 << piv_i << "\n";
    }
  }
  outputfile2.close();

}



void AnalysisManager::SearchSimilarPoseClip(
    const std::vector<std::vector<EVec3f>> &_pose_sequence,
    const int clip_start_idx  ,
    const int clip_end_idx    ,
    const int threshold       , 
    const int winsize,

    std::vector<float> &diff_sequence,
    std::vector<int>   &found_clip_idx)
{
  const int num_full = (int) _pose_sequence.size();
  const int num_clip = clip_end_idx - clip_start_idx + 1;

  bool bQuerySame = (m_prev_start_idx == clip_start_idx) && 
                    (m_prev_end_idx   == clip_end_idx  ) && 
                    (m_prev_winsize   == winsize);
  
  //1. 相違度の計算
  if (bQuerySame)
  {
    std::cout << "クエリに変化なし．相違度の計算を行いません\n";
    diff_sequence = m_prev_diff_sequence;
  }
  else
  {
    //normalize --> 相違度計算
    std::cout << "相違度計算\n";

    std::vector<std::vector<EVec3f>> pose_seq = _pose_sequence;
    for ( int i = 0; i < num_full; ++i) t_NormalizePose( pose_seq[i] );

    diff_sequence.resize( num_full - num_clip, 0 );

    for ( int piv_i = 0; piv_i < num_full - num_clip; ++piv_i )
    {
      float d = 0;
      for ( int i = 0; i < num_clip; ++i)
        d += t_DiffOfTwoPoses( pose_seq[ piv_i + i ], pose_seq[ clip_start_idx + i ] );
      diff_sequence[piv_i] = d / num_clip;
    }
  }

  //2. local minimaの探索
  std::cout << "局所最小値探索\n";
  found_clip_idx.clear();
  t_SearchLocalMinima(diff_sequence, threshold, winsize, found_clip_idx);

  
  m_prev_start_idx = clip_start_idx;
  m_prev_end_idx   = clip_end_idx;
  m_prev_winsize   = winsize;
  m_prev_diff_sequence = diff_sequence;
}




int AnalysisManager::SearchBestMatchPoseIdx(
  const std::vector< std::vector<EVec3f> > & _trgt_pose_seq , //探索対象
  const std::vector< std::vector<EVec3f> > & _query_pose_seq) //クエリ
{
  if (_trgt_pose_seq.size() <= _query_pose_seq.size()) return 0;

  //1. normalize
  std::vector<std::vector<EVec3f>> trgt_pose_seq  = _trgt_pose_seq;
  std::vector<std::vector<EVec3f>> query_pose_seq = _query_pose_seq;
  const int num_trgt = (int)trgt_pose_seq.size();
  const int num_quely = (int)query_pose_seq.size();
  for (int i = 0; i < num_trgt ; ++i) t_NormalizePose( trgt_pose_seq[i]);
  for (int i = 0; i < num_quely; ++i) t_NormalizePose(query_pose_seq[i]);

  //2. calc diff sequence
  std::vector<float> diff_seq(num_trgt - num_quely, 0);

  for (int piv_i = 0; piv_i < num_trgt - num_quely; ++piv_i)
  {
    float d = 0;
    for (int i = 0; i < num_quely; ++i)
    {
      d += t_DiffOfTwoPoses(trgt_pose_seq[piv_i + i], query_pose_seq[i]);
    }
    diff_seq[piv_i] = d / num_quely;
  }
  
  //3. Find minimum index 
  float min_val = diff_seq[0];
  int   min_idx = 0;
  for (int i=0; i < (int)diff_seq.size(); ++i)
  {
    if (diff_seq[i] >= min_val) continue;
    min_val = diff_seq[i];
    min_idx = i;
  }
  return min_idx;
}
