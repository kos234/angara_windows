#include <iostream>
#include <string>
#include "InputOutputListener.h"
#include "Properties.h"
#include "OpenDialog.h"
#include <msclr\marshal_cppstd.h>

namespace angarawindows {
	const int OPEN_WINDOW = 1;
	const int SAVE_AND_CLOSE_WINDOW = 2;
	const int CLOSE_WINDOW = 3;
	const int SET_URL_DATABASE = 4;
	const int CLOSE_APPLICATION = 5;
	const int SET_LOCALE = 6;

	void setUrlConnection();
	void setLocale();
	void openDialog();
	void saveAndCloseWindow();
	void closeWindow();

	InputOutputListener::InputOutputListener() {
		//std::ios::sync_with_stdio(0);
		//std::cout.tie(0);
		//std::cin.tie(0);
		this->thread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &InputOutputListener::Listener));
		this->thread->Start();
	}

	void InputOutputListener::Listener() {
		//Properties::setDBConnect(L"provider=Microsoft.ACE.OLEDB.12.0;Data Source=C:\\Users\\kosty\\Documents\\tp_ML_ru_2023_11_пя.mdb");
		//OpenDialog^ openDialog = gcnew OpenDialog(4013);
		while (true){
			std::string command;
			std::cin >> command;

			switch (atoi(command.c_str())) {
				case OPEN_WINDOW:
					openDialog();
					break;
				case SAVE_AND_CLOSE_WINDOW:
					saveAndCloseWindow();
					break;
				case CLOSE_WINDOW:
					closeWindow();
					break;
				case SET_URL_DATABASE:
					setUrlConnection();
					break;
				case SET_LOCALE:
					setLocale();
					break;

				default:
					InputOutputListener::write("error command");
					break;
			}
		}
	}

	void InputOutputListener::write(String^ text) {
		std::string message = msclr::interop::marshal_as<std::string>(text);
		if (message[message.length() - 1] != '\n')
			message += "\n";

		std::cout << message;
	}

	void setUrlConnection() {
		std::string url;
		std::getline(std::cin, url);
		Properties::setDBConnect(gcnew String(url.c_str()));
		InputOutputListener::write("ok");
	}

	void setLocale() {
		std::string locale;
		std::cin >> locale;

		Properties::setLocale(gcnew String(locale.c_str()));
		InputOutputListener::write("ok");
	}

	void openDialog() {
		if (Properties::currentDialog != nullptr) {
			InputOutputListener::write("other dialog is already open");
			return;
		}
		int idLink;
		std::cin >> idLink;
		InputOutputListener::write("ok");
		OpenDialog^ openDialog = gcnew OpenDialog(idLink);
	}

	void saveAndCloseWindow() {
		if (Properties::currentDialog == nullptr) {
			InputOutputListener::write("dialog is not open");
			return;
		}

		Properties::currentDialog->save();
		InputOutputListener::write("ok");
	}

	void closeWindow() {
		if (Properties::currentDialog == nullptr) {
			InputOutputListener::write("dialog is not open");
			return;
		}

		Properties::currentDialog->close();
		InputOutputListener::write("ok");
	}
}