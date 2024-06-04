#pragma once
#include <string>
#include <vector>
#include <functional>
#include "AbstractDialogData.h"

extern "C" {
	namespace angarawindows {
		namespace locales {
			const std::wstring RU_LOCALE = L"ru";
			const std::wstring EN_LOCALE = L"en";
			const std::wstring ZH_LOCALE = L"zh";
		};

		EXPORT void setDBConnect(const wchar_t*);
		EXPORT const wchar_t* getUrlConnect();

		EXPORT const wchar_t* getLocale();
		EXPORT void setLocale(const wchar_t*);

		EXPORT AbstractDialogData * openDialogById(int);
	}
}