/*
	03. Composite

	객체의 포함 관계를 나타내는 패턴.

	객체 간 포함 관계가 tree구조로 구현.

	
	* 복합 객체/개별 객체가 공통적으로 상속받는 부모 클래스가 필요함.

*/


#if 0
#include <vector>
#include <string>
#include <iostream>

/*
	1.	문제 상황
		
		폴더와 파일의 용량을 확인할 수 있도록 해보자.

		폴더 : 복합 객체
		파일 : 개별 객체
		
		* 폴더 내에는 파일 뿐만 아니라 폴더도 포함될 수 있다.
		
*/

class Item {
private:
	std::string name;

public :
	Item(const char* name) : name(name) { }
	virtual ~Item() {}

	virtual size_t getSize() = 0;
};

class Folder : public Item {
private:
	std::vector<Item*> item_vector;

public:
	/* Item의 생성자를 사용할 수 있게 된다. */
	using Item::Item;

	void addItem(Item* item) {
		item_vector.push_back(item);
	}

	virtual size_t getSize() override {
		size_t ret = 0;
		for (Item* item : item_vector) {
			ret += item->getSize();
		}
		return ret;
	}
};

class File : public Item {
private:
	size_t size;
public:
	File(const char* name, size_t size) : Item(name), size(size) {}

	virtual size_t getSize() override {
		return size;
	}
};

int main() {
	Folder* root = new Folder("Root");

	Folder* folder_A = new Folder("Folder A");
	Folder* folder_B = new Folder("Folder B");
	
	/* Root에 Folder A를 추가한다. */
	root->addItem(folder_A);

	/* Folder A에 File을 2개 추가한다. */
	folder_A->addItem(new File("File A1", 1));
	folder_A->addItem(new File("File A2", 2));

	/* Folder A에 Folder B를 추가한다. */
	folder_A->addItem(folder_B);

	/* Folder B에 File을 3개 추가한다. */
	folder_B->addItem(new File("File B1", 3));
	folder_B->addItem(new File("File B2", 4));
	folder_B->addItem(new File("File B3", 5));

	Folder* folder_C = new Folder("Folder B");
	/* Root에 Folder C를 추가한다. */
	root->addItem(folder_C);

	/* Folder C에 File을 2개 추가한다. */
	folder_C->addItem(new File("File C1", 6));
	folder_C->addItem(new File("File C2", 7));


	std::cout << root->getSize() << std::endl;
	std::cout << folder_A->getSize() << std::endl;
	std::cout << folder_B->getSize() << std::endl;
	std::cout << folder_C->getSize() << std::endl;
}
/* 
	Item class를 부모 클래스로, Folder, File의 관계를 정의함. 

	복합 개체와 개별 객체의 사용법이 같고, ( = getSize() )

	복합 객체는 복합 객체를 포함할 수 있다. (Folder 내에 Folder가 있을 수 있다.)
*/
#endif