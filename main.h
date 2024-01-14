#pragma once
#include <string>
#include <vector>
#include <functional>

namespace angarawindows {
	void setDBConnect(const char*);
	const char* getUrlConnect();
	template<typename VT> bool _isDefaultValue(VT value);

	template<typename VT> public  struct DBWrapper {
		VT value;
		bool empty = true;
	};

	template <typename OBS> public  class ObserverValue {
		OBS value;
		bool userNotEdit = true;
		bool empty = false;
		bool cancel = false;
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

			//last-----------
			OBS last_value = this->value;
			bool last_empty = this->empty;
			bool last_user_not_edit = this->userNotEdit;
			//---------------

			this->value = value;
			if (!isUser) {
				isEmpty = _isDefaultValue(value);
			}
			this->empty = isEmpty;
			this->userNotEdit |= isUser;
			this->cancel = false;

			for (auto fuctionLink : this->eventHandlers) {
				fuctionLink(*this);

				if (cancel) {
					this->value = last_value;
					this->empty = last_empty;
					this->userNotEdit = last_user_not_edit;
					break;
				}
			}

			this->isUpdate = false;
		}

		void addEventListener(std::function<void(ObserverValue<OBS>&)> func) {
			this->eventHandlers.push_back(func);
		}
		void removeEventListener(std::function<void(ObserverValue<OBS>&)> func) {
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

		void cancelEvent() {
			this->cancel = true;
		}
	};

}