#pragma once
#include "main.h"
#include "AbstractDialogData.h"

namespace angarawindows {
	extern "C" struct EXPORT WaterPumpData : AbstractDialogData {
		struct ChartPoint {
			double Q;
			double H;
			double N;
		};

		int enable = 0;
		std::string name;
		std::string mark;

		float diameter_nominal = 0;
		int turnovers_nominal = 0;

		double H0;
		float S;
		double N0;
		double C;

		std::vector<ChartPoint> points;

		float diameter_current = 0;
		float turnovers_current = 0;
		double resistance_current = -1;

		double efficiency_min = 0;
		double efficiency_max = 0;

		float pressure_in_min = 0;
		float pressure_in_max = 0;

		float pressure_out_min = 0;
		float pressure_out_max = 0;

		float turnovers_min = 0;
		float turnovers_max = 0;

		float diameter_min = 0;
		float diameter_max = 0;
	};
}