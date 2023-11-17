#pragma once
#include <msclr\marshal_cppstd.h>
#include <string>
#include <vector>
#include <algorithm>
#include "angara_windows.h"
namespace angarawindows {

	void sortPoint(std::vector<angarawindows::WaterPumpWindow::ChartPoint> *q) {
		std::sort(q->begin(), q->end(), [](const angarawindows::WaterPumpWindow::ChartPoint p1, angarawindows::WaterPumpWindow::ChartPoint p2) {
			return p1.Q < p2.Q;
			});
	}

	void checkPoint(System::Windows::Forms::DataVisualization::Charting::Chart^ chart, System::Windows::Forms::DataVisualization::Charting::DataPoint^ point, int i) {
		if (chart->Series[1]->Points->Count >= i)
			chart->Series[1]->Points->Add(point);
		else if ((chart->Series[1]->Points[i]->XValue != point->XValue || chart->Series[1]->Points[i]->YValues[0] != point->YValues[0]))
			chart->Series[1]->Points[i] = point;
	}

	std::string SysToStd(System::String^ original) {
		return msclr::interop::marshal_as<std::string>(original);
	}
	System::String^ SysToStd(std::string original) {
		return gcnew System::String(original.c_str());
	}

	int _IntInputHandler(System::Windows::Forms::TextBox^ box) {
		int ans = 0;
		bool isMinus = false;

		for (int i = 0; i < box->Text->Length; i++) {
			auto ch = box->Text[i];

			if (ans == 0 && ch == '-') {
				isMinus = true;
			}
			else if ('0' <= ch && ch <= '9') {
				ans = ans * 10 + (ch - '0');
			}
		}
		return (isMinus ? -1 : 1) * ans;
	}

	double _DoubleInputHandler(System::Windows::Forms::TextBox^ box) {
		double ans = 0;
		double drob = 0;
		double drobSize = 1;
		bool isMinus = false;
		bool isDrob = false;

		for (int i = 0; i < box->Text->Length; i++) {
			auto ch = box->Text[i];

			if (ans == 0 && ch == '-') {
				isMinus = true;
			}
			else if ('0' <= ch && ch <= '9') {
				if (isDrob) {
					drobSize *= 10;
					drob = drob * 10 + (ch - '0');
				}
				else {
					ans = ans * 10 + (ch - '0');
				}
			}else if ((ch == '.' || ch == ',') && !isDrob) {
				isDrob = true;
			}
		}
		return (isMinus ? -1 : 1) * (ans + (isDrob ? (drob/drobSize) : 0));
	}

	void SuperTextSetter(System::Windows::Forms::TextBox^ box, System::String^ text) {
		int last = box->SelectionStart - box->Text->Length;
		box->Text = text;
		box->SelectionStart = last + text->Length;
		box->SelectionLength = 0;
	}

	int GetIntLength(int q) {
		int i = 0;
		bool isMinus = q < 0;
		if (isMinus)
			q = -1 * q;

		for (; q > 0; i++) {
			q /= 10;
		}

		return isMinus + i;
	}

	double getCPD(double H, double Q, double N) {
		return 0.272407 * H * Q / N;
	}

	int getInterval(double maxValue) {
		// 1000 => 500
		// 500 => 100
		// 100 => 50
		// 50 => 10
		// 20 => 5
		// 10 => 1

		if (maxValue < 10)
			return 1;
		if (maxValue < 50)
			return 10;
		if (maxValue < 100)
			return 20;
		if (maxValue < 500)
			return 30;
		if (maxValue < 1000)
			return 200;
		return 1;
	}
}