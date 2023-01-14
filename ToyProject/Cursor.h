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
	
	void setVisibleOption(bool visiable);
	void setPosition(Uint16 x, Uint16 y);
	void setFontColor(Color font_color = Color::Gray, Color background_color = Color::Black);
};
