#pragma once

#include "main.h"
#include "utils.h"

namespace angarawindows {
	using namespace System;
	using namespace System::Resources;

	ref class LocalizationManager {
			static ResourceManager^ rm = nullptr;
			static String^ locale = "ru";
	public:
		static void init() {
			System::Reflection::Assembly^ as = System::Reflection::Assembly::GetExecutingAssembly();

			array<System::String^>^ tmp = as->GetManifestResourceNames();
			System::String^ asname = as->GetName()->Name;
			//log(SysToStd(asname));
			asname = asname->Replace("_", "");
			/*for each (System::String ^ sad in tmp) {
				log(SysToStd(sad));
			}
			log(SysToStd(asname));*/
			LocalizationManager::rm = gcnew ResourceManager(asname + ".strings", System::Reflection::Assembly::GetExecutingAssembly());
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