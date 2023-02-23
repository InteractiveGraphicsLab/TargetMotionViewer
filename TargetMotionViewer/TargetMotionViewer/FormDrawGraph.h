#include "../3rdparty/tmath.h"
#include "../3rdparty/videoloader.h"
#include <vector>

#pragma once

namespace TargetMotionViewer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// FormDrawGraph の概要
	/// </summary>
	public ref class FormDrawGraph : public System::Windows::Forms::Form
	{

    //グラフ描写はsingletonにせずgetInstするたびに新しいグラフを生成したい
    static FormDrawGraph^ m_singleton;
  public:
    static FormDrawGraph^ getInst() {
      if (m_singleton == nullptr) {
        m_singleton = gcnew FormDrawGraph();
      }
      return m_singleton;
    }
  public:
    FormDrawGraph(void);

    void SetDiffSequence(const std::vector<float> &diff_sequence, const float thresh);

    void SetPoseSequence( const int img_width, 
                          const int img_height, 
                          const std::vector<std::vector<EVec3f>> &points) ;

		std::vector<int> GetCheckedLandmarks();
	private:
		void UpdateChartColor();


	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~FormDrawGraph()
		{
			if (components)
			{
				delete components;
			}
		}

  private: System::Windows::Forms::DataVisualization::Charting::Chart^  m_chart_diff ;
  private: System::Windows::Forms::DataVisualization::Charting::Chart^  m_chart_orbit;
  private: System::Windows::Forms::CheckedListBox^    m_checkedListBox;
  private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
  private: System::Windows::Forms::DataVisualization::Charting::Chart^  m_debug_chart;

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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series7 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series8 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series9 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series10 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series11 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series12 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series13 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series14 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series15 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series16 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->m_chart_diff = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->m_chart_orbit = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->m_checkedListBox = (gcnew System::Windows::Forms::CheckedListBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->m_debug_chart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_chart_diff))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_chart_orbit))->BeginInit();
			this->tableLayoutPanel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_debug_chart))->BeginInit();
			this->SuspendLayout();
			// 
			// m_chart_diff
			// 
			this->m_chart_diff->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			chartArea1->AlignmentStyle = System::Windows::Forms::DataVisualization::Charting::AreaAlignmentStyles::Cursor;
			chartArea1->AxisX->Maximum = 0;
			chartArea1->AxisX->Minimum = 0;
			chartArea1->AxisX->Title = L"frame";
			chartArea1->AxisY->Title = L"pix";
			chartArea1->Name = L"m_ThreshChartArea";
			this->m_chart_diff->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->m_chart_diff->Legends->Add(legend1);
			this->m_chart_diff->Location = System::Drawing::Point(3, 3);
			this->m_chart_diff->Name = L"m_chart_diff";
			series1->ChartArea = L"m_ThreshChartArea";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series1->Legend = L"Legend1";
			series1->Name = L"Distance(pix)";
			series2->BorderWidth = 2;
			series2->ChartArea = L"m_ThreshChartArea";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series2->Legend = L"Legend1";
			series2->Name = L"Thresh(pix)";
			this->m_chart_diff->Series->Add(series1);
			this->m_chart_diff->Series->Add(series2);
			this->m_chart_diff->Size = System::Drawing::Size(640, 290);
			this->m_chart_diff->TabIndex = 0;
			this->m_chart_diff->Text = L"m_threshChart";
			// 
			// m_chart_orbit
			// 
			this->m_chart_orbit->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			chartArea2->AxisX->Minimum = 0;
			chartArea2->AxisY->IsReversed = true;
			chartArea2->AxisY->Minimum = 0;
			chartArea2->Name = L"OrbitChartArea";
			this->m_chart_orbit->ChartAreas->Add(chartArea2);
			legend2->Enabled = false;
			legend2->Name = L"Legend1";
			this->m_chart_orbit->Legends->Add(legend2);
			this->m_chart_orbit->Location = System::Drawing::Point(649, 3);
			this->m_chart_orbit->Name = L"m_chart_orbit";
			this->m_chart_orbit->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::None;
			series3->BorderWidth = 3;
			series3->ChartArea = L"OrbitChartArea";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series3->Legend = L"Legend1";
			series3->MarkerSize = 6;
			series3->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series3->Name = L"landmark00";
			series4->BorderWidth = 3;
			series4->ChartArea = L"OrbitChartArea";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series4->Legend = L"Legend1";
			series4->MarkerSize = 6;
			series4->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series4->Name = L"landmark01";
			series5->BorderWidth = 3;
			series5->ChartArea = L"OrbitChartArea";
			series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series5->Legend = L"Legend1";
			series5->MarkerSize = 6;
			series5->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series5->Name = L"landmark02";
			series6->BorderWidth = 3;
			series6->ChartArea = L"OrbitChartArea";
			series6->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series6->Legend = L"Legend1";
			series6->MarkerSize = 6;
			series6->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series6->Name = L"landmark03";
			series7->BorderWidth = 3;
			series7->ChartArea = L"OrbitChartArea";
			series7->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series7->Legend = L"Legend1";
			series7->MarkerSize = 6;
			series7->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series7->Name = L"landmark04";
			series8->BorderWidth = 3;
			series8->ChartArea = L"OrbitChartArea";
			series8->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series8->Legend = L"Legend1";
			series8->MarkerSize = 6;
			series8->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series8->Name = L"landmark05";
			series9->BorderWidth = 3;
			series9->ChartArea = L"OrbitChartArea";
			series9->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series9->Legend = L"Legend1";
			series9->MarkerSize = 6;
			series9->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series9->Name = L"landmark06";
			series10->BorderWidth = 3;
			series10->ChartArea = L"OrbitChartArea";
			series10->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series10->Legend = L"Legend1";
			series10->MarkerSize = 6;
			series10->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series10->Name = L"landmark07";
			series11->BorderWidth = 3;
			series11->ChartArea = L"OrbitChartArea";
			series11->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series11->Legend = L"Legend1";
			series11->MarkerSize = 6;
			series11->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series11->Name = L"landmark08";
			series12->BorderWidth = 3;
			series12->ChartArea = L"OrbitChartArea";
			series12->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series12->Legend = L"Legend1";
			series12->MarkerSize = 6;
			series12->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series12->Name = L"landmark09";
			series13->BorderWidth = 3;
			series13->ChartArea = L"OrbitChartArea";
			series13->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series13->Legend = L"Legend1";
			series13->MarkerSize = 6;
			series13->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series13->Name = L"landmark10";
			series14->BorderWidth = 3;
			series14->ChartArea = L"OrbitChartArea";
			series14->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series14->Legend = L"Legend1";
			series14->MarkerSize = 6;
			series14->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series14->Name = L"landmark11";
			series15->ChartArea = L"OrbitChartArea";
			series15->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series15->Legend = L"Legend1";
			series15->MarkerSize = 6;
			series15->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series15->Name = L"landmark12";
			this->m_chart_orbit->Series->Add(series3);
			this->m_chart_orbit->Series->Add(series4);
			this->m_chart_orbit->Series->Add(series5);
			this->m_chart_orbit->Series->Add(series6);
			this->m_chart_orbit->Series->Add(series7);
			this->m_chart_orbit->Series->Add(series8);
			this->m_chart_orbit->Series->Add(series9);
			this->m_chart_orbit->Series->Add(series10);
			this->m_chart_orbit->Series->Add(series11);
			this->m_chart_orbit->Series->Add(series12);
			this->m_chart_orbit->Series->Add(series13);
			this->m_chart_orbit->Series->Add(series14);
			this->m_chart_orbit->Series->Add(series15);
			this->m_chart_orbit->Size = System::Drawing::Size(619, 290);
			this->m_chart_orbit->TabIndex = 2;
			this->m_chart_orbit->Text = L"chart2";
			// 
			// m_checkedListBox
			// 
			this->m_checkedListBox->CheckOnClick = true;
			this->m_checkedListBox->FormattingEnabled = true;
			this->m_checkedListBox->Items->AddRange(gcnew cli::array< System::Object^  >(13) {
				L"NOSE", L"L_SHOR", L"R_SHOR", L"L_ELBO",
					L"R_ELBO", L"L_WRIS", L"R_WRIS", L"L_HIP", L"R_HIP", L"L_KNEE", L"R_KNEE", L"L_ANKL", L"R_ANKL"
			});
			this->m_checkedListBox->Location = System::Drawing::Point(1274, 3);
			this->m_checkedListBox->Name = L"m_checkedListBox";
			this->m_checkedListBox->Size = System::Drawing::Size(71, 284);
			this->m_checkedListBox->TabIndex = 3;
			this->m_checkedListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &FormDrawGraph::m_checkedListBoxChanged);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50.79765F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				49.20235F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				86)));
			this->tableLayoutPanel1->Controls->Add(this->m_chart_diff, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->m_checkedListBox, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->m_chart_orbit, 1, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(12, 12);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1358, 296);
			this->tableLayoutPanel1->TabIndex = 4;
			// 
			// m_debug_chart
			// 
			chartArea3->AxisX->Title = L"frame";
			chartArea3->AxisY->Title = L"pix";
			chartArea3->Name = L"m_ThreshChartArea";
			this->m_debug_chart->ChartAreas->Add(chartArea3);
			legend3->Name = L"Legend1";
			this->m_debug_chart->Legends->Add(legend3);
			this->m_debug_chart->Location = System::Drawing::Point(15, 388);
			this->m_debug_chart->Name = L"m_debug_chart";
			series16->ChartArea = L"m_ThreshChartArea";
			series16->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series16->Legend = L"Legend1";
			series16->Name = L"Distance(pix)";
			this->m_debug_chart->Series->Add(series16);
			this->m_debug_chart->Size = System::Drawing::Size(606, 238);
			this->m_debug_chart->TabIndex = 4;
			this->m_debug_chart->Text = L"m_threshChart";
			this->m_debug_chart->Visible = false;
			// 
			// FormDrawGraph
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1382, 309);
			this->Controls->Add(this->m_debug_chart);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Location = System::Drawing::Point(0, 650);
			this->Name = L"FormDrawGraph";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"FormDrawGraph";
			this->Load += gcnew System::EventHandler(this, &FormDrawGraph::FormDrawGraph_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_chart_diff))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_chart_orbit))->EndInit();
			this->tableLayoutPanel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->m_debug_chart))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

  private: System::Void m_checkedListBoxChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void FormDrawGraph_Load(System::Object^  sender, System::EventArgs^  e) {
}
};
}
