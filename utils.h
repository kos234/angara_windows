#pragma once

#include <string>
#include <functional>
#include "RealChartPoint.h"
#include "ObserverValue.h"
#include "DBWrapper.h"
#include "main.h"
#include <msclr/gcroot.h>
#include <iostream>


namespace angarawindows {
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Data::OleDb;

	delegate void CalculateDelegat(double, double, double, int);
	delegate void DrawDelegat(double, double, double, double);

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
		DrawDelegat^ drawFunc,
		bool isInterval,
		double maxX,
		System::Collections::Generic::List<RealChartPoint^>^ points);

	ChartIntevals drawPumpCharts(ChartData& data,
		DrawDelegat^ drawFunc,
		bool isInterval,
		double maxX);

	ChartData calculateChartData(double k, System::Collections::Generic::List<RealChartPoint^>^ points, CalculateDelegat^ pointItCallback);

	void sortPoint(System::Collections::Generic::List<RealChartPoint^>^ points);

	void checkPoint(System::Windows::Forms::DataVisualization::Charting::Chart^ chart,
		System::Windows::Forms::DataVisualization::Charting::DataPoint^ point,
		int i);

	std::string toSaintific(double value);

	int GetIntLength(int q);

	DBWrapper<int>^ getInt(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, int def);

	DBWrapper<int>^ getInt(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);

	DBWrapper<short>^ getShort(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, short def);

	DBWrapper<short>^ getShort(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);


	DBWrapper<long long>^ getLongLong(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, long long def);

	DBWrapper<long long>^ getLongLong(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);


	DBWrapper<double>^ getDouble(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, double def);

	DBWrapper<double>^ getDouble(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);


	DBWrapper<float>^ getFloat(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, float def);

	DBWrapper<float>^ getFloat(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);

	DBWrapper<String^>^ getString(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name, std::string def);

	DBWrapper<String^>^ getString(msclr::gcroot <System::Data::OleDb::OleDbDataReader^> reader, System::String^ name);

	void setupChart(System::Windows::Forms::DataVisualization::Charting::Chart^ chart, System::String^ titleY, System::Drawing::Color mainGraf, System::Drawing::Color nominalGraf, System::Drawing::Color points);

	void normalyzeTitleChart(System::Windows::Forms::DataVisualization::Charting::Chart^ chart);

	template<typename T>
	void log(T value) {
		std::cout << value << "\n";
	}

	ref class GetNextIdLink {
	protected:
		int idLink = -1;
		void readNextIdLink(OleDbDataReader^ reader);
	public:
		int get();
	};


	public ref class QueryBuilder {
	protected:
		OleDbCommand^ command;
	public:
		delegate void Read(OleDbDataReader^);

		QueryBuilder() {

		}
		QueryBuilder(String^ sql) {
			setSql(sql);
		}
		QueryBuilder^ setSql(String^ sql) {
			command = gcnew OleDbCommand(sql);
			return this;
		}
		template<typename T>
		QueryBuilder^ add(T value) {
			throw std::runtime_error("a function not defined for" + typeid(T).name());
			return this;
		}

		template<>
		QueryBuilder^ add<long long>(long long value) {
			OleDbParameter^ prms = gcnew OleDbParameter("?", OleDbType::BigInt);
			prms->Value = value;
			command->Parameters->Add(prms);
			return this;
		}
		template<>
		QueryBuilder^ add<int>(int value) {
			OleDbParameter^ prms = gcnew OleDbParameter("?", OleDbType::Integer);
			prms->Value = value;
			command->Parameters->Add(prms);
			return this;
		}
		template<>
		QueryBuilder^ add<float>(float value) {
			OleDbParameter^ prms = gcnew OleDbParameter("?", OleDbType::Single);
			prms->Value = value;
			command->Parameters->Add(prms);
			return this;
		}
		template<>
		QueryBuilder^ add<double>(double value) {
			OleDbParameter^ prms = gcnew OleDbParameter("?", OleDbType::Double);
			prms->Value = value;
			command->Parameters->Add(prms);
			return this;
		}
		template<>
		QueryBuilder^ add<std::string>(std::string value) {
			OleDbParameter^ prms = gcnew OleDbParameter("?", OleDbType::VarChar);
			prms->Value = gcnew String(value.c_str());
			command->Parameters->Add(prms);
			return this;
		}
		template<>
		QueryBuilder^ add<String^>(String^ value) {
			OleDbParameter^ prms = gcnew OleDbParameter("?", OleDbType::VarChar);
			prms->Value = value;
			command->Parameters->Add(prms);
			return this;
		}

		QueryBuilder^ addEmpty() {
			command->Parameters->AddWithValue("?", DBNull::Value);
			return this;
		}

		template<typename T>
		QueryBuilder^ add(ObserverValue<T>^ value) {
			if (value->isEmpty())
				return addEmpty();
			return add(value->getValue());
		}

		int executeUpdate() {
			OleDbConnection^ connection = gcnew OleDbConnection(gcnew String(getUrlConnect()));
			connection->Open();
			command->Connection = connection;

			int ans = command->ExecuteNonQuery();
			connection->Close();
			return ans;
		}

		void executeQuery(Read^ func) {
			OleDbConnection^ connection = gcnew OleDbConnection(gcnew String(getUrlConnect()));
			connection->Open();
			command->Connection = connection;

			OleDbDataReader^ reader = command->ExecuteReader();
			func(reader);
			reader->Close();
			connection->Close();
		}
	};
}