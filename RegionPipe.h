#pragma once
#include "main.h"
#include "AbstractDialog.h"

namespace angarawindows {
	class RegionPipe : public AbstractDialog {
	public:

		void save() override;
		void close() override;

	public:
		int idLink;

		void show(int idLink) override;
		void show() override {
			show(-1);
		};
	};
}
