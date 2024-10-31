
---

### Пример 1: Класс `Date`

Класс `Date` позволяет управлять датой, контролируя значения дня, месяца и года.

```cpp
#include <iostream>

class Date {
private:
    int day;
    int month;
    int year;

public:
    // Геттеры
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    // Сеттеры с проверкой корректности
    void setDay(int d) {
        if (d > 0 && d <= 31) day = d;
        else std::cerr << "Некорректный день\n";
    }

    void setMonth(int m) {
        if (m > 0 && m <= 12) month = m;
        else std::cerr << "Некорректный месяц\n";
    }

    void setYear(int y) {
        if (y > 0) year = y;
        else std::cerr << "Некорректный год\n";
    }

    // Статический метод для проверки високосного года
    static bool isLeapYear(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }
};
```

**Пример использования:**

```cpp
int main() {
    Date date;
    date.setDay(25);
    date.setMonth(12);
    date.setYear(2023);

    std::cout << "Дата: " << date.getDay() << "/" << date.getMonth() << "/" << date.getYear() << std::endl;
    return 0;
}
```

Этот пример показывает, как ограничить доступ к полям и валидировать их значения. Также можно добавить статический метод для логики, связанной с объектами `Date`.

---

### Пример 2: Стек на односвязном списке

Перепишем стек на базе односвязного списка в ООП стиле. Это также демонстрирует принципы инкапсуляции и использования классов.

```cpp
#include <iostream>

class Node {
public:
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Stack {
private:
    Node* top; // указатель на верхний элемент стека

public:
    Stack() : top(nullptr) {}

    // Проверка, пуст ли стек
    bool isEmpty() const { return top == nullptr; }

    // Добавление элемента в стек
    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    // Удаление элемента из стека
    void pop() {
        if (isEmpty()) {
            std::cerr << "Стек пуст!\n";
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    // Получение верхнего элемента без удаления
    int peek() const {
        if (isEmpty()) {
            std::cerr << "Стек пуст!\n";
            return -1;
        }
        return top->data;
    }
};
```

**Пример использования:**

```cpp
int main() {
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Верхний элемент стека: " << stack.peek() << std::endl;
    stack.pop();
    std::cout << "Верхний элемент после pop: " << stack.peek() << std::endl;

    return 0;
}
```

---

