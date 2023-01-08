/* 
	04. Observer Pattern

	객체 사이의 1:N의 종속 관계를 정의.

	-> 객체가 변화할 때, 종속되어 있는 다른 객체들에게도 변화를 알려주는 방식

*/
#if 0
#include <stdio.h>
#include <unordered_set>

// 변화를 감지해야하는 객체
class IObserver {
public:
	virtual ~IObserver() {}
	virtual void update() = 0;
};

// 옵져버들이 보고 있는, 관심 있는 객체
class ISubject {
private:
	// 본인이 변화했을 때, 알려줘야할 객체들의 목록
	std::unordered_set<IObserver*> observer_set;

public:
	ISubject() {}
	~ISubject() {
		observer_set.clear();
	}

	void registerObserver(IObserver& observer) {
		observer_set.insert(&observer);
	}
	void removeObserver(IObserver& observer) {
		observer_set.erase(&observer);
	}
	//
	void notifyObserver() {
		for (IObserver* observer : observer_set) {
			observer->update();
		}
	}
};

/* 
	위의 인터페이스를 이용해서 간단한 예시를 만들어보자.


	* update()에 parameter를 넘겨주는 방식도 있지만,

	개인적으로는 observer 내에서 target 객체로 접근해서 필요한 정보만 쓰는게 더 좋아보여서

	아래처럼 구현했다.
*/

// Observer들이 바라볼 객체
class TargetSubject : public ISubject {
public:
	struct TargetInfo {
		int info1, info2;
		TargetInfo() : info1(0), info2(0) {}
	};

private:
	TargetInfo target_info;

public:
	void setInfo1(int value) {
		printf("Info1 is Changed ! (value:%d)\n", value);
		target_info.info1 = value;
		notifyObserver();
	}

	void setInfo2(int value) {
		printf("Info2 is Changed ! (value:%d)\n", value);
		target_info.info2 = value;
		notifyObserver();
	}

	TargetInfo& info() { return target_info; }
};

// Info1이 필요한 Observer A
class ObserverA : public IObserver {
private:
	TargetSubject* target;
	int info1;

public:
	ObserverA(TargetSubject& target) : target(&target) {
		target.registerObserver(*this);
	}
	~ObserverA() {
		target->removeObserver(*this);
	}

	void action() {
		printf("ObserverA : action(info1:%d)\n", info1);
	}

	virtual void update() override {
		if (info1 == target->info().info1) return;
		info1 = target->info().info1;
		action();
	}
};

// Info2가 필요한 Observer B
class ObserverB : public IObserver {
private:
	TargetSubject* target;
	int info2;

public:
	ObserverB(TargetSubject& target) : target(&target) {
		target.registerObserver(*this);
	}
	~ObserverB() {
		target->removeObserver(*this);
	}

	void action() {
		printf("ObserverB : action(info2:%d)\n", info2);
	}

	virtual void update() override {
		if (info2 == target->info().info2) return;
		info2 = target->info().info2;
		action();
	}
};

int main() {
	TargetSubject target_subject;
	ObserverA obs_A(target_subject);
	ObserverB obs_B(target_subject);

	target_subject.setInfo1(1);
	target_subject.setInfo2(1);

	return 0;
}
#endif