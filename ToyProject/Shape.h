constexpr Uint8 SHAPE_WIDTH = 4;
constexpr Uint8 SHAPE_HEIGHT = 4;

class IShape {
protected:
	Color color;
	bool shape[SHAPE_WIDTH][SHAPE_HEIGHT];

	//virtual ~IShape() {}
	//virtual Color color();
	//virtual void getShape();
};

class Rect : public IShape {
public:
	Rect();
};

