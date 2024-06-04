#pragma once
#include "main.h"
#include "AbstractDialogData.h"

extern "C" {
	namespace angarawindows {
		struct EXPORT WaterPumpData : AbstractDialogData {
			struct ChartPoint {
				double Q;
				double H;
				double N;
			};

			int enable;
			std::wstring name;
			std::wstring mark;

			float diameter_nominal;
			int turnovers_nominal;

			double H0;
			float S;
			double N0;
			double C;

			std::vector<ChartPoint> points;

			float diameter_current;
			float turnovers_current;
			double resistance_current;

			double efficiency_min;
			double efficiency_max;

			float pressure_in_min;
			float pressure_in_max;

			float pressure_out_min;
			float pressure_out_max;

			float turnovers_min;
			float turnovers_max;

			float diameter_min;
			float diameter_max;
		};
	}
}