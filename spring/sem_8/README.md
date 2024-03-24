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
для работы с обобщенными функциями distance next advance, необходимо определить несколько вложенных псевдонимов типов

5. [Класс Subrange](https://en.cppreference.com/w/cpp/ranges/subrange)
6. Использовать copy fill 
