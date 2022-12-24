/*
	01. Template Method

	���ϴ� �κ��� virtual �Լ��� ����.
	= ������ �ʿ��� ���, �ڽ� Ŭ������ ���� ���� virtual �Լ� ������.
	
*/

#if 0
/*
	1.	���� ��Ȳ :

		�̸�, �ֹε�Ϲ�ȣ�� �Է��ϴ� �ؽ�Ʈ â�� ����ٰ� ����.

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
	2.	���� ��Ȳ :

		�ڵ� �ߺ��� �ٿ�����	-> ����� ���� �ذ�����

		1) �ϴ� �⺻���� Ŭ������ ¥����.

*/
#include <string>
#include <conio.h>

class Editor {
public:
	std::string getString() {
		std::string data;
		
		while (1) {
			char c = _getch();

			/* ���� ����. (ex. ����Ű) */
			if (c == 13) break;

			/* ���⼭ �Է��� ���� �������� ���� üũ�ؾ��� */
			data += c;
		}

		return data;
	}
};

int main() {
	
}

/*
	�Է¹��� ���� üũ�޴� �κ��� �޶����� �κ��̴�.

	-> �� �κ��� virtual �Լ��� ��������.
*/
#endif


#if 0
/*
		2) virtual �Լ��� �����غ���.
*/
#include <string>
#include <iostream>
#include <conio.h>

class Editor {
public:
	std::string getString() {
		std::string data;

		while (1) {
			char c = _getch();

			if (c == 13) break;

			if (validate(c) == false) continue;
			data += c;
		}

		return data;
	}

	/* �⺻�����δ� ��� �� �߰��ϴ� ������.. */
	virtual bool validate(char c) { return true; }
};

class NumEditor : public Editor {
	virtual bool validate(char c) override {
		return isdigit(c);
	}
};

int main() {
	Editor editor;
	NumEditor num_editor;

	/* 
		���� �Է��ϰ� ���͸� �ĺ���. 

		ó���� �Է��� ��� ��µ� ���̰�, 
		������ ���ڸ� ���� ��.
	*/
	std::cout << editor.getString() << std::endl;
	std::cout << num_editor.getString() << std::endl;
}

/*
	�̷��� ���ϴ� �κ��� virtual �Լ��� �и��ϴ� ����,

	template Method�̴�.
*/
#endif