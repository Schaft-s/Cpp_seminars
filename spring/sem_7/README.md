Hello  

0. Лекция:
    > Операция new, delete \
    > Какие формы, в чём отличие?


1. Placement new (reserve, push_back => vector...)
2. Выравнивание...
3. Optional
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

***reinterpret_cast*** в C++ используется для выполнения низкоуровневых, потенциально небезопасных преобразований типов. Он не выполняет никаких операций преобразования во время выполнения (например, не проверяет совместимость типов), а лишь переинтерпретирует битовое представление одного типа как другой.
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
