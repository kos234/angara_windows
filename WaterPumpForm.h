#pragma once

#include "utils.h"
#include "RealChartPoint.h"
#include "LocalizationManager.h"
#include <cliext/set>
#include <cliext/set>

namespace angarawindows {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для WaterPump
	/// </summary>
	public ref class WaterPumpForm : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::GroupBox^ groupBox9;
	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::Label^ label42;
	private: System::Windows::Forms::Label^ label43;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel7;
	public: System::Windows::Forms::TextBox^ pump_dim;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel8;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel9;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel10;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel11;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel12;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel13;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel14;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel15;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel16;

	public:
		WaterPumpForm() {
			InitializeComponent();
			setupChart(this->chart1, L"H("+ LocalizationManager::getStr("charts.m") +")", Color::FromArgb(2, 8, 88), Color::FromArgb(4, 10, 144), Color::FromArgb(7, 15, 203));
			setupChart(this->chart2, L"N("+ LocalizationManager::getStr("charts.kw") +")", Color::FromArgb(193, 143, 0), Color::FromArgb(218, 165, 32), Color::FromArgb(243, 187, 58));
			setupChart(this->chart3, L"η(%)", Color::FromArgb(30, 166, 61), Color::FromArgb(62, 188, 81), Color::FromArgb(88, 210, 101));
		
			this->tabPage1->Text = LocalizationManager::getStr("tabs.charts.hydraulic");
			this->tabPage2->Text = LocalizationManager::getStr("tabs.charts.power");
			this->tabPage3->Text = LocalizationManager::getStr("tabs.charts.efficiency");
			this->groupBox7->Text = LocalizationManager::getStr("charts.point_graph");
			this->label16->Text = LocalizationManager::getStr("charts.m3/h");
			this->label20->Text = LocalizationManager::getStr("charts.m");
			this->label24->Text = LocalizationManager::getStr("charts.m");
			this->label26->Text = LocalizationManager::getStr("tabs.charts.efficiency");
			this->label27->Text = LocalizationManager::getStr("charts.kw");
			this->groupBox6->Text = LocalizationManager::getStr("charts.coefficients");
			this->groupBox8->Text = LocalizationManager::getStr("charts.working_zone");
			this->label_q_min->Text = LocalizationManager::getStr("charts.qmin");
			this->label_q_max->Text = LocalizationManager::getStr("charts.qmax");
			this->button1->Text = LocalizationManager::getStr("button.cancel");
			this->button2->Text = LocalizationManager::getStr("button.save");
			this->tabPage4->Text = LocalizationManager::getStr("tabs.parameters.main");
			this->label1->Text = LocalizationManager::getStr("parameters.main.pump_name");
			this->label2->Text = LocalizationManager::getStr("parameters.main.pump_status");
			this->groupBox1->Text = LocalizationManager::getStr("parameters.main.nominal_parameters");
			this->label3->Text = LocalizationManager::getStr("parameters.main.nominal_parameters.mark");
			this->label4->Text = LocalizationManager::getStr("parameters.main.nominal_parameters.diameter");
			this->label5->Text = LocalizationManager::getStr("parameters.main.nominal_parameters.turnovers");
			this->label32->Text = LocalizationManager::getStr("parameters.main.dots_characteristics");
			this->label35->Text = LocalizationManager::getStr("parameters.main.dots_characteristics.consumption");
			this->label36->Text = LocalizationManager::getStr("parameters.main.dots_characteristics.pressure");
			this->label38->Text = LocalizationManager::getStr("parameters.main.dots_characteristics.efficiency");
			this->label37->Text = LocalizationManager::getStr("parameters.main.dots_characteristics.power");
			this->tabPage5->Text = LocalizationManager::getStr("tabs.parameters.limits");
			this->label42->Text = LocalizationManager::getStr("parameters.limits.mode_parameters");
			this->groupBox2->Text = LocalizationManager::getStr("parameters.limits.mode_parameters.capacity");
			this->label21->Text = LocalizationManager::getStr("parameters.limits.min");
			this->label22->Text = LocalizationManager::getStr("parameters.limits.max");
			this->label40->Text = LocalizationManager::getStr("parameters.limits.work_point");
			this->groupBox3->Text = LocalizationManager::getStr("parameters.limits.mode_parameters.inlet_pressure");
			this->label6->Text = LocalizationManager::getStr("parameters.limits.min");
			this->label7->Text = LocalizationManager::getStr("parameters.limits.max");
			this->label39->Text = LocalizationManager::getStr("parameters.limits.work_point");
			this->groupBox9->Text = LocalizationManager::getStr("parameters.limits.mode_parameters.outlet_pressure");
			this->label14->Text = LocalizationManager::getStr("parameters.limits.min");
			this->label30->Text = LocalizationManager::getStr("parameters.limits.max");
			this->label41->Text = LocalizationManager::getStr("parameters.limits.work_point");
			this->label43->Text = LocalizationManager::getStr("parameters.limits.control_parameters");
			this->groupBox5->Text = LocalizationManager::getStr("parameters.main.nominal_parameters.diameter");
			this->label10->Text = LocalizationManager::getStr("parameters.limits.min");
			this->label11->Text = LocalizationManager::getStr("parameters.limits.max");
			this->groupBox4->Text = LocalizationManager::getStr("parameters.main.nominal_parameters.turnovers");
			this->label8->Text = LocalizationManager::getStr("parameters.limits.min");
			this->label9->Text = LocalizationManager::getStr("parameters.limits.max");
			this->tabPage6->Text = LocalizationManager::getStr("tabs.parameters.control");
			this->label18->Text = LocalizationManager::getStr("parameters.main.nominal_parameters.diameter");
			this->label19->Text = LocalizationManager::getStr("parameters.main.nominal_parameters.turnovers");
			this->label12->Text = LocalizationManager::getStr("parameters.control.throttling_resistance");
		}

	protected:
		System::Collections::Generic::Dictionary<String^, bool>^ notCallEvents = gcnew System::Collections::Generic::Dictionary<String^, bool>();
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~WaterPumpForm()
		{

			if (components)
			{
				delete components;
			}
		}

	protected: System::Collections::Generic::Dictionary<String^, int>^ listTab = gcnew System::Collections::Generic::Dictionary<String^, int>();
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel16;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel2;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel5;
	public: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::Panel^ panel2;
	public: System::Windows::Forms::DataVisualization::Charting::Chart^ chart2;
	private: System::Windows::Forms::Panel^ panel3;
	public: System::Windows::Forms::DataVisualization::Charting::Chart^ chart3;
	private: System::Windows::Forms::TabControl^ tabControl1;
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::TabPage^ tabPage3;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel18;
	private: System::Windows::Forms::GroupBox^ groupBox7;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::Label^ label15;
	public: System::Windows::Forms::TextBox^ box_point_q;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ label20;
	public: System::Windows::Forms::TextBox^ box_point_h;
	private: System::Windows::Forms::Label^ label23;
	private: System::Windows::Forms::Label^ label24;
	private: System::Windows::Forms::Label^ label25;
	private: System::Windows::Forms::Label^ label26;
	private: System::Windows::Forms::Label^ label27;
	private: System::Windows::Forms::Label^ label28;
	public: System::Windows::Forms::TextBox^ box_point_dh;
	public: System::Windows::Forms::TextBox^ box_point_n;
	public: System::Windows::Forms::TextBox^ box_point_m;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel17;
	private: System::Windows::Forms::GroupBox^ groupBox6;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Label^ label29;
	private: System::Windows::Forms::Label^ label31;
	private: System::Windows::Forms::Label^ label33;
	public: System::Windows::Forms::TextBox^ box_k_c;
	public: System::Windows::Forms::TextBox^ box_k_h0;
	public: System::Windows::Forms::TextBox^ box_k_n0;
	public: System::Windows::Forms::TextBox^ box_k_s;
	private: System::Windows::Forms::GroupBox^ groupBox8;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel4;
	private: System::Windows::Forms::Label^ label_q_min;
	private: System::Windows::Forms::Label^ label_q_max;
	public: System::Windows::Forms::TextBox^ box_q_min;
	public: System::Windows::Forms::TextBox^ box_q_max;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	public: System::Windows::Forms::Button^ button1;
	public: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel24;
	private: System::Windows::Forms::TabControl^ tabControl2;
	private: System::Windows::Forms::TabPage^ tabPage4;

	private: System::Windows::Forms::FlowLayoutPanel^ cardSettings1;

	private: System::Windows::Forms::Label^ label1;
	public: System::Windows::Forms::TextBox^ pump_name;

	private: System::Windows::Forms::Label^ label2;
	public: System::Windows::Forms::ComboBox^ pump_enable;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel6;

	private: System::Windows::Forms::Label^ label3;
	public: System::Windows::Forms::TextBox^ pump_mark;

	private: System::Windows::Forms::Label^ label4;


	private: System::Windows::Forms::Label^ label5;
	public: System::Windows::Forms::TextBox^ pump_turn;
	private: System::Windows::Forms::Label^ label32;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel6;
	private: System::Windows::Forms::Label^ label34;
	private: System::Windows::Forms::Label^ label35;
	private: System::Windows::Forms::Label^ label36;
	private: System::Windows::Forms::Label^ label37;
	private: System::Windows::Forms::Label^ label38;
	public: System::Windows::Forms::NumericUpDown^ numeric_input_point;
	public: System::Windows::Forms::TextBox^ box_elem_q;
	public: System::Windows::Forms::TextBox^ box_elem_h;
	public: System::Windows::Forms::TextBox^ box_elem_n;
	public: System::Windows::Forms::TextBox^ box_elem_m;
	private: System::Windows::Forms::TabPage^ tabPage5;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel10;
	private: System::Windows::Forms::GroupBox^ groupBox2;

	private: System::Windows::Forms::Label^ label21;
	public: System::Windows::Forms::TextBox^ pump_eff_min;
	private: System::Windows::Forms::Label^ label22;
	public: System::Windows::Forms::TextBox^ pump_eff_max;


	private: System::Windows::Forms::Label^ label6;
	public: System::Windows::Forms::TextBox^ pump_pres_min;
	private: System::Windows::Forms::Label^ label7;
	public: System::Windows::Forms::TextBox^ pump_pres_max;


	private: System::Windows::Forms::Label^ label14;
	public: System::Windows::Forms::TextBox^ pump_pres_min_out;
	private: System::Windows::Forms::Label^ label30;
	public: System::Windows::Forms::TextBox^ pump_pres_max_out;


	private: System::Windows::Forms::Label^ label8;
	public: System::Windows::Forms::TextBox^ pump_turn_min;
	private: System::Windows::Forms::Label^ label9;
	public: System::Windows::Forms::TextBox^ pump_turn_max;
	private: System::Windows::Forms::GroupBox^ groupBox5;

	private: System::Windows::Forms::Label^ label10;
	public: System::Windows::Forms::TextBox^ pump_dim_min;
	private: System::Windows::Forms::Label^ label11;
	public: System::Windows::Forms::TextBox^ pump_dim_max;
	private: System::Windows::Forms::TabPage^ tabPage6;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel19;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel20;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel21;
	public: System::Windows::Forms::TrackBar^ pump_slide_dim;
	public: System::Windows::Forms::TextBox^ pump_cur_dim;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel22;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel23;
	public: System::Windows::Forms::TrackBar^ pump_slide_turn;
	public: System::Windows::Forms::TextBox^ pump_cur_turn;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel14;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel15;
	public: System::Windows::Forms::TrackBar^ pump_slide_s;
	public: System::Windows::Forms::TextBox^ pump_cur_s;



	private: System::Windows::Forms::Label^ label40;
	public: System::Windows::Forms::TextBox^ input_data_q;

	private: System::Windows::Forms::Label^ label39;
	public: System::Windows::Forms::TextBox^ input_data_h_in;

