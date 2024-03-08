#pragma once
#include <functional>
#include <msclr/gcroot.h>
#include "utils.h"
#include "WaterPump.h"
#include "RegionPipe.h"
#include "LocalizationManager.h"


namespace angarawindows {
	const char* urlConnect;

	const std::string locales::RU_LOCALE = "ru";
	const std::string locales::EN_LOCALE = "en";
	const std::string locales::ZH_LOCALE = "zh";

	void setDBConnect(const char* connect) {
		urlConnect = connect;
		Application::SetCompatibleTextRenderingDefault(false);
		Application::EnableVisualStyles();

		LocalizationManager::init();
	}

	std::string getLocale() {
		return SysToStd(LocalizationManager::getLocale());
	}

	void setLocale(std::string locale) {
		LocalizationManager::setLocale(StdToSys(locale));
	}

	const char* getUrlConnect() {
		return urlConnect;
	}
}


int maind() {
	angarawindows::setDBConnect("provider=Microsoft.ACE.OLEDB.12.0;Data Source=C:\\Users\\kosty\\Documents\\TP_EqNS_ML.MDB");
	angarawindows::setLocale(angarawindows::locales::ZH_LOCALE);

	angarawindows::RegionPipe windPump;
	windPump.show(4028);
	return 0;
}