#pragma once
#include "DBWrapper.h"
#include "inputs.h"
#include <stdexcept>
#include <map>

namespace angarawindows {
	using namespace System;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;

	template<typename T>
	struct has_number {
		static const bool value = std::is_arithmetic<T>::value;
	};
	//---------------------------------------
	template<typename T>
	struct has_string {
		static const bool value = false;
	};
	template<>
	struct has_string<std::string> {
		static const bool value = true;
	};
	template<>
	struct has_string<const char*> {
		static const bool value = true;
	};
	template<>
	struct has_string<System::String^> {
		static const bool value = true;
	};
	//---------------------------------------
	template<typename T>
	struct has_container {
		static const bool value = false;
	};
	template<typename T>
	struct has_container<List<T>^> {
		static const bool value = true;
	};
	//---------------------------------------
	template < typename T>
	bool isDefaultValue(T value, typename std::enable_if<has_number<T>::value, T>::type* = 0) {
		return value == 0;
	}

	template < typename T>
	bool isDefaultValue(T value, typename std::enable_if<has_string<T>::value, T>::type* = 0) {
		if constexpr (std::is_same<T, std::string>::value) {
			return value.empty();
		}
		else if constexpr (std::is_same<T, const char*>::value) {
			while (*value != '\0') {
				if (!isspace((unsigned char)*value))
					return false;
				value++;
			}
			return true;
		}
		else if constexpr (std::is_same<T, System::String^>::value) {
			return value->Length == 0;
		}

		return false;
	}

	template < typename T>
	bool isDefaultValue(T value, typename std::enable_if<has_container<T>::value, T>::type* = 0) {
		return value->Count == 0;
	}

	template < typename T>
	bool isDefaultValue(T value, typename std::enable_if<!has_string<T>::value && !has_number<T>::value && !has_container<T>::value, T>::type* = 0) {
		throw "x";
		return false;
	}

