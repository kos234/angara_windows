#pragma once
#include "WaterPumpForm.h"
#include "ChartPoint.h"
#include "AbstractDialog.h"
#include "ObserverValue.h"

namespace angarawindows {
	ref class WaterPump : public AbstractDialog {
	public:
		WaterPump(int idLink);

		void init() override;
		void close() override;
		void save() override;
		//—ÎÛÊÂ·ÌÓÂ --------------------------------------
		WaterPumpForm^ form;
		int idLink;
		double resistance_min = 0;
		float QPoint = 0;
		float HInPoint = 0;
		float HOutPoint = 0;

		List<ChartPoint^>^ points_ = gcnew List<ChartPoint^>();
		ObserverValue<double>^ k;
		ObserverValue<double>^ pointer;
		ObserverValue<int>^ elemMove;
		ObserverValue<double>^ point_input_q;
		ObserverValue<double>^ point_input_h;
		ObserverValue<double>^ point_input_n;
		ObserverValue<double>^ point_input_m;
		//------------------------------------------------

		ObserverValue<String^>^ name;
		ObserverValue<String^>^ mark;
		ObserverValue<int>^ enable;

		ObserverValue<float>^ diameter_nominal;
		ObserverValue<float>^ diameter_current;
		ObserverValue<float>^ diameter_min;
		ObserverValue<float>^ diameter_max;

		ObserverValue<float>^ turnovers_nominal;
		ObserverValue<float>^ turnovers_current;
		ObserverValue<float>^ turnovers_min;
		ObserverValue<float>^ turnovers_max;

		ObserverValue<float>^ H0;
		ObserverValue<float>^ S;
		ObserverValue<float>^ N0;
		ObserverValue<float>^ C;

		ObserverValue<double>^ resistance_current;

		ObserverValue<float>^ efficiency_min;
		ObserverValue<float>^ efficiency_max;

		ObserverValue<float>^ pressure_in_min;
		ObserverValue<float>^ pressure_in_max;
		ObserverValue<float>^ pressure_out_min;
		ObserverValue<float>^ pressure_out_max;

		ObserverValue<List<ChartPoint^>^>^ points;

		void readStatusesDB(OleDbDataReader^ reader);
		void readDataDB(OleDbDataReader^ reader);
		System::Void FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
		System::Void exitButtonClick(System::Object^ sender, System::EventArgs^ e);

		//—Œ¡€“»ﬂ » ¬¿À»ƒ¿“Œ–€ -------------------------------------------
		String^ name_valide(String^ value, bool empty);

		String^ mark_valide(String^ value, bool empty);

		String^ five_points_valid(double value, bool empty);
		String^ five_points_valid(float value, bool empty);

		String^ diameter_valide(float value, bool empty);

		void diameter_nominal_event(ObserverValue<float>^ link);

		void set_k_event(ObserverValue<double>^ link);
		void set_k_event(ObserverValue<float>^ link);

		String^ diameter_max_min_valide(float value, bool empty);

		void diameter_max_event(ObserverValue<float>^ link);

		void diameter_min_event(ObserverValue<float>^ link);



		String^ turnovers_valide(float value, bool empty);

		void turnovers_nominal_event(ObserverValue<float>^ link);


		String^ turnovers_max_min_valide(float value, bool empty);

		void turnovers_max_event(ObserverValue<float>^ link);

		void turnovers_min_event(ObserverValue<float>^ link);



		void k_event(ObserverValue<double>^ link);

		void drawNominalPointCallBack(double q, double h, double n, double m);
		void drawExtendsPointCallBack(double q, double h, double n, double m);

		String^ resistance_current_valid(double value, bool empty);

		double resistance_current_PrepareToShow(double value, bool isShow);

		String^ efficiency_valide(float value, bool empty);

		void efficiency_event(ObserverValue<float>^ link);

		float efficiency_PrepareToShow(float value, bool isShow);


		String^ pressure_in_valide(float value, bool empty);

		String^ pressure_out_valide(float value, bool empty);

		void pressure_in_event(ObserverValue<float>^ link);

		void pressure_out_event(ObserverValue<float>^ link);

		void PointsCalculate(double q, double h, double n, int i);

		void points_event(ObserverValue<List<ChartPoint^>^>^ link);

		String^ point_input_valide(double value, bool empty);

		void point_input_event(ObserverValue<double>^ link);

		void elementMove_event(ObserverValue<int>^ value);

		String^ pointer_valid(double value, bool empty);

		void pointer_event(ObserverValue<double>^ link);

		//—Œ¡€“»ﬂ ‘Œ–Ã€ -----------------------------------------------------
		bool chartMove = true;
		bool isMove = false;
		bool isShift = false;

		System::Void PostPaint(System::Object^ sender, System::Windows::Forms::DataVisualization::Charting::ChartPaintEventArgs^ e);

		System::Void chart_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void chart_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void chart_MouseLeave(System::Object^ sender, System::EventArgs^ e);
		System::Void chart_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

		System::Void chart_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
		System::Void chart_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);

		System::Void chart_DoubleClick(System::Object^ sender, System::EventArgs^ e);

		void addEventsToChar(System::Windows::Forms::DataVisualization::Charting::Chart^ chart);
		void removeEventsToChar(System::Windows::Forms::DataVisualization::Charting::Chart^ chart);
	};
}