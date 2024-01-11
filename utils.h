#pragma once

#include <vector>
#include <string>
#include <functional>
#include <iomanip>
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

	DBWrapper<int> _IntInputHandler(System::Windows::Forms::TextBox^ box);

	DBWrapper<double> _DoubleInputHandler(System::Windows::Forms::TextBox^ box);

	std::string toSaintific(double value);

	void SuperTextSetter(System::Windows::Forms::TextBox^ box, System::String^ text);

	template<typename OBS> void SuperTextSetter(System::Windows::Forms::TextBox^ box, angarawindows::ObserverValue<OBS>& value) {
		SuperTextSetter(box, value.getValue(), value.isEmpty());
	}
	
	template<typename OBS> void SuperTextSetter(System::Windows::Forms::TextBox^ box, OBS value, bool isEmpty) {
		if (isEmpty) {
			SuperTextSetter(box, "");
			return;
		}

		if constexpr (std::is_same<OBS, double>::value || std::is_same<OBS, float>::value) {
			if (0.002 > value) {
				SuperTextSetter(box, StdToSys(toSaintific(value)));
				return;
			}else
				value = round3(value);
		}

		SuperTextSetter(box, value + "");
	}

	int GetIntLength(int q);

	DBWrapper<int> getInt(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, int def);

	DBWrapper<int> getInt(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);


	DBWrapper<short> getShort(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, short def);

	DBWrapper<short> getShort(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);


	DBWrapper<long long> getLongLong(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, long long def);

	DBWrapper<long long> getLongLong(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);


	DBWrapper<double> getDouble(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, double def);

	DBWrapper<double> getDouble(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);


	DBWrapper<float> getFloat(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, float def);

	DBWrapper<float> getFloat(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);

	DBWrapper<std::string> getString(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, std::string def);

	DBWrapper<std::string> getString(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);

	void setupChart(System::Windows::Forms::DataVisualization::Charting::Chart^ chart, System::String^ titleY, System::Drawing::Color mainGraf, System::Drawing::Color nominalGraf, System::Drawing::Color points);

	void normalyzeTitleChart(System::Windows::Forms::DataVisualization::Charting::Chart^ chart);

	template<typename T>
	struct has_number {
		static const bool value = std::is_arithmetic<T>::value;
	};
	//---------------------------------------
	template<typename T>
	struct has_string {
		static const bool value = false;
	};
	template<>
	struct has_string<std::string> {
		static const bool value = true;
	};
	template<>
	struct has_string<const char*> {
		static const bool value = true;
	};
	template<>
	struct has_string<System::String^> {
		static const bool value = true;
	};
	//---------------------------------------
	template<typename T>
	struct has_container {
		static const bool value = false;
	};
	template<typename T>
	struct has_container<std::vector<T>> {
		static const bool value = true;
	};
	//---------------------------------------
	template < typename T>
	bool isDefaultValue(T value, typename std::enable_if<has_number<T>::value, T>::type* = 0) {
		return value == 0;
	}

	template < typename T>
	bool isDefaultValue(T value, typename std::enable_if<has_string<T>::value, T>::type* = 0) {
		if constexpr (std::is_same<T, std::string>::value) {
			return value.empty();
		}
		else if constexpr (std::is_same<T, const char*>::value) {
			while (*value != '\0') {
				if (!isspace((unsigned char)*value))
					return false;
				value++;
			}
			return true;
		}
		else if constexpr (std::is_same<T, System::String^>::value) {
			return value->Empty;
		}

		return false;
	}

	template < typename T>
	bool isDefaultValue(T value, typename std::enable_if<has_container<T>::value, T>::type* = 0) {
		return value.empty();
	}

	template < typename T>
	bool isDefaultValue(T value, typename std::enable_if<!has_string<T>::value && !has_number<T>::value && !has_container<T>::value, T>::type* = 0) {
		return false;
	}
}