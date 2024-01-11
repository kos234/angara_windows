#pragma once

#include <msclr/gcroot.h>
#include <iostream>
#include "utils.h"
#include "angara_windows.h"
#include "WaterPump.h"

namespace angarawindows {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Data::OleDb;



	[STAThreadAttribute]
		void WaterPumpWindow::show(int idLink) {
		//Инициализация ------------------------------------------------------------
		angarawindows::WaterPump form(this);
		msclr::gcroot <WaterPump^> stackLink = % form;
		
		//Ивенты -------------------------------------------------------------------
		this->name.addEventListener([&stackLink](ObserverValue<std::string>& name) {
			SuperTextSetter(stackLink->pump_name, StdToSys(name.getValue()));
			});

		this->enable.addEventListener([&stackLink](ObserverValue<int>& value) {
			stackLink->pump_enable->SelectedIndex = value.getValue() - 1;
			});

		this->mark.addEventListener([&stackLink](ObserverValue<std::string>& mark) {
			SuperTextSetter(stackLink->pump_mark, StdToSys(mark.getValue()));
			});

		this->diameter_nominal.addEventListener([&stackLink, this](ObserverValue<float>& value) {
			stackLink->pump_slide_dim->Enabled = !value.isEmpty();
			stackLink->pump_cur_dim->Enabled = !value.isEmpty();

			if (this->diameter_max.isUserNotEdit()) {
				this->diameter_max.setValue(value.getValue());
			}
			if (this->diameter_min.isUserNotEdit()) {
				this->diameter_min.setValue(0);
			}

			SuperTextSetter(stackLink->pump_dim, value);
			});

		this->turnovers_nominal.addEventListener([&stackLink, this](ObserverValue<int>& value) {
			stackLink->pump_slide_turn->Enabled = !value.isEmpty();
			stackLink->pump_cur_turn->Enabled = !value.isEmpty();

			if (this->turnovers_max.isUserNotEdit()) {
				this->turnovers_max.setValue(value.getValue());
			}
			if (this->turnovers_min.isUserNotEdit()) {
				this->turnovers_min.setValue(0);
			}
			SuperTextSetter(stackLink->pump_turn, value);
			});

		this->turnovers_current.addEventListener([&stackLink, this](ObserverValue<float>& value) {
			SuperTextSetter(stackLink->pump_cur_turn, value);
			stackLink->pump_slide_turn->Value = value.getValue();

			this->k.setValue((this->turnovers_current.getValue() * this->diameter_current.getValue()) / (this->turnovers_nominal.getValue() * this->diameter_nominal.getValue()));
			});

		this->diameter_current.addEventListener([&stackLink, this](ObserverValue<float> & value) {
			SuperTextSetter(stackLink->pump_cur_dim, value);
			stackLink->pump_slide_dim->Value = value.getValue();

			this->k.setValue((this->turnovers_current.getValue() * this->diameter_current.getValue()) / (this->turnovers_nominal.getValue() * this->diameter_nominal.getValue()));
			});

		this->resistance_current.addEventListener([&stackLink, this](ObserverValue<double>& value) {
			//SuperTextSetter(stackLink->pump_cur_s, this->resistance_current);
			stackLink->pump_cur_s->Text = (value.getValue() + "");
			stackLink->pump_slide_s->Value = Math::Round(value.getValue() / this->resistance_min * 100);
			this->k.throwEvent();
			});

		this->efficiency_min.addEventListener([&stackLink, this](ObserverValue<double>& value) {
			//Значение обновляется в postPaint в WaterPump.h
			SuperTextSetter(stackLink->pump_eff_min, value);
			stackLink->chart1->Invalidate();
			stackLink->chart2->Invalidate();
			stackLink->chart3->Invalidate();

			this->QPoint.throwEvent();
			});

		this->efficiency_max.addEventListener([&stackLink, this](ObserverValue<double>& value) {
			//Значение обновляется в postPaint в WaterPump.h
			SuperTextSetter(stackLink->pump_eff_max, value);
			stackLink->chart1->Invalidate();
			stackLink->chart2->Invalidate();
			stackLink->chart3->Invalidate();
			this->QPoint.throwEvent();
			});

		this->pressure_in_min.addEventListener([&stackLink, this](ObserverValue<float>& value) {
			SuperTextSetter(stackLink->pump_pres_min, value);
			this->HInPoint.throwEvent();
			});

		this->pressure_in_max.addEventListener([&stackLink, this](ObserverValue<float>& value) {
			SuperTextSetter(stackLink->pump_pres_max, value);
			this->HInPoint.throwEvent();
			});

		this->pressure_out_min.addEventListener([&stackLink, this](ObserverValue<float>& value) {
			SuperTextSetter(stackLink->pump_pres_min_out, value);
			this->HOutPoint.throwEvent();
			});

		this->pressure_out_max.addEventListener([&stackLink, this](ObserverValue<float>& value) {
			SuperTextSetter(stackLink->pump_pres_max_out, value);
			this->HOutPoint.throwEvent();
			});

		this->diameter_min.addEventListener([&stackLink, this](ObserverValue<float>& value) {
			SuperTextSetter(stackLink->pump_dim_min, value);

			stackLink->pump_slide_dim->Minimum = value.getValue();

			stackLink->pump_slide_dim->TickFrequency = (this->diameter_max.getValue() - value.getValue()) / 10;
			});

		this->diameter_max.addEventListener([&stackLink, this](ObserverValue<float> & value) {
			SuperTextSetter(stackLink->pump_dim_max, this->diameter_max);

			stackLink->pump_slide_dim->Maximum = value.getValue();

			if (this->diameter_current.isUserNotEdit() || this->diameter_current.getValue() > value.getValue())
				this->diameter_current.setValue(value.getValue());
			});

		this->turnovers_min.addEventListener([&stackLink, this](ObserverValue<float>& value) {
			SuperTextSetter(stackLink->pump_turn_min, value);

			stackLink->pump_slide_turn->Minimum = value.getValue();
			stackLink->pump_slide_turn->TickFrequency = (this->turnovers_max.getValue() - value.getValue()) / 10;
			});

		this->turnovers_max.addEventListener([&stackLink, this](ObserverValue<float>& value) {
			SuperTextSetter(stackLink->pump_turn_max, value);

			stackLink->pump_slide_turn->Maximum = value.getValue();
			if (this->turnovers_current.isUserNotEdit() || this->turnovers_current.getValue() > value.getValue())
				this->turnovers_current.setValue(value.getValue());
			});

		this->H0.addEventListener([&stackLink](ObserverValue<double>& value) {
			SuperTextSetter(stackLink->box_k_h0, value);
			});
		this->N0.addEventListener([&stackLink](ObserverValue<double>& value) {
			SuperTextSetter(stackLink->box_k_n0, value);
			});
		this->C.addEventListener([&stackLink](ObserverValue<double>& value) {
			SuperTextSetter(stackLink->box_k_c, value);
			});
		this->S.addEventListener([&stackLink](ObserverValue<float>& value) {
			SuperTextSetter(stackLink->box_k_s, value);
			});

		this->elemMove.addEventListener([&stackLink](ObserverValue<int>& value) {
			int elemMoveValue = value.getValue();
			stackLink->chart1->Series[2]->Points->Clear();
			stackLink->chart2->Series[2]->Points->Clear();
			stackLink->chart3->Series[2]->Points->Clear();

			stackLink->removeFromsErrors(stackLink->box_elem_h);
			stackLink->removeFromsErrors(stackLink->box_elem_q);
			stackLink->removeFromsErrors(stackLink->box_elem_n);

			stackLink->numeric_input_point->Value = elemMoveValue + 1;

			if (value.getValue() != -1) {
				auto p1 = stackLink->chart1->Series[3]->Points[elemMoveValue];
				auto p2 = stackLink->chart2->Series[3]->Points[elemMoveValue];
				auto p3 = stackLink->chart3->Series[3]->Points[elemMoveValue];

				stackLink->chart1->Series[2]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(p1->XValue, p1->YValues[0]));
				stackLink->chart2->Series[2]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(p2->XValue, p2->YValues[0]));
				stackLink->chart3->Series[2]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(p3->XValue, p3->YValues[0]));

				SuperTextSetter(stackLink->box_elem_h, p1->YValues[0], false);
				SuperTextSetter(stackLink->box_elem_n, p2->YValues[0], false);
				SuperTextSetter(stackLink->box_elem_m, p3->YValues[0], false);
				SuperTextSetter(stackLink->box_elem_q, p1->XValue, false);

				stackLink->box_elem_h->ReadOnly = false;
				stackLink->box_elem_n->ReadOnly = false;
				stackLink->box_elem_q->ReadOnly = false;
			}
			else {
				stackLink->box_elem_h->Text = "";
				stackLink->box_elem_n->Text = "";
				stackLink->box_elem_m->Text = "";
				stackLink->box_elem_q->Text = "";

				stackLink->box_elem_h->ReadOnly = true;
				stackLink->box_elem_n->ReadOnly = true;
				stackLink->box_elem_q->ReadOnly = true;
			}
			});

		this->pointer.addEventListener([&stackLink, this](ObserverValue<double>& link) {
			double value = link.getValue();
			if (value < 0)
				return;
			if (value > stackLink->chart1->ChartAreas[0]->AxisX->Maximum)
				return;
			if (value == 0)
				value = 1e-11;

			stackLink->chart1->Series[4]->Points->Clear();
			stackLink->chart2->Series[4]->Points->Clear();
			stackLink->chart3->Series[4]->Points->Clear();

			if (!this->pointer.isEmpty()) {
				stackLink->chart1->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, 0));
				stackLink->chart1->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, stackLink->chart1->ChartAreas[0]->AxisY->Maximum));

				stackLink->chart2->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, 0));
				stackLink->chart2->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, stackLink->chart2->ChartAreas[0]->AxisY->Maximum));

				stackLink->chart3->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, 0));
				stackLink->chart3->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, stackLink->chart3->ChartAreas[0]->AxisY->Maximum));
			}

			SuperTextSetter(stackLink->box_point_q, link);

			double h = this->H0.getValue() - this->S.getValue() * value * value;
			SuperTextSetter(stackLink->box_point_h, h, link.isEmpty());
			SuperTextSetter(stackLink->box_point_dh, this->H0.getValue() - h, link.isEmpty());

			double n = this->N0.getValue() + this->C.getValue() * value;
			SuperTextSetter(stackLink->box_point_n, n, link.isEmpty());
			SuperTextSetter(stackLink->box_point_m, getCPD(h, value, n), link.isEmpty());
			});

		this->QPoint.addEventListener([&stackLink, this](ObserverValue<float>& value) {
			SuperTextSetter(stackLink->input_data_q, value);
			if (value.isEmpty())
				return;

			if ((!this->efficiency_min.isEmpty() && this->efficiency_min.getValue() > value.getValue()) 
				||
				(!this->efficiency_max.isEmpty() && this->efficiency_max.getValue() < value.getValue())) {
				stackLink->addToErrors(stackLink->input_data_q, "Рабочая точка не попадает в диапазон рабочей зоны");
				return;
			}

			stackLink->removeFromsErrors(stackLink->input_data_q);
			});

		this->HInPoint.addEventListener([&stackLink, this](ObserverValue<float>& value) {
			SuperTextSetter(stackLink->input_data_h_in, value);
			if ((!this->pressure_in_min.isEmpty() && this->pressure_in_min.getValue() > value.getValue()) 
				|| 
				(!this->pressure_in_max.isEmpty() && this->pressure_in_max.getValue() < value.getValue())) {
				stackLink->addToErrors(stackLink->input_data_h_in, "Рабочая точка не попадает в диапазон рабочей зоны");
				return;
			}

			stackLink->removeFromsErrors(stackLink->input_data_h_in);
			});

		this->HOutPoint.addEventListener([&stackLink, this](ObserverValue<float>& value) {
			SuperTextSetter(stackLink->input_data_h_out, value);
			if ((!this->pressure_out_min.isEmpty() && this->pressure_out_min.getValue() > value.getValue())
				|| 
				(!this->pressure_out_max.isEmpty() && this->pressure_out_max.getValue() < value.getValue())) {
				stackLink->addToErrors(stackLink->input_data_h_out, "Рабочая точка не попадает в диапазон рабочей зоны");
				return;
			}

			stackLink->removeFromsErrors(stackLink->input_data_h_out);
			});

		this->chartPoints.addEventListener([&stackLink, this](ObserverValue<std::vector<ChartPoint>>& value) {
			stackLink->chart1->Series[0]->Points->Clear();
			stackLink->chart1->Series[3]->Points->Clear();
			stackLink->chart2->Series[0]->Points->Clear();
			stackLink->chart2->Series[3]->Points->Clear();
			stackLink->chart3->Series[0]->Points->Clear();
			stackLink->chart3->Series[3]->Points->Clear();

			ChartData data = calculateChartData(1, value.getValue(), [&stackLink](double q, double h, double n, int i) {
				checkPoint(stackLink->chart1, (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, h)), i);
				checkPoint(stackLink->chart2, (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, n)), i);
				checkPoint(stackLink->chart3, (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, getCPD(h, q, n))), i);
				});


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

				if (intervals.HInterval != 0)
					stackLink->chart1->ChartAreas[0]->AxisY->Interval = intervals.HInterval;
				if (intervals.HMax != 0)
					stackLink->chart1->ChartAreas[0]->AxisY->Maximum = intervals.HMax;

				if (intervals.NInterval != 0)
					stackLink->chart2->ChartAreas[0]->AxisY->Interval = intervals.NInterval;
				if (intervals.NMax != 0)
					stackLink->chart2->ChartAreas[0]->AxisY->Maximum = intervals.NMax;

				if (intervals.MInterval != 0)
					stackLink->chart3->ChartAreas[0]->AxisY->Interval = intervals.MInterval;
				if (intervals.MMax != 0)
					stackLink->chart3->ChartAreas[0]->AxisY->Maximum = intervals.MMax;



				normalyzeTitleChart(stackLink->chart1);
				normalyzeTitleChart(stackLink->chart2);
				normalyzeTitleChart(stackLink->chart3);
			}

			stackLink->numeric_input_point->Maximum = value.getValue().size();

			this->k.throwEvent();
			});

		//Получение данных из бд------------------------------------------------------------------------
		abstactQuery("SELECT * FROM Состояния_элементов WHERE IdElement = 17 ORDER BY idState",
			[&stackLink, this](msclr::gcroot <OleDbDataReader^> reader) {
				while (reader->Read()) {
					stackLink->pump_enable->Items->Add(StdToSys(getString(reader, "StateName").value));
				}
			}
		);

		if (idLink != -1)
			abstactQuery("SELECT *, (SELECT IdState FROM Связи WHERE idLink = " + idLink + ") as IdState FROM Насосный_агрегат WHERE idLink = " + idLink,
				[&idLink, this](msclr::gcroot <OleDbDataReader^> reader) {
					if (!reader->HasRows) {
						MessageBox::Show("Элемента с idLink = " + idLink + " не существует", "Ошибка");
						return;
					}

					reader->Read();

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
						tmpP.H = getDouble(reader, "H" + i).value;
						tmpP.N = getDouble(reader, "N" + i).value;
						tmpP.Q = getDouble(reader, "Q" + i).value;

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

					this->enable.setValue(getInt(reader, "IdState"));
				});

		//События, которые не должны вызываться при чтении -----------------------------------------------------------
		this->k.addEventListener([&stackLink, this](ObserverValue<double> & link) {
			double value = link.getValue();
			stackLink->chart1->Series[1]->Points->Clear();
			stackLink->chart2->Series[1]->Points->Clear();
			stackLink->chart3->Series[1]->Points->Clear();
			ChartData data = calculateChartData(value, this->chartPoints.getValue(), [&stackLink](double q, double h, double n, int i) {});
			double resMin = data.H0 / (value * value * this->efficiency_min.getValue() * this->efficiency_min.getValue()) - data.S;

			stackLink->pump_cur_s->Enabled = true;
			stackLink->pump_slide_s->Enabled = true;

			if (Double::IsInfinity(resMin) || Double::IsNaN(resMin)){
				if (data.S == 0) {
					resMin = 1;
					stackLink->pump_cur_s->Enabled = false;
					stackLink->pump_slide_s->Enabled = false;
				}else
					resMin = data.H0 / (0.1) - data.S;
			}

			this->resistance_min = resMin;


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

}
