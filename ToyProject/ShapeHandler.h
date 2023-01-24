class ShapeHandler {
private:
	IShape* shape;
	void (ShapeHandler::*move_func[(Uint8)KeyEnum::Max])();
	void moveLeft();
	void moveRight();
	void moveDown();
	void moveSpaceBar();

public:
	ShapeHandler();
	~ShapeHandler() {}
	void move(KeyEnum key);
	void setShape(IShape* shape);
};