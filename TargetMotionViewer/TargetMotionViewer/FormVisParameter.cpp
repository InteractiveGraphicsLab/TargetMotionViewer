#include "FormVisParameter.h"
#include "FormMain.h"
#include "VideoManager.h"
#include "AnalysisManager.h"
#include "FormDrawGraph.h"


#include <string>
#include <vector>
#include <algorithm>

using namespace TargetMotionViewer;
using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;


FormVisParameter::FormVisParameter(void)
{
  InitializeComponent();

  m_textbox_startidx->Text     = ( 10).ToString();
  m_textbox_endidx->Text       = (100).ToString();
  m_textbox_alignmentidx->Text = (-1).ToString();

  m_trackbar_threshold->SetRange(0, 200);
  m_trackbar_threshold->Value = 50;
  m_label_threshval->Text = (m_trackbar_threshold->Value).ToString();

  m_trackbar_winsize->SetRange(0, 500);
  m_trackbar_winsize->Value = 100;
  m_label_winsizeval->Text = (m_trackbar_winsize->Value).ToString();

  m_trackbar_export_margin->SetRange(0, 400);
  m_trackbar_export_margin->Value = 10;
  m_label_marginval->Text = (m_trackbar_export_margin->Value).ToString();
}



System::Void FormVisParameter::m_button_set_startidx_Click(
    System::Object^  sender, 
    System::EventArgs^  e)
{
  int seekbar_value = FormMain::getInst()->GetSeekbarValue();
  m_textbox_startidx->Text = (seekbar_value).ToString();
}


System::Void FormVisParameter::m_button_set_endidx_Click(
    System::Object^  sender, 
    System::EventArgs^  e)
{
  int seekbar_value = FormMain::getInst()->GetSeekbarValue();
  m_textbox_endidx->Text =  (seekbar_value).ToString() ;
}


System::Void FormVisParameter::m_button_set_alignmentidx_Click(
    System::Object^  sender, 
    System::EventArgs^  e) 
{
  int seekbar_value = FormMain::getInst()->GetSeekbarValue();
  m_textbox_alignmentidx->Text = (seekbar_value).ToString();
}


System::Void FormVisParameter::m_button_medianfilter_Click(
    System::Object^  sender,
    System::EventArgs^  e)
{
  VideoManager::GetInst()->ForcusVideo_SmoothLandmarks_Median(5);
}


System::Void FormVisParameter::m_button_gaussianfilter_Click(
    System::Object^  sender, 
    System::EventArgs^  e)
{
  VideoManager::GetInst()->ForcusVideo_SmoothLnadmarks_Gauss();
}


System::Void FormVisParameter::m_trackbar_export_margin_Scroll(
    System::Object^  sender, 
    System::EventArgs^  e)
{
  m_label_marginval->Text = m_trackbar_export_margin->Value.ToString();
}


System::Void FormVisParameter::m_trackbar_winsize_scroll(
    System::Object^  sender, 
    System::EventArgs^  e) 
{
  m_label_winsizeval->Text = m_trackbar_winsize->Value.ToString();
}


System::Void FormVisParameter::m_trackbar_threshold_scroll(
    System::Object^  sender, 
    System::EventArgs^  e) 
{
  m_label_threshval->Text = m_trackbar_threshold->Value.ToString();
}


System::Void FormVisParameter::m_button_searchclips_Click(System::Object^  sender, System::EventArgs^  e)
{
  const std::vector<std::vector<EVec3f>> pose_seq
    = VideoManager::GetInst()->FocusVideo_GetPoseSequence();
  const int start_idx = Convert::ToInt32( m_textbox_startidx->Text    );
  const int end_idx   = Convert::ToInt32( m_textbox_endidx  ->Text    );
  const int align_idx = Convert::ToInt32( m_textbox_alignmentidx->Text);
  const int threshold = m_trackbar_threshold->Value;
  const int winsize   = m_trackbar_winsize->Value;

  if (pose_seq.size() == 0) return;

  if(start_idx < 0 || end_idx < 0 )
  {
    MessageBox::Show("ClipのStartIndexとEndIndexの両方を指定してください","caption");
    return;
  }
  if(start_idx >=  end_idx )
  {
    MessageBox::Show("StartIndexはendIndexより小さな値を指定してください","caption");
    return;
  }
  if (align_idx != -1 && (align_idx < start_idx || end_idx <= align_idx))
  {
    MessageBox::Show("Alignment Indexには、Startとendの間の値を指定してください", "caption");
    return;
  }
  
  //検索
  std::vector<float> diff_seq;
  std::vector<int>   clip_idxes;
  AnalysisManager::getInst()->SearchSimilarPoseClip( 
      pose_seq, start_idx, end_idx, 
      threshold, winsize, 
      diff_seq, clip_idxes);

  const int num_clip = end_idx - start_idx + 1;

  //見つかったclipに対して alighment 検索
  std::vector<int> align_idxes;
  if (align_idx != -1) 
  {
    std::vector<std::vector<EVec3f>> query_pose ={ 
        pose_seq[align_idx - 2], pose_seq[align_idx - 1], pose_seq[align_idx],
        pose_seq[align_idx + 1], pose_seq[align_idx + 2] };

    for (int i = 0; i < clip_idxes.size(); ++i) 
    {
      std::vector<std::vector<EVec3f>> trgt_pose_seq(num_clip);
      std::copy( pose_seq.begin() + clip_idxes[i], 
                 pose_seq.begin() + clip_idxes[i] + num_clip,
                 trgt_pose_seq.begin());
    
      int idx = AnalysisManager::SearchBestMatchPoseIdx(trgt_pose_seq, query_pose);

      align_idxes.push_back(clip_idxes[i] + idx);
    }
  }

  //グラフの描画
  FormDrawGraph::getInst()->Show();
  FormDrawGraph::getInst()->SetDiffSequence(diff_seq, (float)threshold);

  //thambnail追加
  FormMain::getInst()->AddNewClips( clip_idxes, align_idxes, num_clip);

  //シークバーを描画
  FormMain::getInst()->RedrawSeekbarPictureBox();
}


