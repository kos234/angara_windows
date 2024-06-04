#pragma once
#include "inputs.h"
#include <stdexcept>
#include <cmath>
#include <msclr\marshal_cppstd.h>
#include <iostream>

namespace angarawindows {

	std::wstring SysToStd(System::String^ original) {
		return msclr::interop::marshal_as<std::wstring>(original);
	}

	std::string SysToStdString(System::String^ original) {
		return msclr::interop::marshal_as<std::string>(original);
	}

	System::String^ StdToSys(std::wstring original) {
		std::wcout << "original =" << original << "\n";
		System::String^ v = gcnew System::String(original.c_str());
		std::wcout << "fuck = " << original << "\n";

		return v;
	}

	void SuperTextSetter(System::Windows::Forms::TextBox^ box, System::String^ text) {
		int last = System::Math::Max(box->SelectionStart - box->Text->Length, 0);
		box->Text = text;
		box->SelectionStart = last + text->Length;
		box->SelectionLength = 0;
	}

}