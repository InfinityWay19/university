#include <iostream>
#include <string>
#include <vector>

// базовый класс "Книга"
class Book {
protected:
    std::string title; // обычный string отлично работает с UTF-8 в Linux
    int year;

public:
    Book(std::string t = "Неизвестно", int y = 0) : title(t), year(y) {}
    virtual ~Book() {}

    virtual void printInfo() const {
        std::cout << "Название: " << title << ", Год издания: " << year;
    }
};

// производный класс "Данные автора"
class AuthorData : public Book {
private:
    std::string authorName;
    std::string authorCountry;

public:
    AuthorData(std::string t, int y, std::string name, std::string country)
        : Book(t, y), authorName(name), authorCountry(country) {}

    void printInfo() const override {
        Book::printInfo(); // вызов метода базового класса
        std::cout << ", Автор: " << authorName << " (" << authorCountry << ")";
    }
};

// производный класс "Индекс книги"
class BookIndex : public Book {
private:
    std::string libraryIndex;
    int shelfNumber;

public:
    BookIndex(std::string t, int y, std::string index, int shelf)
        : Book(t, y), libraryIndex(index), shelfNumber(shelf) {}

    void printInfo() const override {
        Book::printInfo(); // вызов метода базового класса
        std::cout << ", Индекс: " << libraryIndex << ", Полка: " << shelfNumber;
    }
};

int main() {
    std::cout << "=== Задача 3: Картотека ===" << std::endl << std::endl;

    std::vector<Book*> libraryCardCatalog;

    libraryCardCatalog.push_back(new AuthorData("Преступление и наказание", 1866, "Ф. Достоевский", "Россия"));
    libraryCardCatalog.push_back(new BookIndex("Чистый код", 2008, "УДК 004.42", 12));
    libraryCardCatalog.push_back(new AuthorData("Властелин колец", 1954, "Дж. Р. Р. Толкин", "Великобритания"));

    for (size_t i = 0; i < libraryCardCatalog.size(); ++i) {
        std::cout << "Запись №" << i + 1 << ": ";
        libraryCardCatalog[i]->printInfo(); 
        std::cout << std::endl;
    }

    for (Book* book : libraryCardCatalog) {
        delete book;
    }
    return 0;
}