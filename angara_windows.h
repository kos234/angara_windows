#pragma once
#include <string>
#include <vector>
#include <functional>

namespace angarawindows {

	void setDBConnect(const char*);

	template <typename OBS>class ObserverValue {
		OBS value;

		std::vector<std::function<void(OBS)>> eventHandlers;

	public:
		bool isUpdate;
		ObserverValue() {};
		ObserverValue(OBS value) {
			this->value = value;
		};
		void setValue(OBS value);
		void addEventListener(std::function<void(OBS)>);
		void removeEventListener(std::function<void(OBS)>);
		void throwEvent();
		OBS getValue();
	};


	template <typename OBS>class ObserverArray {
		std::vector<OBS> value;
		bool isUpdate;

		std::vector<std::function<void(std::vector<OBS>*)>> eventHandlers;

	public:
		ObserverArray() {};
		void addEventListener(std::function<void(std::vector<OBS>*)>);
		void removeEventListener(std::function<void(std::vector<OBS>*)>);
		void throwEvent();
		std::vector<OBS>* getValue();
	};

	class WaterPumpWindow {
	public:
		ObserverValue<int> elemMove{ -1 };
		int idLink;
		int getas = 2;
		ObserverValue<int> enable{ 0 };
		ObserverValue<std::string> name;
		ObserverValue<std::string> mark;
		ObserverValue<double> diameter_nominal{ 0 };
		ObserverValue<int> turnovers_nominal{ 0 };
		ObserverValue<double> H0{ 0 };
		ObserverValue<float> S{ 0 };
		ObserverValue<double> N0{ 0 };
		ObserverValue<double> C{ 0 };
		struct ChartPoint{
			double Q;
			double H;
			double N;
		};
		ObserverArray<ChartPoint> chartPoints;
		ObserverValue<double> diameter_current{ 0 };
		ObserverValue<int> turnovers_current{ 0 };
		ObserverValue<double> resistance_current{ 0 };
		ObserverValue<double> efficiency_min{ 0 };
		ObserverValue<double> efficiency_max{ 0 };
		ObserverValue<double> pressure_min{ 0 };
		ObserverValue<double> pressure_max{ 0 };
		ObserverValue<int> turnovers_min{ 0 };
		ObserverValue<int> turnovers_max{ 0 };
		ObserverValue<int> diameter_min{ 0 };
		ObserverValue<int> diameter_max{ 0 };

		void show(int idLink);
	};
}