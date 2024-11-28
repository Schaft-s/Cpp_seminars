## Повторение
- <algorithm> - какие функции помните? Что они принимают? 
- Классы, поля, методы, перегрузка операций..
  
## Lambda

Лямбда-выражения в C++ — это способ определить анонимную функцию, которая может быть использована прямо в месте вызова. Они упрощают работу с функциональными объектами, не требуя создания отдельного класса или функции.  

```cpp
[захват] (параметры) -> возвращаемый_тип { тело; };
```

- **[список захват]** — определяет, какие переменные из окружающей области видимости использовать  
- **(параметры)** — список параметров функции   
- **-> возвращаемый_тип** — необязательный указатель возвращаемого типа (если можно вывести автоматически)  
- **тело** — непосредственно логика функции  

Пример 

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {5, 2, 9, 1, 5, 6};

    // Сортировка по убыванию
    std::sort(vec.begin(), vec.end(), [](int a, int b) {
        return a > b;
    });

    std::for_each(vec.begin(), vec.end(), [](int x) {
        std::cout << x << " ";
    });

    return 0;
}
```

Задания
 
1. Найти сумму всех элементов массива.  // std::accumulate
2. Отфильтровать элементы массива с помощью `std::copy_if`, оставив только четные числа.
3. Сортировать строки массива в порядке убывания их длины.
4. Использовать `std::transform` для перевода всех символов строки в верхний регистр.
5. + ещё 2 своих придуманных, желательно  переделать в lambda виде код с предыдущего семинара

## Github + тесты