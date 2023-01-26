/*
	06. Singleton Pattern

	�̱��� ������ Ŭ������ �� �ϳ��� ����� ����ϵ��� �Ѵ�.

	���α׷����� �� �ϳ��� �־���ϴ� ��쿡 �����ϸ� �ȴ�.

	
	��𼭳� �������� �� �ϰ� ����� ���� �����ڸ� private���� �����ϰ�,

	class�� ��ȯ�ϴ� static method�� �����Ͽ� ����Ѵ�.
*/

#if 0
#include <stdio.h>
class Singleton {
private:
	Singleton() {}
	// �޾ƿ� �̱��� Ŭ������ �������� �� �ϵ��� ���� ������ ����
	Singleton(const Singleton&) = delete;
	// �Ҵ� ������ ����
	void operator=(const Singleton&) = delete;
	// �̰� �� ���α׷��� ������ Singleton Ŭ������ �� ��.
	static Singleton* unique_class;

public:
	static Singleton& getInstance() {
		// ���ٸ� �������� ��, ��ȯ�Ѵ�.
		if (unique_class == nullptr) {
			unique_class = new Singleton();
		}
		return *unique_class;
	}

	void hello() {
		printf("Hello, Singleton\n");
	}
};
Singleton* Singleton::unique_class = nullptr;


int main() {
	// �̷��� ���ų�,
	Singleton::getInstance().hello();

	// ref�� �޾ƿͼ� ����� ����.
	Singleton& singleton_ref = Singleton::getInstance();
	singleton_ref.hello();

	// ������, �̷����ϸ� ���簡 �Ǳ� ������ ����ϸ� �� �ȴ�.
	// '����'�̶�� �̱��� ���� ��Ģ�� ������.
	// Singleton singleton_copy = Singleton::getInstance();
}
#endif

// ������, ���� �̱����� ������ �ִ�.
#if 0
#include <stdio.h>
class Singleton {
private:
	Singleton() {
		// ����, �����ڿ��� �ð��� �� �ɸ��ٸ�?? 
	}
	Singleton(const Singleton&) = delete;
	void operator=(const Singleton&) = delete;

	static Singleton* unique_class;

public:
	// + ��Ƽ ������ ȯ�濡�� getInstance�� ������������ ȣ���ߴٸ�?
	// Ŭ������ ���� �߿� �� ȣ���� �Ѵٸ�, ���� nullptr�̱� ������ �� ������ ���̴�.
	// -> Ŭ������ �������� �ʴ�.
	// -> ��Ƽ ������ ȯ�濡���� �ҿ�����.
	static Singleton& getInstance() {
		if (unique_class == nullptr) {
			unique_class = new Singleton();
		}
		return *unique_class;
	}

	void hello() {
		printf("Hello, Singleton\n");
	}
};
Singleton* Singleton::unique_class = nullptr;

#endif

// ���� ���� : Mayer Singleton
#if 1
#include <stdio.h>
class Singleton {
private:
	Singleton() {}
	Singleton(const Singleton&) = delete;
	void operator=(const Singleton&) = delete;

public:
	static Singleton& getInstance() {
		// ���� new �����ʿ� ����, static ������ �ٷ� ������ �ְ� �Ѵ�.
		// Java�� ���� �Ẹ�� �ʾ�����, ù��° ���̽��� Java�� ������ ����.
		static Singleton unique_class;
		return unique_class;
	}

	void hello() {
		printf("Hello, Singleton\n");
	}
};

int main() {
	Singleton::getInstance().hello();

	Singleton& singleton_ref = Singleton::getInstance();
	singleton_ref.hello();
}
#endif