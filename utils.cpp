#pragma once

#include "utils.h"
#include "angara_windows.h"
#include <msclr\marshal_cppstd.h>
#include <algorithm>
#include <stdexcept>
#include <msclr/gcroot.h>

namespace angarawindows {

	double getCPD(double H, double Q, double N) {
		return 0.272407 * H * Q / N;
	}

	double* getInterval(double x) {
		double copyX = x;
		int size = 0;

		while (copyX > 34)
		{
			size++;
			copyX /= 10;
		}

		copyX = System::Math::Floor(copyX * 10) / 10.0;
		double offset = 1;
		double max = x + 1;
		double normalyze = System::Math::Pow(10, size);

		if (copyX > 14 && copyX < 35) {
			offset = 5 * normalyze;
			normalyze *= 15;

			max = normalyze + offset * (System::Math::Floor((x - normalyze) / offset) + 1);
		}
		else if (copyX >= 6 && copyX <= 14) {
			offset = 2 * System::Math::Pow(10, size);
			normalyze *= 6;

			max = normalyze + offset * (System::Math::Floor((x - normalyze) / offset) + 1);
		}
		else if (copyX >= 3.5 && copyX < 6) {
			offset = System::Math::Pow(10, size);
			max = normalyze * 3 + offset * (System::Math::Ceiling((x - normalyze * 3.5) / offset) + 1);
		}

		double ans[2];
		ans[0] = offset;
		ans[1] = System::Math::Ceiling(max);
		return ans;
	}

	double round3(double x) {
		if (x != x)
			return 0;

		return System::Math::Round(x * 1000) / 1000.0;
	}

	ChartIntevals drawPumpCharts(ChartData &data, std::function<void(double, double, double, double)> drawFunc, bool isInterval, double maxX) {
		ChartIntevals intervals;

		//System::Windows::Forms::MessageBox::Show(data.S + " = s");
		//System::Windows::Forms::MessageBox::Show(data.C + " = C");

		if (data.S <= 0 || data.C <= 0)
			return intervals;

		double lastX = 0;
		double endX = maxX == -1 ? System::Math::Sqrt(data.H0 / data.S) : maxX;
		double offset = endX / 8;

		double maxM = 0;
		double maxN = 0;
		while (true) {
			bool isEnd = false;
			if (lastX > endX) {
				lastX = endX;
				isEnd = true;
			}

			double yH = data.H0 - data.S * lastX * lastX;
			double yN = data.N0 + data.C * lastX;
			double yM = getCPD(yH, lastX, yN);
			if (maxM < yM)
				maxM = yM;
			maxN = yN;

			drawFunc(lastX, yH, yN, yM);

			lastX += offset;

			if (isEnd)
				break;
		}

		if (isInterval) {
			auto q1 = getInterval(endX);
			intervals.QMax = q1[1];
			intervals.QInterval = q1[0];
			
			q1 = getInterval(data.H0);
			intervals.HMax = q1[1];
			intervals.HInterval = q1[0];

			q1 = getInterval(maxN);
			intervals.NMax = q1[1];
			intervals.NInterval = q1[0];

			q1 = getInterval(maxM);
			intervals.MMax = q1[1];
			intervals.MInterval = q1[0];
		}

		return intervals;
	}

