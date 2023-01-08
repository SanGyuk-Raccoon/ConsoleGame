/* 
	04. Observer Pattern

	��ü ������ 1:N�� ���� ���踦 ����.

	-> ��ü�� ��ȭ�� ��, ���ӵǾ� �ִ� �ٸ� ��ü�鿡�Ե� ��ȭ�� �˷��ִ� ���

*/
#if 0
#include <stdio.h>
#include <unordered_set>

// ��ȭ�� �����ؾ��ϴ� ��ü
class IObserver {
public:
	virtual ~IObserver() {}
	virtual void update() = 0;
};

// ���������� ���� �ִ�, ���� �ִ� ��ü
class ISubject {
private:
	// ������ ��ȭ���� ��, �˷������ ��ü���� ���
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
	���� �������̽��� �̿��ؼ� ������ ���ø� ������.


	* update()�� parameter�� �Ѱ��ִ� ��ĵ� ������,

	���������δ� observer ������ target ��ü�� �����ؼ� �ʿ��� ������ ���°� �� ���ƺ�����

	�Ʒ�ó�� �����ߴ�.
*/

// Observer���� �ٶ� ��ü
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

// Info1�� �ʿ��� Observer A
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

// Info2�� �ʿ��� Observer B
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