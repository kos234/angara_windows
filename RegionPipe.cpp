#pragma once
#include "RegionPipe.h"

namespace angarawindows {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Data::OleDb;

	[STAThreadAttribute]
	RegionPipe::RegionPipe(int idLink){
		this->idLink = idLink;
		RegionForm form;
		this->form = % form;
		init();
		Application::Run(this->form);
	}

	void RegionPipe::init() {
	
	};
	
	void RegionPipe::close() {
	
	};
	
	void RegionPipe::save() {
	
	};

}