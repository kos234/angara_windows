#pragma once

namespace angarawindows {
	using namespace System;
	using namespace System::Threading;
	using namespace System::Data::OleDb;

	ref class OpenDialog {
	private:
		int idLink = -1;
		Thread^ thread;

		void open();
		void readDB(OleDbDataReader^ reader);
	public:
		OpenDialog(int idLink);
	};
}