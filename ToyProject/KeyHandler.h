enum class KeyEnum : char {
	ExpandKey = -32,
	None = 0,
	Enter = 13,
	SpaceBar = 32,
	Up = 72,
	Down = 80,
	Left = 75,
	Right = 77,
};

class KeyHandler {
private:
	static bool isValidKey(char c);
public:
	static KeyEnum getKey();
};