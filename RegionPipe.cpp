#pragma once

#include "RealRegionPipe.h"
#include "RegionPipe.h"

namespace angarawindows {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Data::OleDb;

	[STAThreadAttribute]
	RealRegionPipe::RealRegionPipe(RegionPipe* model){
		this->model = model;
		RegionForm form;
		this->form = % form;
		init();
		Application::Run(this->form);
	}

	void RealRegionPipe::init() {
	
	};
	
	void RealRegionPipe::close() {
	
	};
	
	void RealRegionPipe::save() {
	
	};
	
	void RealRegionPipe::migrate() {
	
	};

	void RegionPipe::save() {
	}
	
	void RegionPipe::close() {
	
	};


	void RegionPipe::show(int idLink) {
		this->idLink = idLink;
		RealRegionPipe^ rl = gcnew RealRegionPipe(this);
	}

}