	template <typename OBS> ref class ObserverValue {
	public:
		delegate String^ Valide(OBS, bool);
		delegate void Event(ObserverValue<OBS>^);
		delegate OBS PrepareToShow(OBS, bool);
	private:
		OBS value; //pointer to value
		Dictionary<System::String^, int>^ errors = nullptr; //pointer to errors;
		ToolTip^ errorTip;

		bool isUser = false;
		bool empty = false;
		List<Event^>^ eventHandlers = gcnew List<Event^>();
		Dictionary<Control^, PrepareToShow^>^ inputs = gcnew Dictionary<Control^, PrepareToShow^>();
		Valide^ validate = nullptr;
	public:
		bool isUpdateProcess = false;
		bool isValidProcess = false;

		ObserverValue(OBS value, Dictionary<System::String^, int>^ errors, ToolTip^ errorTip) {
			this->value = value;
			this->errors = errors; //set pointer
			this->errorTip = errorTip;
			this->setValue(value);
		};

		void setValue(OBS value) {
			this->setValue(value, isDefaultValue(value));
		}

		void setValue(DBWrapper<OBS>^ value) {
			setValue(value, true);
		}

		void setValue(DBWrapper<OBS>^ value, bool isUser) {
			this->setValue(value->value, value->empty, isUser);
		}

		void setValue(OBS value, bool isEmpty) {
			this->setValue(value, isEmpty, false);
		}

		void setValue(OBS value, bool isEmpty, bool isUser) {
			if (this->isUpdateProcess)
				return;
			this->isUpdateProcess = true;

			//--------------------------------------------
			OBS last_value = this->value;
			bool last_empty = this->empty;
			bool last_is_user = this->isUser;
			//--------------------------------------------
			this->value = value;
			this->empty = isEmpty;
			this->isUser |= isUser;

			if (this->valid()) {

				for (int i = 0; i < this->eventHandlers->Count; i++) {
					this->eventHandlers[i](this);
				}

				setValueToInput();
			}
			else {
				this->value = last_value;
				this->empty = last_empty;
				this->isUser = last_is_user;
			}

			this->isUpdateProcess = false;
		}

		ObserverValue<OBS>^ addEventListener(Event^ func) {
			this->eventHandlers->Add(func);
			return this;
		}
		ObserverValue<OBS>^ removeEventListener(Event^ func) {
			this->eventHandlers->Remove(func);
			return this;
		}
		void throwEvent() {
			this->setValue(this->getValue());
		}
		bool valid() {
			if (this->isValidProcess)
				return false;
			this->isValidProcess = true;

			String^ error = "";
			if (validate != nullptr)
				error = this->validate(value, this->empty);

			if (error == "") {
				removeFromsErrors();
			}
			else {
				addToErrors(error);
			}

			this->isValidProcess = false;
			return error == "";
		}
		OBS getValue() {
			return this->value;
		}

		DBWrapper<OBS>^ getWrapper() {
			DBWrapper<OBS>^ wrapper = gcnew DBWrapper<OBS>();
			wrapper->empty = empty;
			wrapper->value = value;

			return wrapper;
		}

		bool isUserNotEdit() {
			return !this->isUser;
		}

		bool isEmpty() {
			return this->empty;
		}

		ObserverValue<OBS>^ addValidate(Valide^ validate) {
			this->validate = validate;
			return this;
		}

		System::Void showErrorsEvent(System::Object^ sender, System::EventArgs^ e) {
			Control^ t = safe_cast<Control^>(sender);

			

			if (!this->errors->ContainsKey(t->Name))
				return;
			this->errorTip->Active = false;
			this->errorTip->Active = true;
		}

		System::Void eventHandler(System::Object^ sender, System::EventArgs^ e) {
			Control^ control = safe_cast<Control^>(sender);
			if (this->isUpdateProcess)
				return;
			try {
				DBWrapper<OBS>^ wrapper = gcnew DBWrapper<OBS>;

				if (TextBox^ box = dynamic_cast<TextBox^>(control)) {
					if constexpr (std::is_same<OBS, double>::value || std::is_same<OBS, float>::value) {
						wrapper = _DoubleInputHandler<OBS>(box);
					}
					else if constexpr (std::is_same<OBS, int>::value) {
						wrapper = _IntInputHandler<OBS>(box);
					}
					else if constexpr (std::is_same<OBS, System::String^>::value) {
						wrapper->value = box->Text;
						wrapper->empty = box->Text->Length == 0;
					}
				}
				else if constexpr (std::is_same<OBS, double>::value || std::is_same<OBS, int>::value || std::is_same<OBS, float>::value) {
					if (TrackBar^ bar = dynamic_cast<TrackBar^>(control)) {
						wrapper->value = bar->Value;
						wrapper->empty = false;
					}
					else if (ComboBox^ comboBox = dynamic_cast<ComboBox^>(control)) {
						wrapper->value = comboBox->SelectedIndex;
						wrapper->empty = false;
					}
					else if (NumericUpDown^ numeric = dynamic_cast<NumericUpDown^>(control)) {
						wrapper->value = (int)numeric->Value;
						wrapper->empty = false;
					}
				}

				PrepareToShow^ pr = inputs[control];
				if (pr != nullptr)
					wrapper->value = pr(wrapper->value, false);
				this->setValue(wrapper, true);
			}catch (std::invalid_argument q) {
				//await
			}
		}

		ObserverValue<OBS>^ addInput(TrackBar^ trackBar, PrepareToShow^ handler) {
			inputs->Add(trackBar, handler);

			trackBar->ValueChanged += gcnew System::EventHandler(this, &ObserverValue::eventHandler);
			trackBar->MouseEnter += gcnew System::EventHandler(this, &ObserverValue::showErrorsEvent);
			return this;
		}

		ObserverValue<OBS>^ addInput(TrackBar^ trackBar) {
			return addInput(trackBar, nullptr);
		}


		ObserverValue<OBS>^ addInput(ComboBox^ comboBox, PrepareToShow ^ handler) {
			inputs->Add(comboBox, handler);

			comboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ObserverValue::eventHandler);
			comboBox->MouseEnter += gcnew System::EventHandler(this, &ObserverValue::showErrorsEvent);
			return this;
		}

		ObserverValue<OBS>^ addInput(ComboBox^ comboBox) {
			return addInput(comboBox, nullptr);
		}

		ObserverValue<OBS>^ addInput(NumericUpDown^ numeric, PrepareToShow ^ handler) {
			inputs->Add(numeric, handler);

			numeric->ValueChanged += gcnew System::EventHandler(this, &ObserverValue::eventHandler);
			numeric->MouseEnter += gcnew System::EventHandler(this, &ObserverValue::showErrorsEvent);
			return this;
		}