	private: System::Windows::Forms::Label^ label41;
	public: System::Windows::Forms::TextBox^ input_data_h_out;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	public: System::Windows::Forms::ToolTip^ toolTip1;
	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Требуемый метод для поддержки конструктора — не изменяйте 
		   /// содержимое этого метода с помощью редактора кода.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			   System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			   System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			   System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			   System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			   System::Windows::Forms::DataVisualization::Charting::Legend^ legend3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			   this->flowLayoutPanel16 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->panel4 = (gcnew System::Windows::Forms::Panel());
			   this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			   this->panel2 = (gcnew System::Windows::Forms::Panel());
			   this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			   this->panel3 = (gcnew System::Windows::Forms::Panel());
			   this->chart3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			   this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			   this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			   this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			   this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			   this->flowLayoutPanel18 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			   this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->label15 = (gcnew System::Windows::Forms::Label());
			   this->box_point_q = (gcnew System::Windows::Forms::TextBox());
			   this->label16 = (gcnew System::Windows::Forms::Label());
			   this->label17 = (gcnew System::Windows::Forms::Label());
			   this->label20 = (gcnew System::Windows::Forms::Label());
			   this->box_point_h = (gcnew System::Windows::Forms::TextBox());
			   this->label23 = (gcnew System::Windows::Forms::Label());
			   this->label24 = (gcnew System::Windows::Forms::Label());
			   this->label25 = (gcnew System::Windows::Forms::Label());
			   this->label26 = (gcnew System::Windows::Forms::Label());
			   this->label27 = (gcnew System::Windows::Forms::Label());
			   this->label28 = (gcnew System::Windows::Forms::Label());
			   this->box_point_dh = (gcnew System::Windows::Forms::TextBox());
			   this->box_point_n = (gcnew System::Windows::Forms::TextBox());
			   this->box_point_m = (gcnew System::Windows::Forms::TextBox());
			   this->flowLayoutPanel17 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			   this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->label13 = (gcnew System::Windows::Forms::Label());
			   this->label29 = (gcnew System::Windows::Forms::Label());
			   this->label31 = (gcnew System::Windows::Forms::Label());
			   this->label33 = (gcnew System::Windows::Forms::Label());
			   this->box_k_c = (gcnew System::Windows::Forms::TextBox());
			   this->box_k_h0 = (gcnew System::Windows::Forms::TextBox());
			   this->box_k_n0 = (gcnew System::Windows::Forms::TextBox());
			   this->box_k_s = (gcnew System::Windows::Forms::TextBox());
			   this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			   this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->label_q_min = (gcnew System::Windows::Forms::Label());
			   this->label_q_max = (gcnew System::Windows::Forms::Label());
			   this->box_q_min = (gcnew System::Windows::Forms::TextBox());
			   this->box_q_max = (gcnew System::Windows::Forms::TextBox());
			   this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->flowLayoutPanel24 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->tabControl2 = (gcnew System::Windows::Forms::TabControl());
			   this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			   this->cardSettings1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->tableLayoutPanel11 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->pump_name = (gcnew System::Windows::Forms::TextBox());
			   this->tableLayoutPanel10 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->pump_enable = (gcnew System::Windows::Forms::ComboBox());
			   this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			   this->flowLayoutPanel6 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->tableLayoutPanel8 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->pump_mark = (gcnew System::Windows::Forms::TextBox());
			   this->tableLayoutPanel7 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->pump_dim = (gcnew System::Windows::Forms::TextBox());
			   this->tableLayoutPanel9 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   this->pump_turn = (gcnew System::Windows::Forms::TextBox());
			   this->label32 = (gcnew System::Windows::Forms::Label());
			   this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->label34 = (gcnew System::Windows::Forms::Label());
			   this->label35 = (gcnew System::Windows::Forms::Label());
			   this->label36 = (gcnew System::Windows::Forms::Label());
			   this->label38 = (gcnew System::Windows::Forms::Label());
			   this->numeric_input_point = (gcnew System::Windows::Forms::NumericUpDown());
			   this->box_elem_q = (gcnew System::Windows::Forms::TextBox());
			   this->box_elem_h = (gcnew System::Windows::Forms::TextBox());
			   this->box_elem_n = (gcnew System::Windows::Forms::TextBox());
			   this->box_elem_m = (gcnew System::Windows::Forms::TextBox());
			   this->label37 = (gcnew System::Windows::Forms::Label());
			   this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			   this->flowLayoutPanel10 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->label42 = (gcnew System::Windows::Forms::Label());
			   this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			   this->tableLayoutPanel14 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->label21 = (gcnew System::Windows::Forms::Label());
			   this->pump_eff_min = (gcnew System::Windows::Forms::TextBox());
			   this->label22 = (gcnew System::Windows::Forms::Label());
			   this->pump_eff_max = (gcnew System::Windows::Forms::TextBox());
			   this->label40 = (gcnew System::Windows::Forms::Label());
			   this->input_data_q = (gcnew System::Windows::Forms::TextBox());
			   this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			   this->tableLayoutPanel15 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->label6 = (gcnew System::Windows::Forms::Label());
			   this->pump_pres_min = (gcnew System::Windows::Forms::TextBox());
			   this->label7 = (gcnew System::Windows::Forms::Label());
			   this->pump_pres_max = (gcnew System::Windows::Forms::TextBox());
			   this->label39 = (gcnew System::Windows::Forms::Label());
			   this->input_data_h_in = (gcnew System::Windows::Forms::TextBox());
			   this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
			   this->tableLayoutPanel16 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->label14 = (gcnew System::Windows::Forms::Label());
			   this->pump_pres_min_out = (gcnew System::Windows::Forms::TextBox());
			   this->label30 = (gcnew System::Windows::Forms::Label());
			   this->pump_pres_max_out = (gcnew System::Windows::Forms::TextBox());
			   this->label41 = (gcnew System::Windows::Forms::Label());
			   this->input_data_h_out = (gcnew System::Windows::Forms::TextBox());
			   this->label43 = (gcnew System::Windows::Forms::Label());
			   this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			   this->tableLayoutPanel12 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->label10 = (gcnew System::Windows::Forms::Label());
			   this->pump_dim_min = (gcnew System::Windows::Forms::TextBox());
			   this->label11 = (gcnew System::Windows::Forms::Label());
			   this->pump_dim_max = (gcnew System::Windows::Forms::TextBox());
			   this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			   this->tableLayoutPanel13 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->label8 = (gcnew System::Windows::Forms::Label());
			   this->pump_turn_min = (gcnew System::Windows::Forms::TextBox());
			   this->label9 = (gcnew System::Windows::Forms::Label());
			   this->pump_turn_max = (gcnew System::Windows::Forms::TextBox());
			   this->tabPage6 = (gcnew System::Windows::Forms::TabPage());
			   this->flowLayoutPanel19 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->flowLayoutPanel20 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->label18 = (gcnew System::Windows::Forms::Label());
			   this->flowLayoutPanel21 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->pump_slide_dim = (gcnew System::Windows::Forms::TrackBar());
			   this->pump_cur_dim = (gcnew System::Windows::Forms::TextBox());
			   this->flowLayoutPanel22 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->label19 = (gcnew System::Windows::Forms::Label());
			   this->flowLayoutPanel23 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->pump_slide_turn = (gcnew System::Windows::Forms::TrackBar());
			   this->pump_cur_turn = (gcnew System::Windows::Forms::TextBox());
			   this->flowLayoutPanel14 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->label12 = (gcnew System::Windows::Forms::Label());
			   this->flowLayoutPanel15 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->pump_slide_s = (gcnew System::Windows::Forms::TrackBar());
			   this->pump_cur_s = (gcnew System::Windows::Forms::TextBox());
			   this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			   this->flowLayoutPanel16->SuspendLayout();
			   this->panel4->SuspendLayout();
			   this->flowLayoutPanel2->SuspendLayout();
			   this->tableLayoutPanel5->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			   this->panel2->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			   this->panel3->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart3))->BeginInit();
			   this->tabControl1->SuspendLayout();
			   this->flowLayoutPanel18->SuspendLayout();
			   this->groupBox7->SuspendLayout();
			   this->tableLayoutPanel2->SuspendLayout();
			   this->flowLayoutPanel17->SuspendLayout();
			   this->groupBox6->SuspendLayout();
			   this->tableLayoutPanel3->SuspendLayout();
			   this->groupBox8->SuspendLayout();
			   this->tableLayoutPanel4->SuspendLayout();
			   this->flowLayoutPanel1->SuspendLayout();
			   this->flowLayoutPanel24->SuspendLayout();
			   this->tabControl2->SuspendLayout();
			   this->tabPage4->SuspendLayout();
			   this->cardSettings1->SuspendLayout();
			   this->tableLayoutPanel11->SuspendLayout();
			   this->tableLayoutPanel10->SuspendLayout();
			   this->groupBox1->SuspendLayout();
			   this->flowLayoutPanel6->SuspendLayout();
			   this->tableLayoutPanel8->SuspendLayout();
			   this->tableLayoutPanel7->SuspendLayout();
			   this->tableLayoutPanel9->SuspendLayout();
			   this->tableLayoutPanel6->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numeric_input_point))->BeginInit();
			   this->tabPage5->SuspendLayout();
			   this->flowLayoutPanel10->SuspendLayout();
			   this->groupBox2->SuspendLayout();
			   this->tableLayoutPanel14->SuspendLayout();
			   this->groupBox3->SuspendLayout();
			   this->tableLayoutPanel15->SuspendLayout();
			   this->groupBox9->SuspendLayout();
			   this->tableLayoutPanel16->SuspendLayout();
			   this->groupBox5->SuspendLayout();
			   this->tableLayoutPanel12->SuspendLayout();
			   this->groupBox4->SuspendLayout();
			   this->tableLayoutPanel13->SuspendLayout();
			   this->tabPage6->SuspendLayout();
			   this->flowLayoutPanel19->SuspendLayout();
			   this->flowLayoutPanel20->SuspendLayout();
			   this->flowLayoutPanel21->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pump_slide_dim))->BeginInit();
			   this->flowLayoutPanel22->SuspendLayout();
			   this->flowLayoutPanel23->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pump_slide_turn))->BeginInit();
			   this->flowLayoutPanel14->SuspendLayout();
			   this->flowLayoutPanel15->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pump_slide_s))->BeginInit();
			   this->tableLayoutPanel1->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // flowLayoutPanel16
			   // 
			   this->flowLayoutPanel16->AutoSize = true;
			   this->flowLayoutPanel16->Controls->Add(this->panel4);
			   this->flowLayoutPanel16->Controls->Add(this->flowLayoutPanel18);
			   this->flowLayoutPanel16->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->flowLayoutPanel16->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			   this->flowLayoutPanel16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->flowLayoutPanel16->Location = System::Drawing::Point(363, 3);
			   this->flowLayoutPanel16->Name = L"flowLayoutPanel16";
			   this->flowLayoutPanel16->Size = System::Drawing::Size(354, 427);
			   this->flowLayoutPanel16->TabIndex = 1;
			   this->flowLayoutPanel16->WrapContents = false;
			   // 
			   // panel4
			   // 
			   this->panel4->Controls->Add(this->flowLayoutPanel2);
			   this->panel4->Controls->Add(this->tabControl1);
			   this->panel4->Location = System::Drawing::Point(0, 0);
			   this->panel4->Margin = System::Windows::Forms::Padding(0);
			   this->panel4->Name = L"panel4";
			   this->panel4->Size = System::Drawing::Size(351, 208);
			   this->panel4->TabIndex = 3;
			   // 
			   // flowLayoutPanel2
			   // 
			   this->flowLayoutPanel2->BackColor = System::Drawing::Color::White;
			   this->flowLayoutPanel2->Controls->Add(this->tableLayoutPanel5);
			   this->flowLayoutPanel2->Controls->Add(this->panel2);
			   this->flowLayoutPanel2->Controls->Add(this->panel3);
			   this->flowLayoutPanel2->Location = System::Drawing::Point(4, 22);
			   this->flowLayoutPanel2->Margin = System::Windows::Forms::Padding(0);
			   this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			   this->flowLayoutPanel2->Size = System::Drawing::Size(343, 182);
			   this->flowLayoutPanel2->TabIndex = 0;
			   this->flowLayoutPanel2->WrapContents = false;
			   // 
			   // tableLayoutPanel5
			   // 
			   this->tableLayoutPanel5->ColumnCount = 1;
			   this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   100)));
			   this->tableLayoutPanel5->Controls->Add(this->chart1, 0, 1);
			   this->tableLayoutPanel5->Location = System::Drawing::Point(0, 0);
			   this->tableLayoutPanel5->Margin = System::Windows::Forms::Padding(0);
			   this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
			   this->tableLayoutPanel5->RowCount = 3;
			   this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			   this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel5->Size = System::Drawing::Size(343, 182);
			   this->tableLayoutPanel5->TabIndex = 1;
			   // 
			   // chart1
			   // 
			   this->chart1->BackColor = System::Drawing::Color::Transparent;
			   this->chart1->BackImageWrapMode = System::Windows::Forms::DataVisualization::Charting::ChartImageWrapMode::Scaled;
			   chartArea1->AxisX->Interval = 2;
			   chartArea1->AxisX->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			   chartArea1->AxisX->LineColor = System::Drawing::Color::Gray;
			   chartArea1->AxisX->LogarithmBase = 100;
			   chartArea1->AxisX->MajorGrid->LineColor = System::Drawing::Color::Gray;
			   chartArea1->AxisX->Maximum = 10;
			   chartArea1->AxisX->Minimum = 0;
			   chartArea1->AxisX->TitleFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6));
			   chartArea1->AxisX2->LineColor = System::Drawing::Color::Gray;
			   chartArea1->AxisY->Interval = 2;
			   chartArea1->AxisY->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			   chartArea1->AxisY->LineColor = System::Drawing::Color::Gray;
			   chartArea1->AxisY->MajorGrid->LineColor = System::Drawing::Color::Gray;
			   chartArea1->AxisY->Maximum = 10;
			   chartArea1->AxisY->Minimum = 0;
			   chartArea1->AxisY->TitleAlignment = System::Drawing::StringAlignment::Far;
			   chartArea1->AxisY2->LineColor = System::Drawing::Color::Gray;
			   chartArea1->BackColor = System::Drawing::Color::Transparent;
			   chartArea1->BackImageAlignment = System::Windows::Forms::DataVisualization::Charting::ChartImageAlignmentStyle::Center;
			   chartArea1->BorderColor = System::Drawing::Color::Gray;
			   chartArea1->Name = L"ChartArea1";
			   chartArea1->Position->Auto = false;
			   chartArea1->Position->Height = 100;
			   chartArea1->Position->Width = 98;
			   chartArea1->Position->X = 2;
			   chartArea1->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(128)));
			   this->chart1->ChartAreas->Add(chartArea1);
			   this->chart1->Dock = System::Windows::Forms::DockStyle::Fill;
			   legend1->Enabled = false;
			   legend1->Name = L"Legend1";
			   legend1->TableStyle = System::Windows::Forms::DataVisualization::Charting::LegendTableStyle::Wide;
			   this->chart1->Legends->Add(legend1);
			   this->chart1->Location = System::Drawing::Point(0, 0);
			   this->chart1->Margin = System::Windows::Forms::Padding(0);
			   this->chart1->Name = L"chart1";
			   this->chart1->Size = System::Drawing::Size(343, 182);
			   this->chart1->TabIndex = 0;
			   this->chart1->Text = L"chart1";
			   // 
			   // panel2
			   // 
			   this->panel2->BackColor = System::Drawing::Color::White;
			   this->panel2->Controls->Add(this->chart2);
			   this->panel2->Location = System::Drawing::Point(343, 0);
			   this->panel2->Margin = System::Windows::Forms::Padding(0);
			   this->panel2->Name = L"panel2";
			   this->panel2->Size = System::Drawing::Size(343, 182);
			   this->panel2->TabIndex = 2;
			   // 
			   // chart2
			   // 
			   chartArea2->AxisX->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			   chartArea2->AxisX->IsMarginVisible = false;
			   chartArea2->AxisX->LineColor = System::Drawing::Color::Gray;
			   chartArea2->AxisX->MajorGrid->LineColor = System::Drawing::Color::Gray;
			   chartArea2->AxisX->Minimum = 0;
			   chartArea2->AxisY->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			   chartArea2->AxisY->IsMarginVisible = false;
			   chartArea2->AxisY->LineColor = System::Drawing::Color::Gray;
			   chartArea2->AxisY->MajorGrid->LineColor = System::Drawing::Color::Gray;
			   chartArea2->AxisY->Minimum = 0;
			   chartArea2->Name = L"ChartArea1";
			   chartArea2->Position->Auto = false;
			   chartArea2->Position->Height = 100;
			   chartArea2->Position->Width = 99.5F;
			   chartArea2->Position->X = 0.5F;
			   this->chart2->ChartAreas->Add(chartArea2);
			   legend2->Enabled = false;
			   legend2->Name = L"Legend1";
			   legend2->TableStyle = System::Windows::Forms::DataVisualization::Charting::LegendTableStyle::Wide;
			   this->chart2->Legends->Add(legend2);
			   this->chart2->Location = System::Drawing::Point(0, 0);
			   this->chart2->Margin = System::Windows::Forms::Padding(0);
			   this->chart2->Name = L"chart2";
			   this->chart2->Size = System::Drawing::Size(343, 182);
			   this->chart2->TabIndex = 0;
			   this->chart2->Text = L"chart2";
			   // 
			   // panel3
			   // 
			   this->panel3->BackColor = System::Drawing::Color::White;
			   this->panel3->Controls->Add(this->chart3);
			   this->panel3->Location = System::Drawing::Point(686, 0);
			   this->panel3->Margin = System::Windows::Forms::Padding(0);
			   this->panel3->Name = L"panel3";
			   this->panel3->Size = System::Drawing::Size(343, 182);
			   this->panel3->TabIndex = 3;
			   // 
			   // chart3
			   // 
			   chartArea3->AxisX->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			   chartArea3->AxisX->LineColor = System::Drawing::Color::Gray;
			   chartArea3->AxisX->MajorGrid->LineColor = System::Drawing::Color::Gray;
			   chartArea3->AxisX->Minimum = 0;
			   chartArea3->AxisY->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			   chartArea3->AxisY->LineColor = System::Drawing::Color::Gray;
			   chartArea3->AxisY->MajorGrid->LineColor = System::Drawing::Color::Gray;
			   chartArea3->AxisY->Minimum = 0;
			   chartArea3->Name = L"ChartArea1";
			   chartArea3->Position->Auto = false;
			   chartArea3->Position->Height = 100;
			   chartArea3->Position->Width = 100;
			   this->chart3->ChartAreas->Add(chartArea3);
			   legend3->Enabled = false;
			   legend3->Name = L"Legend1";
			   legend3->TableStyle = System::Windows::Forms::DataVisualization::Charting::LegendTableStyle::Wide;
			   this->chart3->Legends->Add(legend3);
			   this->chart3->Location = System::Drawing::Point(0, 0);
			   this->chart3->Margin = System::Windows::Forms::Padding(0);
			   this->chart3->Name = L"chart3";
			   this->chart3->Size = System::Drawing::Size(343, 182);
			   this->chart3->TabIndex = 0;
			   this->chart3->Text = L"chart3";
			   // 
			   // tabControl1
			   // 
			   this->tabControl1->Controls->Add(this->tabPage1);
			   this->tabControl1->Controls->Add(this->tabPage2);
			   this->tabControl1->Controls->Add(this->tabPage3);
			   this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->tabControl1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->tabControl1->Location = System::Drawing::Point(0, 0);
			   this->tabControl1->Name = L"tabControl1";
			   this->tabControl1->SelectedIndex = 0;
			   this->tabControl1->Size = System::Drawing::Size(351, 208);
			   this->tabControl1->TabIndex = 3;
			   this->tabControl1->SelectedIndexChanged += gcnew System::EventHandler(this, &WaterPumpForm::tabControl1_SelectedIndexChanged);
			   // 
			   // tabPage1
			   // 
			   this->tabPage1->BackColor = System::Drawing::Color::DimGray;
			   this->tabPage1->Location = System::Drawing::Point(4, 24);
			   this->tabPage1->Name = L"tabPage1";
			   this->tabPage1->Size = System::Drawing::Size(343, 180);
			   this->tabPage1->TabIndex = 0;
			   // 
			   // tabPage2
			   // 
			   this->tabPage2->Location = System::Drawing::Point(4, 24);
			   this->tabPage2->Name = L"tabPage2";
			   this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			   this->tabPage2->Size = System::Drawing::Size(343, 180);
			   this->tabPage2->TabIndex = 1;
			   this->tabPage2->UseVisualStyleBackColor = true;
			   // 
			   // tabPage3
			   // 
			   this->tabPage3->Location = System::Drawing::Point(4, 24);
			   this->tabPage3->Name = L"tabPage3";
			   this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			   this->tabPage3->Size = System::Drawing::Size(343, 180);
			   this->tabPage3->TabIndex = 2;
			   this->tabPage3->UseVisualStyleBackColor = true;
			   // 
			   // flowLayoutPanel18
			   // 
			   this->flowLayoutPanel18->Controls->Add(this->groupBox7);
			   this->flowLayoutPanel18->Controls->Add(this->flowLayoutPanel17);
			   this->flowLayoutPanel18->Location = System::Drawing::Point(0, 208);
			   this->flowLayoutPanel18->Margin = System::Windows::Forms::Padding(0);
			   this->flowLayoutPanel18->Name = L"flowLayoutPanel18";
			   this->flowLayoutPanel18->Size = System::Drawing::Size(351, 219);
			   this->flowLayoutPanel18->TabIndex = 5;
			   this->flowLayoutPanel18->WrapContents = false;
			   // 
			   // groupBox7
			   // 
			   this->groupBox7->AutoSize = true;
			   this->groupBox7->Controls->Add(this->tableLayoutPanel2);
			   this->groupBox7->Location = System::Drawing::Point(3, 3);
			   this->groupBox7->Name = L"groupBox7";
			   this->groupBox7->Size = System::Drawing::Size(156, 155);
			   this->groupBox7->TabIndex = 5;
			   this->groupBox7->TabStop = false;
			   this->groupBox7->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &WaterPumpForm::groupBox2_Paint);
			   // 
			   // tableLayoutPanel2
			   // 
			   this->tableLayoutPanel2->AutoSize = true;
			   this->tableLayoutPanel2->ColumnCount = 3;
			   this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   40)));
			   this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   70)));
			   this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   40)));
			   this->tableLayoutPanel2->Controls->Add(this->label15, 0, 0);
			   this->tableLayoutPanel2->Controls->Add(this->box_point_q, 1, 0);
			   this->tableLayoutPanel2->Controls->Add(this->label16, 2, 0);
			   this->tableLayoutPanel2->Controls->Add(this->label17, 0, 1);
			   this->tableLayoutPanel2->Controls->Add(this->label20, 2, 1);
			   this->tableLayoutPanel2->Controls->Add(this->box_point_h, 1, 1);
			   this->tableLayoutPanel2->Controls->Add(this->label23, 0, 2);
			   this->tableLayoutPanel2->Controls->Add(this->label24, 2, 2);
			   this->tableLayoutPanel2->Controls->Add(this->label25, 0, 3);
			   this->tableLayoutPanel2->Controls->Add(this->label26, 0, 4);
			   this->tableLayoutPanel2->Controls->Add(this->label27, 2, 3);
			   this->tableLayoutPanel2->Controls->Add(this->label28, 2, 4);
			   this->tableLayoutPanel2->Controls->Add(this->box_point_dh, 1, 2);
			   this->tableLayoutPanel2->Controls->Add(this->box_point_n, 1, 3);
			   this->tableLayoutPanel2->Controls->Add(this->box_point_m, 1, 4);
			   this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->tableLayoutPanel2->Location = System::Drawing::Point(3, 17);
			   this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			   this->tableLayoutPanel2->RowCount = 5;
			   this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			   this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			   this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			   this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			   this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			   this->tableLayoutPanel2->Size = System::Drawing::Size(150, 135);
			   this->tableLayoutPanel2->TabIndex = 4;
			   // 
			   // label15
			   // 
			   this->label15->AutoSize = true;
			   this->label15->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label15->Location = System::Drawing::Point(3, 0);
			   this->label15->Name = L"label15";
			   this->label15->Size = System::Drawing::Size(34, 27);
			   this->label15->TabIndex = 5;
			   this->label15->Text = L"Q";
			   this->label15->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // box_point_q
			   // 
			   this->box_point_q->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->box_point_q->Location = System::Drawing::Point(43, 3);
			   this->box_point_q->Name = L"box_point_q";
			   this->box_point_q->Size = System::Drawing::Size(64, 21);
			   this->box_point_q->TabIndex = 6;
			   this->box_point_q->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			   // 
			   // label16
			   // 
			   this->label16->AutoSize = true;
			   this->label16->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label16->Location = System::Drawing::Point(113, 0);
			   this->label16->Name = L"label16";
			   this->label16->Size = System::Drawing::Size(34, 27);
			   this->label16->TabIndex = 7;
			   this->label16->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // label17
			   // 
			   this->label17->AutoSize = true;
			   this->label17->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label17->Location = System::Drawing::Point(3, 27);
			   this->label17->Name = L"label17";
			   this->label17->Size = System::Drawing::Size(34, 27);
			   this->label17->TabIndex = 8;
			   this->label17->Text = L"H";
			   this->label17->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // label20
			   // 
			   this->label20->AutoSize = true;
			   this->label20->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label20->Location = System::Drawing::Point(113, 27);
			   this->label20->Name = L"label20";
			   this->label20->Size = System::Drawing::Size(34, 27);
			   this->label20->TabIndex = 9;
			   this->label20->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // box_point_h
			   // 
			   this->box_point_h->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->box_point_h->Location = System::Drawing::Point(43, 30);
			   this->box_point_h->Name = L"box_point_h";
			   this->box_point_h->ReadOnly = true;
			   this->box_point_h->Size = System::Drawing::Size(64, 21);
			   this->box_point_h->TabIndex = 10;
			   this->box_point_h->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			   // 
			   // label23
			   // 
			   this->label23->AutoSize = true;
			   this->label23->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label23->Location = System::Drawing::Point(3, 54);
			   this->label23->Name = L"label23";
			   this->label23->Size = System::Drawing::Size(34, 27);
			   this->label23->TabIndex = 11;
			   this->label23->Text = L"dH";
			   this->label23->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // label24
			   // 
			   this->label24->AutoSize = true;
			   this->label24->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label24->Location = System::Drawing::Point(113, 54);
			   this->label24->Name = L"label24";
			   this->label24->Size = System::Drawing::Size(34, 27);
			   this->label24->TabIndex = 12;
			   this->label24->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // label25
			   // 
			   this->label25->AutoSize = true;
			   this->label25->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label25->Location = System::Drawing::Point(3, 81);
			   this->label25->Name = L"label25";
			   this->label25->Size = System::Drawing::Size(34, 27);
			   this->label25->TabIndex = 13;
			   this->label25->Text = L"N";
			   this->label25->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // label26
			   // 
			   this->label26->AutoSize = true;
			   this->label26->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label26->Location = System::Drawing::Point(3, 108);
			   this->label26->Name = L"label26";
			   this->label26->Size = System::Drawing::Size(34, 27);
			   this->label26->TabIndex = 14;
			   this->label26->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // label27
			   // 
			   this->label27->AutoSize = true;
			   this->label27->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label27->Location = System::Drawing::Point(113, 81);
			   this->label27->Name = L"label27";
			   this->label27->Size = System::Drawing::Size(34, 27);
			   this->label27->TabIndex = 15;
			   this->label27->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // label28
			   // 
			   this->label28->AutoSize = true;
			   this->label28->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label28->Location = System::Drawing::Point(113, 108);
			   this->label28->Name = L"label28";
			   this->label28->Size = System::Drawing::Size(34, 27);
			   this->label28->TabIndex = 16;
			   this->label28->Text = L"%";
			   this->label28->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // box_point_dh
			   // 
			   this->box_point_dh->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->box_point_dh->Location = System::Drawing::Point(43, 57);
			   this->box_point_dh->Name = L"box_point_dh";
			   this->box_point_dh->ReadOnly = true;
			   this->box_point_dh->Size = System::Drawing::Size(64, 21);
			   this->box_point_dh->TabIndex = 17;
			   this->box_point_dh->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			   // 
			   // box_point_n
			   // 
			   this->box_point_n->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->box_point_n->Location = System::Drawing::Point(43, 84);
			   this->box_point_n->Name = L"box_point_n";
			   this->box_point_n->ReadOnly = true;
			   this->box_point_n->Size = System::Drawing::Size(64, 21);
			   this->box_point_n->TabIndex = 18;
			   this->box_point_n->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			   // 
			   // box_point_m
			   // 
			   this->box_point_m->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->box_point_m->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->box_point_m->Location = System::Drawing::Point(43, 111);
			   this->box_point_m->Name = L"box_point_m";
			   this->box_point_m->ReadOnly = true;
			   this->box_point_m->Size = System::Drawing::Size(64, 21);
			   this->box_point_m->TabIndex = 19;
			   this->box_point_m->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			   // 
			   // flowLayoutPanel17
			   // 
			   this->flowLayoutPanel17->Controls->Add(this->groupBox6);
			   this->flowLayoutPanel17->Controls->Add(this->groupBox8);
			   this->flowLayoutPanel17->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			   this->flowLayoutPanel17->Location = System::Drawing::Point(165, 3);
			   this->flowLayoutPanel17->Name = L"flowLayoutPanel17";
			   this->flowLayoutPanel17->Size = System::Drawing::Size(193, 236);
			   this->flowLayoutPanel17->TabIndex = 6;
			   this->flowLayoutPanel17->WrapContents = false;
			   // 
			   // groupBox6
			   // 
			   this->groupBox6->AutoSize = true;
			   this->groupBox6->Controls->Add(this->tableLayoutPanel3);
			   this->groupBox6->Location = System::Drawing::Point(3, 3);
			   this->groupBox6->Name = L"groupBox6";
			   this->groupBox6->Padding = System::Windows::Forms::Padding(3, 3, 3, 5);
			   this->groupBox6->Size = System::Drawing::Size(177, 130);
			   this->groupBox6->TabIndex = 6;
			   this->groupBox6->TabStop = false;
			   this->groupBox6->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &WaterPumpForm::groupBox2_Paint);
			   // 
			   // tableLayoutPanel3
			   // 
			   this->tableLayoutPanel3->AutoSize = true;
			   this->tableLayoutPanel3->ColumnCount = 2;
			   this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   40)));
			   this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   131)));
			   this->tableLayoutPanel3->Controls->Add(this->label13, 0, 0);
			   this->tableLayoutPanel3->Controls->Add(this->label29, 0, 1);
			   this->tableLayoutPanel3->Controls->Add(this->label31, 0, 2);
			   this->tableLayoutPanel3->Controls->Add(this->label33, 0, 3);
			   this->tableLayoutPanel3->Controls->Add(this->box_k_c, 1, 3);
			   this->tableLayoutPanel3->Controls->Add(this->box_k_h0, 1, 0);
			   this->tableLayoutPanel3->Controls->Add(this->box_k_n0, 1, 2);
			   this->tableLayoutPanel3->Controls->Add(this->box_k_s, 1, 1);
			   this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->tableLayoutPanel3->Location = System::Drawing::Point(3, 17);
			   this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			   this->tableLayoutPanel3->RowCount = 4;
			   this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel3->Size = System::Drawing::Size(171, 108);
			   this->tableLayoutPanel3->TabIndex = 4;
			   // 
			   // label13
			   // 
			   this->label13->AutoSize = true;
			   this->label13->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label13->Location = System::Drawing::Point(3, 0);
			   this->label13->Name = L"label13";
			   this->label13->Size = System::Drawing::Size(34, 27);
			   this->label13->TabIndex = 5;
			   this->label13->Text = L"Ho";
			   this->label13->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // label29
			   // 
			   this->label29->AutoSize = true;
			   this->label29->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label29->Location = System::Drawing::Point(3, 27);
			   this->label29->Name = L"label29";
			   this->label29->Size = System::Drawing::Size(34, 27);
			   this->label29->TabIndex = 8;
			   this->label29->Text = L"S";
			   this->label29->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // label31
			   // 
			   this->label31->AutoSize = true;
			   this->label31->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label31->Location = System::Drawing::Point(3, 54);
			   this->label31->Name = L"label31";
			   this->label31->Size = System::Drawing::Size(34, 27);
			   this->label31->TabIndex = 11;
			   this->label31->Text = L"No";
			   this->label31->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // label33
			   // 
			   this->label33->AutoSize = true;
			   this->label33->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label33->Location = System::Drawing::Point(3, 81);
			   this->label33->Name = L"label33";
			   this->label33->Size = System::Drawing::Size(34, 27);
			   this->label33->TabIndex = 13;
			   this->label33->Text = L"C";
			   this->label33->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // box_k_c
			   // 
			   this->box_k_c->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->box_k_c->Location = System::Drawing::Point(43, 84);
			   this->box_k_c->Name = L"box_k_c";
			   this->box_k_c->ReadOnly = true;
			   this->box_k_c->Size = System::Drawing::Size(125, 21);
			   this->box_k_c->TabIndex = 14;
			   // 
			   // box_k_h0
			   // 
			   this->box_k_h0->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->box_k_h0->Location = System::Drawing::Point(43, 3);
			   this->box_k_h0->Name = L"box_k_h0";
			   this->box_k_h0->ReadOnly = true;
			   this->box_k_h0->Size = System::Drawing::Size(125, 21);
			   this->box_k_h0->TabIndex = 15;
			   // 
			   // box_k_n0
			   // 
			   this->box_k_n0->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->box_k_n0->Location = System::Drawing::Point(43, 57);
			   this->box_k_n0->Name = L"box_k_n0";
			   this->box_k_n0->ReadOnly = true;
			   this->box_k_n0->Size = System::Drawing::Size(125, 21);
			   this->box_k_n0->TabIndex = 16;
			   // 
			   // box_k_s
			   // 
			   this->box_k_s->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->box_k_s->Location = System::Drawing::Point(43, 30);
			   this->box_k_s->Name = L"box_k_s";
			   this->box_k_s->ReadOnly = true;
			   this->box_k_s->Size = System::Drawing::Size(125, 21);
			   this->box_k_s->TabIndex = 17;
			   // 
			   // groupBox8
			   // 
			   this->groupBox8->AutoSize = true;
			   this->groupBox8->Controls->Add(this->tableLayoutPanel4);
			   this->groupBox8->Location = System::Drawing::Point(3, 139);
			   this->groupBox8->Name = L"groupBox8";
			   this->groupBox8->Padding = System::Windows::Forms::Padding(3, 3, 3, 5);
			   this->groupBox8->Size = System::Drawing::Size(177, 76);
			   this->groupBox8->TabIndex = 7;
			   this->groupBox8->TabStop = false;
			   this->groupBox8->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &WaterPumpForm::groupBox2_Paint);
			   // 
			   // tableLayoutPanel4
			   // 
			   this->tableLayoutPanel4->AutoSize = true;
			   this->tableLayoutPanel4->ColumnCount = 2;
			   this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   50)));
			   this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   121)));
			   this->tableLayoutPanel4->Controls->Add(this->label_q_min, 0, 0);
			   this->tableLayoutPanel4->Controls->Add(this->label_q_max, 0, 1);
			   this->tableLayoutPanel4->Controls->Add(this->box_q_min, 1, 0);
			   this->tableLayoutPanel4->Controls->Add(this->box_q_max, 1, 1);
			   this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->tableLayoutPanel4->Location = System::Drawing::Point(3, 17);
			   this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			   this->tableLayoutPanel4->RowCount = 2;
			   this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel4->Size = System::Drawing::Size(171, 54);
			   this->tableLayoutPanel4->TabIndex = 4;
			   // 
			   // label_q_min
			   // 
			   this->label_q_min->AutoSize = true;
			   this->label_q_min->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label_q_min->Location = System::Drawing::Point(3, 0);
			   this->label_q_min->Name = L"label_q_min";
			   this->label_q_min->Size = System::Drawing::Size(44, 27);
			   this->label_q_min->TabIndex = 5;
			   this->label_q_min->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // label_q_max
			   // 
			   this->label_q_max->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label_q_max->Location = System::Drawing::Point(3, 27);
			   this->label_q_max->Name = L"label_q_max";
			   this->label_q_max->Size = System::Drawing::Size(44, 27);
			   this->label_q_max->TabIndex = 8;
			   this->label_q_max->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // box_q_min
			   // 
			   this->box_q_min->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->box_q_min->Location = System::Drawing::Point(53, 3);
			   this->box_q_min->Name = L"box_q_min";
			   this->box_q_min->ReadOnly = true;
			   this->box_q_min->Size = System::Drawing::Size(115, 21);
			   this->box_q_min->TabIndex = 15;
			   // 
			   // box_q_max
			   // 
			   this->box_q_max->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->box_q_max->Location = System::Drawing::Point(53, 30);
			   this->box_q_max->Name = L"box_q_max";
			   this->box_q_max->ReadOnly = true;
			   this->box_q_max->Size = System::Drawing::Size(115, 21);
			   this->box_q_max->TabIndex = 17;
			   // 
			   // flowLayoutPanel1
			   // 
			   this->flowLayoutPanel1->AutoSize = true;
			   this->flowLayoutPanel1->Controls->Add(this->button1);
			   this->flowLayoutPanel1->Controls->Add(this->button2);
			   this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Top;
			   this->flowLayoutPanel1->FlowDirection = System::Windows::Forms::FlowDirection::RightToLeft;
			   this->flowLayoutPanel1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->flowLayoutPanel1->Location = System::Drawing::Point(363, 436);
			   this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			   this->flowLayoutPanel1->Size = System::Drawing::Size(354, 29);
			   this->flowLayoutPanel1->TabIndex = 2;
			   // 
			   // button1
			   // 
			   this->button1->AutoSize = true;
			   this->button1->Location = System::Drawing::Point(276, 3);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(75, 23);
			   this->button1->TabIndex = 0;
			   this->button1->UseVisualStyleBackColor = true;
			   // 
			   // button2
			   // 
			   this->button2->AutoSize = true;
			   this->button2->Location = System::Drawing::Point(195, 3);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(75, 23);
			   this->button2->TabIndex = 1;
			   this->button2->UseVisualStyleBackColor = true;
			   // 
			   // flowLayoutPanel24
			   // 
			   this->flowLayoutPanel24->Controls->Add(this->tabControl2);
			   this->flowLayoutPanel24->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->flowLayoutPanel24->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			   this->flowLayoutPanel24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->flowLayoutPanel24->Location = System::Drawing::Point(3, 3);
			   this->flowLayoutPanel24->Name = L"flowLayoutPanel24";
			   this->flowLayoutPanel24->Size = System::Drawing::Size(354, 427);
			   this->flowLayoutPanel24->TabIndex = 3;
			   this->flowLayoutPanel24->WrapContents = false;
			   // 
			   // tabControl2
			   // 
			   this->tabControl2->Controls->Add(this->tabPage4);
			   this->tabControl2->Controls->Add(this->tabPage5);
			   this->tabControl2->Controls->Add(this->tabPage6);
			   this->tabControl2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->tabControl2->Location = System::Drawing::Point(3, 3);
			   this->tabControl2->Name = L"tabControl2";
			   this->tabControl2->SelectedIndex = 0;
			   this->tabControl2->Size = System::Drawing::Size(354, 424);
			   this->tabControl2->TabIndex = 4;
			   // 
			   // tabPage4
			   // 
			   this->tabPage4->Controls->Add(this->cardSettings1);
			   this->tabPage4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->tabPage4->Location = System::Drawing::Point(4, 24);
			   this->tabPage4->Name = L"tabPage4";
			   this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			   this->tabPage4->Size = System::Drawing::Size(346, 396);
			   this->tabPage4->TabIndex = 0;
			   this->tabPage4->UseVisualStyleBackColor = true;
			   // 
			   // cardSettings1
			   // 
			   this->cardSettings1->Controls->Add(this->tableLayoutPanel11);
			   this->cardSettings1->Controls->Add(this->tableLayoutPanel10);
			   this->cardSettings1->Controls->Add(this->groupBox1);
			   this->cardSettings1->Controls->Add(this->label32);
			   this->cardSettings1->Controls->Add(this->tableLayoutPanel6);
			   this->cardSettings1->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			   this->cardSettings1->Location = System::Drawing::Point(0, 0);
			   this->cardSettings1->Margin = System::Windows::Forms::Padding(0);
			   this->cardSettings1->Name = L"cardSettings1";
			   this->cardSettings1->Size = System::Drawing::Size(337, 337);
			   this->cardSettings1->TabIndex = 0;
			   this->cardSettings1->WrapContents = false;
			   // 
			   // tableLayoutPanel11
			   // 
			   this->tableLayoutPanel11->AutoSize = true;
			   this->tableLayoutPanel11->ColumnCount = 2;
			   this->tableLayoutPanel11->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel11->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   100)));
			   this->tableLayoutPanel11->Controls->Add(this->label1, 0, 0);
			   this->tableLayoutPanel11->Controls->Add(this->pump_name, 1, 0);
			   this->tableLayoutPanel11->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->tableLayoutPanel11->Location = System::Drawing::Point(3, 3);
			   this->tableLayoutPanel11->Name = L"tableLayoutPanel11";
			   this->tableLayoutPanel11->RowCount = 1;
			   this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   27)));
			   this->tableLayoutPanel11->Size = System::Drawing::Size(334, 27);
			   this->tableLayoutPanel11->TabIndex = 5;
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Dock = System::Windows::Forms::DockStyle::Right;
			   this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->label1->Location = System::Drawing::Point(4, 0);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(0, 27);
			   this->label1->TabIndex = 0;
			   this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // pump_name
			   // 
			   this->pump_name->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->pump_name->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->pump_name->Location = System::Drawing::Point(9, 3);
			   this->pump_name->Name = L"pump_name";
			   this->pump_name->Size = System::Drawing::Size(322, 21);
			   this->pump_name->TabIndex = 1;
			   // 
			   // tableLayoutPanel10
			   // 
			   this->tableLayoutPanel10->AutoSize = true;
			   this->tableLayoutPanel10->ColumnCount = 2;
			   this->tableLayoutPanel10->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel10->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   100)));
			   this->tableLayoutPanel10->Controls->Add(this->label2, 0, 0);
			   this->tableLayoutPanel10->Controls->Add(this->pump_enable, 1, 0);
			   this->tableLayoutPanel10->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->tableLayoutPanel10->Location = System::Drawing::Point(3, 43);
			   this->tableLayoutPanel10->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
			   this->tableLayoutPanel10->Name = L"tableLayoutPanel10";
			   this->tableLayoutPanel10->RowCount = 1;
			   this->tableLayoutPanel10->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel10->Size = System::Drawing::Size(334, 29);
			   this->tableLayoutPanel10->TabIndex = 4;
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->label2->Location = System::Drawing::Point(3, 0);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(1, 29);
			   this->label2->TabIndex = 0;
			   this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // pump_enable
			   // 
			   this->pump_enable->BackColor = System::Drawing::SystemColors::Control;
			   this->pump_enable->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pump_enable->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			   this->pump_enable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->pump_enable->FormattingEnabled = true;
			   this->pump_enable->Location = System::Drawing::Point(9, 3);
			   this->pump_enable->Name = L"pump_enable";
			   this->pump_enable->Size = System::Drawing::Size(322, 23);
			   this->pump_enable->TabIndex = 1;
			   // 
			   // groupBox1
			   // 
			   this->groupBox1->Controls->Add(this->flowLayoutPanel6);
			   this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->groupBox1->Location = System::Drawing::Point(3, 85);
			   this->groupBox1->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
			   this->groupBox1->Name = L"groupBox1";
			   this->groupBox1->Size = System::Drawing::Size(334, 137);
			   this->groupBox1->TabIndex = 2;
			   this->groupBox1->TabStop = false;
			   this->groupBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &WaterPumpForm::groupBox2_Paint);
			   // 
			   // flowLayoutPanel6
			   // 
			   this->flowLayoutPanel6->Controls->Add(this->tableLayoutPanel8);
			   this->flowLayoutPanel6->Controls->Add(this->tableLayoutPanel7);
			   this->flowLayoutPanel6->Controls->Add(this->tableLayoutPanel9);
			   this->flowLayoutPanel6->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->flowLayoutPanel6->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			   this->flowLayoutPanel6->Location = System::Drawing::Point(3, 17);
			   this->flowLayoutPanel6->Name = L"flowLayoutPanel6";
			   this->flowLayoutPanel6->Size = System::Drawing::Size(328, 117);
			   this->flowLayoutPanel6->TabIndex = 0;
			   this->flowLayoutPanel6->WrapContents = false;
			   // 
			   // tableLayoutPanel8
			   // 
			   this->tableLayoutPanel8->AutoSize = true;
			   this->tableLayoutPanel8->ColumnCount = 2;
			   this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   100)));
			   this->tableLayoutPanel8->Controls->Add(this->label3, 0, 0);
			   this->tableLayoutPanel8->Controls->Add(this->pump_mark, 1, 0);
			   this->tableLayoutPanel8->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->tableLayoutPanel8->Location = System::Drawing::Point(3, 3);
			   this->tableLayoutPanel8->Name = L"tableLayoutPanel8";
			   this->tableLayoutPanel8->RowCount = 1;
			   this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel8->Size = System::Drawing::Size(230, 27);
			   this->tableLayoutPanel8->TabIndex = 5;
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->label3->Location = System::Drawing::Point(3, 0);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(1, 27);
			   this->label3->TabIndex = 0;
			   this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // pump_mark
			   // 
			   this->pump_mark->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pump_mark->Location = System::Drawing::Point(9, 3);
			   this->pump_mark->Name = L"pump_mark";
			   this->pump_mark->Size = System::Drawing::Size(218, 21);
			   this->pump_mark->TabIndex = 1;
			   // 
			   // tableLayoutPanel7
			   // 
			   this->tableLayoutPanel7->AutoSize = true;
			   this->tableLayoutPanel7->ColumnCount = 2;
			   this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   100)));
			   this->tableLayoutPanel7->Controls->Add(this->label4, 0, 0);
			   this->tableLayoutPanel7->Controls->Add(this->pump_dim, 1, 0);
			   this->tableLayoutPanel7->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->tableLayoutPanel7->Location = System::Drawing::Point(3, 43);
			   this->tableLayoutPanel7->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
			   this->tableLayoutPanel7->Name = L"tableLayoutPanel7";
			   this->tableLayoutPanel7->RowCount = 1;
			   this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel7->Size = System::Drawing::Size(230, 27);
			   this->tableLayoutPanel7->TabIndex = 4;
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->label4->Location = System::Drawing::Point(3, 0);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(1, 27);
			   this->label4->TabIndex = 0;
			   this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // pump_dim
			   // 
			   this->pump_dim->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pump_dim->Location = System::Drawing::Point(9, 3);
			   this->pump_dim->Name = L"pump_dim";
			   this->pump_dim->Size = System::Drawing::Size(218, 21);
			   this->pump_dim->TabIndex = 1;
			   // 
			   // tableLayoutPanel9
			   // 
			   this->tableLayoutPanel9->AutoSize = true;
			   this->tableLayoutPanel9->ColumnCount = 2;
			   this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   100)));
			   this->tableLayoutPanel9->Controls->Add(this->label5, 0, 0);
			   this->tableLayoutPanel9->Controls->Add(this->pump_turn, 1, 0);
			   this->tableLayoutPanel9->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->tableLayoutPanel9->Location = System::Drawing::Point(3, 83);
			   this->tableLayoutPanel9->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
			   this->tableLayoutPanel9->Name = L"tableLayoutPanel9";
			   this->tableLayoutPanel9->RowCount = 1;
			   this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel9->Size = System::Drawing::Size(230, 27);
			   this->tableLayoutPanel9->TabIndex = 6;
			   // 
			   // label5
			   // 
			   this->label5->AutoSize = true;
			   this->label5->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->label5->Location = System::Drawing::Point(3, 0);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(1, 27);
			   this->label5->TabIndex = 0;
			   this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // pump_turn
			   // 
			   this->pump_turn->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pump_turn->Location = System::Drawing::Point(9, 3);
			   this->pump_turn->Name = L"pump_turn";
			   this->pump_turn->Size = System::Drawing::Size(218, 21);
			   this->pump_turn->TabIndex = 1;
			   // 
			   // label32
			   // 
			   this->label32->AutoSize = true;
			   this->label32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->label32->Location = System::Drawing::Point(3, 237);
			   this->label32->Margin = System::Windows::Forms::Padding(3, 12, 3, 3);
			   this->label32->Name = L"label32";
			   this->label32->Size = System::Drawing::Size(0, 15);
			   this->label32->TabIndex = 3;
			   // 
			   // tableLayoutPanel6
			   // 
			   this->tableLayoutPanel6->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Inset;
			   this->tableLayoutPanel6->ColumnCount = 5;
			   this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   12.62136F)));
			   this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   21.84466F)));
			   this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   21.84466F)));
			   this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   21.84466F)));
			   this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   21.84466F)));
			   this->tableLayoutPanel6->Controls->Add(this->label34, 0, 0);
			   this->tableLayoutPanel6->Controls->Add(this->label35, 1, 0);
			   this->tableLayoutPanel6->Controls->Add(this->label36, 2, 0);
			   this->tableLayoutPanel6->Controls->Add(this->label38, 4, 0);
			   this->tableLayoutPanel6->Controls->Add(this->numeric_input_point, 0, 1);
			   this->tableLayoutPanel6->Controls->Add(this->box_elem_q, 1, 1);
			   this->tableLayoutPanel6->Controls->Add(this->box_elem_h, 2, 1);
			   this->tableLayoutPanel6->Controls->Add(this->box_elem_n, 3, 1);
			   this->tableLayoutPanel6->Controls->Add(this->box_elem_m, 4, 1);
			   this->tableLayoutPanel6->Controls->Add(this->label37, 3, 0);
			   this->tableLayoutPanel6->Dock = System::Windows::Forms::DockStyle::Left;
			   this->tableLayoutPanel6->Location = System::Drawing::Point(3, 258);
			   this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
			   this->tableLayoutPanel6->RowCount = 2;
			   this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 46)));
			   this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			   this->tableLayoutPanel6->Size = System::Drawing::Size(334, 80);
			   this->tableLayoutPanel6->TabIndex = 3;
			   // 
			   // label34
			   // 
			   this->label34->AutoSize = true;
			   this->label34->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->label34->Location = System::Drawing::Point(5, 2);
			   this->label34->Name = L"label34";
			   this->label34->Size = System::Drawing::Size(34, 46);
			   this->label34->TabIndex = 0;
			   this->label34->Text = L"№";
			   this->label34->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label35
			   // 
			   this->label35->AutoSize = true;
			   this->label35->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label35->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->label35->Location = System::Drawing::Point(47, 2);
			   this->label35->Name = L"label35";
			   this->label35->Size = System::Drawing::Size(64, 46);
			   this->label35->TabIndex = 3;
			   this->label35->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label36
			   // 
			   this->label36->AutoSize = true;
			   this->label36->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->label36->Location = System::Drawing::Point(119, 2);
			   this->label36->Name = L"label36";
			   this->label36->Size = System::Drawing::Size(64, 46);
			   this->label36->TabIndex = 4;
			   this->label36->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label38
			   // 
			   this->label38->AutoSize = true;
			   this->label38->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label38->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->label38->Location = System::Drawing::Point(263, 2);
			   this->label38->Name = L"label38";
			   this->label38->Size = System::Drawing::Size(66, 46);
			   this->label38->TabIndex = 6;
			   this->label38->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // numeric_input_point
			   // 
			   this->numeric_input_point->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->numeric_input_point->Location = System::Drawing::Point(5, 53);
			   this->numeric_input_point->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 0, 0, 0, 0 });
			   this->numeric_input_point->Name = L"numeric_input_point";
			   this->numeric_input_point->Size = System::Drawing::Size(34, 21);
			   this->numeric_input_point->TabIndex = 7;
			   // 
			   // box_elem_q
			   // 
			   this->box_elem_q->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->box_elem_q->Location = System::Drawing::Point(47, 53);
			   this->box_elem_q->Name = L"box_elem_q";
			   this->box_elem_q->ReadOnly = true;
			   this->box_elem_q->Size = System::Drawing::Size(64, 21);
			   this->box_elem_q->TabIndex = 8;
			   // 
			   // box_elem_h
			   // 
			   this->box_elem_h->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->box_elem_h->Location = System::Drawing::Point(119, 53);
			   this->box_elem_h->Name = L"box_elem_h";
			   this->box_elem_h->ReadOnly = true;
			   this->box_elem_h->Size = System::Drawing::Size(64, 21);
			   this->box_elem_h->TabIndex = 9;
			   // 
			   // box_elem_n
			   // 
			   this->box_elem_n->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->box_elem_n->Location = System::Drawing::Point(191, 53);
			   this->box_elem_n->Name = L"box_elem_n";
			   this->box_elem_n->ReadOnly = true;
			   this->box_elem_n->Size = System::Drawing::Size(64, 21);
			   this->box_elem_n->TabIndex = 10;
			   // 
			   // box_elem_m
			   // 
			   this->box_elem_m->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->box_elem_m->Location = System::Drawing::Point(263, 53);
			   this->box_elem_m->Name = L"box_elem_m";
			   this->box_elem_m->ReadOnly = true;
			   this->box_elem_m->Size = System::Drawing::Size(66, 21);
			   this->box_elem_m->TabIndex = 11;
			   // 
			   // label37
			   // 
			   this->label37->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			   this->label37->Location = System::Drawing::Point(191, 2);
			   this->label37->Name = L"label37";
			   this->label37->Size = System::Drawing::Size(64, 46);
			   this->label37->TabIndex = 5;
			   this->label37->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // tabPage5
			   // 
			   this->tabPage5->Controls->Add(this->flowLayoutPanel10);
			   this->tabPage5->Location = System::Drawing::Point(4, 24);
			   this->tabPage5->Margin = System::Windows::Forms::Padding(0);
			   this->tabPage5->Name = L"tabPage5";
			   this->tabPage5->Size = System::Drawing::Size(346, 396);
			   this->tabPage5->TabIndex = 1;
			   this->tabPage5->UseVisualStyleBackColor = true;
			   // 
			   // flowLayoutPanel10
			   // 
			   this->flowLayoutPanel10->AutoSize = true;
			   this->flowLayoutPanel10->Controls->Add(this->label42);
			   this->flowLayoutPanel10->Controls->Add(this->groupBox2);
			   this->flowLayoutPanel10->Controls->Add(this->groupBox3);
			   this->flowLayoutPanel10->Controls->Add(this->groupBox9);
			   this->flowLayoutPanel10->Controls->Add(this->label43);
			   this->flowLayoutPanel10->Controls->Add(this->groupBox5);
			   this->flowLayoutPanel10->Controls->Add(this->groupBox4);
			   this->flowLayoutPanel10->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->flowLayoutPanel10->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			   this->flowLayoutPanel10->Location = System::Drawing::Point(0, 0);
			   this->flowLayoutPanel10->Margin = System::Windows::Forms::Padding(0);
			   this->flowLayoutPanel10->Name = L"flowLayoutPanel10";
			   this->flowLayoutPanel10->Size = System::Drawing::Size(346, 396);
			   this->flowLayoutPanel10->TabIndex = 1;
			   this->flowLayoutPanel10->WrapContents = false;
			   // 
			   // label42
			   // 
			   this->label42->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold));
			   this->label42->Location = System::Drawing::Point(3, 6);
			   this->label42->Margin = System::Windows::Forms::Padding(3, 6, 3, 6);
			   this->label42->Name = L"label42";
			   this->label42->Size = System::Drawing::Size(340, 15);
			   this->label42->TabIndex = 7;
			   // 
			   // groupBox2
			   // 
			   this->groupBox2->AutoSize = true;
			   this->groupBox2->BackColor = System::Drawing::Color::Transparent;
			   this->groupBox2->Controls->Add(this->tableLayoutPanel14);
			   this->groupBox2->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->groupBox2->Location = System::Drawing::Point(3, 30);
			   this->groupBox2->Name = L"groupBox2";
			   this->groupBox2->Size = System::Drawing::Size(340, 61);
			   this->groupBox2->TabIndex = 0;
			   this->groupBox2->TabStop = false;
			   this->groupBox2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &WaterPumpForm::groupBox2_Paint);
			   // 
			   // tableLayoutPanel14
			   // 
			   this->tableLayoutPanel14->AutoSize = true;
			   this->tableLayoutPanel14->ColumnCount = 6;
			   this->tableLayoutPanel14->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel14->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   33.33333F)));
			   this->tableLayoutPanel14->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel14->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   33.33333F)));
			   this->tableLayoutPanel14->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel14->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   33.33333F)));
			   this->tableLayoutPanel14->Controls->Add(this->label21, 0, 0);
			   this->tableLayoutPanel14->Controls->Add(this->pump_eff_min, 1, 0);
			   this->tableLayoutPanel14->Controls->Add(this->label22, 2, 0);
			   this->tableLayoutPanel14->Controls->Add(this->pump_eff_max, 3, 0);
			   this->tableLayoutPanel14->Controls->Add(this->label40, 4, 0);
			   this->tableLayoutPanel14->Controls->Add(this->input_data_q, 5, 0);
			   this->tableLayoutPanel14->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->tableLayoutPanel14->Location = System::Drawing::Point(3, 17);
			   this->tableLayoutPanel14->Margin = System::Windows::Forms::Padding(0);
			   this->tableLayoutPanel14->Name = L"tableLayoutPanel14";
			   this->tableLayoutPanel14->Padding = System::Windows::Forms::Padding(0, 7, 0, 7);
			   this->tableLayoutPanel14->RowCount = 1;
			   this->tableLayoutPanel14->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel14->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   27)));
			   this->tableLayoutPanel14->Size = System::Drawing::Size(334, 41);
			   this->tableLayoutPanel14->TabIndex = 7;
			   // 
			   // label21
			   // 
			   this->label21->AutoSize = true;
			   this->label21->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label21->Location = System::Drawing::Point(3, 7);
			   this->label21->Name = L"label21";
			   this->label21->Size = System::Drawing::Size(1, 27);
			   this->label21->TabIndex = 0;
			   this->label21->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // pump_eff_min
			   // 
			   this->pump_eff_min->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pump_eff_min->Location = System::Drawing::Point(9, 10);
			   this->pump_eff_min->Name = L"pump_eff_min";
			   this->pump_eff_min->Size = System::Drawing::Size(99, 21);
			   this->pump_eff_min->TabIndex = 1;
			   // 
			   // label22
			   // 
			   this->label22->AutoSize = true;
			   this->label22->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label22->Location = System::Drawing::Point(114, 7);
			   this->label22->Name = L"label22";
			   this->label22->Size = System::Drawing::Size(1, 27);
			   this->label22->TabIndex = 2;
			   this->label22->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // pump_eff_max
			   // 
			   this->pump_eff_max->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pump_eff_max->Location = System::Drawing::Point(120, 10);
			   this->pump_eff_max->Name = L"pump_eff_max";
			   this->pump_eff_max->Size = System::Drawing::Size(99, 21);
			   this->pump_eff_max->TabIndex = 3;
			   // 
			   // label40
			   // 
			   this->label40->AutoSize = true;
			   this->label40->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label40->Location = System::Drawing::Point(225, 7);
			   this->label40->Name = L"label40";
			   this->label40->Size = System::Drawing::Size(1, 27);
			   this->label40->TabIndex = 0;
			   this->label40->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // input_data_q
			   // 
			   this->input_data_q->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->input_data_q->Location = System::Drawing::Point(231, 10);
			   this->input_data_q->Name = L"input_data_q";
			   this->input_data_q->ReadOnly = true;
			   this->input_data_q->Size = System::Drawing::Size(100, 21);
			   this->input_data_q->TabIndex = 6;
			   // 
			   // groupBox3
			   // 
			   this->groupBox3->AutoSize = true;
			   this->groupBox3->Controls->Add(this->tableLayoutPanel15);
			   this->groupBox3->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->groupBox3->Location = System::Drawing::Point(3, 97);
			   this->groupBox3->Name = L"groupBox3";
			   this->groupBox3->Padding = System::Windows::Forms::Padding(3, 5, 3, 3);
			   this->groupBox3->Size = System::Drawing::Size(340, 63);
			   this->groupBox3->TabIndex = 4;
			   this->groupBox3->TabStop = false;
			   this->groupBox3->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &WaterPumpForm::groupBox2_Paint);
			   // 
			   // tableLayoutPanel15
			   // 
			   this->tableLayoutPanel15->AutoSize = true;
			   this->tableLayoutPanel15->ColumnCount = 6;
			   this->tableLayoutPanel15->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel15->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   33.33333F)));
			   this->tableLayoutPanel15->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel15->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   33.33333F)));
			   this->tableLayoutPanel15->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel15->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   33.33333F)));
			   this->tableLayoutPanel15->Controls->Add(this->label6, 0, 0);
			   this->tableLayoutPanel15->Controls->Add(this->pump_pres_min, 1, 0);
			   this->tableLayoutPanel15->Controls->Add(this->label7, 2, 0);
			   this->tableLayoutPanel15->Controls->Add(this->pump_pres_max, 3, 0);
			   this->tableLayoutPanel15->Controls->Add(this->label39, 4, 0);
			   this->tableLayoutPanel15->Controls->Add(this->input_data_h_in, 5, 0);
			   this->tableLayoutPanel15->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->tableLayoutPanel15->Location = System::Drawing::Point(3, 19);
			   this->tableLayoutPanel15->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
			   this->tableLayoutPanel15->Name = L"tableLayoutPanel15";
			   this->tableLayoutPanel15->Padding = System::Windows::Forms::Padding(0, 7, 0, 7);
			   this->tableLayoutPanel15->RowCount = 1;
			   this->tableLayoutPanel15->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel15->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   27)));
			   this->tableLayoutPanel15->Size = System::Drawing::Size(334, 41);
			   this->tableLayoutPanel15->TabIndex = 7;
			   // 
			   // label6
			   // 
			   this->label6->AutoSize = true;
			   this->label6->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->label6->Location = System::Drawing::Point(3, 7);
			   this->label6->Name = L"label6";
			   this->label6->Size = System::Drawing::Size(1, 27);
			   this->label6->TabIndex = 0;
			   this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // pump_pres_min
			   // 
			   this->pump_pres_min->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pump_pres_min->Location = System::Drawing::Point(9, 10);
			   this->pump_pres_min->Name = L"pump_pres_min";
			   this->pump_pres_min->Size = System::Drawing::Size(99, 21);
			   this->pump_pres_min->TabIndex = 1;
			   // 
			   // label7
			   // 
			   this->label7->AutoSize = true;
			   this->label7->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->label7->Location = System::Drawing::Point(114, 7);
			   this->label7->Name = L"label7";
			   this->label7->Size = System::Drawing::Size(1, 27);
			   this->label7->TabIndex = 2;
			   this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // pump_pres_max
			   // 
			   this->pump_pres_max->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pump_pres_max->Location = System::Drawing::Point(120, 10);
			   this->pump_pres_max->Name = L"pump_pres_max";
			   this->pump_pres_max->Size = System::Drawing::Size(99, 21);
			   this->pump_pres_max->TabIndex = 3;
			   // 
			   // label39
			   // 
			   this->label39->AutoSize = true;
			   this->label39->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label39->Location = System::Drawing::Point(225, 7);
			   this->label39->Name = L"label39";
			   this->label39->Size = System::Drawing::Size(1, 27);
			   this->label39->TabIndex = 0;
			   this->label39->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // input_data_h_in
			   // 
			   this->input_data_h_in->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->input_data_h_in->Location = System::Drawing::Point(231, 10);
			   this->input_data_h_in->Name = L"input_data_h_in";
			   this->input_data_h_in->ReadOnly = true;
			   this->input_data_h_in->Size = System::Drawing::Size(100, 21);
			   this->input_data_h_in->TabIndex = 6;
			   // 
			   // groupBox9
			   // 
			   this->groupBox9->AutoSize = true;
			   this->groupBox9->Controls->Add(this->tableLayoutPanel16);
			   this->groupBox9->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->groupBox9->Location = System::Drawing::Point(3, 166);
			   this->groupBox9->Name = L"groupBox9";
			   this->groupBox9->Padding = System::Windows::Forms::Padding(3, 5, 3, 3);
			   this->groupBox9->Size = System::Drawing::Size(340, 63);
			   this->groupBox9->TabIndex = 5;
			   this->groupBox9->TabStop = false;
			   this->groupBox9->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &WaterPumpForm::groupBox2_Paint);
			   // 
			   // tableLayoutPanel16
			   // 
			   this->tableLayoutPanel16->AutoSize = true;
			   this->tableLayoutPanel16->ColumnCount = 6;
			   this->tableLayoutPanel16->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel16->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   33.33333F)));
			   this->tableLayoutPanel16->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel16->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   33.33333F)));
			   this->tableLayoutPanel16->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel16->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   33.33333F)));
			   this->tableLayoutPanel16->Controls->Add(this->label14, 0, 0);
			   this->tableLayoutPanel16->Controls->Add(this->pump_pres_min_out, 1, 0);
			   this->tableLayoutPanel16->Controls->Add(this->label30, 2, 0);
			   this->tableLayoutPanel16->Controls->Add(this->pump_pres_max_out, 3, 0);
			   this->tableLayoutPanel16->Controls->Add(this->label41, 4, 0);
			   this->tableLayoutPanel16->Controls->Add(this->input_data_h_out, 5, 0);
			   this->tableLayoutPanel16->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->tableLayoutPanel16->Location = System::Drawing::Point(3, 19);
			   this->tableLayoutPanel16->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
			   this->tableLayoutPanel16->Name = L"tableLayoutPanel16";
			   this->tableLayoutPanel16->Padding = System::Windows::Forms::Padding(0, 7, 0, 7);
			   this->tableLayoutPanel16->RowCount = 1;
			   this->tableLayoutPanel16->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel16->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   27)));
			   this->tableLayoutPanel16->Size = System::Drawing::Size(334, 41);
			   this->tableLayoutPanel16->TabIndex = 7;
			   // 
			   // label14
			   // 
			   this->label14->AutoSize = true;
			   this->label14->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label14->Location = System::Drawing::Point(3, 7);
			   this->label14->Name = L"label14";
			   this->label14->Size = System::Drawing::Size(1, 27);
			   this->label14->TabIndex = 0;
			   this->label14->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // pump_pres_min_out
			   // 
			   this->pump_pres_min_out->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pump_pres_min_out->Location = System::Drawing::Point(9, 10);
			   this->pump_pres_min_out->Name = L"pump_pres_min_out";
			   this->pump_pres_min_out->Size = System::Drawing::Size(99, 21);
			   this->pump_pres_min_out->TabIndex = 1;
			   // 
			   // label30
			   // 
			   this->label30->AutoSize = true;
			   this->label30->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label30->Location = System::Drawing::Point(114, 7);
			   this->label30->Name = L"label30";
			   this->label30->Size = System::Drawing::Size(1, 27);
			   this->label30->TabIndex = 2;
			   this->label30->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // pump_pres_max_out
			   // 
			   this->pump_pres_max_out->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pump_pres_max_out->Location = System::Drawing::Point(120, 10);
			   this->pump_pres_max_out->Name = L"pump_pres_max_out";
			   this->pump_pres_max_out->Size = System::Drawing::Size(99, 21);
			   this->pump_pres_max_out->TabIndex = 3;
			   // 
			   // label41
			   // 
			   this->label41->AutoSize = true;
			   this->label41->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label41->Location = System::Drawing::Point(225, 7);
			   this->label41->Name = L"label41";
			   this->label41->Size = System::Drawing::Size(1, 27);
			   this->label41->TabIndex = 0;
			   this->label41->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // input_data_h_out
			   // 
			   this->input_data_h_out->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->input_data_h_out->Location = System::Drawing::Point(231, 10);
			   this->input_data_h_out->Name = L"input_data_h_out";
			   this->input_data_h_out->ReadOnly = true;
			   this->input_data_h_out->Size = System::Drawing::Size(100, 21);
			   this->input_data_h_out->TabIndex = 6;
			   // 
			   // label43
			   // 
			   this->label43->AutoSize = true;
			   this->label43->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold));
			   this->label43->Location = System::Drawing::Point(3, 238);
			   this->label43->Margin = System::Windows::Forms::Padding(3, 6, 3, 3);
			   this->label43->Name = L"label43";
			   this->label43->Size = System::Drawing::Size(0, 15);
			   this->label43->TabIndex = 8;
			   // 
			   // groupBox5
			   // 
			   this->groupBox5->AutoSize = true;
			   this->groupBox5->Controls->Add(this->tableLayoutPanel12);
			   this->groupBox5->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->groupBox5->Location = System::Drawing::Point(3, 259);
			   this->groupBox5->Name = L"groupBox5";
			   this->groupBox5->Padding = System::Windows::Forms::Padding(3, 5, 3, 3);
			   this->groupBox5->Size = System::Drawing::Size(340, 49);
			   this->groupBox5->TabIndex = 6;
			   this->groupBox5->TabStop = false;
			   this->groupBox5->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &WaterPumpForm::groupBox2_Paint);
			   // 
			   // tableLayoutPanel12
			   // 
			   this->tableLayoutPanel12->AutoSize = true;
			   this->tableLayoutPanel12->ColumnCount = 4;
			   this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   50)));
			   this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   50)));
			   this->tableLayoutPanel12->Controls->Add(this->label10, 0, 0);
			   this->tableLayoutPanel12->Controls->Add(this->pump_dim_min, 1, 0);
			   this->tableLayoutPanel12->Controls->Add(this->label11, 2, 0);
			   this->tableLayoutPanel12->Controls->Add(this->pump_dim_max, 3, 0);
			   this->tableLayoutPanel12->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->tableLayoutPanel12->Location = System::Drawing::Point(3, 19);
			   this->tableLayoutPanel12->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
			   this->tableLayoutPanel12->Name = L"tableLayoutPanel12";
			   this->tableLayoutPanel12->RowCount = 1;
			   this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel12->Size = System::Drawing::Size(334, 27);
			   this->tableLayoutPanel12->TabIndex = 4;
			   // 
			   // label10
			   // 
			   this->label10->AutoSize = true;
			   this->label10->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label10->Location = System::Drawing::Point(3, 0);
			   this->label10->Name = L"label10";
			   this->label10->Size = System::Drawing::Size(1, 27);
			   this->label10->TabIndex = 0;
			   this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // pump_dim_min
			   // 
			   this->pump_dim_min->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pump_dim_min->Location = System::Drawing::Point(9, 3);
			   this->pump_dim_min->Name = L"pump_dim_min";
			   this->pump_dim_min->Size = System::Drawing::Size(155, 21);
			   this->pump_dim_min->TabIndex = 1;
			   // 
			   // label11
			   // 
			   this->label11->AutoSize = true;
			   this->label11->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label11->Location = System::Drawing::Point(170, 0);
			   this->label11->Name = L"label11";
			   this->label11->Size = System::Drawing::Size(1, 27);
			   this->label11->TabIndex = 2;
			   this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // pump_dim_max
			   // 
			   this->pump_dim_max->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pump_dim_max->Location = System::Drawing::Point(176, 3);
			   this->pump_dim_max->Name = L"pump_dim_max";
			   this->pump_dim_max->Size = System::Drawing::Size(155, 21);
			   this->pump_dim_max->TabIndex = 3;
			   // 
			   // groupBox4
			   // 
			   this->groupBox4->AutoSize = true;
			   this->groupBox4->Controls->Add(this->tableLayoutPanel13);
			   this->groupBox4->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->groupBox4->Location = System::Drawing::Point(3, 314);
			   this->groupBox4->Name = L"groupBox4";
			   this->groupBox4->Padding = System::Windows::Forms::Padding(3, 5, 3, 3);
			   this->groupBox4->Size = System::Drawing::Size(340, 49);
			   this->groupBox4->TabIndex = 4;
			   this->groupBox4->TabStop = false;
			   this->groupBox4->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &WaterPumpForm::groupBox2_Paint);
			   // 
			   // tableLayoutPanel13
			   // 
			   this->tableLayoutPanel13->AutoSize = true;
			   this->tableLayoutPanel13->ColumnCount = 4;
			   this->tableLayoutPanel13->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel13->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   50)));
			   this->tableLayoutPanel13->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			   this->tableLayoutPanel13->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   50)));
			   this->tableLayoutPanel13->Controls->Add(this->label8, 0, 0);
			   this->tableLayoutPanel13->Controls->Add(this->pump_turn_min, 1, 0);
			   this->tableLayoutPanel13->Controls->Add(this->label9, 2, 0);
			   this->tableLayoutPanel13->Controls->Add(this->pump_turn_max, 3, 0);
			   this->tableLayoutPanel13->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->tableLayoutPanel13->Location = System::Drawing::Point(3, 19);
			   this->tableLayoutPanel13->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
			   this->tableLayoutPanel13->Name = L"tableLayoutPanel13";
			   this->tableLayoutPanel13->RowCount = 1;
			   this->tableLayoutPanel13->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			   this->tableLayoutPanel13->Size = System::Drawing::Size(334, 27);
			   this->tableLayoutPanel13->TabIndex = 4;
			   // 
			   // label8
			   // 
			   this->label8->AutoSize = true;
			   this->label8->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->label8->Location = System::Drawing::Point(3, 0);
			   this->label8->Name = L"label8";
			   this->label8->Size = System::Drawing::Size(1, 27);
			   this->label8->TabIndex = 0;
			   this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // pump_turn_min
			   // 
			   this->pump_turn_min->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pump_turn_min->Location = System::Drawing::Point(9, 3);
			   this->pump_turn_min->Name = L"pump_turn_min";
			   this->pump_turn_min->Size = System::Drawing::Size(155, 21);
			   this->pump_turn_min->TabIndex = 1;
			   // 
			   // label9
			   // 
			   this->label9->AutoSize = true;
			   this->label9->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			   this->label9->Location = System::Drawing::Point(170, 0);
			   this->label9->Name = L"label9";
			   this->label9->Size = System::Drawing::Size(1, 27);
			   this->label9->TabIndex = 2;
			   this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // pump_turn_max
			   // 
			   this->pump_turn_max->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pump_turn_max->Location = System::Drawing::Point(176, 3);
			   this->pump_turn_max->Name = L"pump_turn_max";
			   this->pump_turn_max->Size = System::Drawing::Size(155, 21);
			   this->pump_turn_max->TabIndex = 3;
			   // 
			   // tabPage6
			   // 
			   this->tabPage6->Controls->Add(this->flowLayoutPanel19);
			   this->tabPage6->Location = System::Drawing::Point(4, 24);
			   this->tabPage6->Name = L"tabPage6";
			   this->tabPage6->Padding = System::Windows::Forms::Padding(3);
			   this->tabPage6->Size = System::Drawing::Size(346, 396);
			   this->tabPage6->TabIndex = 2;
			   this->tabPage6->UseVisualStyleBackColor = true;
			   // 
			   // flowLayoutPanel19
			   // 
			   this->flowLayoutPanel19->Controls->Add(this->flowLayoutPanel20);
			   this->flowLayoutPanel19->Controls->Add(this->flowLayoutPanel22);
			   this->flowLayoutPanel19->Controls->Add(this->flowLayoutPanel14);
			   this->flowLayoutPanel19->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			   this->flowLayoutPanel19->Location = System::Drawing::Point(0, 0);
			   this->flowLayoutPanel19->Name = L"flowLayoutPanel19";
			   this->flowLayoutPanel19->Size = System::Drawing::Size(337, 337);
			   this->flowLayoutPanel19->TabIndex = 2;
			   this->flowLayoutPanel19->WrapContents = false;
			   // 
			   // flowLayoutPanel20
			   // 
			   this->flowLayoutPanel20->AutoSize = true;
			   this->flowLayoutPanel20->Controls->Add(this->label18);
			   this->flowLayoutPanel20->Controls->Add(this->flowLayoutPanel21);
			   this->flowLayoutPanel20->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			   this->flowLayoutPanel20->Location = System::Drawing::Point(3, 3);
			   this->flowLayoutPanel20->Name = L"flowLayoutPanel20";
			   this->flowLayoutPanel20->Size = System::Drawing::Size(331, 61);
			   this->flowLayoutPanel20->TabIndex = 0;
			   this->flowLayoutPanel20->WrapContents = false;
			   // 
			   // label18
			   // 
			   this->label18->AutoSize = true;
			   this->label18->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label18->Location = System::Drawing::Point(3, 0);
			   this->label18->Name = L"label18";
			   this->label18->Size = System::Drawing::Size(325, 15);
			   this->label18->TabIndex = 0;
			   this->label18->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // flowLayoutPanel21
			   // 
			   this->flowLayoutPanel21->Controls->Add(this->pump_slide_dim);
			   this->flowLayoutPanel21->Controls->Add(this->pump_cur_dim);
			   this->flowLayoutPanel21->Location = System::Drawing::Point(3, 20);
			   this->flowLayoutPanel21->Margin = System::Windows::Forms::Padding(3, 5, 3, 3);
			   this->flowLayoutPanel21->Name = L"flowLayoutPanel21";
			   this->flowLayoutPanel21->Size = System::Drawing::Size(325, 38);
			   this->flowLayoutPanel21->TabIndex = 1;
			   this->flowLayoutPanel21->WrapContents = false;
			   // 
			   // pump_slide_dim
			   // 
			   this->pump_slide_dim->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(249)), static_cast<System::Int32>(static_cast<System::Byte>(249)),
				   static_cast<System::Int32>(static_cast<System::Byte>(249)));
			   this->pump_slide_dim->Enabled = false;
			   this->pump_slide_dim->Location = System::Drawing::Point(3, 3);
			   this->pump_slide_dim->Name = L"pump_slide_dim";
			   this->pump_slide_dim->Size = System::Drawing::Size(213, 45);
			   this->pump_slide_dim->TabIndex = 4;
			   // 
			   // pump_cur_dim
			   // 
			   this->pump_cur_dim->Enabled = false;
			   this->pump_cur_dim->Location = System::Drawing::Point(222, 3);
			   this->pump_cur_dim->Name = L"pump_cur_dim";
			   this->pump_cur_dim->Size = System::Drawing::Size(100, 21);
			   this->pump_cur_dim->TabIndex = 5;
			   // 
			   // flowLayoutPanel22
			   // 
			   this->flowLayoutPanel22->AutoSize = true;
			   this->flowLayoutPanel22->Controls->Add(this->label19);
			   this->flowLayoutPanel22->Controls->Add(this->flowLayoutPanel23);
			   this->flowLayoutPanel22->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			   this->flowLayoutPanel22->Location = System::Drawing::Point(3, 70);
			   this->flowLayoutPanel22->Name = L"flowLayoutPanel22";
			   this->flowLayoutPanel22->Size = System::Drawing::Size(331, 61);
			   this->flowLayoutPanel22->TabIndex = 1;
			   this->flowLayoutPanel22->WrapContents = false;
			   // 
			   // label19
			   // 
			   this->label19->AutoSize = true;
			   this->label19->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label19->Location = System::Drawing::Point(3, 0);
			   this->label19->Name = L"label19";
			   this->label19->Size = System::Drawing::Size(325, 15);
			   this->label19->TabIndex = 0;
			   this->label19->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // flowLayoutPanel23
			   // 
			   this->flowLayoutPanel23->Controls->Add(this->pump_slide_turn);
			   this->flowLayoutPanel23->Controls->Add(this->pump_cur_turn);
			   this->flowLayoutPanel23->Location = System::Drawing::Point(3, 20);
			   this->flowLayoutPanel23->Margin = System::Windows::Forms::Padding(3, 5, 3, 3);
			   this->flowLayoutPanel23->Name = L"flowLayoutPanel23";
			   this->flowLayoutPanel23->Size = System::Drawing::Size(325, 38);
			   this->flowLayoutPanel23->TabIndex = 1;
			   this->flowLayoutPanel23->WrapContents = false;
			   // 
			   // pump_slide_turn
			   // 
			   this->pump_slide_turn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(249)), static_cast<System::Int32>(static_cast<System::Byte>(249)),
				   static_cast<System::Int32>(static_cast<System::Byte>(249)));
			   this->pump_slide_turn->Enabled = false;
			   this->pump_slide_turn->Location = System::Drawing::Point(3, 3);
			   this->pump_slide_turn->Name = L"pump_slide_turn";
			   this->pump_slide_turn->Size = System::Drawing::Size(213, 45);
			   this->pump_slide_turn->TabIndex = 4;
			   // 
			   // pump_cur_turn
			   // 
			   this->pump_cur_turn->Enabled = false;
			   this->pump_cur_turn->Location = System::Drawing::Point(222, 3);
			   this->pump_cur_turn->Name = L"pump_cur_turn";
			   this->pump_cur_turn->Size = System::Drawing::Size(100, 21);
			   this->pump_cur_turn->TabIndex = 5;
			   // 
			   // flowLayoutPanel14
			   // 
			   this->flowLayoutPanel14->AutoSize = true;
			   this->flowLayoutPanel14->Controls->Add(this->label12);
			   this->flowLayoutPanel14->Controls->Add(this->flowLayoutPanel15);
			   this->flowLayoutPanel14->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			   this->flowLayoutPanel14->Location = System::Drawing::Point(3, 137);
			   this->flowLayoutPanel14->Name = L"flowLayoutPanel14";
			   this->flowLayoutPanel14->Size = System::Drawing::Size(331, 61);
			   this->flowLayoutPanel14->TabIndex = 2;
			   this->flowLayoutPanel14->WrapContents = false;
			   // 
			   // label12
			   // 
			   this->label12->AutoSize = true;
			   this->label12->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->label12->Location = System::Drawing::Point(3, 0);
			   this->label12->Name = L"label12";
			   this->label12->Size = System::Drawing::Size(325, 15);
			   this->label12->TabIndex = 0;
			   this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // flowLayoutPanel15
			   // 
			   this->flowLayoutPanel15->Controls->Add(this->pump_slide_s);
			   this->flowLayoutPanel15->Controls->Add(this->pump_cur_s);
			   this->flowLayoutPanel15->Location = System::Drawing::Point(3, 20);
			   this->flowLayoutPanel15->Margin = System::Windows::Forms::Padding(3, 5, 3, 3);
			   this->flowLayoutPanel15->Name = L"flowLayoutPanel15";
			   this->flowLayoutPanel15->Size = System::Drawing::Size(325, 38);
			   this->flowLayoutPanel15->TabIndex = 1;
			   this->flowLayoutPanel15->WrapContents = false;
			   // 
			   // pump_slide_s
			   // 
			   this->pump_slide_s->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(249)), static_cast<System::Int32>(static_cast<System::Byte>(249)),
				   static_cast<System::Int32>(static_cast<System::Byte>(249)));
			   this->pump_slide_s->Enabled = false;
			   this->pump_slide_s->Location = System::Drawing::Point(3, 3);
			   this->pump_slide_s->Maximum = 1000;
			   this->pump_slide_s->Name = L"pump_slide_s";
			   this->pump_slide_s->Size = System::Drawing::Size(213, 45);
			   this->pump_slide_s->TabIndex = 4;
			   this->pump_slide_s->TickFrequency = 100;
			   // 
			   // pump_cur_s
			   // 
			   this->pump_cur_s->Enabled = false;
			   this->pump_cur_s->Location = System::Drawing::Point(222, 3);
			   this->pump_cur_s->Name = L"pump_cur_s";
			   this->pump_cur_s->Size = System::Drawing::Size(100, 21);
			   this->pump_cur_s->TabIndex = 5;
			   // 
			   // tableLayoutPanel1
			   // 
			   this->tableLayoutPanel1->ColumnCount = 2;
			   this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   360)));
			   this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   360)));
			   this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel24, 0, 0);
			   this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel1, 1, 1);
			   this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel16, 1, 0);
			   this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			   this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(0);
			   this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			   this->tableLayoutPanel1->RowCount = 2;
			   this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			   this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 40)));
			   this->tableLayoutPanel1->Size = System::Drawing::Size(720, 473);
			   this->tableLayoutPanel1->TabIndex = 0;
			   // 
			   // toolTip1
			   // 
			   this->toolTip1->AutoPopDelay = 5000;
			   this->toolTip1->InitialDelay = 200;
			   this->toolTip1->ReshowDelay = 500;
			   this->toolTip1->ShowAlways = true;
			   // 
			   // WaterPumpForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(720, 473);
			   this->Controls->Add(this->tableLayoutPanel1);
			   this->KeyPreview = true;
			   this->Name = L"WaterPumpForm";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"WaterPump";
			   this->Resize += gcnew System::EventHandler(this, &WaterPumpForm::WaterPump_Resize);
			   this->flowLayoutPanel16->ResumeLayout(false);
			   this->panel4->ResumeLayout(false);
			   this->flowLayoutPanel2->ResumeLayout(false);
			   this->tableLayoutPanel5->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			   this->panel2->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			   this->panel3->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart3))->EndInit();
			   this->tabControl1->ResumeLayout(false);
			   this->flowLayoutPanel18->ResumeLayout(false);
			   this->flowLayoutPanel18->PerformLayout();
			   this->groupBox7->ResumeLayout(false);
			   this->groupBox7->PerformLayout();
			   this->tableLayoutPanel2->ResumeLayout(false);
			   this->tableLayoutPanel2->PerformLayout();
			   this->flowLayoutPanel17->ResumeLayout(false);
			   this->flowLayoutPanel17->PerformLayout();
			   this->groupBox6->ResumeLayout(false);
			   this->groupBox6->PerformLayout();
			   this->tableLayoutPanel3->ResumeLayout(false);
			   this->tableLayoutPanel3->PerformLayout();
			   this->groupBox8->ResumeLayout(false);
			   this->groupBox8->PerformLayout();
			   this->tableLayoutPanel4->ResumeLayout(false);
			   this->tableLayoutPanel4->PerformLayout();
			   this->flowLayoutPanel1->ResumeLayout(false);
			   this->flowLayoutPanel1->PerformLayout();
			   this->flowLayoutPanel24->ResumeLayout(false);
			   this->tabControl2->ResumeLayout(false);
			   this->tabPage4->ResumeLayout(false);
			   this->cardSettings1->ResumeLayout(false);
			   this->cardSettings1->PerformLayout();
			   this->tableLayoutPanel11->ResumeLayout(false);
			   this->tableLayoutPanel11->PerformLayout();
			   this->tableLayoutPanel10->ResumeLayout(false);
			   this->tableLayoutPanel10->PerformLayout();
			   this->groupBox1->ResumeLayout(false);
			   this->flowLayoutPanel6->ResumeLayout(false);
			   this->flowLayoutPanel6->PerformLayout();
			   this->tableLayoutPanel8->ResumeLayout(false);
			   this->tableLayoutPanel8->PerformLayout();
			   this->tableLayoutPanel7->ResumeLayout(false);
			   this->tableLayoutPanel7->PerformLayout();
			   this->tableLayoutPanel9->ResumeLayout(false);
			   this->tableLayoutPanel9->PerformLayout();
			   this->tableLayoutPanel6->ResumeLayout(false);
			   this->tableLayoutPanel6->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numeric_input_point))->EndInit();
			   this->tabPage5->ResumeLayout(false);
			   this->tabPage5->PerformLayout();
			   this->flowLayoutPanel10->ResumeLayout(false);
			   this->flowLayoutPanel10->PerformLayout();
			   this->groupBox2->ResumeLayout(false);
			   this->groupBox2->PerformLayout();
			   this->tableLayoutPanel14->ResumeLayout(false);
			   this->tableLayoutPanel14->PerformLayout();
			   this->groupBox3->ResumeLayout(false);
			   this->groupBox3->PerformLayout();
			   this->tableLayoutPanel15->ResumeLayout(false);
			   this->tableLayoutPanel15->PerformLayout();
			   this->groupBox9->ResumeLayout(false);
			   this->groupBox9->PerformLayout();
			   this->tableLayoutPanel16->ResumeLayout(false);
			   this->tableLayoutPanel16->PerformLayout();
			   this->groupBox5->ResumeLayout(false);
			   this->groupBox5->PerformLayout();
			   this->tableLayoutPanel12->ResumeLayout(false);
			   this->tableLayoutPanel12->PerformLayout();
			   this->groupBox4->ResumeLayout(false);
			   this->groupBox4->PerformLayout();
			   this->tableLayoutPanel13->ResumeLayout(false);
			   this->tableLayoutPanel13->PerformLayout();
			   this->tabPage6->ResumeLayout(false);
			   this->flowLayoutPanel19->ResumeLayout(false);
			   this->flowLayoutPanel19->PerformLayout();
			   this->flowLayoutPanel20->ResumeLayout(false);
			   this->flowLayoutPanel20->PerformLayout();
			   this->flowLayoutPanel21->ResumeLayout(false);
			   this->flowLayoutPanel21->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pump_slide_dim))->EndInit();
			   this->flowLayoutPanel22->ResumeLayout(false);
			   this->flowLayoutPanel22->PerformLayout();
			   this->flowLayoutPanel23->ResumeLayout(false);
			   this->flowLayoutPanel23->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pump_slide_turn))->EndInit();
			   this->flowLayoutPanel14->ResumeLayout(false);
			   this->flowLayoutPanel14->PerformLayout();
			   this->flowLayoutPanel15->ResumeLayout(false);
			   this->flowLayoutPanel15->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pump_slide_s))->EndInit();
			   this->tableLayoutPanel1->ResumeLayout(false);
			   this->tableLayoutPanel1->PerformLayout();
			   this->ResumeLayout(false);

		   }
