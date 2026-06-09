#include <iostream>
using namespace std;

const int max_len = 10;

class dequeue {
    char s[max_len];
    int bottom, top;

public:
    void reset() {
        top = bottom = max_len / 2;
        top--;
    }

    bool empty() {
        return top < bottom;
    }

    bool full() {
        return top >= max_len - 1 || bottom <= 0;
    }

    void push_t(char c) {
        if (full()) {
            cout << "Очередь полна!" << endl;
            return;
        }
        s[++top] = c;
    }

    char pop_t() {
        if (empty()) {
            cout << "Очередь пуста!" << endl;
            return '\0';
        }
        return s[top--];
    }

    void push_b(char c) {
        if (full()) {
            cout << "Очередь полна!" << endl;
            return;
        }
        s[--bottom] = c;
    }

    char pop_b() {
        if (empty()) {
            cout << "Очередь пуста!" << endl;
            return '\0';
        }
        return s[bottom++];
    }

    char top_of() {
        if (empty()) {
            cout << "Очередь пуста!" << endl;
            return '\0';
        }
        return s[top];
    }

    char bottom_of() {
        if (empty()) {
            cout << "Очередь пуста!" << endl;
            return '\0';
        }
        return s[bottom];
    }

    void out_stack() {
        if (empty()) {
            cout << "Очередь пуста!" << endl;
            return;
        }
        cout << "Дно -> Вершина: ";
        for (int i = bottom; i <= top; i++) {
            cout << s[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    dequeue dq;
    dq.reset();

    cout << "=== Проверка empty и full ===" << endl;
    cout << "Пусто: " << (dq.empty() ? "да" : "нет") << endl;
    cout << "Полно: " << (dq.full() ? "да" : "нет") << endl;

    cout << "\n=== Проверка push_t (вталкивание на вершину) ===" << endl;
    dq.push_t('A');
    dq.push_t('B');
    dq.push_t('C');
    dq.out_stack();

    cout << "\n=== Проверка push_b (вталкивание на дно) ===" << endl;
    dq.push_b('X');
    dq.push_b('Y');
    dq.out_stack();

    cout << "\n=== Проверка top_of и bottom_of ===" << endl;
    cout << "Вершина: " << dq.top_of() << endl;
    cout << "Дно: " << dq.bottom_of() << endl;

    cout << "\n=== Проверка pop_t (выталкивание с вершины) ===" << endl;
    cout << "Вытолкнули с вершины: " << dq.pop_t() << endl;
    dq.out_stack();

    cout << "\n=== Проверка pop_b (выталкивание со дна) ===" << endl;
    cout << "Вытолкнули со дна: " << dq.pop_b() << endl;
    dq.out_stack();

    cout << "\n=== Проверка полного заполнения ===" << endl;
    dq.reset();
    for (int i = 0; i < max_len; i++) {
        dq.push_t('0' + i);
    }
    cout << "Полно: " << (dq.full() ? "да" : "нет") << endl;
    dq.push_t('Z');

    cout << "\n=== Проверка пустой очереди ===" << endl;
    dq.reset();
    dq.pop_t();

    return 0;
}