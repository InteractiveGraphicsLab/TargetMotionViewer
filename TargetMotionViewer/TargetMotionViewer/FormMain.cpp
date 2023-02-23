#include "FormMain.h"
#include "FormDrawGraph.h"

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "VideoManager.h"
#include "FormVisParameter.h"
#include <msclr/marshal_cppstd.h>

using namespace TargetMotionViewer;
using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;






#pragma unmanaged 
class TrajectoryManager
{
private:
  std::vector<std::vector<EVec3f>> m_trajectories;
  TrajectoryManager(){}
  
public:
  static TrajectoryManager* GetInst(){static TrajectoryManager p; return &p;}

  std::vector<std::vector<EVec3f>> GetTrajectories(){ return m_trajectories;}
  void Clear(){ m_trajectories.clear(); }
  void AddTrajectory(std::vector<EVec3f> t){ m_trajectories.push_back(t); }
 
};

#pragma managed 


//FILE IO DIALOG
static bool t_showOpenFileDlg
  (
    const char* filter,
    std::string& fname
  )
{
  OpenFileDialog^ dlg = gcnew OpenFileDialog();
  dlg->Filter = gcnew System::String(filter);
  dlg->Multiselect = false;

  if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::Cancel) return false;

  IntPtr mptr = Marshal::StringToHGlobalAnsi(dlg->FileName);
  fname = static_cast<const char*>(mptr.ToPointer());

  return true;
}


//convert int --> string "hh:mm:ss"
static std::string CvtSecToStr(int seconds) 
{
  std::string st = "";
  int h = seconds / 3600;
  int m = (seconds % 3600) / 60;
  int s = seconds % 60;
  st.append((h < 9 ? "0" : "") + std::to_string(h) + ":");
  st.append((m < 9 ? "0" : "") + std::to_string(m) + ":");
  st.append((s < 9 ? "0" : "") + std::to_string(s)      );
  return st;
}



