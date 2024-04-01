1. [Перегрузка операторов new/delete](https://habr.com/ru/articles/490640/)
  - **Вопрос на экзамене: что происходит в стандартных операторах new/delete ([])**
    - _Сначала выделяется память для объекта._
    - _Если выделение прошло успешно, то вызывается конструктор._
    - _Если конструктор выбрасывает исключение, то выделенная память освобождается._
  - **Перегрузка new/delete**
    - _Список дополнительных параметров функций выделения памяти должен быть не пуст и не состоять из одного void* или const std::nothrow_t&, то есть их сигнатура не должна совпадать с одной из стандартных._
    - _Списки дополнительных параметров в operator new() и operator delete() должны совпадать._
    - _Эти функции можно определить в глобальном пространстве имен или в классе_
2. [Исключения](https://disk.yandex.ru/d/8WEwY2fFdzje5g/C%2B%2B/Лекция10-1.%20Исключения%20I?w=1)
  - Ничего хорошего в них нет:
    - Такое - не СЕ: 
    - ```c++
      void f() noexcept {
        throw ...;
      }
      ```
    - [Google style guide](https://google.github.io/styleguide/cppguide.html#Exceptions)  - **We do not use C++ exceptions.**

  - [Тут на русском, много и хорошо](https://metanit.com/cpp/tutorial/6.1.php)
  - [Лекции Мещерина про исключения](https://www.youtube.com/watch?v=JUofjC1GXwc&list=PL4_hYwCyhAvazfCDGyS0wx_hvBmnAAf4h&index=18), они для продвы, но более чем понятны любому 
  - Оператор noexcept - существует, проверяет есть ли спецификатор в объявлении функции... (не выполняет выражение внутри, delere ..)
  - Условный noexcept:
```c++
void f() noexcept(..Compile Time..){}
```
  - Function try block
```c++
struct S{
  int x = 0;
  std::string s;
  S(int x, const std::string& s) noexcept try: x(x), s(s){ } catch (...) { }
}
int f(int y) coexcept try{ } catch (...) { }
``` 
3. Итераторы и их связь с Range base for  
  - _Итераторы в C++ являются ключевым компонентом стандартной библиотеки шаблонов (STL), обеспечивая унифицированный доступ к элементам контейнеров различных типов. Итераторы позволяют пройти через элементы контейнера без необходимости знать о внутреннем устройстве самого контейнера. Это обеспечивает высокую степень абстракции и гибкости в работе с данными._
  -  базовые операторы, которые должен поддерживать итератор:
    - operator* для доступа к значению элемента.
    - operator++ для перехода к следующему элементу.
    - operator!= и operator== для сравнения итераторов.
4. Для обеспечения совместимости с функциями стандартной библиотеки, такими как std::distance, std::next, std::advance, очень важно, чтобы ваш класс итератора предоставлял определения нескольких вложенных псевдонимов типов.
  - iterator_category определяет категорию итератора, что влияет на то, какие операции можно с ним выполнять.
  - difference_type предоставляет тип для выражения разности между двумя итераторами.
  - value_type определяет тип элементов, к которым итератор может предоставлять доступ.
  - pointer и reference определяют типы указателя и ссылки на элемент контейнера соответственно.
```c++
#include <iterator>

template <typename T>
class MyContainer {
public:
    Iterator begin() { return Iterator(&data[0]); }
    Iterator end() { return Iterator(&data[size]); }
    T data[10];
    size_t size = 10;

    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        Iterator& operator++() { m_ptr++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
    private:
        pointer m_ptr;
    };
};

```
  - (Ещё пример написания своего итератора](https://habr.com/ru/articles/265491/)
5. [Класс Subrange](https://en.cppreference.com/w/cpp/ranges/subrange)
  - Реализуйте класс Subrange, аналог std::ranges::subrange
  - Принимающий пару итераторов и позволяющий пройти по нему как по последовательности элементов от begin до end
  - ( for (auto x : Subrange(v.begin() + 10, v.end() - 10)) )
6. Преимущества использования std::copy и std::fill:
  - Универсальность: std::copy может копировать данные между контейнерами разных типов, при условии совместимости типов элементов, что увеличивает гибкость кода. std::fill позволяет устанавливать значения для элементов контейнера без знания его внутреннего устройства.
  - Производительность: В некоторых случаях, когда компилятор может гарантировать безопасность использования memcpy или memset, STL может автоматически выбрать эти функции для оптимизации производительности, делая std::copy и std::fill не менее эффективными, чем низкоуровневые аналоги.
  - Совместимость с итераторами: В отличие от memcpy и memset, которые работают непосредственно с адресами памяти, std::copy и std::fill разработаны для работы с итераторами, что делает их идеально подходящими для использования с любыми контейнерами STL и пользовательскими контейнерами, поддерживающими итераторы.
