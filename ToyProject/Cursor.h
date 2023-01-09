class Cursor {
private:
	Cursor() {}
	Cursor(const Cursor&) = delete;
	void operator=(const Cursor&) = delete;

public:
	static Cursor& getInstance() {
		static Cursor cursor;
		return cursor;
	}

	void setVisibleOption(bool visible);
	void setPosition(int x, int y);
	void setFontColor(ColorType font_color = ColorType::Gray, ColorType background_color = ColorType::Black);
};
