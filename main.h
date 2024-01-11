#pragma once
#include <string>
#include <vector>
#include <functional>
#include <msclr/gcroot.h>
#include "utils.h"

namespace angarawindows {
	void setDBConnect(const char*);
	void abstactQuery(System::String^, std::function<void(msclr::gcroot<System::Data::OleDb::OleDbDataReader^>)>);
	void abstactShow(System::Windows::Forms::Form^);

	template<typename VT> struct DBWrapper {
		VT value;
		bool empty = true;
	};

	template <typename OBS>  class ObserverValue {
		OBS value;
		bool userNotEdit = true;
		bool empty = false;
		std::vector<std::function<void(ObserverValue<OBS>&)>> eventHandlers;

	public:
		bool isUpdate = false;
		ObserverValue() {};
		ObserverValue(const OBS& value) {
			this->setValue(value);
		};
		void setValue(const OBS& value) {
			this->setValue(value, false);
		}
		void setValue(DBWrapper<OBS> value) {
			this->setValue(value.value, value.empty);
		}
		DBWrapper<OBS> getWrapper(){
			DBWrapper<OBS> wrapper;
			wrapper.empty = empty;
			wrapper.value = value;

			return wrapper;
		}
		void setValue(const OBS& value, bool isEmpty) {
			this->setValue(value, isEmpty, false);
		}
		void setValue(const OBS& value, bool isEmpty, bool isUser) {
			if (this->isUpdate)
				return;
			this->isUpdate = true;
			this->value = value;
			if (!isUser) {
				isEmpty = isDefaultValue(value);
			}
			this->empty = isEmpty;

			this->userNotEdit |= isUser;

			for (auto fuctionLink : this->eventHandlers) {
				fuctionLink(*this);
			}

			this->isUpdate = false;
		}

		void addEventListener(std::function<void(ObserverValue<OBS>&)> func) {
			this->eventHandlers.push_back(func);
		}
		void removeEventListener(std::function<void(ObserverValue<OBS>&)>) {
			this->eventHandlers.erase(std::remove(this->eventHandlers.begin(), this->eventHandlers.end(), func), this->eventHandlers.end());
		}
		void throwEvent() {
			this->setValue(this->getValue());
		}
		OBS& getValue() {
			return this->value;
		}

		bool isUserNotEdit() {
			return this->userNotEdit;
		}
		bool isEmpty() {
			return this->empty;
		}
	};

}