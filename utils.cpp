#pragma once

#include "utils.h"
#include "angara_windows.h"
#include <msclr\marshal_cppstd.h>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <msclr/gcroot.h>
#include <iostream>

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

			//if (pointItCallback != nullptr) {
				pointItCallback(Q, H, N, i);
			//}

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

	std::string toSaintific(double value) {
		int m = 0;
		int m_size = 1;
		int e = 0;
		int first = 0;
		bool isAllZero = true;
		for (; ;) {
			value *= 10;

			if (!value)
				break;

			if (!first)
				e++;

			int num = value;
			value -= num;

			if (!first && num == 0)
				continue;

			if (!first)
				first = num;
			else {
				isAllZero &= num == 0;
				m = num * m_size + m;
				m_size *= 10;
			}

			if (m_size == 1000)
				break;
		}

		if (!first)
			return std::to_string(0);

		std::string mantis = std::to_string(m);
		mantis.reserve();

		return std::to_string(first) + (isAllZero ? "" : ("." + mantis)) + "e-" + std::to_string(e);
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

	DBWrapper<int> _IntInputHandler(System::Windows::Forms::TextBox^ box) {
		DBWrapper<int> wrapper;
		wrapper.value = 0;
		bool isMinus = false;
		wrapper.empty = true;

		for (int i = 0; i < box->Text->Length; i++) {
			auto ch = box->Text[i];

			if (wrapper.value == 0 && ch == '-') {
				isMinus = true;
			}
			else if ('0' <= ch && ch <= '9') {
				wrapper.empty = false;
				wrapper.value = wrapper.value * 10 + (ch - '0');
			}
			else {
				goto if_there_is_an_extraneous_character;
			}
		}

		if (isMinus && wrapper.empty) {
			throw std::invalid_argument("await");
		}

		if_there_is_an_extraneous_character: {};
		if (isMinus)
			wrapper.value *= -1;

		return wrapper;
	}

	DBWrapper<double> _DoubleInputHandler(System::Windows::Forms::TextBox^ box) {
		DBWrapper<double> wrapper;
		wrapper.value = 0;
		double drob = 0;
		double drobSize = 1;
		bool isMinus = false;
		bool isDrob = false;

		for (int i = 0; i < box->Text->Length; i++) {
			auto ch = box->Text[i];

			if (wrapper.value == 0 && ch == '-') {
				isMinus = true;
			}
			else if ('0' <= ch && ch <= '9') {
				if (isDrob) {
					drobSize *= 10;
					drob = drob * 10 + (ch - '0');
				}
				else {
					wrapper.value = wrapper.value * 10 + (ch - '0');
				}
				wrapper.empty = false;
			}
			else if ((ch == '.' || ch == ',') && !isDrob) {
				isDrob = true;
			}
			else {
				goto if_there_is_an_extraneous_character;
			}
		}

		if ((isMinus && wrapper.empty) || (isDrob && drobSize == 1)) {
			throw std::invalid_argument("await");
		}


	if_there_is_an_extraneous_character: {};
		if (isMinus)
			wrapper.value *= -1;
		if(isDrob)
		wrapper.value += drob / drobSize;

		return wrapper;
	}

	void SuperTextSetter(System::Windows::Forms::TextBox^ box, System::String^ text) {
		int last = System::Math::Max(box->SelectionStart - box->Text->Length, 0);
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

	DBWrapper<int> getInt(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, int def) {
		DBWrapper<int> wrapper;
		wrapper.value = def;
		int id = reader->GetOrdinal(name);

		if (reader->IsDBNull(id))
			return wrapper;

		wrapper.value = reader->GetInt32(id);
		wrapper.empty = wrapper.value == 0;

		return wrapper;
	}
	DBWrapper<int> getInt(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name) {
		return getInt(reader, name, 0);
	}


	DBWrapper<short> getShort(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, short def) {
		DBWrapper<short> wrapper;
		wrapper.value = def; 
		int id = reader->GetOrdinal(name);

		if (reader->IsDBNull(id))
			return wrapper;

		wrapper.value = reader->GetInt16(id);
		wrapper.empty = wrapper.value == 0;

		return wrapper;
	}

	DBWrapper<short> getShort(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name) {
		return getShort(reader, name, 0);
	}


	DBWrapper<long long> getLongLong(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, long long def) {
		DBWrapper<long long> wrapper;
		wrapper.value = def;
		int id = reader->GetOrdinal(name);

		if (reader->IsDBNull(id))
			return wrapper;

		wrapper.value = reader->GetInt64(id);
		wrapper.empty = wrapper.value == 0;

		return wrapper;
	}

	DBWrapper<long long> getLongLong(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name) {
		return getLongLong(reader, name, 0);
	}


	DBWrapper<double> getDouble(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, double def) {
		DBWrapper<double> wrapper;
		wrapper.value = def;
		int id = reader->GetOrdinal(name);

		if (reader->IsDBNull(id))
			return wrapper;

		wrapper.value = reader->GetDouble(id); 
		wrapper.empty = wrapper.value == 0;

		return wrapper;
	}

	DBWrapper<double> getDouble(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name) {
		return getDouble(reader, name, 0);
	}


	DBWrapper<float> getFloat(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, float def) {
		DBWrapper<float> wrapper;
		wrapper.value = def;
		int id = reader->GetOrdinal(name);

		if (reader->IsDBNull(id))
			return wrapper;

		wrapper.value = reader->GetFloat(id);
			wrapper.empty = wrapper.value == 0;

		return wrapper;
	}

	DBWrapper<float> getFloat(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name) {
		return getFloat(reader, name, 0);
	}

	DBWrapper<std::string> getString(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, std::string def) {
		DBWrapper<std::string> wrapper;
		wrapper.value = def;
		int id = reader->GetOrdinal(name);

		if (reader->IsDBNull(id))
			return wrapper;

		wrapper.value = SysToStd(reader->GetString(id));
		wrapper.empty = wrapper.value.empty();

		return wrapper;
	}

	DBWrapper<std::string> getString(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name) {
		return getString(reader, name, "");
	}


	//-------------------------------------------------------------------------------------------------------------------------

	int getNumberLenght(int number) {
		int ans = 0;
		for (; number != 0; ans++) {
			number /= 10;
		}
		return ans;
	}


	void setupChart(System::Windows::Forms::DataVisualization::Charting::Chart^ chart, System::String^ titleY, System::Drawing::Color mainGraf, System::Drawing::Color nominalGraf, System::Drawing::Color points) {
		//Ось Х
		chart->ChartAreas[0]->AxisX->Interval = 2;
		chart->ChartAreas[0]->AxisX->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
		chart->ChartAreas[0]->AxisX->LineColor = System::Drawing::Color::Gray;
		chart->ChartAreas[0]->AxisX->MajorGrid->LineColor = System::Drawing::Color::Gray;
		chart->ChartAreas[0]->AxisX->Maximum = 10;
		chart->ChartAreas[0]->AxisX->Minimum = 0;
		chart->ChartAreas[0]->AxisX2->LineColor = System::Drawing::Color::Gray;

		//Ось Y
		chart->ChartAreas[0]->AxisY->Interval = 2;
		chart->ChartAreas[0]->AxisY->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
		chart->ChartAreas[0]->AxisY->LineColor = System::Drawing::Color::Gray;
		chart->ChartAreas[0]->AxisY->MajorGrid->LineColor = System::Drawing::Color::Gray;
		chart->ChartAreas[0]->AxisY->Maximum = 10;
		chart->ChartAreas[0]->AxisY->Minimum = 0;
		chart->ChartAreas[0]->AxisY2->LineColor = System::Drawing::Color::Gray;

		//Область графика
		chart->ChartAreas[0]->BorderColor = System::Drawing::Color::Gray;
		chart->ChartAreas[0]->Position->Auto = false;
		chart->ChartAreas[0]->Position->Height = 100;
		chart->ChartAreas[0]->Position->Width = 100;
		chart->ChartAreas[0]->Position->X = 0;
		chart->ChartAreas[0]->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
			static_cast<System::Int32>(static_cast<System::Byte>(128)));

		//Основной график
		System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		System::Windows::Forms::DataVisualization::Charting::DataPoint^ dataPoint8 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(9, 9));
		series1->BorderWidth = 2;
		series1->ChartArea = chart->ChartAreas[0]->Name;
		series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
		series1->Color = mainGraf;
		series1->Name = L"Series1";
		series1->Points->Add(dataPoint8);
		chart->Series->Add(series1);

		//Номинальный график
		System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		series2->BorderWidth = 3;
		series2->ChartArea = L"ChartArea1";
		series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
		series2->Color = nominalGraf;
		series2->Name = L"Series2";
		chart->Series->Add(series2);

		//Обводка вокруг точки
		System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		series3->ChartArea = chart->ChartAreas[0]->Name;
		series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
		series3->Color = System::Drawing::Color::Black;
		series3->MarkerSize = 18;
		series3->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
		series3->Name = L"Series3";
		chart->Series->Add(series3);

		//Номинальная точка
		System::Windows::Forms::DataVisualization::Charting::Series^ series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		series4->ChartArea = chart->ChartAreas[0]->Name;
		series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
		series4->Color = points;
		series4->MarkerSize = 13;
		series4->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
		series4->Name = L"Series4";
		series4->ShadowColor = System::Drawing::Color::Empty;
		chart->Series->Add(series4);

		//Линияя выделения
		System::Windows::Forms::DataVisualization::Charting::Series^ series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		series5->BorderDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
		series5->BorderWidth = 2;
		series5->ChartArea = chart->ChartAreas[0]->Name;
		series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
		series5->Color = System::Drawing::Color::Red;
		series5->Name = L"Series5";
		chart->Series->Add(series5);

		chart->Text = titleY;

		normalyzeTitleChart(chart);
	}

	void normalyzeTitleChart(System::Windows::Forms::DataVisualization::Charting::Chart^ chart) {
		double max = chart->ChartAreas[0]->AxisY->Maximum;
		if (System::Double::IsNaN(max) || max == 0)
			return;

		//std::cout << SysToStd(chart->Name) << " ";
		////std::cout << "pow = " << (std::pow(10, chart->Text->Length)) << "; max = " << max << " ";

		int lenMax = getNumberLenght(max);

		if (chart->Text->Length <= lenMax) {
			chart->ChartAreas[0]->Position->X = 0;
			chart->ChartAreas[0]->Position->Width = 100;
			//std::cout << "return " << max << "\n";
			return;
		}

		//std::cout << "set " << (2 * (chart->Text->Length - lenMax - 1)) << "\n";
		chart->ChartAreas[0]->Position->X = 2 * (chart->Text->Length - lenMax - 1);
		chart->ChartAreas[0]->Position->Width = 100 - chart->ChartAreas[0]->Position->X;
	}
}