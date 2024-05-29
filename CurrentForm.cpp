#pragma once
#include "CurrentForm.h"
#include "WaterPumpData.h"

namespace angarawindows {
	AbstractDialogData* lastDialogData = nullptr;

	AbstractDialogData* getLastDialogData() {
		return lastDialogData;
	}

	void CurrentForm::rememberLinkToForm(AbstractDialog^ dialog) {
		if (isOpenDialog())
			return;

		CurrentForm::currentDialog = dialog;
	}

	void CurrentForm::forgetLinkToForm(AbstractDialogData* data) {
		if (!isOpenDialog())
			return;

		CurrentForm::currentDialog = nullptr;
		delete lastDialogData;
		lastDialogData = data;

	}

	bool CurrentForm::isOpenDialog() {
		return CurrentForm::currentDialog != nullptr;
	}
}