FormMain::FormMain(void)
{
	InitializeComponent();

  m_seekbar->SetRange(0,1);
  m_seekbar->Value = 0;
  m_textbox_seekbar->Text = gcnew System::String( (0).ToString() );


  //penを作っておく(べた書きしておく)
  m_blushes = gcnew cli::array<SolidBrush^, 1>(LM_NUM);
  m_pens    = gcnew cli::array<Pen^       , 1>(LM_NUM);
  m_blush_nocolor = gcnew SolidBrush(Color::FromArgb(0, 0, 0, 0));
  m_pen_nocolor   = gcnew Pen(Color::FromArgb(0, 0, 0, 0));

  for (int i = 0; i < LM_NUM; ++i)
  {
    m_blushes[i] = m_blush_nocolor; //透明ブラシで初期化
    m_pens   [i] = m_pen_nocolor;
  }

  m_blushes[LM_NOSE  ] = gcnew SolidBrush(Color::FromArgb(255, 128, 128, 128));
  m_blushes[LM_L_EYE ] = gcnew SolidBrush(Color::FromArgb(255, 255, 255,   0));
  m_blushes[LM_R_EYE ] = gcnew SolidBrush(Color::FromArgb(255, 128, 128,   0));
  m_blushes[LM_L_EAR ] = gcnew SolidBrush(Color::FromArgb(255, 255, 255,   0));
  m_blushes[LM_R_EAR ] = gcnew SolidBrush(Color::FromArgb(255, 128, 128,   0));
  m_blushes[LM_L_SHOR] = gcnew SolidBrush(Color::FromArgb(255, 255,   0,  32));
  m_blushes[LM_L_ELBW] = gcnew SolidBrush(Color::FromArgb(255, 204,   0,  64));
  m_blushes[LM_L_WRST] = gcnew SolidBrush(Color::FromArgb(255, 255, 255,   0));
  m_blushes[LM_L_HIP ] = gcnew SolidBrush(Color::FromArgb(255, 128,   0, 128));
  m_blushes[LM_L_KNEE] = gcnew SolidBrush(Color::FromArgb(255,  96,   0, 170));
  m_blushes[LM_L_ANKL] = gcnew SolidBrush(Color::FromArgb(255,  64,   0, 204));
  m_blushes[LM_L_HEEL] = gcnew SolidBrush(Color::FromArgb(255,  32,   0, 255));
  m_blushes[LM_R_SHOR] = gcnew SolidBrush(Color::FromArgb(255,  32, 255,  64));
  m_blushes[LM_R_ELBW] = gcnew SolidBrush(Color::FromArgb(255,  64, 204,  64));
  m_blushes[LM_R_WRST] = gcnew SolidBrush(Color::FromArgb(255,   0, 255, 255));
  m_blushes[LM_R_HIP ] = gcnew SolidBrush(Color::FromArgb(255, 128, 128,  64));
  m_blushes[LM_R_KNEE] = gcnew SolidBrush(Color::FromArgb(255, 170,  96,  64));
  m_blushes[LM_R_ANKL] = gcnew SolidBrush(Color::FromArgb(255, 204,  64,  64));
  m_blushes[LM_R_HEEL] = gcnew SolidBrush(Color::FromArgb(255, 255,  32,  64));

  m_pens[ 0] = gcnew Pen(Color::FromArgb(255, 255,   0,   0), 2);
  m_pens[ 1] = gcnew Pen(Color::FromArgb(255,   0, 255,   0), 2);
  m_pens[ 2] = gcnew Pen(Color::FromArgb(255,   0,   0, 255), 2);
  m_pens[ 3] = gcnew Pen(Color::FromArgb(255, 255, 255,   0), 2);
  m_pens[ 4] = gcnew Pen(Color::FromArgb(255,   0, 255, 255), 2);
  m_pens[ 5] = gcnew Pen(Color::FromArgb(255, 255,   0, 255), 2);
  m_pens[ 6] = gcnew Pen(Color::FromArgb(255, 255,  64,  64), 2);
  m_pens[ 7] = gcnew Pen(Color::FromArgb(255,  64, 255,  64), 2);
  m_pens[ 8] = gcnew Pen(Color::FromArgb(255,  64,  64, 255), 2);
  m_pens[ 9] = gcnew Pen(Color::FromArgb(255,  96,   0, 170), 2);
  m_pens[10] = gcnew Pen(Color::FromArgb(255,  64,   0, 204), 2);
  m_pens[11] = gcnew Pen(Color::FromArgb(255,  32,   0, 255), 2);
  m_pens[12] = gcnew Pen(Color::FromArgb(255,  32, 255,  64), 2);
  m_pens[13] = gcnew Pen(Color::FromArgb(255,  64, 204,  64), 2);
  m_pens[14] = gcnew Pen(Color::FromArgb(255,   0, 255, 255), 2);
  m_pens[15] = gcnew Pen(Color::FromArgb(255, 128, 128,  64), 2);
  m_pens[16] = gcnew Pen(Color::FromArgb(255, 170,  96,  64), 2);
  m_pens[17] = gcnew Pen(Color::FromArgb(255, 204,  64,  64), 2);
  m_pens[18] = gcnew Pen(Color::FromArgb(255, 255,  32,  64), 2);
}



void FormMain::UpdateSeekbarText()
{
  const int   num_frm = VideoManager::GetInst()->FocusVideo_GetNumFrame() - 1;
  const float fps       = VideoManager::GetInst()->FocusVideo_GetFPS();
  const int   time_sec  = (int)(m_seekbar->Value / fps);

  m_textbox_seekbar->Text  = m_seekbar->Value.ToString() + "/" + num_frm.ToString();
  m_textbox_seekbar->Text += Environment::NewLine;
  m_textbox_seekbar->Text += gcnew System::String(CvtSecToStr(time_sec).c_str());
}



System::Void FormMain::loadVideomp4ToolStripMenuItem_Click(
    System::Object^  sender, 
    System::EventArgs^  e)
{
  std::string fname_video, fname_pose;
  if (!t_showOpenFileDlg("video(*.mp4;*.mov)|*.mp4;*.mov"   , fname_video) ) return;
  if (!t_showOpenFileDlg("pose data (*.txt)|*.txt"          , fname_pose ) ) return;
  if (!VideoManager::GetInst()->LoadVideoAndPose(fname_video, fname_pose ) ) return;
  
  const int num_frame = VideoManager::GetInst()->FocusVideo_GetNumFrame() - 1;
  m_seekbar->SetRange(0, num_frame);
  m_seekbar->Value = 0;
  UpdateSeekbarText();

  //サムネイルを追加（ここ以外ではm_loadedVideoImageListに追加をしない）
  const int   video_idx = VideoManager::GetInst()->GetFocusedVideoIdx();
  m_loadedVideoImageList->Images->Add( GenerateBitmapFromFocusedVideo(10) );
  ListViewItem^ lvi = gcnew ListViewItem( video_idx.ToString(), m_loadedVideoImageList->Images->Count - 1);
  m_listview_loadvideo->Items->Add(lvi);

  m_textbox_seekbar->Refresh();
  this->RedrawPictureBox();
}



