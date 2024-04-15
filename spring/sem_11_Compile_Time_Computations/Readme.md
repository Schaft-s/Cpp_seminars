0. **Гарантии безопасности**
1. **С лекции:**
    - Что такое литеральные типы?
    - consteval
    - constinit
    - constexpr
2. **Волшебное слово auto**
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
3. **Доп возможности auto** 
    - ещё можем ```int* p = new auto(5)```
    - в возвращаемом значении функции?
```cpp
auto g(T x) {
    if (x > 0) return 0;
    else return 1u;
}  
```
    - конкретно так нельзя, потому что статически типизированный язык, а тут разный тип может быть
```cpp
template <typename T>
auto g() {
    if constexpr (std::is_same_v<T, int>) return 0;
    else return 1u;
}  
```
    - это ок, if constexpr выполняется раньше
4. **trailing return type**
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
5.  **auto в принимаемых типах**
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
6.  **Шаблонные параметры???**
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
7.  
