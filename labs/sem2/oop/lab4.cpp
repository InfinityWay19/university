#include <iostream>
#include <vector>
#include <algorithm>

class IntSet {
private:
    std::vector<int> elements;

    bool contains(int val) const {
        return std::find(elements.begin(), elements.end(), val) != elements.end();
    }

public:
    IntSet() {}

    void add(int val) {
        if (!contains(val)) {
            elements.push_back(val);
        }
    }

    // а) Удаление элемента (операция -)
    IntSet operator-(int val) {
        IntSet newSet = *this;
        auto it = std::find(newSet.elements.begin(), newSet.elements.end(), val);
        if (it != newSet.elements.end()) {
            newSet.elements.erase(it);
        }
        return newSet; 
    }

    // б) Проверка наличия (операция /)
    bool operator/(int val) const {
        return contains(val);
    }

    // функция вывода конечного множества
    void printf() const {
        std::cout << "{ ";
        for (size_t i = 0; i < elements.size(); ++i) {
            std::cout << elements[i];
            if (i < elements.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " }" << std::endl;
    }
};

int main() {
    std::cout << "=== Задача 4: Множество целых чисел ===" << std::endl;

    IntSet mySet;
    mySet.add(10); mySet.add(20); mySet.add(30); mySet.add(40);

    std::cout << "Исходное множество: ";
    mySet.printf();

    std::cout << "\n--- Проверка наличия (операция /) ---" << std::endl;
    int searchNum = 20;
    if (mySet / searchNum) { 
        std::cout << "Элемент " << searchNum << " есть в множестве!" << std::endl;
    } else {
        std::cout << "Элемента " << searchNum << " нет в множестве." << std::endl;
    }

    std::cout << "\n--- Удаление элемента (операция -) ---" << std::endl;
    std::cout << "Удаляем число 20..." << std::endl;
    mySet = mySet - 20; 
    
    std::cout << "Конечное множество: ";
    mySet.printf();

    return 0;
}