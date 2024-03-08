#pragma once
#include "RegionPipe.h"
#include "RegionForm.h"
#include "RealAbstractDialog.h"
#include "ObserverValue.h"

namespace angarawindows {
	ref class RealRegionPipe : public RealAbstractDialog {
	public:
		RealRegionPipe(RegionPipe* model);
		void init() override;
		void close() override;
		void save() override;
		void migrate() override;

		RegionPipe* model;
		RegionForm^ form;
	};
}