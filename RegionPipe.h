#pragma once
#include "RegionForm.h"
#include "ObserverValue.h"

namespace angarawindows {
	ref class RegionPipe : public AbstractDialog {
	public:
		RegionPipe(int idLink);
		void init() override;
		void close() override;
		void save() override;

		int idLink;
		RegionForm^ form;
	};
}