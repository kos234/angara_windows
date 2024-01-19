#pragma once
#include <string>
#include <vector>
#include <functional>

namespace angarawindows {
	class locales {
	public:
		static const std::string RU_LOCALE;
		static const std::string EN_LOCALE;
		static const std::string ZH_LOCALE;
	};

	void setDBConnect(const char*);
	const char* getUrlConnect();

	std::string getLocale();
	void setLocale(std::string);
}