	ChartData calculateChartData(double k, std::vector<angarawindows::WaterPumpWindow::ChartPoint> & points, std::function<void(double,double,double,int)> pointItCallback) {
		ChartData data;

		int PointsQH = 0;
		int PointsQN = 0;
		double sumH = 0;
		double sumQ = 0;
		double sumHQ2 = 0;
		double sumQ2 = 0;
		double sumQ4 = 0;
		double sumN = 0;
		double sumNQ = 0;
		for (int i = 0; i < points.size(); i++) {
			auto q = points.at(i);

			//System::Windows::Forms::MessageBox::Show(q.Q + "x");
			//System::Windows::Forms::MessageBox::Show(q.H + "y");

			double Q = k * q.Q;
			double H = k * k * q.H;
			double N = k * k * k * q.N;

			if (pointItCallback != nullptr) {
				pointItCallback(Q, H, N, i);
			}

			if (Q > 0 || H > 0) {
				PointsQH++;
				sumH += H;
				sumQ += Q;
				sumHQ2 += H * Q * Q;
				sumQ2 += Q * Q;
				sumQ4 += Q * Q * Q * Q;
			}

			if (Q > 0 || N > 0) {
				PointsQN++;
				sumN += N;
				sumNQ += N * Q;
			}
		}

		switch (PointsQH) {
		case 0:
			break;
		case 1:
			data.H0 = sumH;
			break;
		default:
			if (PointsQH * sumQ4 - sumQ2 * sumQ2 > 0) {
				data.S = -(sumHQ2 - sumH * sumQ2 / PointsQH) / (sumQ4 - sumQ2 * sumQ2 / PointsQH);

				data.H0 = ((sumH + sumQ2 * data.S) / PointsQH);
			}
			break;
		}
		switch (PointsQN) {
		case 0:
			break;
		case 1:
			data.N0 = sumN;
			break;
		default:
			if (PointsQN * sumQ2 - sumQ * sumQ) {
				data.C = ((sumNQ - sumQ * sumN / PointsQN) / (sumQ2 - sumQ * sumQ / PointsQN));

				data.N0 = ((sumN - sumQ * data.C) / PointsQN);
			}
			break;
		}

	//	System::Windows::Forms::MessageBox::Show(data.S + " d");

		return data;
	}

	void sortPoint(std::vector<angarawindows::WaterPumpWindow::ChartPoint> &q) {
		std::sort(q.begin(), q.end(), [](const angarawindows::WaterPumpWindow::ChartPoint p1, angarawindows::WaterPumpWindow::ChartPoint p2) {
			return p1.Q < p2.Q;
			});
	}

	void checkPoint(System::Windows::Forms::DataVisualization::Charting::Chart^ chart, System::Windows::Forms::DataVisualization::Charting::DataPoint^ point, int i) {
		if (chart->Series[3]->Points->Count >= i)
			chart->Series[3]->Points->Add(point);
		else if ((chart->Series[3]->Points[i]->XValue != point->XValue || chart->Series[3]->Points[i]->YValues[0] != point->YValues[0]))
			chart->Series[3]->Points[i] = point;
	}

	std::string SysToStd(System::String^ original) {
		return msclr::interop::marshal_as<std::string>(original);
	}
	System::String^ StdToSys(std::string original) {
		return gcnew System::String(original.c_str());
	}

	int _IntInputHandler(System::Windows::Forms::TextBox^ box) {
		int ans = 0;
		bool isMinus = false;
		bool isNot = true;

		for (int i = 0; i < box->Text->Length; i++) {
			auto ch = box->Text[i];

			if (ans == 0 && ch == '-') {
				isMinus = true;
			}
			else if ('0' <= ch && ch <= '9') {
				isNot = false;
				ans = ans * 10 + (ch - '0');
			}
		}

		if (isNot && box->Text->Length != 0)
			throw std::invalid_argument("");

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

	int getInt(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, int def) {
		int id = reader->GetOrdinal(name);

		if (reader->IsDBNull(id))
			return def;

		return reader->GetInt32(id);
	}

	int getInt(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name) {
		return getInt(reader, name, 0);
	}


	short getShort(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, short def) {
		int id = reader->GetOrdinal(name);

		if (reader->IsDBNull(id))
			return def;

		return reader->GetInt16(id);
	}

	short getShort(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name) {
		return getShort(reader, name, 0);
	}


	long long getLongLong(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, long long def) {
		int id = reader->GetOrdinal(name);

		if (reader->IsDBNull(id))
			return def;

		return reader->GetInt64(id);
	}

	long long getLongLong(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name) {
		return getLongLong(reader, name, 0);
	}


	double getDouble(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, double def) {
		int id = reader->GetOrdinal(name);

		if (reader->IsDBNull(id))
			return def;

		return reader->GetDouble(id);
	}

	double getDouble(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name) {
		return getDouble(reader, name, 0);
	}


	float getFloat(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, float def) {
		int id = reader->GetOrdinal(name);

		if (reader->IsDBNull(id))
			return def;

		return reader->GetFloat(id);
	}

	float getFloat(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name) {
		return getFloat(reader, name, 0);
	}

	std::string getString(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, const char* def) {
		int id = reader->GetOrdinal(name);


		if (reader->IsDBNull(id))
			return std::string(def);

		return SysToStd(reader->GetString(id));
	}

	std::string getString(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name) {
		return getString(reader, name, 0);
	}
}