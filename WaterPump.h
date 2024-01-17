#pragma once
#include "main.h"
#include "AbstractDialog.h"

namespace angarawindows {
	class WaterPump : public AbstractDialog {
	public:
		struct ChartPoint {
			double Q;
			double H;
			double N;
		};

		void save() override;

	public:
		int idLink;

		int enable = 0;
		std::string name;
		std::string mark;

		float diameter_nominal = 0;
		int turnovers_nominal = 0;

		double H0 = 0;
		float S = 0;
		double N0 = 0;
		double C = 0;

		std::vector <ChartPoint> points;

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

		void show(int idLink) override;
		void show() override {
			show(-1);
		};
	};
}