/*
	02. Strategy

	���ϴ� �κ��� Ŭ������ ����.

	-> ����ϴ� Ŭ���������� ������ ������ Ŭ���� �����͸� ������ ����Ѵ�.

*/


#if 0
/*
	1.	���� ��Ȳ :

		�̸�, �ֹε�Ϲ�ȣ�� �Է��ϴ� �ؽ�Ʈ â�� ����ٰ� ����.

		(01.TemplateMethod �� ������ ��Ȳ.)

*/
void getName() {
	/* �̸� �Է¹޴� ���� */
}

void getId() {
	/* �ֹε�Ϲ�ȣ �Է¹޴� ���� */
}

int main() {
	getName();
	getId();
}

/*
	�̷������� ¥��, getName()�� getId() ���� ������ ���� ����ϰ� �ȴ�.

	-> �ڵ� �ߺ��� ������.
*/
#endif



#if 0
/*
	2.	���ϴ� �κ�(Validation)�� Ŭ������ ��������.
*/
#include <string>
#include <conio.h>
#include <iostream>

/* Validator �������̽� */
class IValidator {
public:
	virtual ~IValidator() {}

	/* ���� �����Լ��� �����Ѵ�. */
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

	/* �⺻���δ� ��� ���� �� �Է¹޴´�. */
	std::cout << editor.getString() << std::endl;
	
	/* Validator�� �������ش�. */
	NumValidator num_validator;
	editor.setValidator(&num_validator);

	/* ���ڰ��� �Է¹޴´�. */
	std::cout << editor.getString() << std::endl;
}

/*
	���ϴ� �κ��� Ŭ������ ����
	-> ����ϴ� �������� �������̽��� �����͸� ������ ����ϴ� ����,

	Strategy �����̴�.
*/
#endif
