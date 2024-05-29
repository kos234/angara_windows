#pragma once
#include "OpenDialog.h"
#include "utils.h"
#include "WaterPump.h"
#include "CurrentForm.h"

namespace angarawindows {
	OpenDialog::OpenDialog(int idLink) {
		this->idLink = idLink;
		QueryBuilder("SELECT IdElement FROM Связи WHERE IdLink = ?").add(this->idLink)
			->executeQuery(gcnew QueryBuilder::Read(this, &OpenDialog::readDB));
	}


	void OpenDialog::readDB(OleDbDataReader^ reader) {
		if (CurrentForm::isOpenDialog())
			return;

		reader->Read();

		int windowType = getDBData<int>(reader, "IdElement")->value;
		AbstractDialog^ dialog = nullptr;

		switch (windowType)
		{
		case 17:
			dialog = gcnew WaterPump(this->idLink);
			break;
		default:
			return;
			break;
		}

	}
}