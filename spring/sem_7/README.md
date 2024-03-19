0. Прошлое занятие: 
    - Что такое универсальные ссылки? 
    - Зачем они нужны? 
    - Как их использовать? 
1. Прошедшая лекция :
    - operator new, delete 
    - operator new[] - в чём отличие?
    - placement new ?  ```void* operator new(size_t count, void* ptr);```
    - 
```c++
auto single = operator new(sizeof(T));
auto array = operator new(sizeof(T) * n);
operator delete(single); // принимает void*
operator delete(array);
```
2. Выравнивание
   - [по-человечески](https://ru.stackoverflow.com/questions/435726/Выравнивание-данных)
   - **aligned**: int - лежит хорошо, если адрес кратен 4 (замедляется работа, если не так. зависит от процессора)
   - new и malloc возвращают выровненные адреса
   - [std::max_align_t](https://en.cppreference.com/w/cpp/types/max_align_t) == long double == int128_t == 16 - константа системы
   - функция [alignof](https://en.cppreference.com/w/cpp/language/alignof)(int) == 4
   - ключевое слово alignas(... // max_align_t):  
     struct alignas(..) Stack{}
   - Можно ли выравнивать больше чем на max_align_t ? Зачем ?
  ```c++
#include <iostream>

struct alignas(16) AlignedStruct {
    int x;
};

int main() {
    AlignedStruct s;
    std::cout << "Адрес объекта s: " << &s << std::endl;
    std::cout << "Выравнивание объекта s: " << alignof(s) << std::endl;

    return 0;
}

  ```
- Есть специальная форма new с выравниванием
```c++
#include <new>

void* operator new(std::size_t size, std::align_val_t alignment);
void operator delete(void* ptr, std::align_val_t alignment) noexcept;
``` 
3. Битовые поля
    - [по-русски](https://learn.microsoft.com/ru-ru/cpp/cpp/cpp-bit-fields?view=msvc-170)
    - нельзя адрес брать
```c++
struct S {
  int i : 3;  // 0 - 31
  int j : 5;  // 0 - 7
}
```
5. Optional
     * [Зачем?](https://habr.com/ru/articles/372103/)
     * [Proposal to add optional](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3793.html)
     * [Эталонная реализация](https://github.com/akrzemi1/Optional) 
  
       
***std::optional*** — это шаблон класса, представленный в стандарте C++17, который обеспечивает механизм для представления необязательных (optional) значений. Этот класс удобен в ситуациях, когда значение может отсутствовать, что предпочтительнее использования "магических значений" (например, -1 для целых чисел) или сложных конструкций с указателями (например, nullptr для указывающего, что значение отсутствует). *std::optional* облегчает код, делая его более читаемым и безопасным, предотвращая ошибки связанные с обработкой неинициализированных значений или нулевых указателей.

__Идеи реализации__ 
```c++
template <class T>
class Optional {
  alignas(T) unsigned char storage_[sizeof(T)];
  bool has_value_ = false;
```
Init
```c++
template <class... Args>
void Init(Args&&... args) ?? { //noexept check
  new (??) T(std::forward<Args>(args)...);
  has_value_ = true;
}
```

Исключение:
```c++
class BadOptionalAccess : public std::exception {
 public:
   ?? const char* what() ?? override {  // NOLINT
    return "BadOptionalAccess";
  }
};
```
4. reinterpret_cast, alignas

- ***[reinterpret_cast](https://learn.microsoft.com/ru-ru/cpp/cpp/reinterpret-cast-operator?view=msvc-170)*** в C++ используется для выполнения низкоуровневых, потенциально небезопасных преобразований типов. 
- Он не выполняет никаких операций преобразования во время выполнения (например, не проверяет совместимость типов), а лишь переинтерпретирует битовое представление одного типа как другой. \
- Оператор приведения reinterpret_cast используется для приведения несовместимых типов. Может приводить целое число к указателю, указатель к целому числу, указатель к указателю (это же касается и ссылок). 
- Является функционально усеченным аналогом приведения типов в стиле языка С. Отличие состоит в том, что reinterpret_cast не может снимать квалификаторы const и volatile, а также не может делать небезопасное приведение типов не через указатели, а напрямую по значению. 
 Например, переменную типа int к переменной типа double привести при помощи reinterpret_cast нельзя.

```c++
int a = 10;
// Преобразование указателя на int в указатель на char
char* charPtr = reinterpret_cast<char*>(&a);

// Вывод первого байта переменной a
std::cout << "Первый байт переменной a: " << *charPtr << std::endl;

// Преобразование обратно в указатель на int и вывод значения
int* intPtr = reinterpret_cast<int*>(charPtr);
std::cout << "Значение переменной a: " << *intPtr << std::endl;
```

Нельзя [std::aligned_storage](https://en.cppreference.com/w/cpp/types/aligned_storage), т.к. он _deprecated_. Используйте массив char или [std::byte](https://en.cppreference.com/w/cpp/types/byte) .