System::Void FormMain::m_seekbar_Scroll(
    System::Object^  sender, 
    System::EventArgs^  e) 
{
  UpdateSeekbarText();
  m_textbox_seekbar->Refresh();
  this->RedrawPictureBox();
}


void FormMain::SetSeekbarValue(const int val)
{
  if( val < m_seekbar->Minimum || m_seekbar->Maximum <= val ) return;
  m_seekbar->Value = val;
  UpdateSeekbarText();
  m_textbox_seekbar->Refresh();
  this->RedrawPictureBox();
}


int  FormMain::GetSeekbarValue()
{
  return m_seekbar->Value;
}


System::Void FormMain::AutoPlayFocusedClip(int clip_length)
{
  if(clip_length <= 0) return;

  const int   curr_idx  = m_seekbar->Value;
  const int   num_frame = VideoManager::GetInst()->FocusVideo_GetNumFrame();
  const float spf = 1.0f / VideoManager::GetInst()->FocusVideo_GetFPS();

  int max_idx = min(num_frame, curr_idx + clip_length);
  for (int i = curr_idx; i < max_idx; i++)
  {
    m_seekbar->Value = i;
    FormMain::getInst()->RedrawPictureBox();
    Sleep(10); //Sleep(spf * 1000)
  }
  m_seekbar->Value = curr_idx;
  FormMain::getInst()->RedrawPictureBox();
}


static const int LM_RADI = 16;

System::Void FormMain::m_pictureBox_MouseDown(
    System::Object^  sender, 
    System::Windows::Forms::MouseEventArgs^  e)
{
  /*
  if(e->Button == System::Windows::Forms::MouseButtons::Left) 
  {
    const float sx = m_pictureBox->Width / (float) VideoManager::GetInst()->FocusVideo_GetWidth();
    const float sy = m_pictureBox->Height / (float)VideoManager::GetInst()->FocusVideo_GetHeight();
    const int x = e->X, y = e->Y;
    const int f = m_seekbar->Value;
    std::vector<EVec3f> points = VideoManager::GetInst()->FocusVideo_GetLandmarks(f);
     
    int min_idx = -1;
    float min_dist = FLT_MAX;
    for (int i = 0; i < (int)points.size(); ++i)
    {
      float xx = points[i][0] * sx;
      float yy = points[i][1] * sy;
      float  d = (x-xx) * (x - xx) + (y - yy) * (y - yy);
      if (d < min_dist)
      {
        min_dist = d;
        min_idx = i;
      }
    }

    if (min_dist < (LM_RADI+2) * (LM_RADI+2) && min_idx != -1)
      m_traj_lm_idx = min_idx;
    else
      m_traj_lm_idx = -1;
    RedrawPictureBox();
  }
  */
  
}



void FormMain::DrawLandmarks(Graphics ^g, const int W, const int H)
{
  int r = LM_RADI;
  
  const int fi = m_seekbar->Value;
  const std::vector<EVec3f> &landmarks = VideoManager::GetInst()->FocusVideo_GetLandmarks(fi);
  
  for(int i = 0; i < (int)landmarks.size(); ++i)
  { 
    const auto &p = landmarks[i];
    SolidBrush^ brush = landmarkToolStripMenuItem->Checked ? m_blushes[i] : m_blush_nocolor;
    if (0 <= p[0] && p[0] <= W-r && 0 <= p[1] && p[1] <= H-r )
      g->FillEllipse(brush, (int)(p[0]-r/2), (int)(p[1]-r/2), r, r );
  }
}



void FormMain::DrawTrajectory(Graphics ^g, const int W, const int H)
{
  const std::vector<std::vector<EVec3f>> &trajectories = TrajectoryManager::GetInst()->GetTrajectories();

  for (int t = 0; t < (int)trajectories.size(); ++t)
  {
    Pen^ pen = m_pens[t % (m_pens->Length)];
    std::vector<EVec3f> traj = trajectories[t];
    
    int r = W > 1080 ? 6 : 3;
    for (int i = 1; i < traj.size(); ++i)
    {
      const auto& p1 = traj[i-1];
      const auto& p2 = traj[ i ];
      g->DrawLine(pen, (int)p1[0], (int)p1[1], (int)p2[0], (int)p2[1]);
    }
  }
}



