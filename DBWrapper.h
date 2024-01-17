#pragma once

namespace angarawindows {
	template<typename VT> ref class DBWrapper {
	public:
		VT value;
		bool empty = true;
	};
}