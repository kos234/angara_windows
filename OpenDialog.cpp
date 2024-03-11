#pragma once
#include <iostream>
#include "OpenDialog.h"
#include "InputOutputListener.h"
#include "utils.h"
#include "WaterPump.h"
#include "Properties.h"

namespace angarawindows {
	OpenDialog::OpenDialog(int idLink) {
		this->idLink = idLink;
		this->thread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &OpenDialog::open));
		this->thread->Start();
	}

	void OpenDialog::open() {
		QueryBuilder("SELECT IdElement FROM Связи WHERE IdLink = ?").add(this->idLink)
			->executeQuery(gcnew QueryBuilder::Read(this, &OpenDialog::readDB));
	}

	template<typename T>
	void openDialog(int idLink) {
		T^ dialog = gcnew T(idLink);
	}

	void OpenDialog::readDB(OleDbDataReader^ reader) {
		if (Properties::currentDialog != nullptr)
			return;

		reader->Read();

		int windowType = getDBData<int>(reader, "IdElement")->value;

		switch (windowType)
		{
			case 17:
				openDialog<WaterPump>(this->idLink);
				break;
			default:
				InputOutputListener::write("bad IdElement");
				return;
				break;
		}
	}
}