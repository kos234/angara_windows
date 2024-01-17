#include <map>
#include <string>

namespace angarawindows {
	class AbstractDialog {
	public:
		std::map<std::string, int> errors;
		virtual void save() = 0;
		virtual void show(int idLink) = 0;
		virtual void show() = 0;
	};
}