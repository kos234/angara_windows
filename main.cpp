#pragma once
#include <functional>
#include <msclr/gcroot.h>
#include "main.h"
#include "utils.h"
#include "OpenDialog.h"
#include "AbstractDialogData.h"
#include "CurrentForm.h"
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

	AbstractDialogData* openDialogById(int id) {
		OpenDialog^ openDialog = gcnew OpenDialog(id);
		
		return getLastDialogData();
	}
}

/*
int maind() {
	angarawindows::setDBConnect("provider=Microsoft.ACE.OLEDB.12.0;Data Source=C:\\Users\\kosty\\Documents\\tp_ML_ru_2023_11.mdb");
	angarawindows::setLocale(angarawindows::locales::RU_LOCALE);

	angarawindows::WaterPump windPump;
	windPump.show(4028);
	return 0;
}*/