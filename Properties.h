#pragma once
#include "AbstractDialog.h"

namespace angarawindows {
	using namespace System;

	ref class Properties {
	private:
		static String^ urlConnect;
	public:
		static AbstractDialog^ currentDialog = nullptr;

		ref class Locales {
		public:
			static String^ RU_LOCALE = "ru";
			static String^ EN_LOCALE = "en";
			static String^ ZH_LOCALE = "zh";
		};

		static void setDBConnect(String^);
		static String^ getUrlConnect();

		static String^ getLocale();
		static void setLocale(String^);
	};
}