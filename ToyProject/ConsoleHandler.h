class ConsoleHandler {
private:
	ConsoleHandler() = delete;
	static const unsigned int Max_Buffer_Size;
public:
	static HANDLE& getHandle() {
		static HANDLE handle = NULL;
		if (handle == NULL) {
			handle = GetStdHandle(STD_OUTPUT_HANDLE);
		}
		return handle;
	}

	static void setConsoleSize(unsigned int width, unsigned int height);
	static void setTitle(const char* title);
};