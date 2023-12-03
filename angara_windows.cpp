#pragma once

#include <msclr/gcroot.h>
#include "utils.h"
#include "WaterPump.h"
#include "angara_windows.h"


namespace angarawindows {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Data::OleDb;

	const char* urlConnect;


	void setDBConnect(const char* connect) {
		urlConnect = connect;
		Application::SetCompatibleTextRenderingDefault(false);
		Application::EnableVisualStyles();
	}

	[STAThreadAttribute]
		void abstactShow(System::Windows::Forms::Form^ form) {
		Application::Run(form);
	}

	void abstactQuery(String^ sql, std::function<void(msclr::gcroot<OleDbDataReader^>)> func) {
		OleDbConnection^ connection = gcnew OleDbConnection(gcnew String(urlConnect));
		connection->Open();
		OleDbCommand^ command = gcnew OleDbCommand(sql, connection);
		OleDbDataReader^ reader = command->ExecuteReader();
		func(reader);
		reader->Close();
		connection->Close();
	};

	[STAThreadAttribute]
	void WaterPumpWindow::show(int idLink) {
		angarawindows::WaterPump form(this);
		msclr::gcroot <WaterPump^> stackLink = %form;

		this->name.addEventListener([&stackLink](const std::string & name) {
			stackLink->pump_name->Text = gcnew String(name.c_str());
		});
		this->mark.addEventListener([&stackLink](const std::string& name) {
			stackLink->pump_mark->Text = gcnew String(name.c_str());
		});
		this->diameter_nominal.addEventListener([&stackLink, this](double & value) {
			if (this->diameter_max.isUserNotEdit()) {
				this->diameter_max.setValue(value);
			}
			if (this->diameter_min.isUserNotEdit()) {
				this->diameter_min.setValue(0);
			}

			SuperTextSetter(stackLink->pump_dim, gcnew String(value + ""));
		});
		this->turnovers_nominal.addEventListener([&stackLink, this](const int& value) {
			if (this->turnovers_max.isUserNotEdit()) {
				this->turnovers_max.setValue(value);
			}
			if (this->turnovers_min.isUserNotEdit()) {
				this->turnovers_min.setValue(0);
			}
			SuperTextSetter(stackLink->pump_turn, gcnew String(value + ""));
		});
		this->turnovers_current.addEventListener([&stackLink, this](const int& value) {
			SuperTextSetter(stackLink->pump_cur_turn, gcnew String(value + ""));
			stackLink->pump_slide_turn->Value = value;

			this->k.setValue((this->turnovers_current.getValue() * this->diameter_current.getValue()) / (this->turnovers_nominal.getValue() * this->diameter_nominal.getValue()));
			});
		this->diameter_current.addEventListener([&stackLink, this](const int& value) {
			SuperTextSetter(stackLink->pump_cur_dim, gcnew String(value + ""));
			stackLink->pump_slide_dim->Value = value;

			this->k.setValue((this->turnovers_current.getValue() * this->diameter_current.getValue()) / (this->turnovers_nominal.getValue() * this->diameter_nominal.getValue()));
		});
		this->resistance_min.addEventListener([&stackLink, this](const double & value) {

			stackLink->pump_slide_s->Maximum = 100;
			stackLink->pump_slide_s->TickFrequency = 10;
		});
		this->resistance_current.addEventListener([&stackLink, this](const double& value) {
			SuperTextSetter(stackLink->pump_cur_s, gcnew String(value + ""));
			stackLink->pump_slide_s->Value = Math::Round(value / this->resistance_min.getValue() * 100);
			this->k.throwEvent();
		});

		this->efficiency_min.addEventListener([&stackLink](const int& value) {
			SuperTextSetter(stackLink->pump_eff_min, gcnew String(value + ""));
			stackLink->chart1->Invalidate();
			stackLink->chart2->Invalidate();
			stackLink->chart3->Invalidate();
		});
		this->efficiency_max.addEventListener([&stackLink](const int& value) {
			SuperTextSetter(stackLink->pump_eff_max, gcnew String(value + ""));
			stackLink->chart1->Invalidate();
			stackLink->chart2->Invalidate();
			stackLink->chart3->Invalidate();
			});
		this->pressure_in_min.addEventListener([&stackLink](const int& value) {
			SuperTextSetter(stackLink->pump_pres_min, gcnew String(value + ""));
		});
		this->pressure_in_max.addEventListener([&stackLink](const int& value) {
			SuperTextSetter(stackLink->pump_pres_max, gcnew String(value + ""));
		});
		this->pressure_out_min.addEventListener([&stackLink](const int& value) {
			SuperTextSetter(stackLink->pump_pres_min_out, gcnew String(value + ""));
		});
		this->pressure_out_max.addEventListener([&stackLink](const int& value) {
			SuperTextSetter(stackLink->pump_pres_max_out, gcnew String(value + ""));
		});
		this->diameter_min.addEventListener([&stackLink, this](const int& value) {
			SuperTextSetter(stackLink->pump_dim_min, gcnew String(value + ""));

			stackLink->pump_slide_dim->Minimum = value;

			stackLink->pump_slide_dim->TickFrequency = (this->diameter_max.getValue() - value) / 10;
		});
		this->diameter_max.addEventListener([&stackLink, this](const int& value) {
			SuperTextSetter(stackLink->pump_dim_max, gcnew String(value + ""));

			stackLink->pump_slide_dim->Maximum = value;
			if(this->diameter_current.isUserNotEdit() || this->diameter_current.getValue() > value)
				this->diameter_current.setValue(value);
		});
		this->turnovers_min.addEventListener([&stackLink, this](const int& value) {
			SuperTextSetter(stackLink->pump_turn_min, gcnew String(value + ""));

			stackLink->pump_slide_turn->Minimum = value;
			stackLink->pump_slide_turn->TickFrequency = (this->turnovers_max.getValue() - value) / 10;
		});
		this->turnovers_max.addEventListener([&stackLink, this](const int& value) {
			SuperTextSetter(stackLink->pump_turn_max, gcnew String(value + ""));

			stackLink->pump_slide_turn->Maximum = value;
			if (this->turnovers_current.isUserNotEdit() || this->turnovers_current.getValue() > value)
				this->turnovers_current.setValue(value);
		});

		this->H0.addEventListener([&stackLink](const double& value) {
			stackLink->box_k_h0->Text = value + "";
		});
		this->N0.addEventListener([&stackLink](const double& value) {
			stackLink->box_k_n0->Text = value + "";
		});
		this->C.addEventListener([&stackLink](const double& value) {
			stackLink->box_k_c->Text = value + "";
		});
		this->S.addEventListener([&stackLink](const double& value) {
			stackLink->box_k_s->Text = value + "";
		});

		this->elemMove.addEventListener([&stackLink](const int& value) {
			stackLink->chart1->Series[2]->Points->Clear();
			stackLink->chart2->Series[2]->Points->Clear();
			stackLink->chart3->Series[2]->Points->Clear();

			stackLink->numeric_input_point->Value = value + 1;

			if (value != -1) {
				auto p1 = stackLink->chart1->Series[3]->Points[value];
				auto p2 = stackLink->chart2->Series[3]->Points[value];
				auto p3 = stackLink->chart3->Series[3]->Points[value];

				stackLink->chart1->Series[2]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(p1->XValue, p1->YValues[0]));
				stackLink->chart2->Series[2]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(p2->XValue, p2->YValues[0]));
				stackLink->chart3->Series[2]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(p3->XValue, p3->YValues[0]));

				stackLink->box_elem_h->Text = round3(stackLink->chart1->Series[3]->Points[value]->YValues[0]) + "";
				stackLink->box_elem_n->Text = round3(stackLink->chart2->Series[3]->Points[value]->YValues[0]) + "";
				stackLink->box_elem_m->Text = round3(stackLink->chart3->Series[3]->Points[value]->YValues[0]) + "";
				stackLink->box_elem_q->Text = round3(stackLink->chart1->Series[3]->Points[value]->XValue) + "";

				stackLink->box_elem_h->ReadOnly = false;
				stackLink->box_elem_n->ReadOnly = false;
				stackLink->box_elem_q->ReadOnly = false;
			}else {
				stackLink->box_elem_h->Text = "";
				stackLink->box_elem_n->Text = "";
				stackLink->box_elem_m->Text = "";
				stackLink->box_elem_q->Text = "";

				stackLink->box_elem_h->ReadOnly = true;
				stackLink->box_elem_n->ReadOnly = true;
				stackLink->box_elem_q->ReadOnly = true;
			}
		});

		this->pointer.addEventListener([&stackLink, this](double& value) {
			if (value < 0)
				return;
			if (value > stackLink->chart1->ChartAreas[0]->AxisX->Maximum)
				return;

			stackLink->chart1->Series[4]->Points->Clear();
			stackLink->chart2->Series[4]->Points->Clear();
			stackLink->chart3->Series[4]->Points->Clear();

			stackLink->chart1->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, 0));
			stackLink->chart1->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, stackLink->chart1->ChartAreas[0]->AxisY->Maximum));

			stackLink->chart2->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, 0));
			stackLink->chart2->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, stackLink->chart2->ChartAreas[0]->AxisY->Maximum));

			stackLink->chart3->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, 0));
			stackLink->chart3->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, stackLink->chart3->ChartAreas[0]->AxisY->Maximum));
		
			stackLink->box_point_q->Text = round3(value)+"";
			double h = this->H0.getValue() - this->S.getValue() * value * value;
			stackLink->box_point_h->Text = round3(h)+"";
			stackLink->box_point_dh->Text = round3(this->H0.getValue() - h)+"";
			double n = this->N0.getValue() + this->C.getValue() * value;
			stackLink->box_point_n->Text = round3(n)+"";
			stackLink->box_point_m->Text = round3(getCPD(h, value, n))+"";
		});

		this->QPoint.addEventListener([&stackLink, this](float& value) {
			stackLink->input_data_q->Text = "" + value;
			if (this->efficiency_min.getValue() > value || this->efficiency_max.getValue() < value) {
				stackLink->addToErrors(stackLink->input_data_q, "Рабочая точка не попадает в диапазон рабочей зоны");
				return;
			}
			stackLink->removeFromsErrors(stackLink->input_data_q);
		});
		this->HInPoint.addEventListener([&stackLink](float& value) {
			stackLink->input_data_h_in->Text = "" + value;
		});
		this->HOutPoint.addEventListener([&stackLink](float& value) {
			stackLink->input_data_h_out->Text = "" + value;
		});

		this->chartPoints.addEventListener([&stackLink, this](std::vector<ChartPoint> & value) {
			stackLink->chart1->Series[0]->Points->Clear();
			stackLink->chart1->Series[3]->Points->Clear();
			stackLink->chart2->Series[0]->Points->Clear();
			stackLink->chart2->Series[3]->Points->Clear();
			stackLink->chart3->Series[0]->Points->Clear();
			stackLink->chart3->Series[3]->Points->Clear();

			ChartData data = calculateChartData(1, value, [&stackLink](double q, double h, double n, int i) {
				checkPoint(stackLink->chart1, (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, h)), i);
				checkPoint(stackLink->chart2, (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, n)), i);
				checkPoint(stackLink->chart3, (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, getCPD(h, q, n))), i);
			});

			//MessageBox::Show(data.S + "");

			bool isInterval = !stackLink->isMove;

			auto intervals = drawPumpCharts(data, [&stackLink](double q, double h, double n, double m) {
				stackLink->chart1->Series[0]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, h));
				stackLink->chart2->Series[0]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, n));
				stackLink->chart3->Series[0]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, m));
			}, isInterval, -1);

			if (isInterval) {
				if (intervals.QInterval != 0) {
					stackLink->chart1->ChartAreas[0]->AxisX->Interval = intervals.QInterval;
					stackLink->chart2->ChartAreas[0]->AxisX->Interval = intervals.QInterval;
					stackLink->chart3->ChartAreas[0]->AxisX->Interval = intervals.QInterval;
				}
				if (intervals.QMax != 0) {
					stackLink->chart1->ChartAreas[0]->AxisX->Maximum = intervals.QMax;
					stackLink->chart2->ChartAreas[0]->AxisX->Maximum = intervals.QMax;
					stackLink->chart3->ChartAreas[0]->AxisX->Maximum = intervals.QMax;
				}

				if(intervals.HInterval != 0)
					stackLink->chart1->ChartAreas[0]->AxisY->Interval = intervals.HInterval;
				if (intervals.HMax != 0) {
					stackLink->chart1->ChartAreas[0]->AxisY->Maximum = intervals.HMax;
					if(intervals.HMax < 10)
						stackLink->chart1->ChartAreas[0]->Position->X = 2;
					else
						stackLink->chart1->ChartAreas[0]->Position->X = 0;
				}

				if (intervals.NInterval != 0)
					stackLink->chart2->ChartAreas[0]->AxisY->Interval = intervals.NInterval;
				if (intervals.NMax != 0) {
					stackLink->chart2->ChartAreas[0]->AxisY->Maximum = intervals.NMax;
				
					if (intervals.NMax < 10)
						stackLink->chart2->ChartAreas[0]->Position->X = 6;
					else if (intervals.NMax < 100)
						stackLink->chart2->ChartAreas[0]->Position->X = 4;
					else if (intervals.NMax < 1000)
						stackLink->chart2->ChartAreas[0]->Position->X = 2;
					else
						stackLink->chart2->ChartAreas[0]->Position->X = 0;
				}

				if (intervals.MInterval != 0)
				stackLink->chart3->ChartAreas[0]->AxisY->Interval = intervals.MInterval;
				if (intervals.MMax != 0) {
					stackLink->chart3->ChartAreas[0]->AxisY->Maximum = intervals.MMax;
					if (intervals.HMax < 10)
						stackLink->chart3->ChartAreas[0]->Position->X = 2;
					else
						stackLink->chart3->ChartAreas[0]->Position->X = 0;
				}
			}

			stackLink->numeric_input_point->Maximum = value.size();

			this->k.throwEvent();
			//MessageBox::Show("z");
		});

		if(idLink != -1)
			abstactQuery("SELECT * FROM Насосный_агрегат WHERE idLink = " + idLink, 
			[&idLink, this](msclr::gcroot <OleDbDataReader^> reader) {
			if (!reader->HasRows) {
				MessageBox::Show("Элемента с idLink = " + idLink + " не существует", "Ошибка");
				return;
			}

			reader->Read();
		
			this->enable.setValue(1);
			this->name.setValue(getString(reader, "name"));
			this->mark.setValue(getString(reader, "mark"));

			this->diameter_max.setValue(getFloat(reader, "DrkMax"));
			this->diameter_min.setValue(getFloat(reader, "DrkMin"));

			this->turnovers_max.setValue(getFloat(reader, "TurnMax"));
			this->turnovers_min.setValue(getFloat(reader, "TurnMin"));

			this->diameter_nominal.setValue(getFloat(reader, "Drk0"));
			this->turnovers_nominal.setValue(getInt(reader, "Turn0"));

		
			this->H0.setValue(getDouble(reader, "H0"));
			this->N0.setValue(getDouble(reader, "N0"));
			this->S.setValue(getFloat(reader, "S"));
			this->C.setValue(getDouble(reader, "C"));
		
			for (int i = 1; i <= 5; i++) {
				ChartPoint tmpP;
				tmpP.H = getDouble(reader, "H" + i);
				tmpP.N = getDouble(reader, "N" + i);
				tmpP.Q = getDouble(reader, "Q" + i);
	
				this->chartPoints.getValue().push_back(tmpP);
			}

			this->chartPoints.throwEvent();

			this->diameter_current.setValue(getFloat(reader, "Drk"));
			this->turnovers_current.setValue(getFloat(reader, "Turn"));

			this->efficiency_min.setValue(getDouble(reader, "Qmin"));
			this->efficiency_max.setValue(getDouble(reader, "Qmax"));

			this->pressure_in_min.setValue(getFloat(reader, "HNmin"));
			this->pressure_in_max.setValue(getFloat(reader, "HNmax"));

			this->pressure_out_min.setValue(getFloat(reader, "HKmin"));
			this->pressure_out_max.setValue(getFloat(reader, "HKmax"));


			this->QPoint.setValue(getFloat(reader, "Q"));
			this->HInPoint.setValue(getFloat(reader, "HN"));
			this->HOutPoint.setValue(getFloat(reader, "HK"));
			});

		this->k.addEventListener([&stackLink, this](const double& value) {
			stackLink->chart1->Series[1]->Points->Clear();
			stackLink->chart2->Series[1]->Points->Clear();
			stackLink->chart3->Series[1]->Points->Clear();
			ChartData data = calculateChartData(value, this->chartPoints.getValue(), nullptr);
			double resMin = data.H0 / (value * value * this->efficiency_min.getValue() * this->efficiency_min.getValue()) - data.S;

			
			if (Double::IsInfinity(resMin) || Double::IsNaN(resMin))
				resMin = data.S;

			this->resistance_min.setValue(resMin);


			if (this->resistance_current.getValue() == -1) {
				this->resistance_current.setValue(Math::Max(this->S.getValue() - data.S, 0.0));
			}

			data.S += this->resistance_current.getValue();

			drawPumpCharts(data, [&stackLink](double q, double h, double n, double m) {
				stackLink->chart1->Series[1]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, h));
				stackLink->chart2->Series[1]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, n));
				stackLink->chart3->Series[1]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, m));
				}, false, stackLink->chart1->ChartAreas[0]->AxisX->Maximum);

			this->S.setValue(data.S);
			this->C.setValue(data.C);
			this->H0.setValue(data.H0);
			this->N0.setValue(data.N0);

			this->pointer.throwEvent();
		});

		this->k.throwEvent();
		abstactShow(% form);
	}
	void WaterPumpWindow::show(void) {
		WaterPumpWindow::show(-1);
	}

	template<class OBS> void ObserverValue<OBS>::setValue(const OBS &value) {
		if (this->isUpdate)
			return;
		this->isUpdate = true;
		this->value = value;
		for (auto fuctionLink : this->eventHandlers) {
			fuctionLink(const_cast<OBS &>(value));
		}

		this->isUpdate = false;
	}

	template<class OBS> OBS & ObserverValue<OBS>::getValue() {
		return this->value;
	}
	template<class OBS> void ObserverValue<OBS>::addEventListener(std::function<void(OBS &)> func) {
		this->eventHandlers.push_back(func);
	} 

	template<class OBS> void ObserverValue<OBS>::removeEventListener(std::function<void(OBS &)>) {
		this->eventHandlers.erase(std::remove(this->eventHandlers.begin(), this->eventHandlers.end(), func), this->eventHandlers.end());
	}
	template<class OBS> void ObserverValue<OBS>::throwEvent() {
		this->setValue(this->getValue());
	}
	template<class OBS> bool ObserverValue<OBS>::isUserNotEdit() {
		return this->userNotEdit;
	}
	template<class OBS> void ObserverValue<OBS>::userEdit() {
		if (this->isUpdate)
			return;
		this->userNotEdit = false;
	}

}

int maind() {
	angarawindows::setDBConnect("provider=Microsoft.ACE.OLEDB.12.0;Data Source=C:\\Users\\User\\Documents\\TP_EqNS_ML.MDB");

	angarawindows::WaterPumpWindow windPump;
	windPump.show();
	return 0;
}
