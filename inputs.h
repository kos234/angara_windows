#pragma once
#include "DBWrapper.h"
#include <string>


namespace angarawindows {
	std::wstring SysToStd(System::String^ original);
	std::string SysToStdString(System::String^ original);

	System::String^ StdToSys(std::wstring original);

	template<typename OBS>
	DBWrapper<OBS>^ _IntInputHandler(System::Windows::Forms::TextBox^ box) {
		DBWrapper<int>^ wrapper = gcnew DBWrapper<OBS>();
		wrapper->value = 0;
		bool isMinus = false;
		wrapper->empty = true;

		for (int i = 0; i < box->Text->Length; i++) {
			auto ch = box->Text[i];

			if (wrapper->value == 0 && ch == '-') {
				isMinus = true;
			}
			else if ('0' <= ch && ch <= '9') {
				wrapper->empty = false;
				wrapper->value = (OBS) wrapper->value * 10 + (ch - '0');
			}
			else {
				goto if_there_is_an_extraneous_character;
			}
		}

		if (isMinus && wrapper->empty) {
			throw std::invalid_argument("await");
		}

	if_there_is_an_extraneous_character: {};
		if (isMinus)
			wrapper->value *= -1;

		return wrapper;
	}

	template<typename OBS>
	DBWrapper<OBS>^ _DoubleInputHandler(System::Windows::Forms::TextBox^ box) {
		DBWrapper<OBS>^ wrapper = gcnew DBWrapper<OBS>();
		wrapper->value = 0;
		double drob = 0;
		double drobSize = 1;
		bool isMinus = false;
		bool isDrob = false;

		bool isSaintific = false;
		bool isMinusSaintific = false;
		double saintificPow = 0;

		for (int i = 0; i < box->Text->Length; i++) {
			auto ch = box->Text[i];

			if (wrapper->value == 0 && ch == '-') {
				isMinus = true;
			}
			else if (isSaintific && ch == '-') {
				isMinusSaintific = true;
			}
			else if ('0' <= ch && ch <= '9') {
				int val = (ch - '0');

				if (isSaintific) {
					saintificPow = saintificPow * 10 + val;
				}
				else if (isDrob) {
					drobSize *= 10;
					drob = drob * 10 + val;
				}
				else {
					wrapper->value = (OBS)wrapper->value * 10 + val;
				}
				wrapper->empty = false;
			}
			else if ((ch == '.' || ch == ',') && !isDrob) {
				isDrob = true;
			}
			else if (ch == 'e' || ch == L'å') {
				isSaintific = true;
			}
			else if (ch == '+' && isSaintific) {
				isMinusSaintific = false;
			}
			else {
				goto if_there_is_an_extraneous_character;
			}
		}

		if ((isMinus && wrapper->empty) || (isDrob && drobSize == 1)) {
			throw std::invalid_argument("await");
		}


	if_there_is_an_extraneous_character: {};
		if (isMinus)
			wrapper->value *= (OBS)-1;
		if (isDrob)
			wrapper->value += (OBS)drob / drobSize;

		if (isSaintific) {
			wrapper->value *= (OBS)pow(10, (isMinusSaintific ? -1 : 1) * saintificPow);;
		}

		return wrapper;
	}

	void SuperTextSetter(System::Windows::Forms::TextBox^ box, System::String^ text);

	template<typename OBS> void SuperTextSetter(System::Windows::Forms::TextBox^ box, OBS value, bool isEmpty) {
		if (isEmpty) {
			SuperTextSetter(box, "");
			return;
		}

		if constexpr (std::is_same<OBS, double>::value || std::is_same<OBS, float>::value || std::is_same<OBS, System::Double^>::value || std::is_same<OBS, System::Single^>::value) {
			if (0.002 > value) {
				SuperTextSetter(box, StdToSys(toSaintific(value)));
				return;
			}
			else
				value = round3(value);
		}

		SuperTextSetter(box, value + "");
	}

	template<typename OBS>
	void SuperTextSetter(System::Windows::Forms::TrackBar^ box, OBS value, bool isEmpty) {
		if constexpr (std::is_same<OBS, double>::value || std::is_same<OBS, float>::value || std::is_same<OBS, int>::value || std::is_same<OBS, long long>::value || std::is_same<OBS, System::Double^>::value || std::is_same<OBS, System::Single^>::value || std::is_same<OBS, System::Int32^>::value || std::is_same<OBS, System::Int64^>::value) {
			box->Value = (int) value;
			return;
		}

		throw std::runtime_error("SuperTextSetter function not defined for" + SysToStdString(OBS::typeid->Name));
	}

	template<typename OBS> void SuperTextSetter(System::Windows::Forms::ComboBox^ box, OBS value, bool isEmpty) {
		if constexpr (std::is_same<OBS, double>::value || std::is_same<OBS, float>::value || std::is_same<OBS, int>::value ||  std::is_same<OBS, long long>::value || std::is_same<OBS, System::Double^>::value || std::is_same<OBS, System::Single^>::value || std::is_same<OBS, System::Int32^>::value || std::is_same<OBS, System::Int64^>::value) {
			box->SelectedIndex = (int) value;
			return;
		}
		throw std::runtime_error("SuperTextSetter function not defined for" + SysToStdString(OBS::typeid->Name));
	}

	template<typename OBS> void SuperTextSetter(System::Windows::Forms::NumericUpDown^ box, OBS value, bool isEmpty) {
		if constexpr (std::is_same<OBS, double>::value || std::is_same<OBS, float>::value ||  std::is_same<OBS, int>::value  || std::is_same<OBS, long long>::value || std::is_same<OBS, System::Double^>::value || std::is_same<OBS, System::Single^>::value || std::is_same<OBS, System::Int32^>::value || std::is_same<OBS, System::Int64^>::value) {
			box->Value = (int)value;
			return;
		}

		throw std::runtime_error("SuperTextSetter function not defined for" + SysToStdString(OBS::typeid->Name));
	}
}