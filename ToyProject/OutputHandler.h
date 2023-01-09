
class OutputHandler {
private:
	OutputHandler() = delete;

public:
	static HANDLE& getInstance() {
		static HANDLE handle = NULL;
		if (handle == NULL) {
			handle = GetStdHandle(STD_OUTPUT_HANDLE);
		}
		return handle;
	}
};