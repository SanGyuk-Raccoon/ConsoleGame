/*
	02. Strategy

	변하는 부분을 클래스로 구현.

	-> 사용하는 클래스에서는 위에서 구현한 클래스 포인터를 가지고 사용한다.

*/


#if 0
/*
	1.	문제 상황 :

		이름, 주민등록번호를 입력하는 텍스트 창을 만든다고 하자.

		(01.TemplateMethod 와 동일한 상황.)

*/
void getName() {
	/* 이름 입력받는 로직 */
}

void getId() {
	/* 주민등록번호 입력받는 로직 */
}

int main() {
	getName();
	getId();
}

/*
	이런식으로 짜면, getName()과 getId() 내부 로직은 거의 비슷하게 된다.

	-> 코드 중복이 많아짐.
*/
#endif



#if 0
/*
	2.	변하는 부분(Validation)을 클래스로 구현하자.
*/
#include <string>
#include <conio.h>
#include <iostream>

/* Validator 인터페이스 */
class IValidator {
public:
	virtual ~IValidator() {}

	/* 순수 가상함수로 선언한다. */
	virtual bool validate(char c) = 0;
};

class NumValidator : public IValidator{
public:
	virtual bool validate(char c) override {
		return isdigit(c);
	}
};
class Editor {
private:
	IValidator* validator;
public:
	Editor() : validator(nullptr) {}

	void setValidator(IValidator* validator) {
		this->validator = validator;
	}

	std::string getString() {
		std::string data;

		while (1) {
			char c = _getch();

			
			if (c == 13) break;

			if (validator == nullptr || validator->validate(c)) {
				data += c;
			}
		}

		return data;
	}
};

int main() {
	Editor editor;

	/* 기본으로는 모든 값을 다 입력받는다. */
	std::cout << editor.getString() << std::endl;
	
	/* Validator를 설정해준다. */
	NumValidator num_validator;
	editor.setValidator(&num_validator);

	/* 숫자값만 입력받는다. */
	std::cout << editor.getString() << std::endl;
}

/*
	변하는 부분을 클래스로 구현
	-> 사용하는 곳에서는 인터페이스의 포인터를 가지고 사용하는 것이,

	Strategy 패턴이다.
*/
#endif
