#pragma once

#include "LocalizationManager.h"
#include "main.h"

namespace angarawindows {
	using namespace System;
	using namespace System::Resources;


	void LocalizationManager::init() {
		LocalizationManager::rm = gcnew ResourceManager("angarawindows.strings", Reflection::Assembly::GetExecutingAssembly());
		if (System::Threading::Thread::CurrentThread->CurrentCulture->Name->StartsWith(StdToSys(locales::RU_LOCALE))) {
			locale = StdToSys(locales::RU_LOCALE);
		}
		else if (System::Threading::Thread::CurrentThread->CurrentCulture->Name->StartsWith(StdToSys(locales::EN_LOCALE))) {
			locale = StdToSys(locales::EN_LOCALE);
		}
		else if (System::Threading::Thread::CurrentThread->CurrentCulture->Name->StartsWith(StdToSys(locales::ZH_LOCALE))) {
			locale = StdToSys(locales::ZH_LOCALE);
		}
	}

	void LocalizationManager::setLocale(String^ locale) {
		LocalizationManager::locale = locale;
	}

	String^ LocalizationManager::getLocale() {
		return LocalizationManager::locale;
	}

	String^ LocalizationManager::getStr(String^ key) {
		key = LocalizationManager::locale + "." + key;
		String^ value = LocalizationManager::rm->GetString(key);
		if (value == nullptr)
			return key;
		return value;
	}
}