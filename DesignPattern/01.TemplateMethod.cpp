/*
	01. Template Method

	변하는 부분을 virtual 함수로 구현.
	= 수정이 필요할 경우, 자식 클래스를 새로 만들어서 virtual 함수 재정의.
	
*/

#if 0
/*
	1.	문제 상황 :

		이름, 주민등록번호를 입력하는 텍스트 창을 만든다고 하자.

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
	2.	문제 상황 :

		코드 중복을 줄여보자	-> 상속을 통해 해결하자

		1) 일단 기본적인 클래스를 짜보자.

*/
#include <string>
#include <conio.h>

class Editor {
public:
	std::string getString() {
		std::string data;
		
		while (1) {
			char c = _getch();

			/* 종료 조건. (ex. 엔터키) */
			if (c == 13) break;

			/* 여기서 입력한 값을 저장할지 말지 체크해야함 */
			data += c;
		}

		return data;
	}
};

int main() {
	
}

/*
	입력받은 값을 체크받는 부분이 달라지는 부분이다.

	-> 이 부분을 virtual 함수로 선언하자.
*/
#endif


#if 0
/*
		2) virtual 함수로 구현해보자.
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

	/* 기본적으로는 모두 다 추가하는 것으로.. */
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
		값을 입력하고 엔터를 쳐보자. 

		처음엔 입력한 대로 출력될 것이고, 
		다음엔 숫자만 나올 것.
	*/
	std::cout << editor.getString() << std::endl;
	std::cout << num_editor.getString() << std::endl;
}

/*
	이렇게 변하는 부분을 virtual 함수로 분리하는 것이,

	template Method이다.
*/
#endif