		ObserverValue<OBS>^ addInput(NumericUpDown^ numeric) {
			return addInput(numeric, nullptr);
		}

		ObserverValue<OBS>^ addInput(TextBox^ text_box, PrepareToShow ^ handler) {
			inputs->Add(text_box, handler);

			text_box->TextChanged += gcnew System::EventHandler(this, &ObserverValue::eventHandler);
			text_box->MouseEnter += gcnew System::EventHandler(this, &ObserverValue::showErrorsEvent);
			return this;
		}
		ObserverValue<OBS>^ addInput(TextBox^ text_box) {
			return addInput(text_box, nullptr);
		}

		void clear() {
			for each (Control ^ ctr in this->inputs->Keys) {
				if (TextBox^ textBox = dynamic_cast<TextBox^>(ctr)) {
					textBox->TextChanged -= gcnew System::EventHandler(this, &ObserverValue::eventHandler);
					textBox->MouseEnter -= gcnew System::EventHandler(this, &ObserverValue::showErrorsEvent);
				}
				else if (TrackBar^ bar = dynamic_cast<TrackBar^>(ctr)) {
					bar->ValueChanged -= gcnew System::EventHandler(this, &ObserverValue::eventHandler);
					bar->MouseEnter -= gcnew System::EventHandler(this, &ObserverValue::showErrorsEvent);
				}
				else if (ComboBox^ comboBox = dynamic_cast<ComboBox^>(ctr)) {
					comboBox->SelectedIndexChanged -= gcnew System::EventHandler(this, &ObserverValue::eventHandler);
					comboBox->MouseEnter -= gcnew System::EventHandler(this, &ObserverValue::showErrorsEvent);
				}
				else if (NumericUpDown^ numeric = dynamic_cast<NumericUpDown^>(ctr)) {
					numeric->ValueChanged -= gcnew System::EventHandler(this, &ObserverValue::eventHandler);
					numeric->MouseEnter -= gcnew System::EventHandler(this, &ObserverValue::showErrorsEvent);
				}
			}

			inputs->Clear();
			eventHandlers->Clear();
			errorTip = nullptr;
			validate = nullptr;
		}

		static void inline addToErrors(Control^ control, String^ error, Dictionary<System::String^, int>^ errors, ToolTip^ errorTip) {
			if (!errors->ContainsKey(control->Name))
				errors[control->Name] = control->BackColor.ToArgb();

			errorTip->SetToolTip(control, error);
			control->BackColor = System::Drawing::Color::FromArgb(255, 128, 128);
		}

		void inline addToErrors(String^ error) {
			for each (Control^ box in inputs->Keys) {
				addToErrors(box, error, this->errors, this->errorTip);
			}
		}

		void setValueToInput() {
			for each (Control^ box in inputs->Keys) {

				OBS vl = this->value;
				PrepareToShow^ pr = inputs[box];
				if (pr != nullptr)
					vl = pr(vl, true);

				if (TextBox^ textBox = dynamic_cast<TextBox^>(box)) {
					SuperTextSetter(textBox, vl, this->empty);
				}else if (TrackBar^ bar = dynamic_cast<TrackBar^>(box)) {
					SuperTextSetter(bar, vl, this->empty);
				}
				else if (ComboBox^ comboBox = dynamic_cast<ComboBox^>(box)) {
					SuperTextSetter(comboBox, vl, this->empty);
				}
				else if (NumericUpDown^ numeric = dynamic_cast<NumericUpDown^>(box)) {
					SuperTextSetter(numeric, vl, this->empty);
				}
			}
		}

		static inline void removeFromsErrors(Control^ control, Dictionary<System::String^, int>^ errors, ToolTip^ errorTip) {

			if (!errors->ContainsKey(control->Name))
				return;

			control->BackColor = System::Drawing::Color::FromArgb(errors[control->Name]);
			errors->Remove(control->Name);
			errorTip->SetToolTip(control, nullptr);
		}


		void inline removeFromsErrors() {
			for each (Control ^ box in inputs->Keys) {
				removeFromsErrors(box, this->errors, this->errorTip);
			}
		}
	};
}