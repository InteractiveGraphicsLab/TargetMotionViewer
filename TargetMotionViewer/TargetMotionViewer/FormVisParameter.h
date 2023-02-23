#pragma once

namespace TargetMotionViewer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class FormVisParameter : public System::Windows::Forms::Form
	{

    static FormVisParameter^ m_singleton;
		FormVisParameter(void);
	public:

    static FormVisParameter^ getInst(){
      if( m_singleton == nullptr ) m_singleton = gcnew FormVisParameter();
      return m_singleton;
    }

	protected:
		~FormVisParameter()
		{
			if (components)
			{
				delete components;
			}
		}


  private: System::Windows::Forms::Label^  m_label1;
  private: System::Windows::Forms::Label^  m_label2;
  private: System::Windows::Forms::Label^  m_label3;
  private: System::Windows::Forms::Label^  m_label4;
  private: System::Windows::Forms::Label^  m_label5;
  private: System::Windows::Forms::Label^  m_label6;
  private: System::Windows::Forms::Label^  m_label7;
  private: System::Windows::Forms::Label^  m_label8;

  private: System::Windows::Forms::Label^  m_label_winsizeval;
  private: System::Windows::Forms::Label^  m_label_threshval;
  private: System::Windows::Forms::Label^  m_label_marginval;

  private: System::Windows::Forms::TextBox^  m_textbox_startidx;
  private: System::Windows::Forms::TextBox^  m_textbox_endidx;
  private: System::Windows::Forms::TextBox^  m_textbox_alignmentidx;


  private: System::Windows::Forms::TrackBar^  m_trackbar_threshold;
  private: System::Windows::Forms::TrackBar^  m_trackbar_winsize;
  private: System::Windows::Forms::TrackBar^  m_trackbar_export_margin;

  private: System::Windows::Forms::Button^  m_button_set_startidx;
  private: System::Windows::Forms::Button^  m_button_set_endidx;
  private: System::Windows::Forms::Button^  m_button_set_alignmentidx;
  private: System::Windows::Forms::Button^  m_button_medianfilter;
  private: System::Windows::Forms::Button^  m_button_gaussianfilter;
  private: System::Windows::Forms::Button^  m_button_searchclips;
  private: System::Windows::Forms::Button^  m_button_exportallclips;
  private: System::Windows::Forms::Button^  m_button_exportoverlayclips;
  private: System::Windows::Forms::Button^  m_button_clearfoundclips;
  private: System::Windows::Forms::Button^  m_button_exportclip_poses;
  private: System::Windows::Forms::Button^  m_button_export_thumbnail_poses;


	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
      this->m_label1 = (gcnew System::Windows::Forms::Label());
      this->m_label6 = (gcnew System::Windows::Forms::Label());
      this->m_label7 = (gcnew System::Windows::Forms::Label());
      this->m_textbox_startidx = (gcnew System::Windows::Forms::TextBox());
      this->m_textbox_endidx = (gcnew System::Windows::Forms::TextBox());
      this->m_button_set_startidx = (gcnew System::Windows::Forms::Button());
      this->m_button_set_endidx = (gcnew System::Windows::Forms::Button());
      this->m_button_medianfilter = (gcnew System::Windows::Forms::Button());
      this->m_button_gaussianfilter = (gcnew System::Windows::Forms::Button());
      this->m_button_searchclips = (gcnew System::Windows::Forms::Button());
      this->m_trackbar_winsize = (gcnew System::Windows::Forms::TrackBar());
      this->m_trackbar_threshold = (gcnew System::Windows::Forms::TrackBar());
      this->m_label3 = (gcnew System::Windows::Forms::Label());
      this->m_label2 = (gcnew System::Windows::Forms::Label());
      this->m_label_winsizeval = (gcnew System::Windows::Forms::Label());
      this->m_label_threshval = (gcnew System::Windows::Forms::Label());
      this->m_button_clearfoundclips = (gcnew System::Windows::Forms::Button());
      this->m_button_exportallclips = (gcnew System::Windows::Forms::Button());
      this->m_button_exportoverlayclips = (gcnew System::Windows::Forms::Button());
      this->m_label4 = (gcnew System::Windows::Forms::Label());
      this->m_label_marginval = (gcnew System::Windows::Forms::Label());
      this->m_label5 = (gcnew System::Windows::Forms::Label());
      this->m_trackbar_export_margin = (gcnew System::Windows::Forms::TrackBar());
      this->m_button_exportclip_poses = (gcnew System::Windows::Forms::Button());
      this->m_button_export_thumbnail_poses = (gcnew System::Windows::Forms::Button());
      this->m_label8 = (gcnew System::Windows::Forms::Label());
      this->m_textbox_alignmentidx = (gcnew System::Windows::Forms::TextBox());
      this->m_button_set_alignmentidx = (gcnew System::Windows::Forms::Button());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_trackbar_winsize))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_trackbar_threshold))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_trackbar_export_margin))->BeginInit();
      this->SuspendLayout();
      // 
      // m_label1
      // 
      this->m_label1->AutoSize = true;
      this->m_label1->Font = (gcnew System::Drawing::Font(L"游ゴシック", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_label1->Location = System::Drawing::Point(3, 3);
      this->m_label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->m_label1->Name = L"m_label1";
      this->m_label1->Size = System::Drawing::Size(82, 17);
      this->m_label1->TabIndex = 2;
      this->m_label1->Text = L"Search Clip";
      // 
      // m_label6
      // 
      this->m_label6->AutoSize = true;
      this->m_label6->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_label6->Location = System::Drawing::Point(43, 26);
      this->m_label6->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->m_label6->Name = L"m_label6";
      this->m_label6->Size = System::Drawing::Size(60, 20);
      this->m_label6->TabIndex = 3;
      this->m_label6->Text = L"start idx";
      // 
      // m_label7
      // 
      this->m_label7->AutoSize = true;
      this->m_label7->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_label7->Location = System::Drawing::Point(48, 59);
      this->m_label7->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->m_label7->Name = L"m_label7";
      this->m_label7->Size = System::Drawing::Size(55, 20);
      this->m_label7->TabIndex = 4;
      this->m_label7->Text = L"end idx";
      // 
      // m_textbox_startidx
      // 
      this->m_textbox_startidx->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_textbox_startidx->Location = System::Drawing::Point(107, 24);
      this->m_textbox_startidx->Margin = System::Windows::Forms::Padding(2);
      this->m_textbox_startidx->Name = L"m_textbox_startidx";
      this->m_textbox_startidx->Size = System::Drawing::Size(60, 27);
      this->m_textbox_startidx->TabIndex = 5;
      // 
      // m_textbox_endidx
      // 
      this->m_textbox_endidx->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_textbox_endidx->Location = System::Drawing::Point(107, 56);
      this->m_textbox_endidx->Margin = System::Windows::Forms::Padding(2);
      this->m_textbox_endidx->Name = L"m_textbox_endidx";
      this->m_textbox_endidx->Size = System::Drawing::Size(60, 27);
      this->m_textbox_endidx->TabIndex = 6;
      // 
      // m_button_set_startidx
      // 
      this->m_button_set_startidx->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_button_set_startidx->Location = System::Drawing::Point(171, 23);
      this->m_button_set_startidx->Margin = System::Windows::Forms::Padding(2);
      this->m_button_set_startidx->Name = L"m_button_set_startidx";
      this->m_button_set_startidx->Size = System::Drawing::Size(123, 29);
      this->m_button_set_startidx->TabIndex = 7;
      this->m_button_set_startidx->Text = L"Set Idx";
      this->m_button_set_startidx->UseVisualStyleBackColor = true;
      this->m_button_set_startidx->Click += gcnew System::EventHandler(this, &FormVisParameter::m_button_set_startidx_Click);
      // 
      // m_button_set_endidx
      // 
      this->m_button_set_endidx->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_button_set_endidx->Location = System::Drawing::Point(171, 56);
      this->m_button_set_endidx->Margin = System::Windows::Forms::Padding(2);
      this->m_button_set_endidx->Name = L"m_button_set_endidx";
      this->m_button_set_endidx->Size = System::Drawing::Size(123, 27);
      this->m_button_set_endidx->TabIndex = 8;
      this->m_button_set_endidx->Text = L"Set Idx";
      this->m_button_set_endidx->UseVisualStyleBackColor = true;
      this->m_button_set_endidx->Click += gcnew System::EventHandler(this, &FormVisParameter::m_button_set_endidx_Click);
      // 
      // m_button_medianfilter
      // 
      this->m_button_medianfilter->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_button_medianfilter->Location = System::Drawing::Point(14, 568);
      this->m_button_medianfilter->Margin = System::Windows::Forms::Padding(2);
      this->m_button_medianfilter->Name = L"m_button_medianfilter";
      this->m_button_medianfilter->Size = System::Drawing::Size(106, 29);
      this->m_button_medianfilter->TabIndex = 10;
      this->m_button_medianfilter->Text = L"Median Filter";
      this->m_button_medianfilter->UseVisualStyleBackColor = true;
      this->m_button_medianfilter->Click += gcnew System::EventHandler(this, &FormVisParameter::m_button_medianfilter_Click);
      // 
      // m_button_gaussianfilter
      // 
      this->m_button_gaussianfilter->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_button_gaussianfilter->Location = System::Drawing::Point(124, 568);
      this->m_button_gaussianfilter->Margin = System::Windows::Forms::Padding(2);
      this->m_button_gaussianfilter->Name = L"m_button_gaussianfilter";
      this->m_button_gaussianfilter->Size = System::Drawing::Size(127, 29);
      this->m_button_gaussianfilter->TabIndex = 11;
      this->m_button_gaussianfilter->Text = L"Gaussian Filter";
      this->m_button_gaussianfilter->UseVisualStyleBackColor = true;
      this->m_button_gaussianfilter->Click += gcnew System::EventHandler(this, &FormVisParameter::m_button_gaussianfilter_Click);
      // 
      // m_button_searchclips
      // 
      this->m_button_searchclips->Font = (gcnew System::Drawing::Font(L"メイリオ", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_button_searchclips->Location = System::Drawing::Point(12, 242);
      this->m_button_searchclips->Margin = System::Windows::Forms::Padding(2);
      this->m_button_searchclips->Name = L"m_button_searchclips";
      this->m_button_searchclips->Size = System::Drawing::Size(273, 35);
      this->m_button_searchclips->TabIndex = 16;
      this->m_button_searchclips->Text = L"Search All Clips";
      this->m_button_searchclips->UseVisualStyleBackColor = true;
      this->m_button_searchclips->Click += gcnew System::EventHandler(this, &FormVisParameter::m_button_searchclips_Click);
      // 
      // m_trackbar_winsize
      // 
      this->m_trackbar_winsize->Location = System::Drawing::Point(12, 206);
      this->m_trackbar_winsize->Maximum = 1000;
      this->m_trackbar_winsize->Name = L"m_trackbar_winsize";
      this->m_trackbar_winsize->Size = System::Drawing::Size(186, 45);
      this->m_trackbar_winsize->TabIndex = 18;
      this->m_trackbar_winsize->TickFrequency = 100;
      this->m_trackbar_winsize->TickStyle = System::Windows::Forms::TickStyle::None;
      this->m_trackbar_winsize->Value = 100;
      this->m_trackbar_winsize->Scroll += gcnew System::EventHandler(this, &FormVisParameter::m_trackbar_winsize_scroll);
      // 
      // m_trackbar_threshold
      // 
      this->m_trackbar_threshold->Location = System::Drawing::Point(12, 155);
      this->m_trackbar_threshold->Maximum = 200;
      this->m_trackbar_threshold->Name = L"m_trackbar_threshold";
      this->m_trackbar_threshold->Size = System::Drawing::Size(186, 45);
      this->m_trackbar_threshold->SmallChange = 2;
      this->m_trackbar_threshold->TabIndex = 19;
      this->m_trackbar_threshold->TickFrequency = 20;
      this->m_trackbar_threshold->TickStyle = System::Windows::Forms::TickStyle::None;
      this->m_trackbar_threshold->Value = 50;
      this->m_trackbar_threshold->Scroll += gcnew System::EventHandler(this, &FormVisParameter::m_trackbar_threshold_scroll);
      this->m_trackbar_threshold->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &FormVisParameter::m_trackbar_threshold_mouseUp);
      // 
      // m_label3
      // 
      this->m_label3->AutoSize = true;
      this->m_label3->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_label3->Location = System::Drawing::Point(11, 187);
      this->m_label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->m_label3->Name = L"m_label3";
      this->m_label3->Size = System::Drawing::Size(182, 20);
      this->m_label3->TabIndex = 20;
      this->m_label3->Text = L"Local min win size [frames]";
      // 
      // m_label2
      // 
      this->m_label2->AutoSize = true;
      this->m_label2->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_label2->Location = System::Drawing::Point(11, 135);
      this->m_label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->m_label2->Name = L"m_label2";
      this->m_label2->Size = System::Drawing::Size(148, 20);
      this->m_label2->TabIndex = 21;
      this->m_label2->Text = L"search threshold [pix]";
      // 
      // m_label_winsizeval
      // 
      this->m_label_winsizeval->AutoSize = true;
      this->m_label_winsizeval->Font = (gcnew System::Drawing::Font(L"メイリオ", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_label_winsizeval->Location = System::Drawing::Point(203, 206);
      this->m_label_winsizeval->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->m_label_winsizeval->Name = L"m_label_winsizeval";
      this->m_label_winsizeval->Size = System::Drawing::Size(37, 21);
      this->m_label_winsizeval->TabIndex = 22;
      this->m_label_winsizeval->Text = L"100";
      // 
      // m_label_threshval
      // 
      this->m_label_threshval->AutoSize = true;
      this->m_label_threshval->Font = (gcnew System::Drawing::Font(L"メイリオ", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_label_threshval->Location = System::Drawing::Point(203, 155);
      this->m_label_threshval->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->m_label_threshval->Name = L"m_label_threshval";
      this->m_label_threshval->Size = System::Drawing::Size(28, 21);
      this->m_label_threshval->TabIndex = 23;
      this->m_label_threshval->Text = L"50";
      // 
      // m_button_clearfoundclips
      // 
      this->m_button_clearfoundclips->Font = (gcnew System::Drawing::Font(L"メイリオ", 10.2F));
      this->m_button_clearfoundclips->Location = System::Drawing::Point(140, 280);
      this->m_button_clearfoundclips->Margin = System::Windows::Forms::Padding(2);
      this->m_button_clearfoundclips->Name = L"m_button_clearfoundclips";
      this->m_button_clearfoundclips->Size = System::Drawing::Size(145, 29);
      this->m_button_clearfoundclips->TabIndex = 24;
      this->m_button_clearfoundclips->Text = L"Clear Found Clips";
      this->m_button_clearfoundclips->UseVisualStyleBackColor = true;
      this->m_button_clearfoundclips->Click += gcnew System::EventHandler(this, &FormVisParameter::m_button_clearfoundclips_Click);
      // 
      // m_button_exportallclips
      // 
      this->m_button_exportallclips->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_button_exportallclips->Location = System::Drawing::Point(23, 360);
      this->m_button_exportallclips->Margin = System::Windows::Forms::Padding(2);
      this->m_button_exportallclips->Name = L"m_button_exportallclips";
      this->m_button_exportallclips->Size = System::Drawing::Size(208, 29);
      this->m_button_exportallclips->TabIndex = 25;
      this->m_button_exportallclips->Text = L"export clips";
      this->m_button_exportallclips->UseVisualStyleBackColor = true;
      this->m_button_exportallclips->Click += gcnew System::EventHandler(this, &FormVisParameter::m_button_exportallclips_Click);
      // 
      // m_button_exportoverlayclips
      // 
      this->m_button_exportoverlayclips->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_button_exportoverlayclips->Location = System::Drawing::Point(23, 393);
      this->m_button_exportoverlayclips->Margin = System::Windows::Forms::Padding(2);
      this->m_button_exportoverlayclips->Name = L"m_button_exportoverlayclips";
      this->m_button_exportoverlayclips->Size = System::Drawing::Size(208, 29);
      this->m_button_exportoverlayclips->TabIndex = 31;
      this->m_button_exportoverlayclips->Text = L"export overlayed clips";
      this->m_button_exportoverlayclips->UseVisualStyleBackColor = true;
      this->m_button_exportoverlayclips->Click += gcnew System::EventHandler(this, &FormVisParameter::m_button_exportoverlayclips_Click);
      // 
      // m_label4
      // 
      this->m_label4->AutoSize = true;
      this->m_label4->Font = (gcnew System::Drawing::Font(L"游ゴシック", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_label4->Location = System::Drawing::Point(11, 339);
      this->m_label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->m_label4->Name = L"m_label4";
      this->m_label4->Size = System::Drawing::Size(250, 17);
      this->m_label4->TabIndex = 32;
      this->m_label4->Text = L"Export clips (選択されたclipの書き出し)";
      // 
      // m_label_marginval
      // 
      this->m_label_marginval->AutoSize = true;
      this->m_label_marginval->Font = (gcnew System::Drawing::Font(L"メイリオ", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_label_marginval->Location = System::Drawing::Point(214, 513);
      this->m_label_marginval->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->m_label_marginval->Name = L"m_label_marginval";
      this->m_label_marginval->Size = System::Drawing::Size(37, 21);
      this->m_label_marginval->TabIndex = 35;
      this->m_label_marginval->Text = L"100";
      // 
      // m_label5
      // 
      this->m_label5->AutoSize = true;
      this->m_label5->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_label5->Location = System::Drawing::Point(22, 494);
      this->m_label5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->m_label5->Name = L"m_label5";
      this->m_label5->Size = System::Drawing::Size(174, 20);
      this->m_label5->TabIndex = 34;
      this->m_label5->Text = L"margine frames for export";
      // 
      // m_trackbar_export_margin
      // 
      this->m_trackbar_export_margin->Location = System::Drawing::Point(23, 513);
      this->m_trackbar_export_margin->Maximum = 1000;
      this->m_trackbar_export_margin->Name = L"m_trackbar_export_margin";
      this->m_trackbar_export_margin->Size = System::Drawing::Size(186, 45);
      this->m_trackbar_export_margin->TabIndex = 33;
      this->m_trackbar_export_margin->TickFrequency = 100;
      this->m_trackbar_export_margin->TickStyle = System::Windows::Forms::TickStyle::None;
      this->m_trackbar_export_margin->Value = 100;
      this->m_trackbar_export_margin->Scroll += gcnew System::EventHandler(this, &FormVisParameter::m_trackbar_export_margin_Scroll);
      // 
      // m_button_exportclip_poses
      // 
      this->m_button_exportclip_poses->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_button_exportclip_poses->Location = System::Drawing::Point(23, 426);
      this->m_button_exportclip_poses->Margin = System::Windows::Forms::Padding(2);
      this->m_button_exportclip_poses->Name = L"m_button_exportclip_poses";
      this->m_button_exportclip_poses->Size = System::Drawing::Size(208, 29);
      this->m_button_exportclip_poses->TabIndex = 36;
      this->m_button_exportclip_poses->Text = L"export poses of clips (csv)";
      this->m_button_exportclip_poses->UseVisualStyleBackColor = true;
      this->m_button_exportclip_poses->Click += gcnew System::EventHandler(this, &FormVisParameter::m_button_exportclip_poses_Click);
      // 
      // m_button_export_thumbnail_poses
      // 
      this->m_button_export_thumbnail_poses->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_button_export_thumbnail_poses->Location = System::Drawing::Point(23, 459);
      this->m_button_export_thumbnail_poses->Margin = System::Windows::Forms::Padding(2);
      this->m_button_export_thumbnail_poses->Name = L"m_button_export_thumbnail_poses";
      this->m_button_export_thumbnail_poses->Size = System::Drawing::Size(208, 29);
      this->m_button_export_thumbnail_poses->TabIndex = 37;
      this->m_button_export_thumbnail_poses->Text = L"export thumbnail poses (csv)";
      this->m_button_export_thumbnail_poses->UseVisualStyleBackColor = true;
      this->m_button_export_thumbnail_poses->Click += gcnew System::EventHandler(this, &FormVisParameter::m_button_export_thumbnail_poses_Click);
      // 
      // m_label8
      // 
      this->m_label8->AutoSize = true;
      this->m_label8->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_label8->Location = System::Drawing::Point(11, 92);
      this->m_label8->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->m_label8->Name = L"m_label8";
      this->m_label8->Size = System::Drawing::Size(94, 20);
      this->m_label8->TabIndex = 38;
      this->m_label8->Text = L"alignment idx";
      // 
      // m_textbox_alignmentidx
      // 
      this->m_textbox_alignmentidx->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_textbox_alignmentidx->Location = System::Drawing::Point(107, 87);
      this->m_textbox_alignmentidx->Margin = System::Windows::Forms::Padding(2);
      this->m_textbox_alignmentidx->Name = L"m_textbox_alignmentidx";
      this->m_textbox_alignmentidx->Size = System::Drawing::Size(60, 27);
      this->m_textbox_alignmentidx->TabIndex = 39;
      // 
      // m_button_set_alignmentidx
      // 
      this->m_button_set_alignmentidx->Font = (gcnew System::Drawing::Font(L"メイリオ", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->m_button_set_alignmentidx->Location = System::Drawing::Point(171, 87);
      this->m_button_set_alignmentidx->Margin = System::Windows::Forms::Padding(2);
      this->m_button_set_alignmentidx->Name = L"m_button_set_alignmentidx";
      this->m_button_set_alignmentidx->Size = System::Drawing::Size(123, 27);
      this->m_button_set_alignmentidx->TabIndex = 40;
      this->m_button_set_alignmentidx->Text = L"Set Idx";
      this->m_button_set_alignmentidx->UseVisualStyleBackColor = true;
      this->m_button_set_alignmentidx->Click += gcnew System::EventHandler(this, &FormVisParameter::m_button_set_alignmentidx_Click);
      // 
      // FormVisParameter
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(303, 606);
      this->Controls->Add(this->m_button_set_alignmentidx);
      this->Controls->Add(this->m_textbox_alignmentidx);
      this->Controls->Add(this->m_label8);
      this->Controls->Add(this->m_button_export_thumbnail_poses);
      this->Controls->Add(this->m_button_exportclip_poses);
      this->Controls->Add(this->m_label_marginval);
      this->Controls->Add(this->m_label5);
      this->Controls->Add(this->m_trackbar_export_margin);
      this->Controls->Add(this->m_label4);
      this->Controls->Add(this->m_button_searchclips);
      this->Controls->Add(this->m_button_exportoverlayclips);
      this->Controls->Add(this->m_button_exportallclips);
      this->Controls->Add(this->m_button_clearfoundclips);
      this->Controls->Add(this->m_label_threshval);
      this->Controls->Add(this->m_label_winsizeval);
      this->Controls->Add(this->m_label2);
      this->Controls->Add(this->m_label3);
      this->Controls->Add(this->m_trackbar_threshold);
      this->Controls->Add(this->m_trackbar_winsize);
      this->Controls->Add(this->m_button_gaussianfilter);
      this->Controls->Add(this->m_button_medianfilter);
      this->Controls->Add(this->m_button_set_endidx);
      this->Controls->Add(this->m_button_set_startidx);
      this->Controls->Add(this->m_textbox_endidx);
      this->Controls->Add(this->m_textbox_startidx);
      this->Controls->Add(this->m_label7);
      this->Controls->Add(this->m_label6);
      this->Controls->Add(this->m_label1);
      this->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(128)));
      this->Location = System::Drawing::Point(1100, 0);
      this->Margin = System::Windows::Forms::Padding(2);
      this->Name = L"FormVisParameter";
      this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
      this->Text = L"FormVisParameter";
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_trackbar_winsize))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_trackbar_threshold))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_trackbar_export_margin))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion

  private: System::Void m_trackbar_threshold_scroll      (System::Object^  sender, System::EventArgs^  e);
  private: System::Void m_trackbar_export_margin_Scroll  (System::Object^  sender, System::EventArgs^  e);
  private: System::Void m_trackbar_winsize_scroll        (System::Object^  sender, System::EventArgs^  e);
  private: System::Void m_button_set_startidx_Click      (System::Object^  sender, System::EventArgs^  e);
  private: System::Void m_button_set_endidx_Click        (System::Object^  sender, System::EventArgs^  e); 
  private: System::Void m_button_set_alignmentidx_Click  (System::Object^  sender, System::EventArgs^  e);
  private: System::Void m_button_gaussianfilter_Click    (System::Object^  sender, System::EventArgs^  e);
  private: System::Void m_button_medianfilter_Click      (System::Object^  sender, System::EventArgs^  e);
  private: System::Void m_button_searchclips_Click       (System::Object^  sender, System::EventArgs^  e);
  private: System::Void m_button_clearfoundclips_Click   (System::Object^  sender, System::EventArgs^  e);
  private: System::Void m_button_exportallclips_Click    (System::Object^  sender, System::EventArgs^  e);
  private: System::Void m_button_exportoverlayclips_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void m_button_exportclip_poses_Click  (System::Object^  sender, System::EventArgs^  e);
  private: System::Void m_button_export_thumbnail_poses_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void m_trackbar_threshold_mouseUp     (System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
};
}
