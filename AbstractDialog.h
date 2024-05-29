#pragma once
#include "AbstractDialogData.h"

namespace angarawindows {
	ref class AbstractDialog {
	public:
		System::Collections::Generic::Dictionary<System::String^, int>^ errors = gcnew System::Collections::Generic::Dictionary<System::String^, int>();
		bool isSaveValidation = false;
		int idLink;
		virtual void save() = 0;
		virtual void close() = 0;
		[System::STAThreadAttribute]
		virtual void init() = 0;
		virtual AbstractDialogData* generateFormData() = 0;
	};
}