#pragma endregion

	private: System::Void tabControl1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		TabControl^ tabCont = safe_cast<TabControl^>(sender);

		int lastTab = 0;

		if (listTab->ContainsKey(tabCont->Name))
			lastTab = listTab[tabCont->Name];

		int selectIndex = tabCont->SelectedIndex;
		if (lastTab == selectIndex && e != nullptr)
			return;

		auto linkToElem = tabCont->Parent->Controls[0];

		if (selectIndex + tab_offset > linkToElem->Controls->Count) {
			selectIndex -= selectIndex + tab_offset - linkToElem->Controls->Count;
		}

			for (int i = 0; i < linkToElem->Controls->Count; i++) {
				if (i >= selectIndex && i < selectIndex + tab_offset) 
					linkToElem->Controls[i]->Show();
				else
					linkToElem->Controls[i]->Hide();
			}

			linkToElem->Parent->Size = System::Drawing::Size(8 + tab_offset * 343, linkToElem->Parent->Size.Height);
			linkToElem->Size = System::Drawing::Size(tab_offset * 343, linkToElem->Size.Height);

		listTab[tabCont->Name] = selectIndex;
	}

	private: int last_width = 0;
	private: int tab_offset = 1;
	private: System::Void WaterPump_Resize(System::Object^ sender, System::EventArgs^ e) {
		Control^ control = safe_cast<Control^>(sender);

		if (control->Size.Width < 736 || control->Size.Height < 452)
			control->Size = System::Drawing::Size(Math::Max(control->Size.Width, 736), Math::Max(control->Size.Height, 452));


		if (last_width == 0)
			last_width = control->Size.Width;
		else if (last_width == control->Size.Width)
			return;

		int newTabOffset = Math::Min(3, Math::Max(1, (control->Size.Width - 393) / 343));

		if (newTabOffset == tab_offset)
			return;

		tab_offset = newTabOffset;
		tabControl1_SelectedIndexChanged(this->tabControl1, nullptr);
		last_width = control->Size.Width;
	}

	
	private: System::Void groupBox2_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ gfx = e->Graphics;
		Pen^ p = gcnew Pen(Color::FromArgb(80, 0, 0, 0), 1);
		Pen^ pClear = gcnew Pen(Color::White, 1);

		GroupBox^ gb = dynamic_cast<GroupBox^>(sender);

		Rectangle^ r = gcnew Rectangle(0, 0, gb->Width, gb->Height);
		System::Drawing::Font^ FMSS = gcnew System::Drawing::Font(gcnew System::Drawing::FontFamily("Microsoft Sans Serif"), 9);

		SizeF^ sizeTextX = e->Graphics->MeasureString(gb->Text, FMSS);
		gfx->DrawLine(pClear, 0, 7, 0, r->Height - 2);
		gfx->DrawLine(p, 0, 7, 0, r->Height - 2);

		gfx->DrawLine(pClear, 0, 7, 6, 7);
		gfx->DrawLine(p, 0, 7, 6, 7);

		gfx->DrawLine(pClear, r->Width - 1, 7, r->Width - 1, r->Height - 2);
		gfx->DrawLine(p, r->Width - 1, 7, r->Width - 1, r->Height - 2);

		gfx->DrawLine(pClear, r->Width, r->Height - 2, 1, r->Height - 2);
		gfx->DrawLine(p, r->Width, r->Height - 2, 1, r->Height - 2);

		gfx->DrawLine(pClear, (int)(8 + 2 + sizeTextX->Width), 7, r->Width - 1, 7);
		gfx->DrawLine(p, (int)(8 + 2 + sizeTextX->Width), 7, r->Width - 1, 7);
	}


};
}
