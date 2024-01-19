#pragma once

#include "main.h"
#include "utils.h"

namespace angarawindows {
	using namespace System;
	using namespace System::Resources;

	ref class LocalizationManager {
		protected:
			static ResourceManager^ rm = nullptr;
			static String^ locale = "en";
	public:
		static void init();

		static void setLocale(String^ locale);

		static String^ getLocale();

		static String^ getStr(String^ key);
	};
}	