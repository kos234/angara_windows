#pragma once
#include "inputs.h"
#include <stdexcept>
#include <cmath>
#include <msclr\marshal_cppstd.h>


namespace angarawindows {
	std::string SysToStd(System::String^ original) {
		return msclr::interop::marshal_as<std::string>(original);
	}

	void SuperTextSetter(System::Windows::Forms::TextBox^ box, System::String^ text) {
		int last = System::Math::Max(box->SelectionStart - box->Text->Length, 0);
		box->Text = text;
		box->SelectionStart = last + text->Length;
		box->SelectionLength = 0;
	}

}