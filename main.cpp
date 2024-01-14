#pragma once
#include <functional>
#include "WaterPump.h"
#include <msclr/gcroot.h>
#include "utils.h"


namespace angarawindows {
	const char* urlConnect;

	void setDBConnect(const char* connect) {
		urlConnect = connect;
		Application::SetCompatibleTextRenderingDefault(false);
		Application::EnableVisualStyles();
	}

	const char* getUrlConnect() {
		return urlConnect;
	}

	template<typename VT> bool _isDefaultValue(VT value) {
		return isDefaultValue(value);
	}

	/*void abstactQuery(String^ sql, std::function<void(msclr::gcroot<OleDbDataReader^>)> func) {
		OleDbConnection^ connection = gcnew OleDbConnection(gcnew String(urlConnect));
		connection->Open();
		OleDbCommand^ command = gcnew OleDbCommand(sql, connection);
		OleDbDataReader^ reader = command->ExecuteReader();
		func(reader);
		reader->Close();
		connection->Close();
	};*/

	/*void abstactInsert() {
		OleDbConnection^ connection = gcnew OleDbConnection(gcnew String(urlConnect));
		connection->Open();
		OleDbCommand^ command = gcnew OleDbCommand(sql, connection);
		command->Parameters->Insert
	}*/
}

int maind() {
	angarawindows::setDBConnect("provider=Microsoft.ACE.OLEDB.12.0;Data Source=C:\\Users\\kosty\\Documents\\TP_EqNS_ML.MDB");

	angarawindows::WaterPump windPump;
	windPump.show();
	return 0;
}