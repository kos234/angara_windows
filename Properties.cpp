#pragma once
#include "Properties.h"
#include "LocalizationManager.h"

namespace angarawindows {
	using namespace System;
	using namespace System::Windows::Forms;

	void Properties::setDBConnect(String^ connector) {
		Properties::urlConnect = connector;
		Application::SetCompatibleTextRenderingDefault(false);
		Application::EnableVisualStyles();

		LocalizationManager::init();
	}

	String^ Properties::getLocale() {
		return LocalizationManager::getLocale();
	}

	void Properties::setLocale(String^ locale) {
		LocalizationManager::setLocale(locale);
	}

	String^ Properties::getUrlConnect() {
		return urlConnect;
	}
}