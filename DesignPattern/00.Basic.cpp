/* 00. Basic */
#include <stdio.h>


/*
	1.	�ڽ� Ŭ������ �����ڴ� �θ� Ŭ������ �����ڰ� ȣ��� ���Ŀ� ȣ��ȴ�.
		�ڽ� Ŭ������ �Ҹ����� �������� �θ� Ŭ������ �Ҹ��ڰ� ȣ��ȴ�.

	��������� �θ� Ŭ������ �����ڸ� ȣ������ �ʾҴٸ�,
	�θ� Ŭ������ ����Ʈ �����ڰ� �ڵ����� ȣ��ȴ�.
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
	���� �Ʒ��� �����ϴ�.
	Child() : Parent() { ~~ }

	-> Child�� �����ڰ� ȣ��Ǳ� ���� Parent�� �����ڰ� ȣ��ȴ�.
	*/

	~Child() {
		printf("Delete Child\n");
	}
	/*
	���� �Ʒ��� �����ϴ�.	
	~Child() { ~~; Parent::~Parent(); }

	-> Child�� �Ҹ����� �������� Parent�� �Ҹ��ڰ� ȣ��ȴ�.
	*/
};

int main() {
	Child c;
}
#endif

/*
	2.	�θ� Ŭ������ �����ڸ� ��������� ȣ���ϴ� ���� �ǵ��ϴ� �ٸ� Ȯ���� ������ �� �ִ�.

	�θ� Ŭ������ �����ڰ� ���� �� ���� ��, �ǵ���� �ൿ���� ���� �� �ִ�.
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
	������ Error�� �߻��Ѵ�.
	Child(int n) {
		printf("Create Child(int n)\n");
	}

	���� Parent�� default �����ڸ� ȣ���ϰ� �Ǵµ�, ������ default �����ڰ� �����Ƿ� ������ �߻��Ѵ�.
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
	3.	�θ� Ŭ������ �����ڸ� protected�� �����ϴ� ���� ������ �ǹ̰� �ִ�.
	 
		1) �ڱ��ڽ��� ��ü�� ������ �� ����.

		2) �θ� Ŭ������ ��ӹ��� �ڽ� Ŭ������ ������ �� �ִ�.

	��, �θ� Ŭ������ �߻����� ����� �����Ͽ� ���� ���������� �� �ϰ� �ϰ�
		�ڽ� Ŭ������ ���ؼ��� ������ �� �ֵ��� �Ѵ�.
	
	-> �߻� Ŭ���� / �������̽��� �ǹ̷� ���� �� �ִ�.
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
	������ Error�� �߻��Ѵ�.
	Parent p(0);

	Parent ��ü�� ���� ������ �� ����.
	*/
	Child c(0);
}
#endif


/*
	4.	�θ� Ŭ������ �����ͷ� �ڽ� Ŭ������ ����ų �� �ִ�.

		�ݴ�� �� �ȴ�.
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
	������ ������ �߻��Ѵ�.
	Child* c = new Parent(0);
	*/
}
#endif

/*
	5-1.	�Լ� �ݿ��� ������
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
	p�� Parent* �̹Ƿ� Parent�� print()�� ȣ��ȴ�.
	p�� ����Ű�� ���� Parent�̱� ������...
	*/

	delete p;
	/*
	delete������ ū ������ �߻��Ѵ�.
	�׳� Parent�� �Ҹ��ڸ� ȣ���ϱ� �����̴�.

	�������δ� Child�� �Ҹ��ڰ� ȣ��Ǿ�� �Ѵ�.

	-> Parent* �� p�� ��¥ ����Ű�� �ִ� ��ü�� �������� üũ�� �ؾ��Ѵ�.

	*/
}
#endif


/*
	5-2.	Virtual �Լ�
		
			Virtual �Լ��� ���� �ٶ󺸰� �ִ� ��ü�� üũ�Ͽ�, �ش� ��ü�� �Լ��� �ҷ��ش�.

			���� : ���� �������� �ذ� ����
			���� : ���� ����
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
	�������ϴ� �Լ� �ڿ��� override�� �������� ����.
	��ó�� ��Ÿ�� ���ԵǸ� �׳� ���ο� �Լ��� �����.

	override�� ������ �Ǹ� ��ӹ��� virtual �Լ��� �����ֱ� ������ �Ǽ��� ���� �� �ִ�.
	�Ʒ�ó�� override�� �����ԵǸ� ������ ����.

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
	���� �����Լ�
	�߻� Ŭ����
	�������̽� 
*/
#if 0
class Parent
{
public:
	virtual ~Parent() {}

	virtual void PureVirtualFunc() = 0;
	/* 
	���� �����Լ� : ��ó�� = 0; ���� ������ �Լ�

	�������� ���� �Ǿ��ֱ� ������ �� ���·δ� ȣ���ؼ� ����� �� ����.

	����Ϸ��� ������ ������ ���־���Ѵ�.
	*/
};

/*
	���� �����Լ��� �ϳ��� ���ԵǾ� ������ �߻� Ŭ������� �Ѵ�.

	�߻� Ŭ����/�������̽��� ȥ��Ǵ� ��쵵 �ִٰ� �ϴµ�,
	
	�������̽� : ��� ���� ���� ���� �����Լ��� ����.
	�߻� Ŭ���� : ���� �����Լ� �ܿ� �ٸ� ������ ����.

	���� �����Լ��� �������� ������, ��ü�� ������ �� ����.
	�׷���, �����ͷδ� ��� ����.
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
	������ error�̴�.
	Parent parent;

	���� �����Լ��� �������� ����.
	*/
	
	
	Parent* p = new Child();
	/*
	��ü ������ �ȵ�����, �����ͷ� ����� �����ϴ�.
	*/

	p->PureVirtualFunc();

	delete p;
}
#endif