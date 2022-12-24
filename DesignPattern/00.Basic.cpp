/* 00. Basic */
#include <stdio.h>


/*
	1.	자식 클래스의 생성자는 부모 클래스의 생성자가 호출된 이후에 호출된다.
		자식 클래스의 소멸자의 마지막에 부모 클래스의 소멸자가 호출된다.

	명시적으로 부모 클래스의 생성자를 호출하지 않았다면,
	부모 클래스의 디폴트 생성자가 자동으로 호출된다.
*/
#if 0
class Parent
{
public:
	Parent() {
		printf("Create Parent\n");
	}
	~Parent() {
		printf("Delete Parent\n");
	}
};

class Child : public Parent
{
public:
	Child() {
		printf("Create Child\n");
	}
	/*  
	위는 아래와 동일하다.
	Child() : Parent() { ~~ }

	-> Child의 생성자가 호출되기 전에 Parent의 생성자가 호출된다.
	*/

	~Child() {
		printf("Delete Child\n");
	}
	/*
	위는 아래와 동일하다.	
	~Child() { ~~; Parent::~Parent(); }

	-> Child의 소멸자의 마지막에 Parent의 소멸자가 호출된다.
	*/
};

int main() {
	Child c;
}
#endif

/*
	2.	부모 클래스의 생성자를 명시적으로 호출하는 것이 의도하는 바를 확실히 수행할 수 있다.

	부모 클래스의 생성자가 여러 개 있을 때, 의도대로 행동하지 않을 수 있다.
*/
#if 0
class Parent
{
public:
	Parent(int n) {
		printf("Create Parent(int n)\n");
	}
	~Parent() {
		printf("Delete Parent\n");
	}
};

class Child : public Parent
{
public:
	Child(int n) :  Parent(n) {
		printf("Create Child(int n)\n");
	}
	/* 
	다음은 Error가 발생한다.
	Child(int n) {
		printf("Create Child(int n)\n");
	}

	위는 Parent의 default 생성자를 호출하게 되는데, 지금은 default 생성자가 없으므로 에러가 발생한다.
	*/

	~Child() {
		printf("Delete Child\n");
	}
};

int main() {
	Child c(0);
}
#endif

/*
	3.	부모 클래스의 생성자를 protected로 선언하는 것은 다음의 의미가 있다.
	 
		1) 자기자신의 객체는 생성할 수 없다.

		2) 부모 클래스를 상속받은 자식 클래스는 생성할 수 있다.

	즉, 부모 클래스를 추상적인 존재로 생각하여 직접 생성하지는 못 하게 하고
		자식 클래스를 통해서만 생성될 수 있도록 한다.
	
	-> 추상 클래스 / 인터페이스의 의미로 사용될 수 있다.
*/
#if 0
class Parent
{
protected:
	Parent(int n) {
		printf("Create Parent(int n)\n");
	}
	~Parent() {
		printf("Delete Parent\n");
	}
};

class Child : public Parent
{
public:
	Child(int n) : Parent(n) {
		printf("Create Child(int n)\n");
	}

	~Child() {
		printf("Delete Child\n");
	}
};

int main() {
	/*
	다음은 Error가 발생한다.
	Parent p(0);

	Parent 객체를 직접 생성할 수 없다.
	*/
	Child c(0);
}
#endif


/*
	4.	부모 클래스의 포인터로 자식 클래스를 가리킬 수 있다.

		반대는 안 된다.
*/
#if 0
class Parent
{
public:
	Parent(int n) {
		printf("Create Parent(int n)\n");
	}
	~Parent() {
		printf("Delete Parent\n");
	}
};

class Child : public Parent
{
public:
	Child(int n) : Parent(n) {
		printf("Create Child(int n)\n");
	}

	~Child() {
		printf("Delete Child\n");
	}
};

int main() {
	Parent* p = new Child(0);
	/* 
	다음은 에러가 발생한다.
	Child* c = new Parent(0);
	*/
}
#endif

/*
	5-1.	함수 콜에서 문제점
*/
#if 0
class Parent
{
public:
	void print() {
		printf("print() in Parent\n");
	}
	~Parent() {
		printf("Delete Parent\n");
	}
};

class Child : public Parent
{
public:
	void print() {
		printf("print() in Child\n");
	}
	~Child() {
		printf("Delete Child\n");
	}
};

int main() {
	Parent* p = new Child();

	p->print();
	/* 
	p가 Parent* 이므로 Parent의 print()가 호출된다.
	p가 가리키는 것이 Parent이기 때문에...
	*/

	delete p;
	/*
	delete에서도 큰 문제가 발생한다.
	그냥 Parent의 소멸자를 호출하기 때문이다.

	논리적으로는 Child의 소멸자가 호출되어야 한다.

	-> Parent* 인 p가 진짜 가리키고 있는 객체가 무엇인지 체크를 해야한다.

	*/
}
#endif


/*
	5-2.	Virtual 함수
		
			Virtual 함수는 실제 바라보고 있는 객체를 체크하여, 해당 객체의 함수를 불러준다.

			장점 : 위의 문제점을 해결 가능
			단점 : 성능 저하
*/
#if 0
class Parent
{
public:
	virtual void print() {
		printf("print() in Parent\n");
	}
	virtual ~Parent() {
		printf("Delete Parent\n");
	}
};

class Child : public Parent
{
public:
	virtual void prInt() {
		printf("print() in Child\n");
	}
	/* 
	재정의하는 함수 뒤에는 override를 붙히도록 하자.
	위처럼 오타를 내게되면 그냥 새로운 함수가 생긴다.

	override를 붙히게 되면 상속받은 virtual 함수와 비교해주기 때문에 실수를 줄일 수 있다.
	아래처럼 override를 붙히게되면 에러가 난다.

	virtual void prInt() override {
		printf("print() in Child\n");
	}
	*/
	virtual void print() override {
		printf("print() in Child\n");
	}
	virtual ~Child() override {
		printf("Delete Child\n");
	}
};

int main() {
	Parent* p = new Child();

	p->print();

	delete p;
}
#endif

/*
	순수 가상함수
	추상 클래스
	인터페이스 
*/
#if 0
class Parent
{
public:
	virtual ~Parent() {}

	virtual void PureVirtualFunc() = 0;
	/* 
	순수 가상함수 : 위처럼 = 0; 으로 끝나는 함수

	구현없이 선언만 되어있기 때문에 이 상태로는 호출해서 사용할 수 없다.

	사용하려는 곳에서 구현을 해주어야한다.
	*/
};

/*
	순수 가상함수가 하나라도 포함되어 있으면 추상 클래스라고 한다.

	추상 클래스/인터페이스가 혼용되는 경우도 있다고 하는데,
	
	인터페이스 : 멤버 변수 없이 순수 가상함수만 선언.
	추상 클래스 : 순수 가상함수 외에 다른 정보도 포함.

	순수 가상함수가 구현되지 않으면, 객체로 생성할 수 없다.
	그러나, 포인터로는 사용 가능.
*/

class Child : public Parent
{
public:
	virtual void PureVirtualFunc() {
		printf("PureVirtualFunc() in Child\n");
	}
};

int main() {
	/* 
	다음은 error이다.
	Parent parent;

	순수 가상함수를 구현하지 않음.
	*/
	
	
	Parent* p = new Child();
	/*
	객체 생성은 안되지만, 포인터로 사용은 가능하다.
	*/

	p->PureVirtualFunc();

	delete p;
}
#endif