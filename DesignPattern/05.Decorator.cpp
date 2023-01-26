/* 
	05. Decorator Pattern

	객체에 동적으로 기능을 추가할 수 있게 한다.

	상속에 의해 서브 클래스를 계속 늘리는 방법이 실용적이지 못할 때 유용하다.

	
	기능 추가를 위해 서브 클래스를 늘리는 방법이 아니라

	특정 기능을 하는 클래스를 이어 붙히는 방식으로 기능을 확장한다.
*/
#if 0
#include <stdio.h>
#include <string>

// 그림을 그려보자
class IBase {
public:
	virtual ~IBase() {}
	virtual void draw() = 0;
};

// 다 그리고 사인
class Sign : public IBase {
private:
	const char* sign;
public:
	Sign() = delete;
	Sign(const char* sign) : sign(sign) {}
	virtual void draw() override {
		printf("Drawing is Finished. my sign is ..%s\n", sign);
	}
};

class SettingDecorator : public IBase {
private:
	IBase* next_work;
public:
	SettingDecorator() : next_work(nullptr) {}
	virtual void draw() override {
		printf("Setting to Draw Picture.\n");
		next_work->draw();
	}
	void setNextWork(IBase& next_work) {
		this->next_work = &next_work;
	}
};

class FlowerDecorator : public IBase {
private:
	IBase* next_work;
public:
	FlowerDecorator() : next_work(nullptr) {}
	virtual void draw() override {
		printf("Draw Flower in my Picture\n");
		next_work->draw();
	}
	void setNextWork(IBase& next_work) {
		this->next_work = &next_work;
	}
};

class CatDecorator : public IBase {
private:
	IBase* next_work;
public:
	CatDecorator() : next_work(nullptr) {}
	virtual void draw() override {
		printf("Draw Cat in my Picture\n");
		next_work->draw();
	}
	void setNextWork(IBase& next_work) {
		this->next_work = &next_work;
	}
};

class DogDecorator : public IBase {
private:
	IBase* next_work;
public:
	DogDecorator() : next_work(nullptr) {}
	virtual void draw() override {
		printf("Draw Dog in my Picture\n");
		next_work->draw();
	}
	void setNextWork(IBase& next_work) {
		this->next_work = &next_work;
	}
};


int main() {
	SettingDecorator setting_decorator;
	FlowerDecorator flower_decorator;
	CatDecorator cat_decorator;
	DogDecorator dog_decorator;
	Sign sign("!!!");

	/* 
		꽃과 고양이만 그리고 싶다고 했을 떄,
		
		FlowerCat Class를 만드는 것이 아니라, 각각의 클래스를 이어 붙혀서 원하는 기능을 하도록 한다.
	*/
	{
		setting_decorator.setNextWork(flower_decorator);
		flower_decorator.setNextWork(cat_decorator);
		cat_decorator.setNextWork(sign);

		setting_decorator.draw();
	}

	/*
		원하는 기능을 이어붙혀서 사용할 수 있으므로 기능확장이 편하다.
	*/
	{
		setting_decorator.setNextWork(dog_decorator);
		dog_decorator.setNextWork(cat_decorator);
		cat_decorator.setNextWork(sign);

		setting_decorator.draw();
	}

	return 0;
}
#endif


/*
	아래는 조금 다른 방식으로 구현해보았다.
*/
#if 0
// Decorator
#include <stdio.h>
#include <string>

// 그림을 그려보자
class IBase {
public:
	virtual ~IBase() {}
	virtual void draw() = 0;
};

// 다 그리고 사인
class Sign : public IBase {
private:
	const char* sign;
public:
	Sign() = delete;
	Sign(const char* sign) : sign(sign) {}
	virtual void draw() override {
		printf("Drawing is Finished. my sign is ..%s\n", sign);
	}
};

class SettingDecorator : public IBase {
private:
	IBase* next_work;
public:
	SettingDecorator(SettingDecorator&) = delete;
	SettingDecorator(IBase* next_work) : next_work(next_work) {}
	virtual void draw() override {
		printf("Setting to Draw Picture.\n");
		next_work->draw();
	}
};

class CatDecorator : public IBase {
private:
	IBase* next_work;
public:
	CatDecorator(CatDecorator&) = delete;
	CatDecorator(IBase* next_work) : next_work(next_work) {}
	virtual void draw() override {
		printf("Draw Cat in my Picture\n");
		next_work->draw();
	}
};

class DogDecorator : public IBase {
private:
	IBase* next_work;
public:
	DogDecorator(DogDecorator&) = delete;
	DogDecorator(IBase* next_work) : next_work(next_work) {}
	virtual void draw() override {
		printf("Draw Dog in my Picture\n");
		next_work->draw();
	}
};


int main() {
	// 이 코드에서는 delete가 빠져있음.
	//   사용 후, 직접 메모리 해제를 시켜주거나,
	//   draw() 하면서 순차적으로 해제를 하도록 하면 될것으로 보임.
	Sign sign("!!!");


	{
		// 이렇게 쓰면, 사용 후, 직접 delete 가능함.
		DogDecorator* dog_decorator1 = new DogDecorator(&sign);
		DogDecorator* dog_decorator2 = new DogDecorator(dog_decorator1);
		DogDecorator* dog_decorator3 = new DogDecorator(dog_decorator2);
		DogDecorator* dog_decorator4 = new DogDecorator(dog_decorator3);
		SettingDecorator* setting_decorator = new SettingDecorator(dog_decorator4);

		setting_decorator->draw();
	}

	{
		// 이렇게 쓰면, draw 내부에서 delete 되도록 해야할듯.
		IBase* decorator = new DogDecorator(&sign);
		decorator = new CatDecorator(decorator);
		decorator = new DogDecorator(decorator);
		decorator = new CatDecorator(decorator);
		decorator = new SettingDecorator(decorator);

		decorator->draw();
	}
	return 0;
}
#endif