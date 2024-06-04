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
	//const wchar_t* locales::RU_LOCALE = L"ru";
	//const wchar_t* locales::EN_LOCALE = L"en";
	//const wchar_t* locales::ZH_LOCALE = L"zh";


	const wchar_t* urlConnect;

	void setDBConnect(const wchar_t* connect) {
		std::wcout << L"url to = " << connect << L"\n";
		urlConnect = connect;
		Application::SetCompatibleTextRenderingDefault(false);
		Application::EnableVisualStyles();

		LocalizationManager::init();
	}

	const wchar_t* getLocale() {
		return SysToStd(LocalizationManager::getLocale()).c_str();
	}

	void setLocale(const wchar_t* locale) {
		std::wcout << L"locale is = " << locale << L"\n";

		String^ vsd = StdToSys(locale);
		log<std::string>("pizec");
		LocalizationManager::setLocale(vsd);
	}

	const wchar_t* getUrlConnect() {
		return urlConnect;
	}

	AbstractDialogData* openDialogById(int id) {
		MessageBox::Show("1");
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