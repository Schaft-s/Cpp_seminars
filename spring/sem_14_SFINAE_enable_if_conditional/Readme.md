0. **Прошлая пара**
    - SFINAE - ?
    - declval + decltype
    - CRTP
1. [**std::enable_if**](https://en.cppreference.com/w/cpp/types/enable_if) — это вспомогательный шаблон типов, используемый в C++, который позволяет включать или исключать функции из компиляции на основе значения времени компиляции
- Реализация
```cpp
template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };
```
- Пример 1
```cpp
template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
func(T value) {
    // implementation for integral types
}
template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
func(T value) {
    // implementation for floating-point types
}
```
- Пример 2
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
В этом примере мы используем std::enable_if для определения двух реализаций функции func: одна для целочисленных типов, а другая для типов с плавающей запятой
2. [**conditional**](https://en.cppreference.com/w/cpp/types/conditional) - позволяет выбрать один из двух типов в зависимости от булевого значения, заданного в качестве первого параметра. Если значение истинно, выбирается первый тип, если ложно — второй.
- Реализация
```cpp
template<bool B, class T, class F>
struct conditional { typedef T type; };

template<class T, class F>
struct conditional<false, T, F> { typedef F type; };
```
- Пример 1
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
- Пример 2
```cpp
template<typename T>
typename std::conditional<std::is_integral<T>::value, int, double>::type
func(T value) {
    // implementation for integral types
}

template<typename T>
typename std::conditional<std::is_floating_point<T>::value, int, double>::type
func(T value) {
    // implementation for floating-point types
}
```
3. [**void_t**](https://en.cppreference.com/w/cpp/types/void_t)
- Реализация
```cpp
template<typename...>
using void_t = void;
```
- Пример 1
```cpp
template<typename T, typename = void>
struct has_size : std::false_type {};

template<typename T>
struct has_size<T, void_t<decltype(std::declval<T>().size())>>
: std::true_type {};

template<typename T>
void func(T&& value) {
    if constexpr (has_size<std::remove_reference_t<T>>::value) {
        // implementation for types with size() method
    } else {
        // implementation for types without size() method
    }
}
```
В этом примере мы используем void_t для проверки того, имеет ли тип T метод size. Если тип T имеет метод size, то шаблон has_size будет наследовать std::true_type, иначе - std::false_type. Далее мы определяем шаблон func, который выбирает правильную реализацию в зависимости от того, имеет ли тип T метод size. Если тип T имеет метод size, то используется первая реализация, иначе - вторая реализация.

4. Всякое  
- [**std::conjunction**](https://en.cppreference.com/w/cpp/types/conjunction) - это шаблон из стандартной библиотеки C++, который используется для проверки того, что все предикаты в списке являются истинными. Этот шаблон принимает произвольное количество параметров, каждый из которых представляет собой предикат. Результатом работы шаблона является логическое И всех предикатов.
Реализация
```cpp
template<class...>
struct conjunction : std::true_type {};

template<class B1>
struct conjunction<B1> : B1 {};

template<class B1, class... Bn>
struct conjunction<B1, Bn...>
: std::conditional_t<bool(B1::value), conjunction<Bn...>, B1> {};
```
Пример
```cpp
template<typename T>
void func(T&& value) {
    using is_integral = std::is_integral<std::remove_reference_t<T>>;
    using is_signed = std::is_signed<std::remove_reference_t<T>>;
    using is_not_bool = std::negation<std::is_same<std::remove_reference_t<T>, bool>>;
    using is_valid_type = std::conjunction<is_integral, is_signed, is_not_bool>;

    if constexpr (is_valid_type::value) {
        // implementation for valid types
    } else {
        // implementation for invalid types
    }
}
```
В этом примере мы определяем функцию func, которая выбирает правильную реализацию в зависимости от того, является ли тип T целочисленным и подписанным, но не является bool. Мы используем std::conjunction для проверки всех этих условий, а затем используем результат проверки для выбора правильной реализации.
