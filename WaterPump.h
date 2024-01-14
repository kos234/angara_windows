#pragma once
#include "main.h"

namespace angarawindows {
	class WaterPump {
	public:
		struct ChartPoint {
			double Q;
			double H;
			double N;
		};

		void save();
	protected:
		std::vector<ChartPoint> points;
	public:
		//Служебное --------------------------------------
		int idLink;
		double resistance_min = 0;
		ObserverValue<float> QPoint{ 0 };
		ObserverValue<float> HInPoint{ 0 };
		ObserverValue<float> HOutPoint{ 0 };
		ObserverValue<int> elemMove{ -1 };
		ObserverValue<double> pointer{ -1 };
		ObserverValue<double> k{ 0 };
		//------------------------------------------------

		ObserverValue<int> enable{ 0 };
		ObserverValue<std::string> name;
		ObserverValue<std::string> mark;

		ObserverValue<float> diameter_nominal{ 0 };
		ObserverValue<int> turnovers_nominal{ 0 };

		ObserverValue<double> H0{ 0 };
		ObserverValue<float> S{ 0 };
		ObserverValue<double> N0{ 0 };
		ObserverValue<double> C{ 0 };
		
		ObserverValue<std::vector<ChartPoint>> chartPoints{ points };

		ObserverValue<float> diameter_current{ 0 };
		ObserverValue<float> turnovers_current{ 0 };
		ObserverValue<double> resistance_current{ -1 };

		ObserverValue<double> efficiency_min{ 0 };
		ObserverValue<double> efficiency_max{ 0 };

		ObserverValue<float> pressure_in_min{ 0 };
		ObserverValue<float> pressure_in_max{ 0 };

		ObserverValue<float> pressure_out_min{ 0 };
		ObserverValue<float> pressure_out_max{ 0 };

		ObserverValue<float> turnovers_min{ 0 };
		ObserverValue<float> turnovers_max{ 0 };

		ObserverValue<float> diameter_min{ 0 };
		ObserverValue<float> diameter_max{ 0 };

		void show(int idLink);
		void show(void);
	};
}