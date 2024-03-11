#pragma once

#include "Properties.h"

namespace angarawindows {
	using namespace System;
	using namespace System::Resources;

	ref class LocalizationManager {
			static ResourceManager^ rm = nullptr;
			static String^ locale = "en";
	public:
		static void init() {
			System::Reflection::Assembly^ as = System::Reflection::Assembly::GetExecutingAssembly();

			array<System::String^>^ tmp = as->GetManifestResourceNames();
			System::String^ asname = as->GetName()->Name;
			asname = asname->Replace("_", "");
			LocalizationManager::rm = gcnew ResourceManager(asname + ".strings", System::Reflection::Assembly::GetExecutingAssembly());
			
			if (System::Threading::Thread::CurrentThread->CurrentCulture->Name->StartsWith(Properties::Locales::RU_LOCALE)) {
				locale = Properties::Locales::RU_LOCALE;
			}else if (System::Threading::Thread::CurrentThread->CurrentCulture->Name->StartsWith(Properties::Locales::EN_LOCALE)) {
				locale = Properties::Locales::EN_LOCALE;
			}else if (System::Threading::Thread::CurrentThread->CurrentCulture->Name->StartsWith(Properties::Locales::ZH_LOCALE)) {
				locale = Properties::Locales::ZH_LOCALE;
			}
		}

		static String^ getLocaleFromDB() {
			if (LocalizationManager::locale == "zh")
				return "CN";
			
			return LocalizationManager::locale->ToUpper();
		}

		static void setLocale(String^ locale) {
			LocalizationManager::locale = locale;
		}

		static String^ getLocale() {
			return LocalizationManager::locale;
		}

		static String^ getStr(String^ key) {
			key = LocalizationManager::locale + "." + key;
			String^ value = LocalizationManager::rm->GetString(key);
			if (value == nullptr)
				return key;
			return value;
		}
	};
}	