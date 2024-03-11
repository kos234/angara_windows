#pragma once

namespace angarawindows {
	using namespace System;
	using namespace System::Collections::Generic;
	ref class AbstractDialog {
	public:
		Dictionary<String^, int>^ errors = gcnew Dictionary<String^, int>;
		bool isSaveValidation = false;
		virtual void save() = 0;
		virtual void close() = 0;
	};
}