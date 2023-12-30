#pragma once
#include <functional>
#include "WaterPump.h"
#include <msclr/gcroot.h>

namespace angarawindows {
	const char* urlConnect;

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Data::OleDb;

	void setDBConnect(const char* connect) {
		urlConnect = connect;
		Application::SetCompatibleTextRenderingDefault(false);
		Application::EnableVisualStyles();
	}

	void abstactQuery(String^ sql, std::function<void(msclr::gcroot<OleDbDataReader^>)> func) {
		OleDbConnection^ connection = gcnew OleDbConnection(gcnew String(urlConnect));
		connection->Open();
		OleDbCommand^ command = gcnew OleDbCommand(sql, connection);
		OleDbDataReader^ reader = command->ExecuteReader();
		func(reader);
		reader->Close();
		connection->Close();
	};

	[STAThreadAttribute]
	void abstactShow(System::Windows::Forms::Form^ form) {
		Application::Run(form);
	}
}

int maind() {
	angarawindows::setDBConnect("provider=Microsoft.ACE.OLEDB.12.0;Data Source=C:\\Users\\User\\Documents\\TP_EqNS_ML.MDB");

	angarawindows::WaterPumpWindow windPump;
	windPump.show();
	return 0;
}