System::Void FormMain::m_pictureBox_Paint(
    System::Object^  sender, 
    System::Windows::Forms::PaintEventArgs^  e)
{
  static bool isFirst = true;
  if( isFirst )
  {
    FormVisParameter::getInst()->Show();
    FormDrawGraph::getInst()->Show();
    isFirst = false;
  }

  const int W = VideoManager::GetInst()->FocusVideo_GetWidth ();
  const int H = VideoManager::GetInst()->FocusVideo_GetHeight();
  byte   *rgb = new byte[W*H*3];

  if ( !VideoManager::GetInst()->FocusVideo_GetFrame( m_seekbar->Value, rgb) )
  {
    delete[] rgb;
    return;
  }

  //bitmapを作成して，さらにpixelへのポインタも取得 
  Bitmap^  bmp = gcnew Bitmap(W,H,Imaging::PixelFormat::Format24bppRgb);
  System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height);
  Imaging::BitmapData^ bmpData = bmp->LockBits(rect, Imaging::ImageLockMode::ReadWrite, bmp->PixelFormat); 
  
  Byte* pBuf = (Byte*)bmpData->Scan0.ToPointer();

  for( int y=0; y < H; ++y)
  {
    for( int x=0; x < W; ++x)
    {
      pBuf[y*bmpData->Stride + x*3 + 0] = rgb[3*(x+y*W)+0]; 
      pBuf[y*bmpData->Stride + x*3 + 1] = rgb[3*(x+y*W)+1]; 
      pBuf[y*bmpData->Stride + x*3 + 2] = rgb[3*(x+y*W)+2]; 
    }
  }

  bmp->UnlockBits( bmpData );

  //Draw landmarks and trajectory
  Graphics^ g = Graphics::FromImage(bmp);
  DrawLandmarks (g, W, H);
  DrawTrajectory(g, W, H);

  //拡大縮小もする
  e->Graphics->InterpolationMode = Drawing2D::InterpolationMode::NearestNeighbor;
  e->Graphics->DrawImage(bmp, System::Drawing::Rectangle(0, 0, m_pictureBox->Width, m_pictureBox->Height), rect, GraphicsUnit::Pixel);
    
  delete bmp;
  delete[] rgb;
}



static bool t_InterpretItemText(
    const std::string &str, // input:  "videoid_startid_cliplen" 
    int &videoid,      //output: 
    int &start_idx, 
    int &clip_len)
{
  std::vector<int> tmp;
  std::stringstream strstream(str);
  std::string word;

  while( std::getline(strstream, word, '_') ) 
    tmp.push_back( atoi(word.c_str()) );

  if ( tmp.size() != 3 ) return false;
  videoid   = tmp[0];
  start_idx = tmp[1];
  clip_len  = tmp[2];
  return true;
}


//return vector of 
std::vector<EVec3i> FormMain::GetSelectedClipInfo()
{
  System::Collections::IEnumerator^ myEnum 
    = m_listview_clips->SelectedItems->GetEnumerator();

  std::vector<EVec3i> clips;
  while( myEnum->MoveNext() )
  {
    ListViewItem^ item = safe_cast<ListViewItem^>(myEnum->Current);
    std::string str = msclr::interop::marshal_as<std::string>(item->Text);
    
    int vid, c_startidx, c_length;
    if ( !t_InterpretItemText(str, vid, c_startidx, c_length) )
      continue;
    clips.push_back(EVec3i(vid, c_startidx, c_length));
  }
  return clips;
}



std::vector<int> FormMain::GetSelectedClipInfoAlignIdxs() 
{
  std::vector<int> idxs;
  System::Collections::IEnumerator^ myEnum 
    = this->m_listview_clips->SelectedItems->GetEnumerator();

  while (myEnum->MoveNext())
  {
    ListViewItem^ item = safe_cast<ListViewItem^>(myEnum->Current);
    idxs.push_back((int)item->Tag);
  }
  return idxs;
}





