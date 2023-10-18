#pragma once
#include <string>
#include <vector>

void setDBConnect(const char *);

class WaterPumpWindow {
	public:
		int idLink;
		/*ObserverValue<String> name;
		ObserverValue<String> mark;
		ObserverValue<int> diameter_nominal;
		ObserverValue<int> turnovers_nominal;
		ObserverValue<bool> enable;
		ObserverValue<double> H0;
		ObserverValue<double> S;
		ObserverValue<double> N0;
		ObserverValue<double> C;
		struct ChartPoint{
			double Q;
			double H;
			double N;
		};
		std::vector<ChartPoint> chartPoint;
		ObserverValue<int> diameter_current;
		ObserverValue<int> turnovers_current;*/



		void show(int idLink);
};


template <class OBS>class ObserverValue {
	OBS value;
	bool isUpdate;
	typedef void (*func)(OBS value);

	std::vector<func> eventHandlers;

public:
	void setValue(OBS value);
	void addEventListener(void(*func)(OBS value));
	void removeEventListener(void(*func)(OBS value));
	OBS getValue();
};