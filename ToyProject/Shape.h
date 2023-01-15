class IShape {
public:
	virtual ~IShape() {}
	virtual void move(KeyEnum key) = 0;
};

class Rect : public IShape {
private:
	bool shape[2][2] = { {1, 1}, {1, 1} };
public:
	virtual void move(KeyEnum key) override;
};
