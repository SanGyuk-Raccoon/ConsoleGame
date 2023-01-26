/*
	06. Singleton Pattern

	싱글턴 패턴은 클래스를 단 하나만 만들어 사용하도록 한다.

	프로그램에서 딱 하나만 있어야하는 경우에 적용하면 된다.

	
	어디서나 생성하지 못 하게 만들기 위해 생성자를 private으로 선언하고,

	class를 반환하는 static method를 구현하여 사용한다.
*/

#if 0
#include <stdio.h>
class Singleton {
private:
	Singleton() {}
	// 받아온 싱글턴 클래스를 복사하지 못 하도록 복사 생성자 삭제
	Singleton(const Singleton&) = delete;
	// 할당 연산자 제거
	void operator=(const Singleton&) = delete;
	// 이게 이 프로그램에 유일한 Singleton 클래스가 될 것.
	static Singleton* unique_class;

public:
	static Singleton& getInstance() {
		// 없다면 생성해준 뒤, 반환한다.
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
	// 이렇게 쓰거나,
	Singleton::getInstance().hello();

	// ref로 받아와서 사용은 가능.
	Singleton& singleton_ref = Singleton::getInstance();
	singleton_ref.hello();

	// 하지만, 이렇게하면 복사가 되기 때문에 사용하면 안 된다.
	// '유일'이라는 싱글턴 패턴 규칙을 위배함.
	// Singleton singleton_copy = Singleton::getInstance();
}
#endif

// 하지만, 위의 싱글턴은 문제가 있다.
#if 0
#include <stdio.h>
class Singleton {
private:
	Singleton() {
		// 만약, 생성자에서 시간이 꽤 걸린다면?? 
	}
	Singleton(const Singleton&) = delete;
	void operator=(const Singleton&) = delete;

	static Singleton* unique_class;

public:
	// + 멀티 스레딩 환경에서 getInstance를 여러군데에서 호출했다면?
	// 클래스가 생성 중에 또 호출을 한다면, 아직 nullptr이기 때문에 또 생성할 것이다.
	// -> 클래스가 유일하지 않다.
	// -> 멀티 스레딩 환경에서는 불완전함.
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

// 최종 형태 : Mayer Singleton
#if 1
#include <stdio.h>
class Singleton {
private:
	Singleton() {}
	Singleton(const Singleton&) = delete;
	void operator=(const Singleton&) = delete;

public:
	static Singleton& getInstance() {
		// 굳이 new 해줄필요 없이, static 변수로 바로 가지고 있게 한다.
		// Java를 많이 써보진 않았지만, 첫번째 케이스는 Java의 느낌이 난다.
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