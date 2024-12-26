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

	cout << "=== 동적 배열 사용 ===" << endl;

	// 동적 메모리 할당
	Animal* team_dynamic[3];
	team_dynamic[0] = new Dog(); // Dog 객체 생성
	team_dynamic[1] = new Cat(); // Cat 객체 생성
	team_dynamic[2] = new Cow(); // Cow 객체 생성

	for (int i = 0; i < 3; i++) {
		team_dynamic[i]->makeSound();  // 다형성 적용, 각각의 makdSound() 호출
	}

	// 동적 메모리 해제
	for (int i = 0; i < 3; i++) {
		delete team_dynamic[i];      // 각각의 포인터 배열에 있는 객체를 메모리에서 소멸
	}

	return 0; // main은 유일하게 굳이 return을 안넣어도 되는데 외울때까지는 표시
};
