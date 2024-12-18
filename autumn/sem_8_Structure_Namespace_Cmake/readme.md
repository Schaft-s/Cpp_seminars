## Модульное программирование (повторение)
### Составные типы данных

C++ позволяет создавать новые типы данных на основе базовых. Это можно делать с помощью перечислений (enum), структур (struct), классов (class), а также стандартных контейнеров, таких как `std::pair` и `std::tuple`. Рассмотрим каждый из этих механизмов подробнее.

#### Перечисления (enum)

Перечисление — это набор именованных констант, которые обычно используются для описания возможных состояний или опций. Например, перечисление возрастные группы:

```cpp
enum class Age {
    Child,
    Teen,
    Adult,
    Old
};
```

Перечисления удобны тем, что дают программам читабельность и безопасность типов. Их можно преобразовывать в числа и обратно с помощью `static_cast`:

```cpp
int value = static_cast<int>(Age::Old);  // 3
Age age = static_cast<Age>(2);  // Age::Adult
```
Вот более подробное изложение темы **структур в C++**, основанное на твоей презентации и дополнительной информации.

### Определение и Инициализация Структур

**Структура** — это составной тип данных, который инкапсулирует набор данных разных типов под одним именем. Она используется для представления более сложных объектов, которые содержат несколько полей. В C++ структура объявляется с помощью ключевого слова `struct`.

Пример структур, комплексное число и массив:

```cpp
struct Complex {
    double re;  // действительная часть
    double im;  // мнимая часть
};

struct Array {
    int* buffer;
    size_t size;
};
```

Объявление структуры создаёт новый тип данных, который можно использовать для создания переменных:

```cpp
Complex number;
number.re = 1.0;
number.im = -2.5;
```

#### Инициализация Структур

C++ позволяет инициализировать структуры как через список инициализаторов, так и с помощью фигурных скобок. Если не указать некоторые значения при инициализации, поля будут автоматически обнулены:

```cpp
struct Point {
    int x = 0;
    int y = 0;
};

Point p1 = {10, 20};  // x = 10, y = 20
Point p2 = {5};       // x = 5, y = 0
Point p3;             // x = 0, y = 0
```

Начиная с C++20, доступны **designated initializers**, позволяющие явно указывать, какие поля структуры инициализируются:

```cpp
Point p4 = {.x = 1, .y = 2};
```

### Доступ к Полям

Для доступа к полям структуры используется операция `.`:

```cpp
Point p = {1, 2};
std::cout << p.x << " " << p.y << std::endl;
```

### Статические Поля в Структурах

**Статические поля** принадлежат структуре в целом, а не её экземплярам. Их можно использовать для хранения общих данных для всех объектов структуры. Они объявляются с использованием ключевого слова `static` и должны быть определены отдельно:

```cpp
struct S {
    static int counter;
};

int S::counter = 0;
```

Обращение к статическим полям выполняется через имя структуры:

```cpp
S::counter = 10;
```

### Размещение Структур в Памяти и Выравнивание [3]

Размер структуры в памяти зависит не только от размеров её полей, но и от выравнивания. Компилятор может добавлять "пустые" байты для оптимизации доступа к данным, особенно если поля имеют разные размеры. Это влияет на общий размер структуры.

Пример:

```cpp
struct S {
    char c;     // 1 байт
    int32_t i;  // 4 байта
    int16_t s;  // 2 байта
    int64_t l;  // 8 байт
};

std::cout << sizeof(S);  // 24, а не 15, из-за выравнивания
```

**Правильное упорядочение полей** может уменьшить размер структуры, так как уменьшается количество "пустых" байтов:

```cpp
struct Optimized {
    int64_t l;  // 8 байт
    int32_t i;  // 4 байта
    int16_t s;  // 2 байта
    char c;     // 1 байт
};

std::cout << sizeof(Optimized);  // 16
```

### Копирование Структур
В C++ структуры по умолчанию копируются **побитово**. Это означает, что все поля структуры копируются как есть, даже массивы:

### Доступ к Полям через Указатель

Чтобы обращаться к полям структуры через указатель, используется операция `->`:

```cpp
Point* p = new Point{10, 20};
p->x = 30;
```
### Пары (std::pair) и кортежи (std::tuple)

Для хранения двух и более объектов используются шаблонные структуры `std::pair` и `std::tuple`:

```cpp
std::pair<int, double> p = {42, 3.14};
std::tuple<int, double, Point> t = {42, 3.14, point1};
```

К элементам `std::tuple` можно обращаться через `std::get<>`:

```cpp
std::cout << std::get<0>(t);  // 42
```

Также можно распаковывать данные с помощью structured bindings:  [3]  

```cpp
auto [x, y, point] = t;
```

