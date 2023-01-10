
class OutputHandler {
private:
	OutputHandler() = delete;

public:
	static HANDLE& getHandle() {
		static HANDLE handle = NULL;
		if (handle == NULL) {
			handle = GetStdHandle(STD_OUTPUT_HANDLE);
		}
		return handle;
	}
};