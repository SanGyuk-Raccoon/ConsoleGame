class IShape {
protected:
	Color color;
	bool shape[4][4];
};

class Rect : public IShape {
public:
	Rect();
};

