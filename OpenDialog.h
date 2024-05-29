#pragma once

namespace angarawindows {
	using namespace System;

	ref class OpenDialog {
	private:
		int idLink = -1;
		void readDB(System::Data::OleDb::OleDbDataReader^ reader);
	public:
		OpenDialog(int idLink);
	};
}