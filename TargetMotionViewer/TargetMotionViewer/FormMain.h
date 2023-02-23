#include <vector>
#include <windows.h>

#include "../3rdparty/tmath.h"

#pragma once


//
// 動画・スライダーバー・クリップサムネ・動画サムネの表示
// + サムネイルの作成もMainForm (画像をVideoManagerからもらう) 
// + 抽出した動画クリップはimage listへ追加  (文字列としてStart/End/Frame数を付加)
// + ロードした動画クリップもimage listへ追加()


namespace TargetMotionViewer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// FormMain の概要
	/// </summary>
	public ref class FormMain : public System::Windows::Forms::Form
	{
private:
    System::Windows::Forms::Label^      m_label1;
    System::Windows::Forms::Label^      m_label2;
    System::Windows::Forms::PictureBox^ m_pictureBox;
    System::Windows::Forms::PictureBox^ m_seekbarPictureBox;
    System::Windows::Forms::ListView^   m_listview_clips;
    System::Windows::Forms::ListView^   m_listview_loadvideo;
    System::Windows::Forms::ImageList^  m_keyThumbImageList;
    System::Windows::Forms::ImageList^  m_loadedVideoImageList;
    System::Windows::Forms::TrackBar^   m_seekbar;
    System::Windows::Forms::TextBox^    m_textbox_seekbar;
    System::Windows::Forms::MenuStrip^  m_meshstrip;
    System::Windows::Forms::ToolStripMenuItem^ viewToolStripMenuItem;
    System::Windows::Forms::ToolStripMenuItem^ landmarkToolStripMenuItem;
    System::Windows::Forms::ToolStripMenuItem^ orbitToolStripMenuItem;
    System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
    System::Windows::Forms::ToolStripMenuItem^ loadVideomp4ToolStripMenuItem;
    System::ComponentModel::IContainer^ components;

    System::ComponentModel::BackgroundWorker^ backgroundWorker1;

    SolidBrush^ m_blush_nocolor;
    Pen^ m_pen_nocolor;
    cli::array<SolidBrush^, 1> ^m_blushes;
    cli::array<Pen^, 1> ^m_pens;


    //singleton
    static FormMain^ m_singleton;
    FormMain(void);
  public:
    static FormMain^ getInst()
    {
      if (m_singleton == nullptr) m_singleton = gcnew FormMain();
      return m_singleton;
    }

  protected:
    ~FormMain()
    {
      if (components)
      {
        delete components;
      }
    }

  public:
    void RedrawPictureBox(){
      m_pictureBox->Invalidate();
      m_pictureBox->Update();
    }

    void RedrawSeekbarPictureBox() {
      m_seekbarPictureBox->Invalidate();
      m_seekbarPictureBox->Update();
    }

private:
    void DrawLandmarks (Graphics ^g, const int W, const int H);
    void DrawTrajectory(Graphics ^g, const int W, const int H);
    void UpdateSeekbarText();
    Bitmap^ GenerateBitmapFromFocusedVideo(int frame);

public:
    void SetSeekbarValue(const int val);
    int  GetSeekbarValue();

    void AddNewClips(const std::vector<int> &clip_start_ids, 
                     const std::vector<int> &clip_alignment_ids, 
                     const int clip_length);
    void ClearAllClips();
    System::Void AutoPlayFocusedClip(int clip_length);

    std::vector<EVec3i> GetSelectedClipInfo(); //(vid, startidx, cliplength)
    std::vector<int>    GetSelectedClipInfoAlignIdxs();

	private:

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      this->m_meshstrip = (gcnew System::Windows::Forms::MenuStrip());
      this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->loadVideomp4ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->viewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->landmarkToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->orbitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->m_pictureBox = (gcnew System::Windows::Forms::PictureBox());
      this->m_keyThumbImageList = (gcnew System::Windows::Forms::ImageList(this->components));
      this->m_listview_clips = (gcnew System::Windows::Forms::ListView());
      this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
      this->m_listview_loadvideo = (gcnew System::Windows::Forms::ListView());
      this->m_loadedVideoImageList = (gcnew System::Windows::Forms::ImageList(this->components));
      this->m_label1 = (gcnew System::Windows::Forms::Label());
      this->m_label2 = (gcnew System::Windows::Forms::Label());
      this->m_textbox_seekbar = (gcnew System::Windows::Forms::TextBox());
      this->m_seekbar = (gcnew System::Windows::Forms::TrackBar());
      this->m_seekbarPictureBox = (gcnew System::Windows::Forms::PictureBox());
      this->m_meshstrip->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_pictureBox))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_seekbar))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_seekbarPictureBox))->BeginInit();
      this->SuspendLayout();
      // 
      // m_meshstrip
      // 
      this->m_meshstrip->ImageScalingSize = System::Drawing::Size(20, 20);
      this->m_meshstrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
        this->fileToolStripMenuItem,
          this->viewToolStripMenuItem
      });
      this->m_meshstrip->Location = System::Drawing::Point(0, 0);
      this->m_meshstrip->Name = L"m_meshstrip";
      this->m_meshstrip->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
      this->m_meshstrip->Size = System::Drawing::Size(1067, 24);
      this->m_meshstrip->TabIndex = 0;
      this->m_meshstrip->Text = L"menuStrip1";
      // 
      // fileToolStripMenuItem
      // 
      this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->loadVideomp4ToolStripMenuItem });
      this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
      this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
      this->fileToolStripMenuItem->Text = L"File";
      this->fileToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::fIleToolStripMenuItem_Click);
      // 
      // loadVideomp4ToolStripMenuItem
      // 
      this->loadVideomp4ToolStripMenuItem->Name = L"loadVideomp4ToolStripMenuItem";
      this->loadVideomp4ToolStripMenuItem->Size = System::Drawing::Size(249, 22);
      this->loadVideomp4ToolStripMenuItem->Text = L"Load Video (mp4) and pose (.csv)";
      this->loadVideomp4ToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::loadVideomp4ToolStripMenuItem_Click);
      // 
      // viewToolStripMenuItem
      // 
      this->viewToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
        this->landmarkToolStripMenuItem,
          this->orbitToolStripMenuItem
      });
      this->viewToolStripMenuItem->Name = L"viewToolStripMenuItem";
      this->viewToolStripMenuItem->Size = System::Drawing::Size(44, 20);
      this->viewToolStripMenuItem->Text = L"View";
      // 
      // landmarkToolStripMenuItem
      // 
      this->landmarkToolStripMenuItem->Checked = true;
      this->landmarkToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
      this->landmarkToolStripMenuItem->Name = L"landmarkToolStripMenuItem";
      this->landmarkToolStripMenuItem->Size = System::Drawing::Size(126, 22);
      this->landmarkToolStripMenuItem->Text = L"Landmark";
      this->landmarkToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::landmarkToolStripMenuItem_Click);
      // 
      // orbitToolStripMenuItem
      // 
      this->orbitToolStripMenuItem->Checked = true;
      this->orbitToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
      this->orbitToolStripMenuItem->Name = L"orbitToolStripMenuItem";
      this->orbitToolStripMenuItem->Size = System::Drawing::Size(126, 22);
      this->orbitToolStripMenuItem->Text = L"Orbit";
      this->orbitToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::orbitToolStripMenuItem_Click);
      // 
      // m_pictureBox
      // 
      this->m_pictureBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
        | System::Windows::Forms::AnchorStyles::Left)
        | System::Windows::Forms::AnchorStyles::Right));
      this->m_pictureBox->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->m_pictureBox->Location = System::Drawing::Point(0, 25);
      this->m_pictureBox->Margin = System::Windows::Forms::Padding(2);
      this->m_pictureBox->Name = L"m_pictureBox";
      this->m_pictureBox->Size = System::Drawing::Size(665, 515);
      this->m_pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
      this->m_pictureBox->TabIndex = 1;
      this->m_pictureBox->TabStop = false;
      this->m_pictureBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FormMain::m_pictureBox_Paint);
      this->m_pictureBox->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &FormMain::m_pictureBox_MouseDown);
      this->m_pictureBox->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &FormMain::m_pictureBox_MouseMove);
      this->m_pictureBox->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &FormMain::m_pictureBox_MouseUp);
      // 
      // m_keyThumbImageList
      // 
      this->m_keyThumbImageList->ColorDepth = System::Windows::Forms::ColorDepth::Depth32Bit;
      this->m_keyThumbImageList->ImageSize = System::Drawing::Size(128, 86);
      this->m_keyThumbImageList->TransparentColor = System::Drawing::Color::Transparent;
      // 
      // m_listview_clips
      // 
      this->m_listview_clips->Activation = System::Windows::Forms::ItemActivation::TwoClick;
      this->m_listview_clips->Alignment = System::Windows::Forms::ListViewAlignment::Default;
      this->m_listview_clips->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
        | System::Windows::Forms::AnchorStyles::Right));
      this->m_listview_clips->Font = (gcnew System::Drawing::Font(L"メイリオ", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_listview_clips->GridLines = true;
      this->m_listview_clips->HideSelection = false;
      this->m_listview_clips->LargeImageList = this->m_keyThumbImageList;
      this->m_listview_clips->Location = System::Drawing::Point(669, 25);
      this->m_listview_clips->Margin = System::Windows::Forms::Padding(2);
      this->m_listview_clips->Name = L"m_listview_clips";
      this->m_listview_clips->Size = System::Drawing::Size(256, 515);
      this->m_listview_clips->SmallImageList = this->m_keyThumbImageList;
      this->m_listview_clips->TabIndex = 3;
      this->m_listview_clips->TileSize = System::Drawing::Size(150, 50);
      this->m_listview_clips->UseCompatibleStateImageBehavior = false;
      this->m_listview_clips->View = System::Windows::Forms::View::SmallIcon;
      this->m_listview_clips->SelectedIndexChanged += gcnew System::EventHandler(this, &FormMain::m_keyThumbListView_SelectedIndexChanged);
      this->m_listview_clips->Click += gcnew System::EventHandler(this, &FormMain::m_listview_clips_Clicked);
      // 
      // m_listview_loadvideo
      // 
      this->m_listview_loadvideo->Activation = System::Windows::Forms::ItemActivation::OneClick;
      this->m_listview_loadvideo->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
        | System::Windows::Forms::AnchorStyles::Right));
      this->m_listview_loadvideo->AutoArrange = false;
      this->m_listview_loadvideo->HideSelection = false;
      this->m_listview_loadvideo->LargeImageList = this->m_loadedVideoImageList;
      this->m_listview_loadvideo->Location = System::Drawing::Point(930, 25);
      this->m_listview_loadvideo->Name = L"m_listview_loadvideo";
      this->m_listview_loadvideo->Size = System::Drawing::Size(131, 515);
      this->m_listview_loadvideo->SmallImageList = this->m_loadedVideoImageList;
      this->m_listview_loadvideo->TabIndex = 4;
      this->m_listview_loadvideo->TileSize = System::Drawing::Size(256, 196);
      this->m_listview_loadvideo->UseCompatibleStateImageBehavior = false;
      this->m_listview_loadvideo->View = System::Windows::Forms::View::Tile;
      this->m_listview_loadvideo->Click += gcnew System::EventHandler(this, &FormMain::m_listview_loadedvideos_Clicked);
      // 
      // m_loadedVideoImageList
      // 
      this->m_loadedVideoImageList->ColorDepth = System::Windows::Forms::ColorDepth::Depth32Bit;
      this->m_loadedVideoImageList->ImageSize = System::Drawing::Size(80, 60);
      this->m_loadedVideoImageList->TransparentColor = System::Drawing::Color::Transparent;
      // 
      // m_label1
      // 
      this->m_label1->AutoSize = true;
      this->m_label1->Location = System::Drawing::Point(667, 6);
      this->m_label1->Name = L"m_label1";
      this->m_label1->Size = System::Drawing::Size(61, 12);
      this->m_label1->TabIndex = 5;
      this->m_label1->Text = L"found clips";
      // 
      // m_label2
      // 
      this->m_label2->AutoSize = true;
      this->m_label2->Location = System::Drawing::Point(947, 6);
      this->m_label2->Name = L"m_label2";
      this->m_label2->Size = System::Drawing::Size(75, 12);
      this->m_label2->TabIndex = 6;
      this->m_label2->Text = L"loaded videos";
      // 
      // m_textbox_seekbar
      // 
      this->m_textbox_seekbar->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
      this->m_textbox_seekbar->Font = (gcnew System::Drawing::Font(L"メイリオ", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(128)));
      this->m_textbox_seekbar->Location = System::Drawing::Point(0, 545);
      this->m_textbox_seekbar->Multiline = true;
      this->m_textbox_seekbar->Name = L"m_textbox_seekbar";
      this->m_textbox_seekbar->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
      this->m_textbox_seekbar->Size = System::Drawing::Size(147, 52);
      this->m_textbox_seekbar->TabIndex = 7;
      this->m_textbox_seekbar->Text = L"54476/54476\r\n30:17/30:17";
      // 
      // m_seekbar
      // 
      this->m_seekbar->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
        | System::Windows::Forms::AnchorStyles::Right));
      this->m_seekbar->Location = System::Drawing::Point(153, 551);
      this->m_seekbar->Name = L"m_seekbar";
      this->m_seekbar->Size = System::Drawing::Size(902, 45);
      this->m_seekbar->TabIndex = 8;
      this->m_seekbar->TickStyle = System::Windows::Forms::TickStyle::None;
      this->m_seekbar->Scroll += gcnew System::EventHandler(this, &FormMain::m_seekbar_Scroll);
      // 
      // m_seekbarPictureBox
      // 
      this->m_seekbarPictureBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
        | System::Windows::Forms::AnchorStyles::Right));
      this->m_seekbarPictureBox->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->m_seekbarPictureBox->Location = System::Drawing::Point(161, 574);
      this->m_seekbarPictureBox->Name = L"m_seekbarPictureBox";
      this->m_seekbarPictureBox->Size = System::Drawing::Size(886, 15);
      this->m_seekbarPictureBox->TabIndex = 9;
      this->m_seekbarPictureBox->TabStop = false;
      this->m_seekbarPictureBox->SizeChanged += gcnew System::EventHandler(this, &FormMain::m_seekbarPictureBox_SizeChanged);
      this->m_seekbarPictureBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FormMain::m_seekbarPictureBox_Paint);
      // 
      // FormMain
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(1067, 608);
      this->Controls->Add(this->m_textbox_seekbar);
      this->Controls->Add(this->m_label2);
      this->Controls->Add(this->m_label1);
      this->Controls->Add(this->m_listview_loadvideo);
      this->Controls->Add(this->m_listview_clips);
      this->Controls->Add(this->m_pictureBox);
      this->Controls->Add(this->m_meshstrip);
      this->Controls->Add(this->m_seekbarPictureBox);
      this->Controls->Add(this->m_seekbar);
      this->MainMenuStrip = this->m_meshstrip;
      this->Margin = System::Windows::Forms::Padding(2);
      this->Name = L"FormMain";
      this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
      this->Text = L"FormMain";
      this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FormMain::FormMain_Paint);
      this->m_meshstrip->ResumeLayout(false);
      this->m_meshstrip->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_pictureBox))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_seekbar))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_seekbarPictureBox))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  private: System::Void loadVideomp4ToolStripMenuItem_Click   (System::Object^  sender, System::EventArgs^  e); 
  private: System::Void FormMain_Paint        (System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e){}
  private: System::Void m_pictureBox_Paint    (System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
  private: System::Void m_pictureBox_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
  private: System::Void m_pictureBox_MouseUp  (System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e){}
  private: System::Void m_pictureBox_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e){}
  private: System::Void m_seekbar_Scroll(System::Object^ sender, System::EventArgs^ e);
  private: System::Void m_listview_clips_Clicked       (System::Object^  sender, System::EventArgs^  e);
  private: System::Void m_listview_loadedvideos_Clicked(System::Object^  sender, System::EventArgs^  e);
  private: System::Void fIleToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {}
  private: System::Void m_keyThumbListView_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {}
  private: System::Void m_seekbarPictureBox_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
  private: System::Void m_seekbarPictureBox_SizeChanged(System::Object^  sender, System::EventArgs^  e);
  private: System::Void landmarkToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void orbitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
};
}
