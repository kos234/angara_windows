#pragma once
#include <string>
#include <vector>
#include <functional>
#include "AbstractDialogData.h"

namespace angarawindows {
	extern "C" struct EXPORT locales {
		static const std::string RU_LOCALE;
		static const std::string EN_LOCALE;
		static const std::string ZH_LOCALE;
	};

	extern "C" EXPORT void setDBConnect(const char*);
	extern "C" EXPORT const char* getUrlConnect();

	extern "C" EXPORT std::string getLocale();
	extern "C" EXPORT void setLocale(std::string);

	extern "C" EXPORT AbstractDialogData* openDialogById(int);
}