//
//clipサムネのクリック
//参考 : https://docs.microsoft.com/ja-jp/dotnet/api/system.windows.forms.listview.selectedlistviewitemcollection?view=netframework-4.8
//
System::Void FormMain::m_listview_clips_Clicked( System::Object^ sender, System::EventArgs^  e) 
{
  System::Collections::IEnumerator^ myEnum
    = m_listview_clips->SelectedItems->GetEnumerator();

  std::vector<std::vector<EVec3f>> pose_seq = VideoManager::GetInst()->FocusVideo_GetPoseSequence();
  const int W = VideoManager::GetInst()->FocusVideo_GetWidth();
  const int H = VideoManager::GetInst()->FocusVideo_GetHeight();

  int length = -1;  
  
  TrajectoryManager::GetInst()->Clear();

  while( myEnum->MoveNext() )
  {
    ListViewItem^ item = safe_cast<ListViewItem^>(myEnum->Current);

    std::string str = msclr::interop::marshal_as<std::string>(item->Text);
    int vid, c_start, c_length ;
    if ( !t_InterpretItemText(str, vid, c_start, c_length) ) continue;

    //1. 選択clipに応じて Seekbar位置 を移動 
    VideoManager::GetInst()->SetFocusedVideoIdx(vid);
    m_seekbar->Value = c_start;
    m_seekbar->SetRange(0, VideoManager::GetInst()->FocusVideo_GetNumFrame()-1);
    FormMain::getInst()->RedrawPictureBox();
    
    //2. FormDrawGraphに 選択clipのpose_seqをセット（現状最後に一個だけが表示される）
    std::vector<std::vector<EVec3f>> points(c_length);
    for (int i = 0; i < c_length; ++i) points[i] = pose_seq[i + c_start];
    FormDrawGraph::getInst()->SetPoseSequence(W, H, points);
    
    //3. set visualization trajectory
    if (orbitToolStripMenuItem->Checked)
    {
      std::vector<int> landmarks = FormDrawGraph::getInst()->GetCheckedLandmarks();
      for (auto lm : landmarks)
      {
        std::vector<EVec3f> t;
        for (int i = 0; i < c_length; ++i) t.push_back(pose_seq[i + c_start][lm]);
        TrajectoryManager::GetInst()->AddTrajectory(t);
      }
    }
    length = c_length;
  }
  

  //動画の再生
  RedrawSeekbarPictureBox();
  AutoPlayFocusedClip(length);
}



System::Void FormMain::m_listview_loadedvideos_Clicked(
    System::Object^  sender, 
    System::EventArgs^  e) 
{
  System::Collections::IEnumerator^ myEnum 
    = m_listview_loadvideo->SelectedItems->GetEnumerator();
  
  while (myEnum->MoveNext()) 
  {
    ListViewItem^ item = safe_cast<ListViewItem^>(myEnum->Current);
    int vid = Convert::ToInt32(item->Text);
  
    //focus videoの切り替え
    VideoManager::GetInst()->SetFocusedVideoIdx(vid);
    m_seekbar->SetRange(0, VideoManager::GetInst()->FocusVideo_GetNumFrame()-1);
    FormMain::getInst()->RedrawPictureBox();
  }
  RedrawSeekbarPictureBox();
  AutoPlayFocusedClip(100);
}


// 新しいclip (videoid / startidx / length) を追加
System::Void FormMain::AddNewClips(
    const std::vector<int> &clip_start_ids,
    const std::vector<int> &clip_alignment_ids,
    const int          clip_length)
{
  const int video_id = VideoManager::GetInst()->GetFocusedVideoIdx();
  
  bool bAlignmentSet = clip_alignment_ids.size() != 0;

  for (int i = 0; i < (int) clip_start_ids.size(); ++i )
  {
    const int start_idx = clip_start_ids[i];
    System::String ^s = String::Format( "{0}_{1}_{2}", video_id, start_idx, clip_length);
    
    const int thumb_idx = (bAlignmentSet) ? clip_alignment_ids[i] : start_idx ;
    m_keyThumbImageList->Images->Add( GenerateBitmapFromFocusedVideo(thumb_idx));

    ListViewItem^ lvi = gcnew ListViewItem( s, m_keyThumbImageList->Images->Count - 1);
    lvi->Tag = (bAlignmentSet) ? clip_alignment_ids[i] : 0;
    m_listview_clips->Items->Add(lvi);
  }
}