## Пространства имён
Пространства имён используются в C++ для организации кода и предотвращения конфликтов между идентификаторами (переменные, функции, классы и т.д.), которые могут иметь одинаковые имена в разных библиотеках или модулях. Пространства имён позволяют разделять области видимости и группировать логически связанные элементы. Ключевое слово для определения пространства имён — namespace.
```c++
#include <iostream>

// Определение пространства имён
namespace geometry {
    const double PI = 3.14159;

    double area_of_circle(double radius) {
        return PI * radius * radius;
    }
}

namespace algebra {
    int add(int a, int b) {
        return a + b;
    }
}

int main() {
    // Доступ к функциям и переменным через имя пространства имён
    double circle_area = geometry::area_of_circle(5.0);
    int sum = algebra::add(3, 7);

    std::cout << "Площадь круга: " << circle_area << std::endl;
    std::cout << "Сумма: " << sum << std::endl;

    return 0;
}
```
### Стандартное пространство имён std
std — это стандартное пространство имён в C++, в котором определены все стандартные библиотеки и функции, такие как std::cout, std::cin, контейнеры STL (например, std::vector, std::map) и многие другие.  
Когда мы пишем std::cout, мы обращаемся к функции вывода cout в пространстве имён std. Если не указать пространство имён, компилятор не поймёт, к какому cout мы обращаемся.

### Особенности использования:
  - `using namespace`: Можно использовать using namespace, чтобы не указывать пространство имён перед каждой функцией или переменной. Однако это может привести к конфликтам имен.
  - Лучшей альтернативой является использование using с явным указанием используемой сущности.
  - Область видимости: Пространства имён можно использовать в пределах определённых блоков или функций.
```cpp
int main() {
    using std::cin; // внутри блока можно не писать std для cin
    using std::cout; // внутри блока можно не писать std для cout
    int x, y;
    cin >> x >> y;
    cout << x + y << '\n';
}

void f() {
    namespace my_space = geometry;
    double area = my_space::area_of_circle(10.0);
}
```

## CMake [4]
CMake — это инструмент для автоматизации сборки, который генерирует файлы сборки (например, Makefile для Unix или проектные файлы для Visual Studio) на основе конфигурационных файлов. CMake помогает управлять большими проектами и их зависимостями, упрощая процесс компиляции и линковки.

#### Основные компоненты CMake:
1. **CMakeLists.txt** — основной файл конфигурации, который описывает, как проект должен быть собран.
2. **Команды CMake** — набор инструкций, таких как `add_executable`, `target_link_libraries`, `find_package`, и другие.

#### Пример простого CMakeLists.txt:

```cmake
# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Имя проекта
project(MyProject)

# Добавление исполняемого файла
add_executable(MyExecutable main.cpp)
```

Этот файл говорит CMake, что нужно создать проект с именем `MyProject`, и в качестве исполняемого файла создать `MyExecutable` из файла `main.cpp`.

#### Основные команды CMake:

- **`cmake_minimum_required`** — указывает минимальную версию CMake, необходимую для сборки проекта.
- **`project`** — устанавливает имя проекта.
- **`add_executable`** — добавляет исполняемый файл, который должен быть собран из исходных файлов.
- **`target_link_libraries`** — связывает библиотеки с исполняемым файлом.
  
#### Пример проекта с зависимостью от библиотеки:

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Указание исполняемого файла
add_executable(MyExecutable main.cpp)

# Поиск библиотеки (например, Boost)
find_package(Boost REQUIRED)

# Связывание с библиотекой Boost
target_link_libraries(MyExecutable Boost::boost)
```

В этом примере CMake находит библиотеку Boost и связывает её с исполняемым файлом.

#### Как использовать CMake:
1. Создайте папку для сборки:
   ```bash
   mkdir build
   cd build
   ```

2. Запустите CMake для генерации файлов сборки:
   ```bash
   cmake ..
   ```

3. Соберите проект с помощью команды:
   ```bash
   cmake --build .
   ```

#### Пример использования CMake с тестами:

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Добавляем исполняемый файл
add_executable(MyExecutable main.cpp)

# Включение тестирования
enable_testing()

# Добавление теста
add_test(NAME MyTest COMMAND MyExecutable)
```

В этом примере включается тестирование с помощью команды `enable_testing`, а `add_test` добавляет тест, который запускает наш исполняемый файл.

#### Преимущества CMake:
- Поддержка кросс-платформенной сборки.
- Лёгкая интеграция с различными библиотеками.
- Упрощённое управление зависимостями.
- Генерация файлов сборки для различных сред (Makefile, Visual Studio и др.).


## ДЗ
  - Контест
  - Напишите структуру студента - с базовыми полями и методами. Методы продумайте сами (гетеры, сетеры - точно нужно, можно покреативить про студент поел, отдохнул, сдал сессию, не сдал сессию итд)
    
## Полезные ссылки
- [0] [Учебник](https://education.yandex.ru/handbook/cpp/article/complex-data-types) Яндекса на тему.
- [1] [Статья](https://habr.com/ru/articles/334988/) на хабре про struct, union, enum.
- [2] [Статья](https://tproger.ru/translations/art-of-structure-packing) про выравнивание
- [3] [Статья](https://habr.com/ru/companies/playrix/articles/465181/) где рассказывается про структурное связывание
- [4] [Видео](https://www.youtube.com/watch?v=mrm39JmvJ1c&ab_channel=S0ER) по CMake
