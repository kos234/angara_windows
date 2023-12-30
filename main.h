#pragma once
#include <string>
#include <vector>
#include <functional>
#include <msclr/gcroot.h>
#include "angara_windows.h"

namespace angarawindows {

	void setDBConnect(const char*);
	void abstactQuery(System::String^, std::function<void(msclr::gcroot<System::Data::OleDb::OleDbDataReader^>)>);
	void abstactShow(System::Windows::Forms::Form^);

	template <typename OBS>class ObserverValue {
		OBS value;
		bool userNotEdit = true;

		std::vector<std::function<void(OBS&)>> eventHandlers;

	public:
		bool isUpdate = false;
		ObserverValue() {};
		ObserverValue(const OBS& value) {
			this->value = value;
		};
		void setValue(const OBS& value);
		void addEventListener(std::function<void(OBS&)>);
		void removeEventListener(std::function<void(OBS&)>);
		void throwEvent();
		OBS& getValue();

		bool isUserNotEdit();
		void userEdit();
	};
}