void FormMain::ClearAllClips()
{
  m_keyThumbImageList->Images->Clear();
  m_listview_clips->Clear();
}


//
// seekbarの下にあるpicture boxの描画
//
System::Void FormMain::m_seekbarPictureBox_Paint(
    System::Object^  sender, 
    System::Windows::Forms::PaintEventArgs^  e) 
{
  const int focused_vid = VideoManager::GetInst()->GetFocusedVideoIdx();
  const int num_frame   = VideoManager::GetInst()->FocusVideo_GetNumFrame();

  std::vector<EVec3i> clips; //vid. start_idx, length
  System::Collections::IEnumerator^ myEnum 
    = m_listview_clips->Items->GetEnumerator();

  while (myEnum->MoveNext())
  {
    ListViewItem^ item = safe_cast<ListViewItem^>(myEnum->Current);
    std::string str = msclr::interop::marshal_as<std::string>(item->Text->ToString());
    int vid, c_startidx, c_length;
    if (!t_InterpretItemText(str, vid, c_startidx, c_length)) continue;
    if(vid == focused_vid)
      clips.push_back(EVec3i( vid, c_startidx, c_length));
  }

  if (clips.size() <= 0) return;

  const int W = m_seekbarPictureBox->Size.Width;
  const int H = m_seekbarPictureBox->Size.Height;

  Graphics ^g = e->Graphics;
  SolidBrush^ WhitePen = gcnew SolidBrush(Color::White);
  SolidBrush^ BluePen  = gcnew SolidBrush(Color::FromArgb(2, 161, 252));
  g->FillRectangle(WhitePen, 0, 0, W, H);

  for (int i = 0; i < (int)clips.size(); ++i)
  {
    const int draw_pos = (int)(W * clips[i][1] / (float)num_frame + 0.5f);//左端
    const int draw_wid = (int)(W * clips[i][2] / (float)num_frame + 0.5f);//幅
    g->FillRectangle(BluePen, (int)draw_pos, 0, draw_wid, H);
  }

  delete WhitePen;
  delete BluePen;
}


System::Void FormMain::m_seekbarPictureBox_SizeChanged(
    System::Object^  sender, 
    System::EventArgs^  e) 
{
  RedrawSeekbarPictureBox();
}

System::Void FormMain::landmarkToolStripMenuItem_Click(
    System::Object^  sender, 
    System::EventArgs^  e) 
{
  landmarkToolStripMenuItem->Checked = !landmarkToolStripMenuItem->Checked;
  this->RedrawPictureBox();
}

System::Void FormMain::orbitToolStripMenuItem_Click(
    System::Object^  sender, 
    System::EventArgs^  e) 
{
  orbitToolStripMenuItem->Checked = !orbitToolStripMenuItem->Checked;
  this->RedrawPictureBox();
}


//現在の focused videoからサムネイル画像を生成する
Bitmap^ FormMain::GenerateBitmapFromFocusedVideo(int frame_idx)
{
  const int W = VideoManager::GetInst()->FocusVideo_GetWidth();
  const int H = VideoManager::GetInst()->FocusVideo_GetHeight();
  byte* rgb = new byte[W * H * 3];
  bool tf = VideoManager::GetInst()->FocusVideo_GetFrame(frame_idx, rgb);

  //bitmapを作成して，さらにpixelへのポインタも取得 
  Bitmap^ bmp = gcnew Bitmap(W, H, Imaging::PixelFormat::Format24bppRgb);
  System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height);
  Imaging::BitmapData^ bmpData = bmp->LockBits(rect, Imaging::ImageLockMode::ReadWrite, bmp->PixelFormat);
  Byte* pBuf = (Byte*)bmpData->Scan0.ToPointer();

  //Imaging::PixelFormat::Format24bppRgb はGBRGBRGBRの順序
  for (int y = 0; y < H; ++y)
  {
    for (int x = 0; x < W; ++x)
    {
      pBuf[y * bmpData->Stride + x * 3 + 0] = rgb[3 * (x + y * W) + 0];
      pBuf[y * bmpData->Stride + x * 3 + 1] = rgb[3 * (x + y * W) + 1];
      pBuf[y * bmpData->Stride + x * 3 + 2] = rgb[3 * (x + y * W) + 2];
    }
  }
  bmp->UnlockBits(bmpData);

  delete[] rgb;
  return bmp;
}
