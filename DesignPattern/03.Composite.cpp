/*
	03. Composite

	��ü�� ���� ���踦 ��Ÿ���� ����.

	��ü �� ���� ���谡 tree������ ����.

	
	* ���� ��ü/���� ��ü�� ���������� ��ӹ޴� �θ� Ŭ������ �ʿ���.

*/


#if 0
#include <vector>
#include <string>
#include <iostream>

/*
	1.	���� ��Ȳ
		
		������ ������ �뷮�� Ȯ���� �� �ֵ��� �غ���.

		���� : ���� ��ü
		���� : ���� ��ü
		
		* ���� ������ ���� �Ӹ� �ƴ϶� ������ ���Ե� �� �ִ�.
		
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
	/* Item�� �����ڸ� ����� �� �ְ� �ȴ�. */
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
	
	/* Root�� Folder A�� �߰��Ѵ�. */
	root->addItem(folder_A);

	/* Folder A�� File�� 2�� �߰��Ѵ�. */
	folder_A->addItem(new File("File A1", 1));
	folder_A->addItem(new File("File A2", 2));

	/* Folder A�� Folder B�� �߰��Ѵ�. */
	folder_A->addItem(folder_B);

	/* Folder B�� File�� 3�� �߰��Ѵ�. */
	folder_B->addItem(new File("File B1", 3));
	folder_B->addItem(new File("File B2", 4));
	folder_B->addItem(new File("File B3", 5));

	Folder* folder_C = new Folder("Folder B");
	/* Root�� Folder C�� �߰��Ѵ�. */
	root->addItem(folder_C);

	/* Folder C�� File�� 2�� �߰��Ѵ�. */
	folder_C->addItem(new File("File C1", 6));
	folder_C->addItem(new File("File C2", 7));


	std::cout << root->getSize() << std::endl;
	std::cout << folder_A->getSize() << std::endl;
	std::cout << folder_B->getSize() << std::endl;
	std::cout << folder_C->getSize() << std::endl;
}
/* 
	Item class�� �θ� Ŭ������, Folder, File�� ���踦 ������. 

	���� ��ü�� ���� ��ü�� ������ ����, ( = getSize() )

	���� ��ü�� ���� ��ü�� ������ �� �ִ�. (Folder ���� Folder�� ���� �� �ִ�.)
*/
#endif