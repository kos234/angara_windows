#pragma once

#include <vector>
#include <string>
#include <functional>
#include "angara_windows.h"
#include <msclr/gcroot.h>

namespace angarawindows {
	double getCPD(double H, double Q, double N);

	double* getInterval(double x);

	double round3(double x);

	struct ChartData
	{
		double H0 = 0;
		double S = 0;
		double N0 = 0;
		double C = 0;
	};

	struct ChartIntevals
	{
		double HInterval = 0;
		double HMax = 0;
		double NInterval = 0;
		double NMax = 0;
		double QInterval = 0;
		double QMax = 0;
		double MInterval = 0;
		double MMax = 0;
	};

	ChartIntevals drawPumpCharts(ChartData& data, 
		std::function<void(double, double, double, double)> drawFunc, 
		bool isInterval, 
		double maxX);

	ChartData calculateChartData(double k, 
		std::vector<angarawindows::WaterPumpWindow::ChartPoint>& points, 
		std::function<void(double, double, double, int)> pointItCallback);

	void sortPoint(std::vector<angarawindows::WaterPumpWindow::ChartPoint>& q);

	void checkPoint(System::Windows::Forms::DataVisualization::Charting::Chart^ chart,
		System::Windows::Forms::DataVisualization::Charting::DataPoint^ point,
		int i);

	std::string SysToStd(System::String^ original);

	System::String^ StdToSys(std::string original);

	int _IntInputHandler(System::Windows::Forms::TextBox^ box);

	double _DoubleInputHandler(System::Windows::Forms::TextBox^ box);

	void SuperTextSetter(System::Windows::Forms::TextBox^ box, System::String^ text);

	int GetIntLength(int q);

	int getInt(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, int def);

	int getInt(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);


	short getShort(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, short def);

	short getShort(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);


	long long getLongLong(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, long long def);

	long long getLongLong(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);


	double getDouble(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, double def);

	double getDouble(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);


	float getFloat(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, float def);

	float getFloat(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);

	std::string getString(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, const char* def);

	std::string getString(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);
}