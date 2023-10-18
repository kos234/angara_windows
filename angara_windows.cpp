#include "angara_windows.h"
#include "WaterPump.h"
#include "Pipe.h"
#include <string>

using namespace System;
using namespace System::Windows::Forms;

const char * dbURL;
bool isStyleLoad = false;

void setDBConnect(const char* urlConnect){
	dbURL = urlConnect;

	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	isStyleLoad = true;
}

[STAThreadAttribute]
void abstactShow(System::Windows::Forms::Form^ form) {
	Application::Run(form);
}


[STAThreadAttribute]
void WaterPumpWindow::show(int idLink) {
	angarawindows::WaterPump form;
	abstactShow(% form);
}

template<class OBS> void ObserverValue<OBS>::setValue(OBS value) {
	this->value = value;
	for (auto fuctionLink : this->eventHandlers) {
		fuctionLink(value);
	}
}

template<class OBS> OBS ObserverValue<OBS>::getValue() {
	return this->value;
}
template<class OBS> void ObserverValue<OBS>::addEventListener(void(*func)(OBS value)) {
	this->eventHandlers.push_back(func);
}

template<class OBS> void ObserverValue<OBS>::removeEventListener(void(*func)(OBS value)) {
	this->eventHandlers.erase(std::remove(this->eventHandlers.begin(), this->eventHandlers.end(), func), this->eventHandlers.end());
}




