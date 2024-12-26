#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
	virtual void makeSound() = 0;
};

class Dog : public Animal {
public:
	void makeSound() {
		cout << "Dog : Mung Mung!!" << endl;
	}
};

class Cat : public Animal {
public:
	void makeSound() {
		cout << "Cat : Meow Meow!!" << endl;
	}
};

class Cow : public Animal {
public:
	void makeSound() {
		cout << "Cow : Eumm Mow!!" << endl;
	}
};

void make(Animal* animal) {
	animal->makeSound();
}

int main() {

	cout << "=== ���� �迭 ��� ===" << endl;

	// ���� �޸� �Ҵ�
	Animal* team_dynamic[3];
	team_dynamic[0] = new Dog(); // Dog ��ü ����
	team_dynamic[1] = new Cat(); // Cat ��ü ����
	team_dynamic[2] = new Cow(); // Cow ��ü ����

	for (int i = 0; i < 3; i++) {
		team_dynamic[i]->makeSound();  // ������ ����, ������ makdSound() ȣ��
	}

	// ���� �޸� ����
	for (int i = 0; i < 3; i++) {
		delete team_dynamic[i];      // ������ ������ �迭�� �ִ� ��ü�� �޸𸮿��� �Ҹ�
	}

	return 0; // main�� �����ϰ� ���� return�� �ȳ־ �Ǵµ� �ܿﶧ������ ǥ��
};
