#pragma once

#include <msclr/gcroot.h>
#include <iostream>
#include <string>
#include "LocalizationManager.h"
#include "utils.h"
#include "WaterPumpForm.h"
#include "WaterPump.h"
#include "main.h"
#include "ObserverValue.h"
#include "RealChartPoint.h"
#include "RealWaterPump.h"
#include "CurrentForm.h"

namespace angarawindows {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Data::OleDb;

	[STAThreadAttribute]
	RealWaterPump::RealWaterPump(WaterPump* model) {
		this->model = model;
		WaterPumpForm form;
		this->form = % form;
		init();
		Application::Run(this->form);
	}
	[STAThreadAttribute]
		void RealWaterPump::init() {
		//������� ------------------------------------------------------
		List<RealChartPoint^>^ points_ = gcnew List<RealChartPoint^>();
		//--------------------------------------------------------------

		this->name = (gcnew ObserverValue<String^>(L"", &this->model->errors, form->toolTip1))
			->addInput(form->pump_name)
			->addValidate(gcnew ObserverValue<String^>::Valide(this, &RealWaterPump::name_valide));

		this->mark = (gcnew ObserverValue<String^>(L"", &this->model->errors, form->toolTip1))
			->addInput(form->pump_mark)
			->addValidate(gcnew ObserverValue<String^>::Valide(this, &RealWaterPump::mark_valide));


		this->diameter_nominal = (gcnew ObserverValue<float>(0, &this->model->errors, form->toolTip1))
			->addInput(form->pump_dim)
			->addValidate(gcnew ObserverValue<float>::Valide(this, &RealWaterPump::diameter_valide))
			->addEventListener(gcnew ObserverValue<float>::Event(this, &RealWaterPump::diameter_nominal_event));

		this->diameter_current = (gcnew ObserverValue<float>(0, &this->model->errors, form->toolTip1))
			->addInput(form->pump_cur_dim)
			->addInput(form->pump_slide_dim)
			->addValidate(gcnew ObserverValue<float>::Valide(this, &RealWaterPump::diameter_valide))
			->addEventListener(gcnew ObserverValue<float>::Event(this, &RealWaterPump::set_k_event));

		this->diameter_min = (gcnew ObserverValue<float>(0, &this->model->errors, form->toolTip1))
			->addInput(form->pump_dim_min)
			->addValidate(gcnew ObserverValue<float>::Valide(this, &RealWaterPump::diameter_max_min_valide))
			->addEventListener(gcnew ObserverValue<float>::Event(this, &RealWaterPump::diameter_min_event));

		this->diameter_max = (gcnew ObserverValue<float>(0, &this->model->errors, form->toolTip1))
			->addInput(form->pump_dim_max)
			->addValidate(gcnew ObserverValue<float>::Valide(this, &RealWaterPump::diameter_max_min_valide))
			->addEventListener(gcnew ObserverValue<float>::Event(this, &RealWaterPump::diameter_max_event));



		this->turnovers_nominal = (gcnew ObserverValue<int>(0, &this->model->errors, form->toolTip1))
			->addInput(form->pump_turn)
			->addValidate(gcnew ObserverValue<int>::Valide(this, &RealWaterPump::turnovers_valide))
			->addEventListener(gcnew ObserverValue<int>::Event(this, &RealWaterPump::turnovers_nominal_event));

		this->turnovers_current = (gcnew ObserverValue<float>(0, &this->model->errors, form->toolTip1))
			->addInput(form->pump_cur_turn)
			->addInput(form->pump_slide_turn)
			->addValidate(gcnew ObserverValue<float>::Valide(this, &RealWaterPump::turnovers_valide))
			->addEventListener(gcnew ObserverValue<float>::Event(this, &RealWaterPump::set_k_event));

		this->turnovers_min = (gcnew ObserverValue<float>(0, &this->model->errors, form->toolTip1))
			->addInput(form->pump_turn_min)
			->addValidate(gcnew ObserverValue<float>::Valide(this, &RealWaterPump::turnovers_max_min_valide))
			->addEventListener(gcnew ObserverValue<float>::Event(this, &RealWaterPump::turnovers_min_event));

		this->turnovers_max = (gcnew ObserverValue<float>(0, &this->model->errors, form->toolTip1))
			->addInput(form->pump_turn_max)
			->addValidate(gcnew ObserverValue<float>::Valide(this, &RealWaterPump::turnovers_max_min_valide))
			->addEventListener(gcnew ObserverValue<float>::Event(this, &RealWaterPump::turnovers_max_event));

		this->k = (gcnew ObserverValue<double>(0, &this->model->errors, form->toolTip1));

		this->enable = (gcnew ObserverValue<int>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->pump_enable);

		this->resistance_current = (gcnew ObserverValue<double>(this->model->resistance_current, &this->model->errors, form->toolTip1))
			->addInput(this->form->pump_slide_s, gcnew ObserverValue<double>::PrepareToShow(this, &RealWaterPump::resistance_current_PrepareToShow))
			->addInput(this->form->pump_cur_s)
			->addValidate(gcnew ObserverValue<double>::Valide(this, &RealWaterPump::resistance_current_valid))
			->addEventListener(gcnew ObserverValue<double>::Event(this, &RealWaterPump::set_k_event));

		this->H0 = (gcnew ObserverValue<double>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->box_k_h0)
			->addValidate(gcnew ObserverValue<double>::Valide(this, &RealWaterPump::five_points_valid));
		this->S = (gcnew ObserverValue<float>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->box_k_s)
			->addValidate(gcnew ObserverValue<float>::Valide(this, &RealWaterPump::five_points_valid));
		this->N0 = (gcnew ObserverValue<double>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->box_k_n0)
			->addValidate(gcnew ObserverValue<double>::Valide(this, &RealWaterPump::five_points_valid));
		this->C = (gcnew ObserverValue<double>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->box_k_c)
			->addValidate(gcnew ObserverValue<double>::Valide(this, &RealWaterPump::five_points_valid));


		this->efficiency_min = (gcnew ObserverValue<double>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->pump_eff_min)
			->addInput(this->form->box_q_min, gcnew ObserverValue<double>::PrepareToShow(this, &RealWaterPump::efficiency_PrepareToShow))
			->addValidate(gcnew ObserverValue<double>::Valide(this, &RealWaterPump::efficiency_valide));
		this->efficiency_max = (gcnew ObserverValue<double>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->pump_eff_max)
			->addInput(this->form->box_q_max, gcnew ObserverValue<double>::PrepareToShow(this, &RealWaterPump::efficiency_PrepareToShow))
			->addValidate(gcnew ObserverValue<double>::Valide(this, &RealWaterPump::efficiency_valide));

		this->pressure_in_min = (gcnew ObserverValue<float>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->pump_pres_min)
			->addValidate(gcnew ObserverValue<float>::Valide(this, &RealWaterPump::pressure_in_valide));
		this->pressure_in_max = (gcnew ObserverValue<float>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->pump_pres_max)
			->addValidate(gcnew ObserverValue<float>::Valide(this, &RealWaterPump::pressure_in_valide));

		this->pressure_out_min = (gcnew ObserverValue<float>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->pump_pres_min_out)
			->addValidate(gcnew ObserverValue<float>::Valide(this, &RealWaterPump::pressure_out_valide));
		this->pressure_out_max = (gcnew ObserverValue<float>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->pump_pres_max_out)
			->addValidate(gcnew ObserverValue<float>::Valide(this, &RealWaterPump::pressure_out_valide));


		this->points = (gcnew ObserverValue<List<RealChartPoint^>^>(points_, &this->model->errors, form->toolTip1))
			->addEventListener(gcnew ObserverValue<List<RealChartPoint^>^>::Event(this, &RealWaterPump::points_event));

		this->point_input_q = (gcnew ObserverValue<double>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->box_elem_q)
			->addValidate(gcnew ObserverValue<double>::Valide(this, &RealWaterPump::point_input_valide))
			->addEventListener(gcnew ObserverValue<double>::Event(this, &RealWaterPump::point_input_event));

		this->point_input_h = (gcnew ObserverValue<double>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->box_elem_h)
			->addValidate(gcnew ObserverValue<double>::Valide(this, &RealWaterPump::point_input_valide))
			->addEventListener(gcnew ObserverValue<double>::Event(this, &RealWaterPump::point_input_event));

		this->point_input_n = (gcnew ObserverValue<double>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->box_elem_n)
			->addValidate(gcnew ObserverValue<double>::Valide(this, &RealWaterPump::point_input_valide))
			->addEventListener(gcnew ObserverValue<double>::Event(this, &RealWaterPump::point_input_event));

		this->point_input_m = (gcnew ObserverValue<double>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->box_elem_m)
			->addValidate(gcnew ObserverValue<double>::Valide(this, &RealWaterPump::point_input_valide))
			->addEventListener(gcnew ObserverValue<double>::Event(this, &RealWaterPump::point_input_event));

		this->pointer = (gcnew ObserverValue<double>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->box_point_q)
			->addValidate(gcnew ObserverValue<double>::Valide(this, &RealWaterPump::pointer_valid))
			->addEventListener(gcnew ObserverValue<double>::Event(this, &RealWaterPump::pointer_event));

		this->elemMove = (gcnew ObserverValue<int>(0, &this->model->errors, form->toolTip1))
			->addInput(this->form->numeric_input_point)
			->addEventListener(gcnew ObserverValue<int>::Event(this, &RealWaterPump::elementMove_event));

		//��������� �����
		this->form->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &RealWaterPump::chart_KeyDown);
		this->form->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &RealWaterPump::chart_KeyUp);
		this->form->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &RealWaterPump::FormClosing);

		addEventsToChar(this->form->chart1);
		addEventsToChar(this->form->chart2);
		addEventsToChar(this->form->chart3);

		this->form->button1->Click += gcnew System::EventHandler(this, &RealWaterPump::exitButtonClick);
		this->form->button2->Click += gcnew System::EventHandler(this, &RealWaterPump::exitButtonClick);

		///DATABASE
		//��������� ������ �� ��------------------------------------------------------------------------
		QueryBuilder("SELECT * FROM ���������_��������� WHERE IdElement = 17 ORDER BY idState").executeQuery(gcnew QueryBuilder::Read(this, &RealWaterPump::readStatusesDB));

		if (this->model->idLink != -1)
			QueryBuilder("SELECT *, (SELECT IdState FROM ����� WHERE idLink = " + this->model->idLink + ") as IdState FROM ��������_������� WHERE idLink = " + this->model->idLink)
			.executeQuery(gcnew QueryBuilder::Read(this, &RealWaterPump::readDataDB));


		this->efficiency_min->addEventListener(gcnew ObserverValue<double>::Event(this, &RealWaterPump::efficiency_event));
		this->efficiency_max->addEventListener(gcnew ObserverValue<double>::Event(this, &RealWaterPump::efficiency_event));
		this->pressure_in_min->addEventListener(gcnew ObserverValue<float>::Event(this, &RealWaterPump::pressure_in_event));
		this->pressure_in_max->addEventListener(gcnew ObserverValue<float>::Event(this, &RealWaterPump::pressure_in_event));
		this->pressure_out_min->addEventListener(gcnew ObserverValue<float>::Event(this, &RealWaterPump::pressure_out_event));
		this->pressure_out_max->addEventListener(gcnew ObserverValue<float>::Event(this, &RealWaterPump::pressure_out_event));
		this->k->addEventListener(gcnew ObserverValue<double>::Event(this, &RealWaterPump::k_event));

		this->efficiency_min->throwEvent();
		this->pressure_in_min->throwEvent();
		this->pressure_out_min->throwEvent();
		this->k->throwEvent();
	}

	void RealWaterPump::save() {
		exitButtonClick(this->form->button2, nullptr);
	}
	void RealWaterPump::migrate() {
		for each (RealChartPoint ^ point in this->points->getValue()) {
			WaterPump::ChartPoint tmp;
			tmp.H = point->H;
			tmp.N = point->N;
			tmp.Q = point->Q;

			this->model->points.push_back(tmp);
		}

		this->model->enable = this->enable->getValue();
		this->model->name = SysToStd(this->name->getValue());
		this->model->mark = SysToStd(this->mark->getValue());
		this->model->diameter_max = this->diameter_max->getValue();
		this->model->diameter_min = this->diameter_min->getValue();
		this->model->diameter_nominal = this->diameter_nominal->getValue();
		this->model->turnovers_current = this->turnovers_current->getValue();
		this->model->turnovers_max = this->turnovers_max->getValue();
		this->model->turnovers_min = this->turnovers_min->getValue();
		this->model->turnovers_nominal = this->turnovers_nominal->getValue();
		this->model->turnovers_current = this->turnovers_current->getValue();
		this->model->H0 = this->H0->getValue();
		this->model->S = this->S->getValue();
		this->model->N0 = this->N0->getValue();
		this->model->C = this->C->getValue();
	}

	void RealWaterPump::close() {
		exitButtonClick(this->form->button1, nullptr);
	}

	System::Void RealWaterPump::FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		this->k->clear();
		this->pointer->clear();
		this->elemMove->clear();
		this->point_input_q->clear();
		this->point_input_h->clear();
		this->point_input_n->clear();
		this->point_input_m->clear();

		this->name->clear();
		this->mark->clear();
		this->enable->clear();

		this->diameter_nominal->clear();
		this->diameter_current->clear();
		this->diameter_min->clear();
		this->diameter_max->clear();

		this->turnovers_nominal->clear();
		this->turnovers_current->clear();
		this->turnovers_min->clear();
		this->turnovers_max->clear();

		this->H0->clear();
		this->S->clear();
		this->N0->clear();
		this->C->clear();

		this->resistance_current->clear();

		this->efficiency_min->clear();
		this->efficiency_max->clear();

		this->pressure_in_min->clear();
		this->pressure_in_max->clear();
		this->pressure_out_min->clear();
		this->pressure_out_max->clear();

		this->points->clear();
		this->form->KeyDown -= gcnew System::Windows::Forms::KeyEventHandler(this, &RealWaterPump::chart_KeyDown);
		this->form->KeyUp -= gcnew System::Windows::Forms::KeyEventHandler(this, &RealWaterPump::chart_KeyUp);
		this->form->FormClosing -= gcnew System::Windows::Forms::FormClosingEventHandler(this, &RealWaterPump::FormClosing);

		removeEventsToChar(this->form->chart1);
		removeEventsToChar(this->form->chart2);
		removeEventsToChar(this->form->chart3);

		this->form = nullptr;

		clearCurrentDialog();
	}

	System::Void RealWaterPump::exitButtonClick(System::Object^ sender, System::EventArgs^ e) {
		Button^ button = dynamic_cast<Button^>(sender);

		if (button->Name == this->form->button2->Name) {
			this->isSaveValidation = true;

			this->name->valid();
			this->mark->valid();
			this->diameter_nominal->valid();
			this->turnovers_nominal->valid();
			this->H0->valid();
			this->S->valid();
			this->N0->valid();
			this->C->valid();

			int systemErrors = 0;
			for (auto it : this->model->errors) {
				if (it.first == SysToStd(this->form->input_data_q->Name))
					systemErrors++;
				else if (it.first == SysToStd(this->form->input_data_h_in->Name))
					systemErrors++;
				else if (it.first == SysToStd(this->form->input_data_h_out->Name))
					systemErrors++;

				if (systemErrors == 3)
					return;
			}

			if (this->model->errors.size() - systemErrors == 0) {
				QueryBuilder queryLinks;
				QueryBuilder queryPumps;
				bool isUpdate = true;

				if (this->model->idLink == -1) {
					isUpdate = false;
					this->model->idLink = (gcnew GetNextIdLink)->get();

					queryLinks.setSql("INSERT INTO ����� (idLink, IdElement, IdState) VALUES (?, 17, ?)")
						->add(this->model->idLink);

					queryPumps.setSql("INSERT INTO ��������_������� (idLink, name, mark, DrkMax, DrkMin, Drk0, Drk, TurnMax, TurnMin, Turn0, Turn, H0, N0, S, C, H1, N1, Q1, H2, N2, Q2, H3, N3, Q3, H4, N4, Q4, H5, N5, Q5, Qmin, Qmax, HNmin, HNmax, HKmin, HKmax) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")
						->add(this->model->idLink);
				}
				else {
					queryLinks.setSql("UPDATE ����� SET IdState = ? WHERE idLink = ?");
					queryPumps.setSql("UPDATE ��������_������� SET name = ?, mark = ?, DrkMax = ?, DrkMin = ?, Drk0 = ?, Drk = ?, TurnMax = ?, TurnMin = ?, Turn0 = ?, Turn = ?, H0 = ?, N0 = ?, S = ?, C = ?, H1 = ?, N1 = ?, Q1 = ?, H2 = ?, N2 = ?, Q2 = ?, H3 = ?, N3 = ?, Q3 = ?, H4 = ?, N4 = ?, Q4 = ?, H5 = ?, N5 = ?, Q5 = ?, Qmin = ?, Qmax = ?, HNmin = ?, HNmax = ?, HKmin = ?, HKmax = ? WHERE IdLink = ?");
				}

				queryLinks.add(this->enable);


				queryPumps.add(this->name)
					->add(this->mark)

					->add(this->diameter_max)
					->add(this->diameter_min)
					->add(this->diameter_nominal)
					->add(this->diameter_current)

					->add(this->turnovers_max)
					->add(this->turnovers_min)
					->add(this->turnovers_nominal)
					->add(this->turnovers_current)

					->add(this->H0)
					->add(this->N0)
					->add(this->S)
					->add(this->C);

				List<RealChartPoint^>^ chartPoints = this->points->getValue();
				for (int i = 0; i < 5; i++) {
					if (chartPoints->Count > i) {
						queryPumps.add(chartPoints[i]->H)->add(chartPoints[i]->N)->add(chartPoints[i]->Q);
					}
					else
						queryPumps.addEmpty()->addEmpty()->addEmpty();
				}

				queryPumps.add(this->efficiency_min)
					->add(this->efficiency_max)
					->add(this->pressure_in_max)
					->add(this->pressure_in_min)
					->add(this->pressure_out_max)
					->add(this->pressure_out_min);

				if (isUpdate) {
					queryLinks.add(this->model->idLink);
					queryPumps.add(this->model->idLink);
				}

				queryLinks.executeUpdate();
				queryPumps.executeUpdate();

				migrate();
			}
			else {
				MessageBox::Show(LocalizationManager::getStr("errors.to_save_correct_errors"), LocalizationManager::getStr("errors.attention"));
				this->isSaveValidation = false;
				return;
			}
		}

		this->form->Close();
	}

	void RealWaterPump::readStatusesDB(OleDbDataReader^ reader) {
		while (reader->Read()) {
			this->form->pump_enable->Items->Add(getString(reader, "StateName")->value);
		}
		this->form->pump_enable->SelectedIndex = 0;
	}

	void RealWaterPump::readDataDB(OleDbDataReader^ reader) {
		if (!reader->HasRows) {
			MessageBox::Show(String::Format(LocalizationManager::getStr("errors.isLink_not_found"), this->model->idLink), LocalizationManager::getStr("errors.error"));
			return;
		}

		reader->Read();

		this->name->setValue(getString(reader, "name"));
		this->mark->setValue(getString(reader, "mark"));


		this->diameter_nominal->setValue(getFloat(reader, "Drk0"));
		this->turnovers_nominal->setValue(getInt(reader, "Turn0"));

		this->diameter_current->setValue(getFloat(reader, "Drk"));
		this->turnovers_current->setValue(getFloat(reader, "Turn"));

		this->diameter_max->setValue(getFloat(reader, "DrkMax"));
		this->diameter_min->setValue(getFloat(reader, "DrkMin"));

		this->turnovers_max->setValue(getFloat(reader, "TurnMax"));
		this->turnovers_min->setValue(getFloat(reader, "TurnMin"));

		this->H0->setValue(getDouble(reader, "H0"));
		this->N0->setValue(getDouble(reader, "N0"));
		this->S->setValue(getFloat(reader, "S"));
		this->C->setValue(getDouble(reader, "C"));

		for (int i = 1; i <= 5; i++) {
			RealChartPoint^ tmpP = gcnew RealChartPoint;
			DBWrapper<double>^ pr = getDouble(reader, "Q" + i);
			if (pr->empty)
				break;
			tmpP->H = getDouble(reader, "H" + i)->value;
			tmpP->N = getDouble(reader, "N" + i)->value;
			tmpP->Q = pr->value;

			this->points->getValue()->Add(tmpP);
		}

		this->points->throwEvent();

		this->efficiency_min->setValue(getDouble(reader, "Qmin"));
		this->efficiency_max->setValue(getDouble(reader, "Qmax"));

		this->pressure_in_min->setValue(getFloat(reader, "HNmin"));
		this->pressure_in_max->setValue(getFloat(reader, "HNmax"));

		this->pressure_out_min->setValue(getFloat(reader, "HKmin"));
		this->pressure_out_max->setValue(getFloat(reader, "HKmax"));


		this->QPoint = getFloat(reader, "Q")->value;
		this->form->input_data_q->Text = round3(this->QPoint) + "";
		this->pointer->setValue(this->QPoint);
		this->HInPoint = getFloat(reader, "HN")->value;
		this->form->input_data_h_in->Text = round3(this->HInPoint) + "";
		this->HOutPoint = getFloat(reader, "HK")->value;
		this->form->input_data_h_out->Text = round3(this->HOutPoint) + "";


		this->enable->setValue(getInt(reader, "IdState"));

		migrate();
	}

	//������� � ����������---------------------------------------------------------
	String^ RealWaterPump::name_valide(String^ value, bool empty) {
		if (value->Length > 50)
			return LocalizationManager::getStr("errors.pump_name_greater_50");

		if (this->isSaveValidation && empty) {
			return LocalizationManager::getStr("errors.pump_name_empty");
		}
		return "";
	}

	String^ RealWaterPump::mark_valide(String^ value, bool empty) {
		if (value->Length > 20)
			return LocalizationManager::getStr("errors.pump_mark_greater_20");

		if (this->isSaveValidation && empty) {
			return LocalizationManager::getStr("errors.pump_mark_empty");
		}

		return "";
	}

	String^ RealWaterPump::five_points_valid(double value, bool empty) {
		if (this->isSaveValidation && this->form->chart1->Series[0]->Points->Count < 2) {
			return LocalizationManager::getStr("errors.chart_empty");
		}

		return "";
	}
	String^ RealWaterPump::five_points_valid(float value, bool empty) {
		return five_points_valid((double)value, empty);
	}
	String^ RealWaterPump::diameter_valide(float value, bool empty) {
		if (value < 0)
			return LocalizationManager::getStr("errors.diameter_less_0");

		if (this->isSaveValidation && empty) {
			return LocalizationManager::getStr("errors.nominal_diameter_empty");
		}

		return "";
	}

	void RealWaterPump::diameter_nominal_event(ObserverValue<float>^ link) {
		this->form->pump_slide_dim->Enabled = !link->isEmpty();
		this->form->pump_cur_dim->Enabled = !link->isEmpty();

		if (this->diameter_max->isUserNotEdit()) {
			this->diameter_max->setValue(link->getValue());
		}
		if (this->diameter_min->isUserNotEdit()) {
			this->diameter_min->setValue(0);
		}

		this->diameter_current->throwEvent();
	}

	void RealWaterPump::set_k_event(ObserverValue<double>^ link) {
		this->k->setValue(
			(this->turnovers_current->getValue() * this->diameter_current->getValue())
			/ (this->turnovers_nominal->getValue() * this->diameter_nominal->getValue()));
	}
	void RealWaterPump::set_k_event(ObserverValue<float>^ link) {
		set_k_event(this->resistance_current);
	}

	String^ RealWaterPump::diameter_max_min_valide(float value, bool empty) {
		this->diameter_max->valid();
		this->diameter_min->valid();

		if (!this->diameter_max->isEmpty() && !this->diameter_min->isEmpty() && this->diameter_min->getValue() > this->diameter_max->getValue()) {
			return LocalizationManager::getStr("errors.diameter_" + (this->diameter_max->getValue() == value ? "max_less_min" : "min_greater_max"));
		}

		return diameter_valide(value, false); //false ����� �� ����������� ��������� ��� ����������
	}

	void RealWaterPump::diameter_max_event(ObserverValue<float>^ link) {
		this->form->pump_slide_dim->Maximum = link->getValue();

		if (this->diameter_current->isUserNotEdit() || this->diameter_current->getValue() > link->getValue())
			this->diameter_current->setValue(link->getValue());

		this->form->pump_slide_dim->TickFrequency = (this->diameter_max->getValue() - this->diameter_min->getValue()) / 10;
	}

	void RealWaterPump::diameter_min_event(ObserverValue<float>^ link) {
		this->form->pump_slide_dim->Minimum = link->getValue();

		if (this->diameter_current->getValue() < link->getValue())
			this->diameter_current->setValue(link->getValue());

		this->form->pump_slide_dim->TickFrequency = (this->diameter_max->getValue() - this->diameter_min->getValue()) / 10;
	}



	String^ RealWaterPump::turnovers_valide(float value, bool empty) {
		if (value < 0)
			return LocalizationManager::getStr("errors.turnovers_less_0");

		if (this->isSaveValidation && empty) {
			return LocalizationManager::getStr("errors.nominal_turnovers_empty");
		}

		return "";
	}
	String^ RealWaterPump::turnovers_valide(int value, bool empty) {
		return turnovers_valide((float)value, empty);
	}

	void RealWaterPump::turnovers_nominal_event(ObserverValue<int>^ link) {
		this->form->pump_slide_turn->Enabled = !link->isEmpty();
		this->form->pump_cur_turn->Enabled = !link->isEmpty();

		if (this->turnovers_max->isUserNotEdit()) {
			this->turnovers_max->setValue((float)link->getValue());
		}
		if (this->turnovers_min->isUserNotEdit()) {
			this->turnovers_min->setValue(0);
		}

		this->turnovers_current->throwEvent();
	}


	String^ RealWaterPump::turnovers_max_min_valide(float value, bool empty) {
		this->turnovers_max->valid();
		this->turnovers_min->valid();

		if (!this->turnovers_max->isEmpty() && !this->turnovers_min->isEmpty() && this->turnovers_min->getValue() > this->turnovers_max->getValue()) {
			
			return LocalizationManager::getStr("errors.turnovers_" + (this->turnovers_max->getValue() == value ? "max_less_min" : "min_greater_max"));
		}

		return turnovers_valide(value, false); //false ����� �� ����������� ��������� ��� ����������
	}

	void RealWaterPump::turnovers_max_event(ObserverValue<float>^ link) {
		this->form->pump_slide_turn->Maximum = link->getValue();

		if (this->turnovers_current->isUserNotEdit() || this->turnovers_current->getValue() > link->getValue())
			this->turnovers_current->setValue(link->getValue());

		this->form->pump_slide_turn->TickFrequency = (this->turnovers_max->getValue() - this->turnovers_min->getValue()) / 10;
	}

	void RealWaterPump::turnovers_min_event(ObserverValue<float>^ link) {
		this->form->pump_slide_turn->Minimum = link->getValue();

		if (this->turnovers_current->getValue() < link->getValue())
			this->turnovers_current->setValue(link->getValue());

		this->form->pump_slide_turn->TickFrequency = (this->turnovers_max->getValue() - this->turnovers_min->getValue()) / 10;
	}



	void RealWaterPump::k_event(ObserverValue<double>^ link) {
		double value = link->getValue();
		if (value == 0 || System::Double::IsInfinity(value) || System::Double::IsNaN(value))
			value = 1;

		this->form->chart1->Series[1]->Points->Clear();
		this->form->chart2->Series[1]->Points->Clear();
		this->form->chart3->Series[1]->Points->Clear();
		ChartData data = calculateChartData(value, this->points->getValue(), nullptr);
		double resMin = data.H0 / (value * value * this->efficiency_min->getValue() * this->efficiency_min->getValue()) - data.S;

		this->form->pump_cur_s->Enabled = true;
		this->form->pump_slide_s->Enabled = true;


		if (Double::IsInfinity(resMin) || Double::IsNaN(resMin) || data.S == 0) {
			if (data.S == 0) {
				resMin = 1;
				this->form->pump_cur_s->Enabled = false;
				this->form->pump_slide_s->Enabled = false;
				this->resistance_current->setValue(0);
			}
			else {
				resMin = data.H0 / (0.1) - data.S;
			}
		}

		this->resistance_min = resMin / this->form->pump_slide_s->Maximum;


		if (this->resistance_current->getValue() == -1) {
			this->resistance_current->setValue(Math::Max(this->S->getValue() - data.S, 0.0));
		}

		data.S += this->resistance_current->getValue();

		if (value == link->getValue()) {
			drawPumpCharts(data, gcnew DrawDelegat(this, &RealWaterPump::drawExtendsPointCallBack), false, this->form->chart1->ChartAreas[0]->AxisX->Maximum);
		}
		this->S->setValue(data.S);
		this->C->setValue(data.C);
		this->H0->setValue(data.H0);
		this->N0->setValue(data.N0);

		this->pointer->throwEvent();
		this->efficiency_max->throwEvent();
	}

	void RealWaterPump::drawNominalPointCallBack(double q, double h, double n, double m) {
		double mx = this->form->chart1->ChartAreas[0]->AxisY->Maximum * 2;
		if (mx < 1'000)
			mx = 1'000;
		if (Math::Abs(h) < mx)
			this->form->chart1->Series[0]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, h));

		mx = this->form->chart2->ChartAreas[0]->AxisY->Maximum * 2;
		if (mx < 1'000)
			mx = 1'000;
		if (Math::Abs(n) < mx)
			this->form->chart2->Series[0]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, n));

		mx = this->form->chart3->ChartAreas[0]->AxisY->Maximum * 2;
		if (mx < 1'000)
			mx = 1'000;
		if (Math::Abs(m) < mx)
			this->form->chart3->Series[0]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, m));
	}

	void RealWaterPump::drawExtendsPointCallBack(double q, double h, double n, double m) {
		double mx = this->form->chart1->ChartAreas[0]->AxisY->Maximum * 2;
		if (mx < 1'000)
			mx = 1'000;
		if (Math::Abs(h) < mx)
			this->form->chart1->Series[1]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, h));

		mx = this->form->chart2->ChartAreas[0]->AxisY->Maximum * 2;
		if (mx < 1'000)
			mx = 1'000;
		if (Math::Abs(n) < mx)
			this->form->chart2->Series[1]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, n));

		mx = this->form->chart3->ChartAreas[0]->AxisY->Maximum * 2;
		if (mx < 1'000)
			mx = 1'000;
		if (Math::Abs(m) < mx)
			this->form->chart3->Series[1]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, m));
	}

	String^ RealWaterPump::resistance_current_valid(double value, bool empty) {
		if (value < 0) {
			return LocalizationManager::getStr("errors.throttling_resistance_less_0");
		}

		double q = resistance_current_PrepareToShow(value, true);

		if (q > 1000 || q < 0)
			return LocalizationManager::getStr("errors.resistance_exiting_working_area");

		return "";
	}

	double RealWaterPump::resistance_current_PrepareToShow(double value, bool isShow) {
		if (this->resistance_min == 0)
			return 0;
		if (isShow) {
			return value / this->resistance_min;
		}
		return 	value * this->resistance_min;

	}

	String^ RealWaterPump::efficiency_valide(double value, bool empty) {
		this->efficiency_max->valid();
		this->efficiency_min->valid();

		if (!this->efficiency_max->isEmpty() && !this->efficiency_min->isEmpty() && this->efficiency_min->getValue() > this->efficiency_max->getValue()) {
			return LocalizationManager::getStr("errors.capacity_" + (this->efficiency_max->getValue() == value ? "max_less_min" : "min_greater_max"));
		}

		if (value < 0)
			return LocalizationManager::getStr("errors.capacity_empty");

		return "";
	}

	void RealWaterPump::efficiency_event(ObserverValue<double>^ link) {
		this->form->chart1->Invalidate();
		this->form->chart2->Invalidate();
		this->form->chart3->Invalidate();

		if (this->QPoint != 0)
			if ((!this->efficiency_min->isEmpty() && this->efficiency_min->getValue() > this->QPoint)
				||
				(!this->efficiency_max->isEmpty() && this->efficiency_max->getValue() < this->QPoint)) {


				ObserverValue<int>::addToErrors(this->form->input_data_q, LocalizationManager::getStr("errors.work_point_exiting_working_area"), &this->model->errors, this->form->toolTip1);
				return;
			}

		ObserverValue<int>::removeFromsErrors(this->form->input_data_q, &this->model->errors, this->form->toolTip1);
		this->k->throwEvent();
	}

	double RealWaterPump::efficiency_PrepareToShow(double value, bool isShow) {
		if (isShow) {
			double localK = this->k->getValue();
			if (localK == 0 || System::Double::IsInfinity(localK) || System::Double::IsNaN(localK))
				localK = 1;
			return value * localK;
		}
		return value;
	}


	String^ RealWaterPump::pressure_in_valide(float value, bool empty) {
		this->pressure_in_max->valid();
		this->pressure_in_min->valid();

		if (!this->pressure_in_max->isEmpty() && !this->pressure_in_min->isEmpty() && this->pressure_in_min->getValue() > this->pressure_in_max->getValue()) {
			return LocalizationManager::getStr("errors.pressure_" + (this->pressure_in_max->getValue() == value ? "max_less_min" : "min_greater_max"));
		}

		if (value < 0)
			return LocalizationManager::getStr("errors.pressure_less_0");

		return "";
	}

	String^ RealWaterPump::pressure_out_valide(float value, bool empty) {
		this->pressure_out_max->valid();
		this->pressure_out_min->valid();

		if (!this->pressure_out_max->isEmpty() && !this->pressure_out_min->isEmpty() && this->pressure_out_min->getValue() > this->pressure_out_max->getValue()) {
			return LocalizationManager::getStr("errors.pressure_" + (this->pressure_out_max->getValue() == value ? "max_less_min" : "min_greater_max"));
		}

		if (value < 0)
			return LocalizationManager::getStr("errors.pressure_less_0");

		return "";
	}

	void RealWaterPump::pressure_in_event(ObserverValue<float>^ link) {
		if (this->pressure_in_max->isEmpty() || this->pressure_in_min->isEmpty())
			return;

		if (this->HInPoint != 0)
			if ((!this->pressure_in_min->isEmpty() && this->pressure_in_min->getValue() > this->HInPoint)
				||
				(!this->pressure_in_max->isEmpty() && this->pressure_in_max->getValue() < this->HInPoint)) {


				ObserverValue<int>::addToErrors(this->form->input_data_h_in, LocalizationManager::getStr("errors.work_point_exiting_working_area"), &this->model->errors, this->form->toolTip1);
				return;
			}

		ObserverValue<int>::removeFromsErrors(this->form->input_data_h_in, &this->model->errors, this->form->toolTip1);

	}

	void RealWaterPump::pressure_out_event(ObserverValue<float>^ link) {
		if (this->pressure_out_max->isEmpty() || this->pressure_out_min->isEmpty())
			return;

		if (this->HOutPoint != 0)
			if ((!this->pressure_out_min->isEmpty() && this->pressure_out_min->getValue() > this->HOutPoint)
				||
				(!this->pressure_out_max->isEmpty() && this->pressure_out_max->getValue() < this->HOutPoint)) {


				ObserverValue<int>::addToErrors(this->form->input_data_h_out, LocalizationManager::getStr("errors.work_point_exiting_working_area"), &this->model->errors, this->form->toolTip1);
				return;
			}

		ObserverValue<int>::removeFromsErrors(this->form->input_data_h_out, &this->model->errors, this->form->toolTip1);

	}

	void RealWaterPump::PointsCalculate(double q, double h, double n, int i) {
		checkPoint(this->form->chart1, (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, h)), i);
		checkPoint(this->form->chart2, (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, n)), i);
		checkPoint(this->form->chart3, (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(q, getCPD(h, q, n))), i);
	}

	void RealWaterPump::points_event(ObserverValue<List<RealChartPoint^>^>^ link) {
		if (link->getValue()->Count == 0)
			return;
		this->form->chart1->Series[0]->Points->Clear();
		this->form->chart1->Series[3]->Points->Clear();
		this->form->chart2->Series[0]->Points->Clear();
		this->form->chart2->Series[3]->Points->Clear();
		this->form->chart3->Series[0]->Points->Clear();
		this->form->chart3->Series[3]->Points->Clear();

		ChartData data = calculateChartData(1, link->getValue(), gcnew CalculateDelegat(this, &RealWaterPump::PointsCalculate));


		bool isInterval = !this->isMove;

		auto intervals = drawPumpCharts(data, gcnew DrawDelegat(this, &RealWaterPump::drawNominalPointCallBack), isInterval, -1, link->getValue());

		if (isInterval) {
			if (intervals.QInterval != 0) {
				this->form->chart1->ChartAreas[0]->AxisX->Interval = intervals.QInterval;
				this->form->chart2->ChartAreas[0]->AxisX->Interval = intervals.QInterval;
				this->form->chart3->ChartAreas[0]->AxisX->Interval = intervals.QInterval;
			}
			if (intervals.QMax != 0) {
				this->form->chart1->ChartAreas[0]->AxisX->Maximum = intervals.QMax;
				this->form->chart2->ChartAreas[0]->AxisX->Maximum = intervals.QMax;
				this->form->chart3->ChartAreas[0]->AxisX->Maximum = intervals.QMax;
			}

			if (intervals.HInterval != 0)
				this->form->chart1->ChartAreas[0]->AxisY->Interval = intervals.HInterval;
			if (intervals.HMax != 0)
				this->form->chart1->ChartAreas[0]->AxisY->Maximum = intervals.HMax;

			if (intervals.NInterval != 0)
				this->form->chart2->ChartAreas[0]->AxisY->Interval = intervals.NInterval;
			if (intervals.NMax != 0)
				this->form->chart2->ChartAreas[0]->AxisY->Maximum = intervals.NMax;

			if (intervals.MInterval != 0)
				this->form->chart3->ChartAreas[0]->AxisY->Interval = intervals.MInterval;
			if (intervals.MMax != 0)
				this->form->chart3->ChartAreas[0]->AxisY->Maximum = intervals.MMax;
			
			normalyzeTitleChart(this->form->chart1);
			normalyzeTitleChart(this->form->chart2);
			normalyzeTitleChart(this->form->chart3);
		}

		this->form->numeric_input_point->Maximum = link->getValue()->Count;

		this->k->throwEvent();
	}

	String^ RealWaterPump::point_input_valide(double value, bool empty) {
		if (value < 0) {
			return LocalizationManager::getStr("errors.characterization_less_0");
		}

		if (empty && this->elemMove->getValue() != 0) {
			return LocalizationManager::getStr("errors.characterization_empty");
		}

		return "";
	}

	void RealWaterPump::point_input_event(ObserverValue<double>^ link) {
		if (this->elemMove->isUpdateProcess) {
			return;
		}
		int elemMoveValue = this->elemMove->getValue() - 1;
		if (elemMoveValue == -1) {
			return;
		}

		RealChartPoint^ point = this->points->getValue()[elemMoveValue];

		if (link == this->point_input_q) {
			this->form->chart1->Series[2]->Points[0]->XValue = link->getValue();
			this->form->chart2->Series[2]->Points[0]->XValue = link->getValue();
			this->form->chart3->Series[2]->Points[0]->XValue = link->getValue();
			this->form->chart3->Series[2]->Points[0]->YValues[0] = getCPD(this->point_input_h->getValue(), link->getValue(), this->point_input_n->getValue());

			point->Q = link->getValue();

			sortPoint(this->points->getValue());
			for (int v = 0; v < this->points->getValue()->Count; v++) {
				RealChartPoint^ itPoint = this->points->getValue()[v];

				if (point->Q == itPoint->Q
					&& point->N == itPoint->N
					&& point->H == itPoint->H) {
					elemMoveValue = v;
					break;
				}
			}
		}
		else if (link == this->point_input_h) {
			point->H = link->getValue();
		}
		else if (link == this->point_input_n) {
			point->N = link->getValue();
		}

		this->points->throwEvent();
		this->elemMove->setValue(elemMoveValue + 1);
	}

	void RealWaterPump::elementMove_event(ObserverValue<int>^ value) {
		int elemMoveValue = value->getValue() - 1;
		this->form->chart1->Series[2]->Points->Clear();
		this->form->chart2->Series[2]->Points->Clear();
		this->form->chart3->Series[2]->Points->Clear();

		if (elemMoveValue != -1) {
			auto p1 = this->form->chart1->Series[3]->Points[elemMoveValue];
			auto p2 = this->form->chart2->Series[3]->Points[elemMoveValue];
			auto p3 = this->form->chart3->Series[3]->Points[elemMoveValue];

			this->form->chart1->Series[2]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(p1->XValue, p1->YValues[0]));
			this->form->chart2->Series[2]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(p2->XValue, p2->YValues[0]));
			this->form->chart3->Series[2]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(p3->XValue, p3->YValues[0]));

			this->point_input_h->setValue(p1->YValues[0]);
			this->point_input_n->setValue(p2->YValues[0]);
			this->point_input_m->setValue(p3->YValues[0]);
			this->point_input_q->setValue(p1->XValue);


			this->form->box_elem_h->ReadOnly = false;
			this->form->box_elem_n->ReadOnly = false;
			this->form->box_elem_q->ReadOnly = false;
		}
		else {
			this->point_input_h->setValue(0);
			this->point_input_n->setValue(0);
			this->point_input_m->setValue(0);
			this->point_input_q->setValue(0);

			this->form->box_elem_h->ReadOnly = true;
			this->form->box_elem_n->ReadOnly = true;
			this->form->box_elem_q->ReadOnly = true;
		}
	}

	String^ RealWaterPump::pointer_valid(double value, bool empty) {
		if (value < 0) {
			return LocalizationManager::getStr("errors.capacity_less_0");
		}

		return "";
	}

	void RealWaterPump::pointer_event(ObserverValue<double>^ link) {
		double value = link->getValue();
		if (value < 0)
			return;
		if (value > this->form->chart1->ChartAreas[0]->AxisX->Maximum)
			return;
		if (value == 0)
			value = 1e-11;

		this->form->chart1->Series[4]->Points->Clear();
		this->form->chart2->Series[4]->Points->Clear();
		this->form->chart3->Series[4]->Points->Clear();

		if (!link->isEmpty()) {
			this->form->chart1->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, 0));
			this->form->chart1->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, this->form->chart1->ChartAreas[0]->AxisY->Maximum));

			this->form->chart2->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, 0));
			this->form->chart2->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, this->form->chart2->ChartAreas[0]->AxisY->Maximum));

			this->form->chart3->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, 0));
			this->form->chart3->Series[4]->Points->Add(gcnew DataVisualization::Charting::DataPoint(value, this->form->chart3->ChartAreas[0]->AxisY->Maximum));
		}

		double h = this->H0->getValue() - this->S->getValue() * value * value;
		SuperTextSetter(this->form->box_point_h, h, link->isEmpty());
		SuperTextSetter(this->form->box_point_dh, this->H0->getValue() - h, link->isEmpty());

		double n = this->N0->getValue() + this->C->getValue() * value;
		SuperTextSetter(this->form->box_point_n, n, link->isEmpty());
		SuperTextSetter(this->form->box_point_m, getCPD(h, value, n), link->isEmpty());
	}

	System::Void RealWaterPump::PostPaint(System::Object^ sender, System::Windows::Forms::DataVisualization::Charting::ChartPaintEventArgs^ e)
	{
		double localK = this->k->getValue();
		if (localK == 0 || System::Double::IsInfinity(localK) || System::Double::IsNaN(localK))
			localK = 1;

		//���� ������������ �������, ��� ��� �� ����������, � ���� ������������� ���� ������, �� ��� ���
		if (!e->ChartElement->GetType()->Equals(this->form->chart1->ChartAreas[0]->GetType()))
			return;


		//----------------------------------------------------------------------------------------------------------

		//�������� ��� ��������
		System::Drawing::Brush^ b = gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(100, 255, 0, 0));

		//��������� ������� Qmin
		System::Drawing::RectangleF s1 = System::Drawing::RectangleF::FromLTRB(
			e->Chart->ChartAreas[0]->AxisX->ValueToPixelPosition(0),
			e->Chart->ChartAreas[0]->AxisY->ValueToPixelPosition(e->Chart->ChartAreas[0]->AxisY->Maximum),
			e->Chart->ChartAreas[0]->AxisX->ValueToPixelPosition(this->efficiency_min->getValue() * localK),
			e->Chart->ChartAreas[0]->AxisY->ValueToPixelPosition(0)
		);

		//��������� ������� Qmax
		System::Drawing::RectangleF s2 = System::Drawing::RectangleF::FromLTRB(
			e->Chart->ChartAreas[0]->AxisX->ValueToPixelPosition(this->efficiency_max->getValue() * localK),
			e->Chart->ChartAreas[0]->AxisY->ValueToPixelPosition(e->Chart->ChartAreas[0]->AxisY->Maximum),
			e->Chart->ChartAreas[0]->AxisX->ValueToPixelPosition(e->Chart->ChartAreas[0]->AxisX->Maximum),
			e->Chart->ChartAreas[0]->AxisY->ValueToPixelPosition(0)
		);


		if (this->efficiency_min->getValue() * localK != 0)
			e->ChartGraphics->Graphics->FillRectangle(b, s1);
		if (this->efficiency_max->getValue() * localK != 0)
			e->ChartGraphics->Graphics->FillRectangle(b, s2);

		//----------------------------------------------------------------------------------------------------------


		//������� ����� ��������
		System::Drawing::Font^ FMSS = gcnew System::Drawing::Font(gcnew System::Drawing::FontFamily("Microsoft Sans Serif"), 9);
		System::Drawing::SolidBrush^ backBrush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(255, 255, 255));

		//��������� ������� ��� �
		double endX = e->Chart->ChartAreas[0]->AxisX->ValueToPixelPosition(e->Chart->ChartAreas[0]->AxisX->Maximum);
		double endXNext = e->Chart->ChartAreas[0]->AxisX->ValueToPixelPosition(e->Chart->ChartAreas[0]->AxisX->Maximum - e->Chart->ChartAreas[0]->AxisX->Interval);
		double startY = e->Chart->ChartAreas[0]->AxisY->ValueToPixelPosition(0);

		String^ xText = "Q(" + LocalizationManager::getStr("charts.m3/h") + ")";

		SizeF^ sizeIntervalX = e->ChartGraphics->Graphics->MeasureString(e->Chart->ChartAreas[0]->AxisX->Maximum + "", FMSS);
		SizeF^ sizeIntervalXNext = e->ChartGraphics->Graphics->MeasureString((e->Chart->ChartAreas[0]->AxisX->Maximum - e->Chart->ChartAreas[0]->AxisX->Interval) + "", FMSS);
		SizeF^ sizeTextX = e->ChartGraphics->Graphics->MeasureString(xText, FMSS);

		double maxRecWidthX = Math::Max(sizeIntervalX->Width, sizeTextX->Width);

		double RBX = endX + maxRecWidthX / 2;
		double LTX = endX - maxRecWidthX / 2;

		if (RBX > e->Chart->Size.Width) {
			LTX -= (RBX - e->Chart->Size.Width);
			RBX = e->Chart->Size.Width;
		}

		System::Drawing::RectangleF recBackTextX = System::Drawing::RectangleF::FromLTRB(
			LTX, startY + 2,
			RBX, e->Chart->Size.Height
		);

		e->ChartGraphics->Graphics->FillRectangle(backBrush, recBackTextX);
		e->ChartGraphics->Graphics->DrawString(xText,
			FMSS,
			gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(0, 0, 0)),
			LTX, startY + sizeTextX->Height / 2);

		//----------------------------------------------------------------------------------------------------------
		//��������� �������� ������ ��������

		double startX = e->Chart->ChartAreas[0]->AxisX->ValueToPixelPosition(0);
		double endY = e->Chart->ChartAreas[0]->AxisY->ValueToPixelPosition(e->Chart->ChartAreas[0]->AxisY->Maximum);

		SizeF^ sizeIntervalY = e->ChartGraphics->Graphics->MeasureString(e->Chart->ChartAreas[0]->AxisY->Maximum + "", FMSS);

		SizeF^ sizeTextY = e->ChartGraphics->Graphics->MeasureString(e->Chart->Text, FMSS);
		SizeF^ sizeTextYMax = e->ChartGraphics->Graphics->MeasureString(e->Chart->ChartAreas[0]->AxisY->Maximum + "", FMSS);

		double maxRecHeightY = Math::Max(sizeIntervalY->Height, sizeTextY->Height);

		double RBY = endY + maxRecHeightY / 2;
		double LTY = endY - maxRecHeightY / 2;

		double maxTextWidth = Math::Max(sizeTextY->Width, sizeTextYMax->Width) + 2;

		e->Chart->ChartAreas[0]->Position->X = 30;
		e->Chart->ChartAreas[0]->Position->Width = 100 - 30;
		

		if (LTY < 0) {
			RBY -= LTY;
			LTY = 0;
		}

		

		System::Drawing::RectangleF recBackTextY = System::Drawing::RectangleF::FromLTRB(
			0, LTY,
			startX - 2, RBY
		);

		e->ChartGraphics->Graphics->FillRectangle(backBrush, recBackTextY);
		e->ChartGraphics->Graphics->DrawString(e->Chart->Text,
			FMSS,
			gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(0, 0, 0)),
			startX - maxTextWidth, LTY);


		//----------------------------------------------------------------------------------------------------------
		//���� ����� ���, ������ ��������
		if (this->points->isEmpty()) {
			System::Drawing::RectangleF recBackTextYZ = System::Drawing::RectangleF::FromLTRB(
				0, 0,
				this->form->chart1->Width, this->form->chart1->Height
			);

			e->ChartGraphics->Graphics->FillRectangle(gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(128, 255, 255, 255)), recBackTextYZ);

			String^ emptyText = LocalizationManager::getStr("message.chart_empty" + (e->Chart->Name != this->form->chart3->Name ? "" : "_efficiency"));

			SizeF^ sizeAdd = e->ChartGraphics->Graphics->MeasureString(emptyText, FMSS);
			e->ChartGraphics->Graphics->DrawString(emptyText,
				FMSS,
				gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(0, 0, 0)),
				(startX + endX - sizeAdd->Width) / 2, (startY + endY - sizeAdd->Height) / 2);
		}
	}

	System::Void RealWaterPump::chart_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		DataVisualization::Charting::Chart^ chart = safe_cast<DataVisualization::Charting::Chart^>(sender);
		this->chartMove = chart->Name == this->form->chart1->Name;

		if (this->points->isEmpty())
			return;

		double xChart = chart->ChartAreas[0]->AxisX->PixelPositionToValue(e->X);

		isMove = false;
		for (int i = 0; i < chart->Series[3]->Points->Count; i++) {

			auto q = chart->Series[3]->Points[i];
			double xG = chart->ChartAreas[0]->AxisX->ValueToPixelPosition(q->XValue);
			double yG = chart->ChartAreas[0]->AxisY->ValueToPixelPosition(q->YValues[0]);

			bool r = (e->X - xG) * (e->X - xG) + (e->Y - yG) * (e->Y - yG) <= 50;
			if (r) {
				isMove = chart->Name != this->form->chart3->Name;
				this->elemMove->setValue(i + 1);

				xChart = q->XValue;
				break;
			}
		}


		this->pointer->setValue(xChart);
	}
	System::Void RealWaterPump::chart_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (this->elemMove->getValue() == 0 || !this->isMove)
			return;

		DataVisualization::Charting::Chart^ chart = safe_cast<DataVisualization::Charting::Chart^>(sender);
		if ((chart->Name == this->form->chart1->Name) != this->chartMove)
			return;

		double xChart;
		double yChart;
		try {
			xChart = chart->ChartAreas[0]->AxisX->PixelPositionToValue(e->X);
			yChart = chart->ChartAreas[0]->AxisY->PixelPositionToValue(e->Y);
		}
		catch (Exception^ ignore) {
			return;
		}

		if (yChart < 0 || yChart > chart->ChartAreas[0]->AxisY->Maximum)
			return;
		if (xChart < 0 || xChart > chart->ChartAreas[0]->AxisX->Maximum)
			return;

		if (isShift) {
			this->point_input_q->setValue(xChart);
		}
		else {
			(this->chartMove ? this->point_input_h : this->point_input_n)->setValue(yChart);
		}

	}
	System::Void RealWaterPump::chart_MouseLeave(System::Object^ sender, System::EventArgs^ e) {

		this->chart_MouseUp(sender, nullptr);
	}
	System::Void RealWaterPump::chart_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (!this->isMove)
			return;

		DataVisualization::Charting::Chart^ chart = safe_cast<DataVisualization::Charting::Chart^>(sender);
		isMove = false;

		this->points->throwEvent();
	}

	System::Void RealWaterPump::chart_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::ShiftKey || e->KeyCode == Keys::Shift) {
			this->isShift = true;
		}

		int i = this->elemMove->getValue();
		if (e->KeyCode == Keys::Delete && i != -1)
			if (MessageBox::Show(String::Format(LocalizationManager::getStr("message.chart_point_delete"), i),
				LocalizationManager::getStr("message.chart_point_delete_title"), MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes) {
				this->points->getValue()->RemoveAt(i - 1);
				this->points->throwEvent();
				this->elemMove->setValue(0);
			}
	}
	System::Void RealWaterPump::chart_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::ShiftKey || e->KeyCode == Keys::Shift) {
			this->isShift = false;
		}
	}


	System::Void RealWaterPump::chart_DoubleClick(System::Object^ sender, System::EventArgs^ e) {
		if (this->isMove)
			return;
		if (this->points->getValue()->Count >= 5) {
			MessageBox::Show(LocalizationManager::getStr("message.maximum_5_points_added"), LocalizationManager::getStr("errors.attention"));
			return;
		}

		DataVisualization::Charting::Chart^ localChart = safe_cast<DataVisualization::Charting::Chart^>(sender);
		bool isChart1 = localChart->Name == this->form->chart1->Name;
		MouseEventArgs^ event = safe_cast<MouseEventArgs^>(e);
		RealChartPoint^ newPoint = gcnew RealChartPoint();

		newPoint->Q = localChart->ChartAreas[0]->AxisX->PixelPositionToValue(event->X);

		(isChart1 ? newPoint->H : newPoint->N) = localChart->ChartAreas[0]->AxisY->PixelPositionToValue(event->Y);
		(isChart1 ? newPoint->N : newPoint->H) = 0;

		this->points->getValue()->Add(newPoint);
		sortPoint(this->points->getValue());
		this->points->throwEvent();
	}

	void RealWaterPump::addEventsToChar(System::Windows::Forms::DataVisualization::Charting::Chart^ chart) {
		chart->PostPaint += gcnew System::EventHandler<System::Windows::Forms::DataVisualization::Charting::ChartPaintEventArgs^ >(this, &angarawindows::RealWaterPump::PostPaint);
		if (chart->Name != this->form->chart3->Name)
			chart->DoubleClick += gcnew System::EventHandler(this, &RealWaterPump::chart_DoubleClick);
		chart->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &RealWaterPump::chart_MouseDown);
		chart->MouseLeave += gcnew System::EventHandler(this, &RealWaterPump::chart_MouseLeave);
		chart->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &RealWaterPump::chart_MouseMove);
		chart->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &RealWaterPump::chart_MouseUp);
	}
	void RealWaterPump::removeEventsToChar(System::Windows::Forms::DataVisualization::Charting::Chart^ chart) {
		chart->PostPaint -= gcnew System::EventHandler<System::Windows::Forms::DataVisualization::Charting::ChartPaintEventArgs^ >(this, &angarawindows::RealWaterPump::PostPaint);
		if (chart->Name != this->form->chart3->Name)
			chart->DoubleClick -= gcnew System::EventHandler(this, &RealWaterPump::chart_DoubleClick);
		chart->MouseDown -= gcnew System::Windows::Forms::MouseEventHandler(this, &RealWaterPump::chart_MouseDown);
		chart->MouseLeave -= gcnew System::EventHandler(this, &RealWaterPump::chart_MouseLeave);
		chart->MouseMove -= gcnew System::Windows::Forms::MouseEventHandler(this, &RealWaterPump::chart_MouseMove);
		chart->MouseUp -= gcnew System::Windows::Forms::MouseEventHandler(this, &RealWaterPump::chart_MouseUp);
	}



	void WaterPump::show(int idLink) {
		this->idLink = idLink;
		RealWaterPump^ rl = gcnew RealWaterPump(this);
	//	currentDialog = rl;
	}

	void WaterPump::close() {
		//currentDialog->close();
		clearCurrentDialog();
	}

	void WaterPump::save() {
		//currentDialog->save();
		//clearCurrentDialog();
	}

}