System::Void FormVisParameter::m_button_clearfoundclips_Click(
    System::Object^  sender, 
    System::EventArgs^  e) 
{
  FormMain::getInst()->ClearAllClips();
}


System::Void FormVisParameter::m_button_exportallclips_Click(
    System::Object^  sender, 
    System::EventArgs^  e) 
{
  std::vector<EVec3i> clips = FormMain::getInst()->GetSelectedClipInfo();

  if (clips.size() == 0 ) {
    MessageBox::Show("Ctrl+クリックで複数のclipを選択し，このボタンを押してください．", "caption");
    return;
  }

  FolderBrowserDialog ^dlg = gcnew FolderBrowserDialog( );
  dlg->Description = "Select folder for export clips";
  if(dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
  
  IntPtr mptr = Marshal::StringToHGlobalAnsi( dlg->SelectedPath );
  std::string dirpath = static_cast<const char*>(mptr.ToPointer());

  VideoManager::GetInst()->ExportClips_AsTheyAre( dirpath, clips);
}



System::Void FormVisParameter::m_button_exportoverlayclips_Click(
    System::Object^  sender, 
    System::EventArgs^  e) 
{
  std::vector<EVec3i> clips     = FormMain::getInst()->GetSelectedClipInfo();
  std::vector<int>    alignidxs = FormMain::getInst()->GetSelectedClipInfoAlignIdxs();

  if (clips.size() == 0 ) {
    MessageBox::Show("Ctrl+クリックで複数のclipを選択してください", "caption");
    return;
  }
  
  FolderBrowserDialog ^dlg = gcnew FolderBrowserDialog( );
  dlg->Description = "Select folder for export clips";
  if(dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
  
  IntPtr mptr = Marshal::StringToHGlobalAnsi( dlg->SelectedPath );
  std::string dirpath = static_cast<const char*>(mptr.ToPointer());


  VideoManager::GetInst()->ExportClips_Superimpose( dirpath, clips, alignidxs);
}



System::Void FormVisParameter::m_button_exportclip_poses_Click(
    System::Object^  sender, 
    System::EventArgs^  e) 
{
  std::vector<EVec3i> clips = FormMain::getInst()->GetSelectedClipInfo();
  if ( clips.size() == 0 ) {
    MessageBox::Show("Ctrl+クリックで複数のclipを選択してください", "caption");
    return;
  }

  FolderBrowserDialog ^dlg = gcnew FolderBrowserDialog( );
  dlg->Description = "Select folder for export clips";
  if(dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
  
  IntPtr mptr = Marshal::StringToHGlobalAnsi( dlg->SelectedPath );
  std::string dirpath = static_cast<const char*>(mptr.ToPointer());

  VideoManager::GetInst()->ExportClips_PoseInfo( dirpath, clips );
}


//選択されたクリップのサムネイルのポーズを１つのcsvに出力する
//サムネイルを出力するとユーザーは選択がしやすいけど
//プレビューしているフレームのポーズをスタックしていくほうが、他のニーズも満たせそう
System::Void FormVisParameter::m_button_export_thumbnail_poses_Click(
    System::Object^  sender, 
    System::EventArgs^  e) 
{
  std::vector<EVec3i> clips = FormMain::getInst()->GetSelectedClipInfo();

  if (clips.size() == 0) {
    MessageBox::Show("Ctrl+クリックで複数のclipを選択してください", "caption");
    return;
  }

  FolderBrowserDialog ^dlg = gcnew FolderBrowserDialog();
  dlg->Description = "Select folder for export clips";
  if (dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

  IntPtr mptr = Marshal::StringToHGlobalAnsi(dlg->SelectedPath);
  std::string dirpath = static_cast<const char*>(mptr.ToPointer());

  VideoManager::GetInst()->ExportClips_PoseInfo_1stfrm(dirpath, clips);
}


System::Void FormVisParameter::m_trackbar_threshold_mouseUp(
    System::Object ^ sender, 
    System::Windows::Forms::MouseEventArgs ^ e)
{
}
