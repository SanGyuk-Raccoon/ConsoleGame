class ShapeHandler {
private:
	void(*move_func[(unsigned int)KeyEnum::Max])() ;
public:
	ShapeHandler();
	~ShapeHandler();
	void move(KeyEnum key);
	void moveLeft();
	void moveRight();
	void moveDown();
	void moveSpaceBar();
};