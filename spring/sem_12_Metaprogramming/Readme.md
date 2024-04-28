0. Прошлый сем
1. С лекции:
    - Определители типов
    - Модификаторы типов
    - CT-вычисления
    - 
2. [Метапрограммирование](https://en.cppreference.com/w/cpp/meta)
    - [ЛЕКЦИЯ](Metaprogramming.pdf)
    - [type_traits](https://en.cppreference.com/w/cpp/header/type_traits)
      - Напишите **"is_array"**
      - Напишите **"add_cv"**
    - Условия задач на эту тему из следующего контеста - [ct_prime](README_ct_prime.md), [array_traits](README_array_traits.md)
    - **type_traits** в C++ — это набор шаблонных классов и функций, которые предоставляются стандартной библиотекой для работы с типами во время компиляции. Они используются для получения информации о типах данных, такой как проверка на константность, поддержка арифметики, определение категорий типов и многое другое. Эти утилиты помогают писать более обобщенный и безопасный код.
    - **integral_constant** — это шаблон структуры, который позволяет представлять типы и значения во время компиляции.
    - **integer_sequence** представляет собой шаблон класса, который используется для создания последовательности целых чисел во время компиляции. Пример:
```cpp
template<typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq) {
    ((std::cout << ints << ' '), ...);
}

int main() {
    print_sequence(std::integer_sequence<int, 1, 2, 3, 4, 5>{});
    return 0;
}
```
    - 
3. CMake и устройство тестов
    - add_subdirectory/set/add_executable
    - [Статья](https://habr.com/ru/articles/155467/) из прошлого семестра
    - [Видео](https://www.youtube.com/watch?v=gSTLzOmFChs&ab_channel=SimpleCoding) вроде даже то же самое
    - [Catch](https://github.com/catchorg/Catch2)
    - [Статья](https://ps-group.github.io/cg/mmz01) в которой всё максимально разжёванно про то как написать простейшие тесты, с примерами.
4. Материалы:
    - [Лекция 1](https://www.youtube.com/watch?v=dFrn_vgZb4Y&ab_channel=%D0%9C%D0%B5%D1%89%D0%B5%D1%80%D0%B8%D0%BD%D0%98%D0%BB%D1%8C%D1%8F) Мещерина про метапрограммирование
    - [Лекция 2](https://www.youtube.com/watch?v=FukzTU0ebHw&ab_channel=%D0%9C%D0%B5%D1%89%D0%B5%D1%80%D0%B8%D0%BD%D0%98%D0%BB%D1%8C%D1%8F) Мещерина про метапрограммирование
    - 
