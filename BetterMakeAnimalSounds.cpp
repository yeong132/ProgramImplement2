#include <iostream>
#include <string>
#include <cstdlib> // rand(), srand()
#include <ctime>   // time()

using namespace std;

// ���α׷� ���� ������ ���� �����غ���..
// 1. createAnimal�� ������ ������ �����ȴ�!
// 2. �� ������ 10���� �������� ä���������� Zoo�� ����!
// 3. ������ �� ä������ createAnimal()�� addAnimal()�� ������ ���� �ʴ´�!
// 4. performActions()�� ��� �������� �����Ҹ��� ����Ѵ�!
// 5. Zoo�� �޸𸮿��� �Ҹ�Ǹ鼭 ���α׷��� ����ȴ�!

class Animal {
public:
	virtual void makeSound() = 0;
	virtual ~Animal() {};
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

// �������� �ִ� ��� �������� �ൿ�� �����ϴ� �Լ��� ZooŬ�������� ������ �ߴ�.
// �׷��� �ڿ����� ������ ������ �Ҹ��� ����ϴ� �Լ��� ��ü�Ǵ� �ּ�ó�� ���־���.
/*void make(Animal* animal) {
	animal->makeSound();
}*/

class Zoo {
private:
	Animal** animals; // ���� ��ü�� �����ϴ� ���� �迭 ������
	int animalCount;  // ���� ������ �����ϴ� ����
	int maxCapacity;  // ���� �迭�̴� �ִ� ũ�⸦ �����ؾ���(���� ����!)
public:
	// �����ڿ��� animalCount�� maxCapacity �ʱ�ȭ
	Zoo(int capacity) : animalCount(0), maxCapacity(capacity) {
		animals = new Animal * [maxCapacity]; // ���� �迭 ����
	} 

	// Zoo �Ҹ���
	// - Zoo ��ü�� �Ҹ�� ��, ���� ���Ϳ� ����� ��� ���� ��ü�� �޸𸮸� �����մϴ�.
	// - �޸� ������ �����ϱ� ���� ���� �Ҵ�� Animal ��ü�� `delete` �մϴ�.
	// - �Է� �Ű�����: ����
	// - ��ȯ��: ����
	~Zoo() {
		cout << "Zoo �Ҹ��ڰ� ȣ�� �Ǿ����ϴ�!" << endl;
		for (int i = 0; i < animalCount; i++) {
			delete animals[i]; // ������ ������� ���� ��ü�� �޸� ����
			cout << i + 1 << " ��° ������ �Ҹ�Ǿ����ϴ�!" << endl;
		}
		delete[] animals; // �迭 ��ü �޸� ����
		cout << "���� �迭�� �����ǰ� ��� ������ �޸𸮿��� �Ҹ�Ǿ����ϴ�!" << endl;
	}

	// ������ �������� �߰��ϴ� �Լ�
	// - Animal ��ü�� �����͸� �޾� ������ �迭�� �����մϴ�.
	// - ���� �����̶� ���� �� �߰��� �� �ֽ��ϴ�.
	// - �Է� �Ű�����: Animal* (�߰��� ���� ��ü)
	// - ��ȯ��: ����
	void addAnimal(Animal* animal) {
		if (animalCount < maxCapacity) {
			animals[animalCount] = animal; // ���� �߰�
			animalCount++;  // animalCount�� 1�� ����
		}
	}

	// �������� �ִ� ��� ������ �ൿ�� �����ϴ� �Լ�
	// - ��� ���� ��ü�� ���� ���������� �Ҹ��� ���� �����̴� ������ �����մϴ�.
	// - �Է� �Ű�����: ����
	// - ��ȯ��: ����
	void performActions() {
		for (int i = 0; i < animalCount; i++) {
			animals[i]->makeSound();
		}
	}

	int getMaxCapacity() {
		return maxCapacity;
	}
};

// ���� ������ �����ϴ� �Լ�
// - 0, 1, 2 �� �ϳ��� ������ �����Ͽ� ���� Dog, Cat, Cow ��ü �� �ϳ��� �������� �����մϴ�.
// - ������ ��ü�� Animal Ÿ���� �����ͷ� ��ȯ�˴ϴ�.
// - �Է� �Ű�����: ����
// - ��ȯ��: Animal* (������ ���� ��ü�� ������)
// ����
Animal* createRandomAnimal();

int main() {
	srand(time(0)); // ���� �õ� ���� (���� ���� ������ ���� �ʿ�)

	Zoo myZoo(5); // zoo ��ü ������ �� ������ ���� �� �ְ�! 10���� ����!
	
	// ������ ������ �����ϰ� zoo�� �߰��ؾ���
	for(int i = 0; i < myZoo.getMaxCapacity(); i++) {
		Animal* animal = createRandomAnimal();
		myZoo.addAnimal(animal);
	}

	// �������� ������ �������� �߰��� �Ǿ��ٸ� performAction()���� 
	// ��� ������ ������ �����Ѵ�.
	myZoo.performActions();
		
	// Zoo ��ü�� �Ҹ� (��ü ���(���� �޸𸮿� ����)���� ���������� �ڵ����� ~Zoo()�� ȣ��)
	// ���� ������ ������� ��ü�� �����Ǿ��ٸ� 
	// �������� delete myZoo; << �̷��� �Ҹ��ڸ� ȣ���ؾ��Ѵ�.

	return 0; // main�� �����ϰ� ���� return�� �ȳ־ �Ǵµ� �ܿﶧ������ ǥ��
};

// ����
Animal* createRandomAnimal() {
	//rand() �Լ��� ���� �����Ǵ� ���� : 0 ~ 32767
	int randomValue = rand() % 3; // (���� 0, 1, 2�� �������� ����)

	//  �𸣴°� �Ẹ�� �; switch�� �Ẹ�Ҵ�.
	switch (randomValue) {
		case 0: return new Dog();
		case 1: return new Cat();
		case 2: return new Cow();
		default: return nullptr;  
		// nullptr�� �����Ͱ� �ƹ��͵� ����Ű�� ������ ������ ���� null���̴�.
	}
}


// ���⵵ �䱸���׿� ���ϸ� ������ �� �ٲ� �ּ�ó���ߴ�.
// ������ main()�Լ��� �� �κ�
	/*cout << "=== ���� �迭 ��� ===" << endl;

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
	}*/