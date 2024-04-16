0. **Гарантии безопасности**
1. **С лекции:**
    - Что такое литеральные типы?
    - [constexpr](https://en.cppreference.com/w/cpp/language/constexpr)
    - [consteval](https://en.cppreference.com/w/cpp/language/consteval)
    - [constinit](https://en.cppreference.com/w/cpp/language/constinit)
    - [Факториал](https://rickywxg.github.io/2021/01/03/cpp-compile-time-computation.html) с С++98 до наших дней.
    - 
2. **constexpr** == *может* быть вычислено в compile-time.
    - нельзя вызывать не costexpr функции!  std::cout?
    - не constexpr конструкторы?  а что со стандартными? vector? string?
    - function-try-block до c++20
    - что с new? (файлик)
    - [virtual](https://www.cppstories.com/2021/constexpr-virtual/)?
    - Вопрос на удос:
```cpp
constexpr int sqr(int x){ return x*x }

int x;
std::cin >> x;
std::cout << sqr(x) << '\n';

constexpr int n = sqr(5);
std::array<int, n>  a;
```
3. **Вопрос на хор**
```cpp
const int i = 2;
const char array[ i == 2 ? 64 : throw exception() ] = {};
```
4. **Волшебное слово auto**
    - умеем объявлять переменные: ```auto x =...; auto* x = ...```
    - c & тоже умеем:
```cpp
template <typename T>
void f(T x) {}
auto x = 5;


template <typename T>
void f(const T& x) {}
const auto x& = 5;


template <typename T>
void f(T&& t) {}

auto&& t = x;
```
```cpp
template <typename Container>
void f(Container&& container) {
    for (auto&& value: container) { //... }  // ещё улучшить можно?
}
```
5. **Доп возможности auto** 
    - ещё можем ```int* p = new auto(5)```
    - в возвращаемом значении функции?
```cpp
auto g(T x) {
    if (x > 0) return 0;
    else return 1u;
}  
```
    - конкретно так нельзя, потому что статически типизированный язык, а тут разный тип может быть.
```cpp
template <typename T>
auto g() {
    if constexpr (std::is_same_v<T, int>) return 0;
    else return 1u;
}  
```
    - это ок, if constexpr выполняется раньше.
6. **trailing return type**
```cpp
template <typename T>
std:remove_reference_t<T>&&move(T&& value) {
  return static_cast<std::remove_reference_t<T>&&>(value);
}
// эквивалентно
template <typename T>
auto move(T&& value) -> std:remove_reference_t<T>&&
{
  return static_cast<std::remove_reference_t<T>&&>(value);
}
```
7.  **auto в принимаемых типах**
```cpp
void f(auto&& x) {}
// равносильно
template <typename T>
void f(T&& x) {}

// можно будет вызвать
f<int>(5);

// можно даже 
void f(auto&&... x) {}  // *восторженные крики*  // а мы так разве везде можем? ничего не сломали себе?
```
8.  **Шаблонные параметры???**
```cpp
template <auto N>
struct Example {};

Example<5> ei;
Example<'a'> ec;

-----------------------------
template<auto value> void func() {
    std::cout << value << std::endl;
}

func<5>(); // выводит 5
func<'a'>(); // выводит 'a'
```
9. **[decltype](https://en.cppreference.com/w/cpp/language/decltype)**
    - Compile-time
    - ```std::vector<decltype(x)> a```
    - **не отбрасывает ссылки!**
    - [статья](https://habr.com/ru/articles/206458/) про decltype и auto 2013 года - старая, "но не бесполезная".
  
```cpp
int x = 0;
int& y = x;
decltype(y) z = y;
decltype(x)& t = x;
// 4 одинаковые переменные?
decltype(x)&& t = x;  // ??? (std::move)
```
```cpp
// Костыль чтобы видеть что там за тип под decltype
template <typename T>
struct Debug {
    Debug() = delete;
}
Debug<decltype(expr)>();
```
10. **Вопрос на хор**
```cpp
decltype(throw 1)*p = &x;
```
11. **Вопрос на отл**
```cpp
int x = 0;
decltype(x) u = x;  // (x), ++x lvalue or rvalue x++, 
++u;
printf("%d %d", x,u);
```
12. **decltype в возвращаемом типе**
```cpp
template <typename T>
auto &(\&) getElement(Container&cont, size_t index)  // ссылку можно навесить, но не всегда будет работать.
-> decltype(cont[index])
{ return cont[index] }

decltype(auto) ... // ровно то же самое. == "выведи тип сам, но по правилам decltype, а не auto".
```
13. Бонусы
    - если кто-то сможет решить сt_prime короче чем в 26 строк (не учитываются include, pragma once, пропуски строк)
    - с меня ... (обсуждается)
    - [Лекция](https://www.youtube.com/watch?v=MT8IomEEZPY&ab_channel=%D0%9B%D0%B5%D0%BA%D1%82%D0%BE%D1%80%D0%B8%D0%B9%D0%A4%D0%9F%D0%9C%D0%98) Мещерина про Compile-time-computations.
    - Огромная [статья](https://habr.com/ru/articles/579490/) про развитие const_ (в ней есть код метода, решающий пол задачки ct_prime).
    - Ещё [статья](https://www.jacksondunstan.com/articles/5875), на английском, но суперподробная.
