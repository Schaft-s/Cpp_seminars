0. Прошлая пара
1. **std::enable_if** — это вспомогательный шаблон типов, используемый в C++, который позволяет включать или исключать функции из компиляции на основе значения времени компиляции
```cpp
#include <type_traits>
#include <iostream>

template<typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
void printNumber(T number) {
    std::cout << "Number: " << number << std::endl;
}

int main() {
    printNumber(123);    // Работает
    printNumber(45.67);  // Работает
    // printNumber("test"); // Ошибка компиляции, не является арифметическим типом
}

```
2. **conditional** - позволяет выбрать один из двух типов в зависимости от булевого значения, заданного в качестве первого параметра. Если значение истинно, выбирается первый тип, если ложно — второй.
```cpp
#include <type_traits>
#include <iostream>

template<bool B>
using TypeChooser = std::conditional_t<B, int, double>;

int main() {
    TypeChooser<true> a = 10;   // тип int
    TypeChooser<false> b = 3.14; // тип double

    std::cout << "a: " << a << ", b: " << b << std::endl;
}
```
3. **void_t**
```cpp
#include <iostream>
#include <type_traits>

template<typename T, typename = void>
struct HasSerialize : std::false_type {};

template<typename T>
struct HasSerialize<T, std::void_t<decltype(std::declval<T>().serialize())>> : std::true_type {};

class MyClass {
public:
    void serialize() {
        std::cout << "Serialization done." << std::endl;
    }
};

class MyOtherClass {
};

int main() {
    std::cout << "Has serialize MyClass: " << HasSerialize<MyClass>::value << std::endl;     // выводит 1 (true)
    std::cout << "Has serialize MyOtherClass: " << HasSerialize<MyOtherClass>::value << std::endl; // выводит 0 (false)
}

```
Здесь, если у класса есть метод serialize, специализация HasSerialize для std::void_t<decltype(std::declval<T>().serialize())> будет успешной, и HasSerialize<T> будет наследовать std::true_type. Если метода нет, компиляция этой специализации провалится, и будет использована базовая специализация, наследующая std::false_type.
4. Всякое
