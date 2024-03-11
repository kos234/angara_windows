namespace angarawindows {
	ref class InputOutputListener {
	private:
		void Listener();

		System::Threading::Thread^ thread;
	public:
		InputOutputListener();
		static void write(System::String^ text);
	};
}