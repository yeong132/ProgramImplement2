#include <iostream>
#include <string>
#include <cstdlib> // rand(), srand()
#include <ctime>   // time()

using namespace std;

// 프로그램 동작 순서를 먼저 생각해보자..
// 1. createAnimal로 랜덤한 동물이 생성된다!
// 2. 그 동물이 10마리 정원으로 채워질때까지 Zoo로 들어간다!
// 3. 정원이 다 채워지면 createAnimal()과 addAnimal()이 동작이 되지 않는다!
// 4. performActions()로 모든 동물들의 울음소리를 출력한다!
// 5. Zoo가 메모리에서 소멸되면서 프로그램이 종료된다!

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

// 동물원에 있는 모든 동물들의 행동을 수행하는 함수를 Zoo클래스에서 만들라고 했다.
// 그러면 자연스레 기존의 동물의 소리를 출력하는 함수는 대체되니 주석처리 해주었다.
/*void make(Animal* animal) {
	animal->makeSound();
}*/

class Zoo {
private:
	Animal** animals; // 동물 객체를 저장하는 동적 배열 포인터
	int animalCount;  // 동물 개수를 저장하는 변수
	int maxCapacity;  // 동적 배열이니 최대 크기를 설정해야함(정원 설정!)
public:
	// 생성자에서 animalCount와 maxCapacity 초기화
	Zoo(int capacity) : animalCount(0), maxCapacity(capacity) {
		animals = new Animal * [maxCapacity]; // 동적 배열 생성
	} 

	// Zoo 소멸자
	// - Zoo 객체가 소멸될 때, 동물 벡터에 저장된 모든 동물 객체의 메모리를 해제합니다.
	// - 메모리 누수를 방지하기 위해 동적 할당된 Animal 객체를 `delete` 합니다.
	// - 입력 매개변수: 없음
	// - 반환값: 없음
	~Zoo() {
		cout << "Zoo 소멸자가 호출 되었습니다!" << endl;
		for (int i = 0; i < animalCount; i++) {
			delete animals[i]; // 생성된 순서대로 동물 객체의 메모리 해제
			cout << i + 1 << " 번째 동물이 소멸되었습니다!" << endl;
		}
		delete[] animals; // 배열 자체 메모리 해제
		cout << "동물 배열이 삭제되고 모든 동물이 메모리에서 소멸되었습니다!" << endl;
	}

	// 동물을 동물원에 추가하는 함수
	// - Animal 객체의 포인터를 받아 포인터 배열에 저장합니다.
	// - 같은 동물이라도 여러 번 추가될 수 있습니다.
	// - 입력 매개변수: Animal* (추가할 동물 객체)
	// - 반환값: 없음
	void addAnimal(Animal* animal) {
		if (animalCount < maxCapacity) {
			animals[animalCount] = animal; // 동물 추가
			animalCount++;  // animalCount가 1씩 증가
		}
	}

	// 동물원에 있는 모든 동물의 행동을 수행하는 함수
	// - 모든 동물 객체에 대해 순차적으로 소리를 내고 움직이는 동작을 실행합니다.
	// - 입력 매개변수: 없음
	// - 반환값: 없음
	void performActions() {
		for (int i = 0; i < animalCount; i++) {
			animals[i]->makeSound();
		}
	}

	int getMaxCapacity() {
		return maxCapacity;
	}
};

// 랜덤 동물을 생성하는 함수
// - 0, 1, 2 중 하나의 난수를 생성하여 각각 Dog, Cat, Cow 객체 중 하나를 동적으로 생성합니다.
// - 생성된 객체는 Animal 타입의 포인터로 반환됩니다.
// - 입력 매개변수: 없음
// - 반환값: Animal* (생성된 동물 객체의 포인터)
// 선언
Animal* createRandomAnimal();

int main() {
	srand(time(0)); // 랜덤 시드 설정 (랜덤 동물 생성을 위해 필요)

	Zoo myZoo(5); // zoo 객체 생성할 때 정원을 정할 수 있게! 10마리 설정!
	
	// 랜덤한 동물을 생성하고 zoo에 추가해야함
	for(int i = 0; i < myZoo.getMaxCapacity(); i++) {
		Animal* animal = createRandomAnimal();
		myZoo.addAnimal(animal);
	}

	// 동물원의 동물이 정원까지 추가가 되었다면 performAction()으로 
	// 모든 동물의 동작을 실행한다.
	myZoo.performActions();
		
	// Zoo 객체는 소멸 (객체 방식(스택 메모리에 저장)으로 생성했으니 자동으로 ~Zoo()를 호출)
	// 만약 포인터 방식으로 객체가 생성되었다면 
	// 수동으로 delete myZoo; << 이렇게 소멸자를 호출해야한다.

	return 0; // main은 유일하게 굳이 return을 안넣어도 되는데 외울때까지는 표시
};

// 구현
Animal* createRandomAnimal() {
	//rand() 함수에 의해 생성되는 난수 : 0 ~ 32767
	int randomValue = rand() % 3; // (값이 0, 1, 2로 나오도록 설정)

	//  모르는걸 써보고 싶어서 switch를 써보았다.
	switch (randomValue) {
		case 0: return new Dog();
		case 1: return new Cat();
		case 2: return new Cow();
		default: return nullptr;  
		// nullptr은 포인터가 아무것도 가리키지 않을때 포인터 전용 null값이다.
	}
}


// 여기도 요구사항에 의하면 동작이 싹 바뀌어서 주석처리했다.
// 기존에 main()함수에 들어간 부분
	/*cout << "=== 동적 배열 사용 ===" << endl;

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
	}*/