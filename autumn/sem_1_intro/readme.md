## Установка всего
  - [VSCode](https://code.visualstudio.com/docs/setup/setup-overview) - официальный сайт, [статья](https://habr.com/ru/articles/490754/) на Хабре.
  - [Отладка в VSCode](https://code.visualstudio.com/docs/cpp/cpp-debug)
  - [Clion](https://www.jetbrains.com/clion/), вроде есть огромные приколы с лиценцзией JetBrains, но это можно обойти через [GitHub Student Developer Pack](https://education.github.com/pack?sort=popularity).
  - [Гайд](https://github.com/nguendh/get-student-license) по получении JetBrains лицензии.
  - [Ubuntu](https://ubuntu.com/desktop/wsl) на Windows (wsl), очень просто и до следующего семестра точно хватит такой версии. (С маками будем мучаться весь год... по поводу установки на них пишите сразу нашему ассистенту [Асадбеку](https://t.me/fall_raiin))
## Кратко о Linux
  - [Туториал](https://habr.com/ru/articles/655275/) на все случаи жизни.
  - Основные команды
```
1. ls <путь до директории> - выводит список всех файлов (включая поддиректории) в директории
2. pwd - выводит относительный путь рабочей директории
3. mkdir <путь до директории> - создает новую директорию (не переходит в неё)
4. cd <путь до директории> - переходит в директорию
5. touch <путь до файла> - создает файл
6. cat <путь до файла> - выводит содержимое файла
7. mv <что переместить> <куда> - перемещает файл/директорию в другое место
8. rm <путь до файла> - удалить файл
9. cp <что> <куда> - копировать файл/директорию
10. man <название команды> - руководство к любой команде, которую вы запускаете в терминале

Рекомендую поиграться
сowsay
sl
cmatrix
fortune
telnet towel.blinkenlights.nl - смотреть звездные войны
```
Подробнее [тут](https://losst.pro/prikolnye-komandy-linux)

## Основная часть
  - [Презентация](Types.pdf) от лектора - Ибрагимова Булата Ленаровича, предоставлена для студентов МФТИ.  
  - Типы данных в [учебнике](https://education.yandex.ru/handbook/cpp/article/data-types) от Яндекса.
#### 1. Из чего состоит программа на C++?

Программа на C++ — это последовательность инструкций, которые выполняются компьютером. Основные составляющие программы:

- **Заголовочные файлы**: В начале программы обычно подключаются заголовочные файлы с помощью директивы `#include`. Например, `#include <iostream>` подключает библиотеку для работы с вводом и выводом.

- **Функция `main()`**: Это точка входа в программу. Именно с неё начинается выполнение программы. Пример:
  ```cpp
  int main() {
      // Тело функции
      return 0;
  }
  ```
  Функция `main()` должна возвращать целое число, что указывает на успешное завершение программы (обычно `0`).

- **Инструкции (statements)**: Это команды, которые выполняет программа. Они могут быть простыми (например, присваивание значения переменной) или сложными (например, циклы, условные операторы и т.д.).

#### 2. Что такое выражения и чем "операция" отличается от "оператора"?

- **Выражение (expression)**: Это любая комбинация значений, переменных, операторов и функций, которая вычисляется и возвращает некоторое значение. Примеры выражений:
  ```cpp
  5 + 3
  x * y
  sqrt(16)
  ```

- **Оператор (operator)**: Это символ или комбинация символов, которые указывают компилятору выполнить определённую операцию. Например, `+`, `-`, `*`, `/` — это арифметические операторы.

- **Операция (operation)**: Это процесс, который выполняется в результате применения оператора к операндам. Например, в выражении `5 + 3` оператор `+` выполняет операцию сложения над операндами `5` и `3`.

#### 3. Работа с вводом и выводом

Для взаимодействия программы с пользователем используются операции ввода и вывода. В C++ для этого используется библиотека `<iostream>`.

- **Вывод данных (output)**: Для вывода данных на экран используется объект `std::cout` и оператор `<<`.
  ```cpp
  #include <iostream>

  int main() {
      std::cout << "Hello, World!" << std::endl;
      return 0;
  }
  ```
  Здесь `"Hello, World!"` — строковый литерал, который выводится на экран, а `std::endl` — манипулятор, который переводит курсор на новую строку.

- **Ввод данных (input)**: Для ввода данных с клавиатуры используется объект `std::cin` и оператор `>>`.
  ```cpp
  #include <iostream>

  int main() {
      int age;
      std::cout << "Enter your age: ";
      std::cin >> age;
      std::cout << "You are " << age << " years old." << std::endl;
      return 0;
  }
  ```
  Здесь программа предлагает пользователю ввести возраст, который затем сохраняется в переменную `age`.

#### 4. Концепция типа данных

**Тип данных** определяет множество возможных значений, которые может принимать переменная, а также операции, которые можно выполнять с этими значениями. В C++ типы данных делятся на несколько категорий, включая арифметические типы данных.

##### Арифметические типы данных

1. **Целочисленные типы (integer types)**:
   - `int`: Стандартный целочисленный тип, обычно занимает 4 байта.
   - `short`: Короткий целочисленный тип, обычно занимает 2 байта.
   - `long`: Длинный целочисленный тип, обычно занимает 4 или 8 байт.
   - `long long`: Очень длинный целочисленный тип, обычно занимает 8 байт.
   - `unsigned int`, `unsigned short`, `unsigned long`, `unsigned long long`: Беззнаковые версии целочисленных типов, которые могут хранить только неотрицательные значения.

2. **Типы с плавающей запятой (floating-point types)**:
   - `float`: Тип для хранения чисел с плавающей точкой, занимает 4 байта.
   - `double`: Более точный тип для хранения чисел с плавающей точкой, занимает 8 байт.
   - `long double`: Ещё более точный тип, обычно занимает 8, 12 или 16 байт в зависимости от платформы.

3. **Типы `char` и `bool`**:
   - `char`: Тип для хранения символов. Занимает 1 байт памяти (обычно 8 бит), что позволяет хранить 256 различных значений. В основном используется для хранения символов ASCII.
     ```cpp
     char letter = 'A';
     ```
     Символы заключаются в одинарные кавычки.

   - `bool`: Логический тип данных, который может принимать одно из двух значений: `true` или `false`. Используется для представления логических истинности и ложности.
     ```cpp
     bool isTrue = true;
     ```

#### 5. Различия между типами данных

Типы данных различаются по нескольким характеристикам:

- **Размер (size)**: Разные типы данных занимают разное количество памяти. Например, `int` обычно занимает 4 байта, тогда как `double` — 8 байт.

- **Диапазон (range)**: Диапазон значений, которые может принимать переменная, зависит от типа данных. Например, `int` может хранить целые числа от примерно -2 миллиарда до 2 миллиардов (диапазон `-2^31` до `2^31-1`), в то время как `unsigned int` может хранить от 0 до 4 миллиардов (диапазон `0` до `2^32-1`).

- **Точность (precision)**: Типы с плавающей запятой (`float`, `double`) могут хранить дробные значения, но с определённой точностью. Например, `float` поддерживает около 7 знаков после запятой, тогда как `double` — около 15.

- **Знаковость (signedness)**: Целочисленные типы могут быть знаковыми (`signed`) или беззнаковыми (`unsigned`). Знаковые типы могут хранить как положительные, так и отрицательные числа, в то время как беззнаковые типы только положительные числа.


## ДЗ + Правила игры
  - Домашний [контест](https://contest.yandex.ru/contest/67476/problems/) 
  - Первое время будут маленькие контесты с простыми задачами в качестве домашек.
  - После появятся большие контесты с жёсткими дедлайнами, составляющие основную сложность курса. 
  - В начале каждого семинара будет небольшой тестик по материалам прошлого семинара и последней лекции. 
  - Стоит сказать, что важным условием сдачи задачек будет являться не только прохождение всех тестов, но и прохождение кодстайл-чекера. А после него - прохождение ещё более страшного чекера - ассистента. Подробнее о правилах кодстайл чекера написано [тут](CODESTYLE.md) и будет написано в беседе группы лично ассистентом.

## Полезные ссылки
  - [Лекции](https://disk.yandex.ru/d/l_Cd3y7r3rcnDA) __этого__ года... 
  - Прикольный [гайд](https://github.com/victor-yacovlev/fpmi-caos/tree/master/practice/linux_basics) с введением в С++ со стороны разработки. 
Там также есть про введение в пользование Linux. И вообще не теряйте его, потом не раз пригодится.
  - [Учебник](https://education.yandex.ru/handbook/cpp) от Яндекса, теоретически его хватит чтобы закрыть основную теорию за первый семестр.
