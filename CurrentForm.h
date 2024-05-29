#pragma once
#include <msclr/gcroot.h>
#include "AbstractDialog.h"

namespace angarawindows {
	AbstractDialogData* getLastDialogData();


	ref class CurrentForm {
	private:
		static AbstractDialog^ currentDialog = nullptr;
		public:
			static bool isOpenDialog();
			static void rememberLinkToForm(AbstractDialog^);
			static void forgetLinkToForm(AbstractDialogData*);
	};
}
