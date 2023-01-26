/* 
	05. Decorator Pattern

	��ü�� �������� ����� �߰��� �� �ְ� �Ѵ�.

	��ӿ� ���� ���� Ŭ������ ��� �ø��� ����� �ǿ������� ���� �� �����ϴ�.

	
	��� �߰��� ���� ���� Ŭ������ �ø��� ����� �ƴ϶�

	Ư�� ����� �ϴ� Ŭ������ �̾� ������ ������� ����� Ȯ���Ѵ�.
*/
#if 0
#include <stdio.h>
#include <string>

// �׸��� �׷�����
class IBase {
public:
	virtual ~IBase() {}
	virtual void draw() = 0;
};

// �� �׸��� ����
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
		�ɰ� ����̸� �׸��� �ʹٰ� ���� ��,
		
		FlowerCat Class�� ����� ���� �ƴ϶�, ������ Ŭ������ �̾� ������ ���ϴ� ����� �ϵ��� �Ѵ�.
	*/
	{
		setting_decorator.setNextWork(flower_decorator);
		flower_decorator.setNextWork(cat_decorator);
		cat_decorator.setNextWork(sign);

		setting_decorator.draw();
	}

	/*
		���ϴ� ����� �̾������ ����� �� �����Ƿ� ���Ȯ���� ���ϴ�.
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
	�Ʒ��� ���� �ٸ� ������� �����غ��Ҵ�.
*/
#if 0
// Decorator
#include <stdio.h>
#include <string>

// �׸��� �׷�����
class IBase {
public:
	virtual ~IBase() {}
	virtual void draw() = 0;
};

// �� �׸��� ����
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
	// �� �ڵ忡���� delete�� ��������.
	//   ��� ��, ���� �޸� ������ �����ְų�,
	//   draw() �ϸ鼭 ���������� ������ �ϵ��� �ϸ� �ɰ����� ����.
	Sign sign("!!!");


	{
		// �̷��� ����, ��� ��, ���� delete ������.
		DogDecorator* dog_decorator1 = new DogDecorator(&sign);
		DogDecorator* dog_decorator2 = new DogDecorator(dog_decorator1);
		DogDecorator* dog_decorator3 = new DogDecorator(dog_decorator2);
		DogDecorator* dog_decorator4 = new DogDecorator(dog_decorator3);
		SettingDecorator* setting_decorator = new SettingDecorator(dog_decorator4);

		setting_decorator->draw();
	}

	{
		// �̷��� ����, draw ���ο��� delete �ǵ��� �ؾ��ҵ�.
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