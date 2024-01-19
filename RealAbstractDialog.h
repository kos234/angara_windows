#pragma once

namespace angarawindows {
	ref class RealAbstractDialog {
	public:
		bool isSaveValidation = false;
		virtual void save() = 0;
		virtual void close() = 0;
		virtual void init() = 0;
		virtual void migrate() = 0;
	};
}