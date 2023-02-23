#include "FormDrawGraph.h"
#include "VideoManager.h"
#include <string>
#include <vector>

using namespace TargetMotionViewer;
using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

FormDrawGraph::FormDrawGraph(void)
{
  InitializeComponent();
  m_checkedListBox->SetItemChecked(6, true);
}


void FormDrawGraph::SetDiffSequence(
    const std::vector<float> &diff_seq, 
    const float thresh) 
{
  m_chart_diff->Series[0]->Points->Clear();
  m_chart_diff->Series[1]->Points->Clear();
  m_chart_diff->ChartAreas[0]->AxisX->Maximum = (double)diff_seq.size();

  float average = 0;
  for (int i = 0; i < diff_seq.size(); i++)
  {
    float y = diff_seq[i];
    m_chart_diff->Series[0]->Points->AddY(y);
    m_chart_diff->Series[1]->Points->AddY(thresh);
    average += y;
  }
  average /= diff_seq.size();

  m_chart_diff->ChartAreas[0]->AxisY->Maximum = average * 2;
}


void FormDrawGraph::UpdateChartColor()
{
  for (int lm_i = 0; lm_i < m_chart_orbit->Series->Count; ++lm_i)
    m_chart_orbit->Series[lm_i]->Color = Color::FromArgb(32, 128, 128, 128);

  IEnumerator^ myEnum1 = m_checkedListBox->CheckedIndices->GetEnumerator();
  while (myEnum1->MoveNext())
  {
    Int32 lm_i = *safe_cast<Int32^>(myEnum1->Current);
    m_chart_orbit->Series[lm_i]->Color =
      (lm_i ==  0) ? Color::FromArgb(255, 128, 128, 128) :
      (lm_i ==  1) ? Color::FromArgb(255, 255,   0,  32) :
      (lm_i ==  2) ? Color::FromArgb(255,  32, 255,  64) :
      (lm_i ==  3) ? Color::FromArgb(255, 204,   0,  64) :
      (lm_i ==  4) ? Color::FromArgb(255,  64, 204,  64) :
      (lm_i ==  5) ? Color::FromArgb(255, 255, 255,   0) :
      (lm_i ==  6) ? Color::FromArgb(255,   0, 255, 255) :
      (lm_i ==  7) ? Color::FromArgb(255, 128,   0, 128) :
      (lm_i ==  8) ? Color::FromArgb(255, 128, 128,  64) :
      (lm_i ==  9) ? Color::FromArgb(255,  96,   0, 170) :
      (lm_i == 10) ? Color::FromArgb(255, 170, 96,   64) :
      (lm_i == 11) ? Color::FromArgb(255,  64,   0, 204) :
      Color::FromArgb(255, 204, 64, 64);
  }

}


void FormDrawGraph::SetPoseSequence( 
    const int img_width, 
    const int img_height, 
    const std::vector<std::vector<EVec3f>> &points)
{
  m_chart_orbit->ChartAreas[0]->AxisX->Maximum = img_width;
  m_chart_orbit->ChartAreas[0]->AxisY->Maximum = img_height;


  for (int lm_i = 0; lm_i < m_chart_orbit->Series->Count; ++lm_i)
  {
    int pidx = (lm_i == 0) ? LM_NOSE :
               (lm_i == 1) ? LM_L_SHOR :
               (lm_i == 2) ? LM_R_SHOR :
               (lm_i == 3) ? LM_L_ELBW :
               (lm_i == 4) ? LM_R_ELBW :
               (lm_i == 5) ? LM_L_WRST :
               (lm_i == 6) ? LM_R_WRST :
               (lm_i == 7) ? LM_L_HIP :
               (lm_i == 8) ? LM_R_HIP :
               (lm_i == 9) ? LM_L_KNEE :
               (lm_i == 10) ? LM_R_KNEE :
               (lm_i == 11) ? LM_L_ANKL :
               (lm_i == 12) ? LM_R_ANKL : 0;

    m_chart_orbit->Series[lm_i]->Points->Clear();
    for (int i = 0; i < (int)points.size(); ++i)
      m_chart_orbit->Series[lm_i]->Points->AddXY(points[i][pidx][0], points[i][pidx][1]);

    m_chart_orbit->Series[lm_i]->Color = Color::FromArgb(128, 128, 128, 128);
  }
  UpdateChartColor();

}

System::Void FormDrawGraph::m_checkedListBoxChanged(
    System::Object^  sender, 
    System::EventArgs^  e) 
{
  UpdateChartColor();
}



std::vector<int> FormDrawGraph::GetCheckedLandmarks()
{
  std::vector<int> landmarks;
  IEnumerator^ myEnum1 = m_checkedListBox->CheckedIndices->GetEnumerator();
  while (myEnum1->MoveNext())
  {
    Int32 lm_i = *safe_cast<Int32^>(myEnum1->Current);
    int pidx =(lm_i ==  0) ? LM_NOSE   :
              (lm_i ==  1) ? LM_L_SHOR :
              (lm_i ==  2) ? LM_R_SHOR :
              (lm_i ==  3) ? LM_L_ELBW :
              (lm_i ==  4) ? LM_R_ELBW :
              (lm_i ==  5) ? LM_L_WRST :
              (lm_i ==  6) ? LM_R_WRST :
              (lm_i ==  7) ? LM_L_HIP  :
              (lm_i ==  8) ? LM_R_HIP  :
              (lm_i ==  9) ? LM_L_KNEE :
              (lm_i == 10) ? LM_R_KNEE :
              (lm_i == 11) ? LM_L_ANKL :
              (lm_i == 12) ? LM_R_ANKL : 0;
    landmarks.push_back(pidx );
  }
  return landmarks;
}



