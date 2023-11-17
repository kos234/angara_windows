#pragma once
#include "angara_windows.h"
#include "WaterPump.h"
#include "Pipe.h"
#include <msclr/gcroot.h>
#include "database_safe.cpp"
namespace angarawindows {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Data::OleDb;

	msclr::gcroot<OleDbConnection^> connection;


	void setDBConnect(const char* urlConnect) {
		connection = gcnew OleDbConnection(gcnew String(urlConnect));

		Application::SetCompatibleTextRenderingDefault(false);
		Application::EnableVisualStyles();
	}

	[STAThreadAttribute]
		void abstactShow(System::Windows::Forms::Form^ form) {
		Application::Run(form);
	}

	void abstactQuery(String^ sql, std::function<void(msclr::gcroot<OleDbDataReader^>)> func) {
		connection->Open();
		OleDbCommand^ command = gcnew OleDbCommand(sql, connection);
		OleDbDataReader^ reader = command->ExecuteReader();
		func(reader);
		reader->Close();
		connection->Close();
	};

	void WaterPumpWindow::show(int idLink) {
		angarawindows::WaterPump form(this);
		msclr::gcroot <WaterPump^> stackLink = %form;

		this->name.addEventListener([&stackLink](std::string name) {
			stackLink->pump_name->Text = gcnew String(name.c_str());
		});
		this->mark.addEventListener([&stackLink](std::string name) {
			stackLink->pump_mark->Text = gcnew String(name.c_str());
		});
		this->diameter_nominal.addEventListener([&stackLink](double value) {
			SuperTextSetter(stackLink->pump_dim, gcnew String(value + ""));
			stackLink->pump_slide_dim->Maximum = value;
			stackLink->pump_slide_dim->TickFrequency = value / 10;
			stackLink->pump_slide_dim->Value = value;
		});
		this->turnovers_nominal.addEventListener([&stackLink](int value) {
			SuperTextSetter(stackLink->pump_turn, gcnew String(value + ""));
			stackLink->pump_slide_turn->Maximum = value;
			stackLink->pump_slide_turn->TickFrequency = value / 10;
			stackLink->pump_slide_turn->Value = value;
		});
		this->turnovers_current.addEventListener([&stackLink](int value) {
			SuperTextSetter(stackLink->pump_cur_turn, gcnew String(value + ""));
			stackLink->pump_slide_turn->Value = value;
		});
		this->diameter_current.addEventListener([&stackLink](int value) {
			SuperTextSetter(stackLink->pump_cur_dim, gcnew String(value + ""));
			stackLink->pump_slide_dim->Value = value;
		});
		this->resistance_current.addEventListener([&stackLink](int value) {
			SuperTextSetter(stackLink->pump_cur_s, gcnew String(value + ""));
			stackLink->pump_slide_s->Value = value;
		});

		this->efficiency_min.addEventListener([&stackLink](int value) {
			SuperTextSetter(stackLink->pump_eff_min, gcnew String(value + ""));
			stackLink->pump_slide_s->Maximum = value;
			stackLink->pump_slide_s->TickFrequency = value / 10;
			stackLink->pump_slide_s->Value = Math::Min(stackLink->pump_slide_s->Value, value);
			//stackLink->drawAreas(nullptr);
			stackLink->chart1->Invalidate();
			stackLink->chart2->Invalidate();
			stackLink->chart3->Invalidate();
		});
		this->efficiency_max.addEventListener([&stackLink](int value) {
			SuperTextSetter(stackLink->pump_eff_max, gcnew String(value + ""));
			//stackLink->drawAreas(nullptr);
			stackLink->chart1->Invalidate();
			stackLink->chart2->Invalidate();
			stackLink->chart3->Invalidate();
			});
		this->pressure_min.addEventListener([&stackLink](int value) {
			SuperTextSetter(stackLink->pump_pres_min, gcnew String(value + ""));
		});
		this->pressure_max.addEventListener([&stackLink](int value) {
			SuperTextSetter(stackLink->pump_pres_max, gcnew String(value + ""));
		});
		this->diameter_min.addEventListener([&stackLink](int value) {
			SuperTextSetter(stackLink->pump_dim_min, gcnew String(value + ""));
		});
		this->diameter_max.addEventListener([&stackLink](int value) {
			SuperTextSetter(stackLink->pump_dim_max, gcnew String(value + ""));
		});
		this->turnovers_min.addEventListener([&stackLink](int value) {
			SuperTextSetter(stackLink->pump_turn_min, gcnew String(value + ""));
		});
		this->turnovers_max.addEventListener([&stackLink](int value) {
			SuperTextSetter(stackLink->pump_turn_max, gcnew String(value + ""));
		});

		this->H0.addEventListener([&stackLink](double value) {
			stackLink->box_k_h0->Text = value + "";
		});
		this->N0.addEventListener([&stackLink](double value) {
			stackLink->box_k_n0->Text = value + "";
		});
		this->C.addEventListener([&stackLink](double value) {
			stackLink->box_k_c->Text = value + "";
		});
		this->S.addEventListener([&stackLink](double value) {
			stackLink->box_k_s->Text = value + "";
		});

		this->elemMove.addEventListener([&stackLink](int value) {
			stackLink->chart1->Series[2]->Points->Clear();
			stackLink->chart2->Series[2]->Points->Clear();
			stackLink->numeric_input_point->Value = value + 1;

			if (value != -1) {
				auto p1 = stackLink->chart1->Series[1]->Points[value];
				auto p2 = stackLink->chart2->Series[1]->Points[value];
				stackLink->chart1->Series[2]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(p1->XValue, p1->YValues[0]));
				stackLink->chart2->Series[2]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(p2->XValue, p2->YValues[0]));

				stackLink->box_elem_h->Text = stackLink->chart1->Series[1]->Points[value]->YValues[0] + "";
				stackLink->box_elem_n->Text = stackLink->chart2->Series[1]->Points[value]->YValues[0] + "";
				stackLink->box_elem_m->Text = stackLink->chart3->Series[1]->Points[value]->YValues[0] + "";
				stackLink->box_elem_q->Text = stackLink->chart1->Series[1]->Points[value]->XValue + "";

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
		this->chartPoints.addEventListener([&stackLink, this](std::vector<ChartPoint>* value) {
			//MessageBox::Show("X");
			//bool isCalculate = stackLink->chart1->Series[1]->Points->Count != 0;
			//isCalculate = true;
			//double k = 1;
			//if (isCalculate) {
			double k = (this->turnovers_current.getValue() * this->diameter_current.getValue()) / (this->turnovers_nominal.getValue() * this->diameter_nominal.getValue());
			//}
			//MessageBox::Show("k=" + k);
			
			stackLink->chart1->Series[0]->Points->Clear();
			stackLink->chart1->Series[1]->Points->Clear();
			stackLink->chart2->Series[0]->Points->Clear();
			stackLink->chart2->Series[1]->Points->Clear();
			stackLink->chart3->Series[0]->Points->Clear();
			stackLink->chart3->Series[1]->Points->Clear();
		
			int PointsQH = 0;
			int PointsQN = 0;
			double sumH[] = { 0 , 0 };
			double sumQ[] = { 0, 0 };
			double sumHQ2[] = { 0, 0 };
			double sumQ2[] = { 0, 0 };
			double sumQ4[] = { 0, 0 };
			double sumN[] = { 0, 0 };
			double sumNQ[] = { 0, 0 };
			for (int i = 0; i < value->size(); i++) {
				auto q = value->at(i);

				checkPoint(stackLink->chart1, (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q.Q, q.H)), i);
				checkPoint(stackLink->chart2, (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q.Q, q.N)), i);
				checkPoint(stackLink->chart3, (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q.Q, getCPD(q.H, q.Q, q.N))), i);

				double Q = k * q.Q;
				double H = k * k * q.H;
				double N = k * k * k * q.N;

				//MessageBox::Show("q = " + q.H);
				//MessageBox::Show("Q = " + Q);
			//MessageBox::Show("H = " + H);
				if (Q > 0 || H > 0) {
					PointsQH++;
					sumH[0] += q.H;
					sumH[1] += H;

					sumQ[0] += q.Q;
					sumQ[1] += Q;

					sumHQ2[0] += q.H * q.Q * q.Q;
					sumHQ2[1] += H * Q * Q;

					sumQ2[0] += q.Q * q.Q;
					sumQ2[1] += Q * Q;

					sumQ4[0] += q.Q * q.Q * q.Q * q.Q;
					sumQ4[1] += Q * Q * Q * Q;
				}

				if (Q > 0 || N > 0) {
					PointsQN++;
					sumN[0] += q.N;
					sumN[1] += N;
					sumNQ[0] += q.N * q.Q;
					sumNQ[1] += N * Q;
				}
				//}
			}
			
			double globalH0 = 0;
			double globalS = 0;
			double globalN0 = 0;
			double globalC = 0;
			//if (isCalculate) {
			switch (PointsQH) {
			case 0:
				//MessageBox::Show("q2");
				this->H0.setValue(0);
				this->S.setValue(0);
				break;
			case 1:
				//MessageBox::Show("q3");
				globalH0 = sumH[0];
				this->H0.setValue(sumH[1]);
				this->S.setValue(0);
				break;
			default:
				if (PointsQH * sumQ4[1] - sumQ2[1] * sumQ2[1] > 0) {
					this->S.setValue(-(sumHQ2[1] - sumH[1] * sumQ2[1] / PointsQH) / (sumQ4[1] - sumQ2[1] * sumQ2[1] / PointsQH));
					globalS = -(sumHQ2[0] - sumH[0] * sumQ2[0] / PointsQH) / (sumQ4[0] - sumQ2[0] * sumQ2[0] / PointsQH);

					this->H0.setValue((sumH[1] + sumQ2[1] * this->S.getValue()) / PointsQH);
					globalH0 = ((sumH[0] + sumQ2[0] * globalS) / PointsQH);
				}
				else {
					//	MessageBox::Show("q4");
					this->H0.setValue(0);
					this->S.setValue(0);
				}
				break;
			}
			switch (PointsQN) {
			case 0:
				this->N0.setValue(0);
				this->C.setValue(0);
				break;
			case 1:
				this->N0.setValue(sumN[1]);
				globalN0 = sumN[0];
				this->C.setValue(0);
				break;
			default:
				if (PointsQN * sumQ2[1] - sumQ[1] * sumQ[1]) {
					this->C.setValue((sumNQ[1] - sumQ[1] * sumN[1] / PointsQN) / (sumQ2[1] - sumQ[1] * sumQ[1] / PointsQN));
					globalC = ((sumNQ[0] - sumQ[0] * sumN[0] / PointsQN) / (sumQ2[0] - sumQ[0] * sumQ[0] / PointsQN));

					this->N0.setValue((sumN[1] - sumQ[1] * this->C.getValue()) / PointsQN);
					globalN0 = ((sumN[0] - sumQ[0] * globalC) / PointsQN);
				}
				else {
					this->N0.setValue(0);
					this->C.setValue(0);
				}
				break;
			}

			if (globalS < 0 || globalC < 0)
				return;

			//MessageBox::Show("globalH0=" + globalH0);
			//MessageBox::Show("globalH0=" + globalS);
			//}
			double lastX = 0;
			//MessageBox::Show("globalH0=" + globalH0);
			//MessageBox::Show("globalS=" + globalS);
			double endX = Math::Sqrt(globalH0 / globalS);
			double offset = endX / 7;

			double maxM = 0;
			double maxN = 0;
			for (int i = 0; i < 20; i++) {
				bool isEnd = false;
				if (lastX > endX) {
					lastX = endX;
					isEnd = true;
				}

				double yH = globalH0 - globalS * lastX * lastX;
				double yN = globalN0 + globalC * lastX;
				double yM = getCPD(yH, lastX, yN);
				if (maxM < yM)
					maxM = yM;
				maxN = yN;

				auto pointHQ = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(lastX, yH));
				auto pointNQ = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(lastX, yN));
				auto pointMQ = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(lastX, yM));
				//MessageBox::Show(i + "=(" + lastX + ", " + yH + ")");
				//MessageBox::Show("offset(" + offset + ")");
				stackLink->chart1->Series[0]->Points->Add(pointHQ);
				//MessageBox::Show("X6m1o" + i);
				stackLink->chart2->Series[0]->Points->Add(pointNQ);
				stackLink->chart3->Series[0]->Points->Add(pointMQ);

				lastX += offset;

				if (isEnd)
					break;
			}

			if (this->elemMove.getValue() == -1) {
				stackLink->chart1->ChartAreas[0]->AxisX->Interval = getInterval(endX);
				stackLink->chart2->ChartAreas[0]->AxisX->Interval = getInterval(endX);
				stackLink->chart3->ChartAreas[0]->AxisX->Interval = getInterval(endX);
				stackLink->chart1->ChartAreas[0]->AxisY->Interval = getInterval(globalH0);
				stackLink->chart2->ChartAreas[0]->AxisY->Interval = getInterval(maxN);
				stackLink->chart3->ChartAreas[0]->AxisY->Interval = getInterval(maxM);
			}
		});


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
	
			this->chartPoints.getValue()->push_back(tmpP);
		}

		this->chartPoints.throwEvent();

		this->diameter_current.setValue(getFloat(reader, "Drk"));
		this->turnovers_current.setValue(getFloat(reader, "Turn"));

		this->efficiency_min.setValue(getDouble(reader, "Qmin"));
		this->efficiency_max.setValue(getDouble(reader, "Qmax"));

		this->pressure_min.setValue(getFloat(reader, "HNmin"));
		this->pressure_min.setValue(getFloat(reader, "HNmax"));

		this->diameter_min.setValue(getFloat(reader, "DrkMin"));
		this->diameter_max.setValue(getFloat(reader, "DrkMax"));

		this->turnovers_min.setValue(getFloat(reader, "TurnMin"));
		this->turnovers_max.setValue(getFloat(reader, "TurnMax"));

		});

		//MessageBox::Show((stackLink->model->chartPoints.getValue())->size() + "q");

		abstactShow(% form);
	}

	template<class OBS> void ObserverValue<OBS>::setValue(OBS value) {
		if (this->isUpdate)
			return;
		this->isUpdate = true;
		this->value = value;
		for (auto fuctionLink : this->eventHandlers) {
			fuctionLink(value);
		}

		this->isUpdate = false;
	}

	template<class OBS> OBS ObserverValue<OBS>::getValue() {
		return this->value;
	}
	template<class OBS> void ObserverValue<OBS>::addEventListener(std::function<void(OBS)> func) {
		this->eventHandlers.push_back(func);
	} 

	template<class OBS> void ObserverValue<OBS>::removeEventListener(std::function<void(OBS)>) {
		this->eventHandlers.erase(std::remove(this->eventHandlers.begin(), this->eventHandlers.end(), func), this->eventHandlers.end());
	}
	template<class OBS> void ObserverValue<OBS>::throwEvent() {
		this->setValue(this->getValue());
	}


	template<class OBS> std::vector<OBS>* ObserverArray<OBS>::getValue() {
		return &this->value;
	}
	template<class OBS> void ObserverArray<OBS>::addEventListener(std::function<void(std::vector<OBS>*)> func) {
		this->eventHandlers.push_back(func);
	} 

	template<class OBS> void ObserverArray<OBS>::removeEventListener(std::function<void(std::vector<OBS>*)>) {
		this->eventHandlers.erase(std::remove(this->eventHandlers.begin(), this->eventHandlers.end(), func), this->eventHandlers.end());
	}
	template<class OBS> void ObserverArray<OBS>::throwEvent() {
		if (this->isUpdate)
			return;
		this->isUpdate = true;
		auto q = this->getValue();
		for (auto fuctionLink : this->eventHandlers) {
			fuctionLink(q);
		}

		this->isUpdate = false;
	}

}




