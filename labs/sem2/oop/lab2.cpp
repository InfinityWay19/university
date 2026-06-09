#include <iostream>
#include <string>
#include <algorithm> // для std::reverse

class strtype_a {
private:
    std::wstring text; // используем wstring вместо string для поддержки кириллицы
    size_t invert_up_to;

public:
    // в конструктор передаем std::wstring
    strtype_a(std::wstring str, size_t up_to = 0) {
        text = str;
        
        // теперь text.length() возвращает именно количество СИМВОЛОВ, а не байт
        if (up_to == 0 || up_to > text.length()) {
            invert_up_to = text.length();
        } else {
            invert_up_to = up_to;
        }
    }

    // метод инвертирования теперь корректно перевернет широкие символы
    void invert() {
        std::reverse(text.begin(), text.begin() + invert_up_to);
    }

    // вывод широкой строки в поток
    void print() const {
        std::wcout << text << std::endl;
    }
};

int main() {
    // настраиваем локаль для корректного вывода широких символов (wstring) в консоль
    std::wcout.imbue(std::locale(""));

    std::wcout << L"--- Тест 1: Инвертирование всей строки (по умолчанию) ---" << std::endl;
    // префикс L перед строкой превращает её в широкий тип (const wchar_t*)
    strtype_a s1(L"Привет, мир!"); 
    std::wcout << L"Оригинал: ";
    s1.print();
    
    s1.invert();
    std::wcout << L"Результат: ";
    s1.print(); 
    std::wcout << std::endl;


    std::wcout << L"--- Тест 2: Инвертирование только первых 5 символов ---" << std::endl;
    // теперь число 5 означает именно первые 5 букв ("Приве")
    strtype_a s2(L"Привет, мир!", 5); 
    std::wcout << L"Оригинал: ";
    s2.print();
    
    s2.invert();
    std::wcout << L"Результат: ";
    s2.print(); 

    return 0;
}