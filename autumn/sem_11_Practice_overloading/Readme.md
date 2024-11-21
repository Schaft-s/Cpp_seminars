## Повторение
- Что я не сказал на прошлом семинаре про конструкторы?
  - Делигирующие конструкторы : `Stack::Stack(size_t size) : Stack(size, 0) {}`
  - Конструктор по умолчанию, `ответ на отл: инициализирует все поля-классы конструкторами по
умолчанию, а для полей-примитиных типов ничего не делает.`
  - От одного аргумента == Конструктор преобразования


## Перегрузка операций

В C++, для перегрузки операций используется ключевое слово `operator`, которое позволяет определить, как конкретная операция будет работать для объектов класса. Операции можно перегружать как методы внутри класса, так и внешние функции, определенные вне класса. Например:

```cpp
class MyClass {
public:
    MyClass operator+(const MyClass& other) const {  // Перегрузка оператора в виде метода    }
};

MyClass operator+(const MyClass& lhs, const MyClass& rhs) { // Перегрузка оператора + в виде внешней функции }
```
#### Тонкости выбора метода или внешней функции для перегрузки

1. **Метод класса**: В случае использования метода класса оператор определяется в виде метода внутри класса и использует доступ к приватным членам объекта напрямую. Метод должен учитывать, что первый аргумент (левый операнд) всегда является текущим объектом (`*this`), а правый операнд передается как аргумент.

2. **Внешняя функция**: Внешняя функция перегрузки операции позволяет обеспечить гибкость, особенно когда левый операнд — не пользовательский тип, или если необходимо обеспечить коммутативность операции (например, `2 + Rational`). Для операторов, требующих симметричности и коммутативности, таких как `+` или `-`, обычно предпочтительнее внешняя функция, которая позволяет избежать копирования, создавая возможности для операторов преобразования.


### Правила
1. Хотя бы один операнд должен быть пользовательского типа
2. Нельзя вводить новые операции в язык
3. Нельзя менять арность и приоритет операций.
4. Нельзя переопределять операции :: , . , ?: , .* .
5. Операции = , () , [] , -> могут быть перегружены только в виде
методов.
6. Операции && и || теряют свойство "короткого вычисления"

### Нюансы
- Операцию = перегружать можно, но осторожно. [0] Компилятор за вас перегрузит пока что всё нормально. На самом деле там всё умнее чем мы сейчас думаем, так что лучше не стоит.
- Пре-инкремент - всё ок, пост-инкремент - фиктивный (int) как второй аргумент
- Можно перегружать приведения типов [1] [2]
- Ключевое слово `friend`
  - Друзья класса - внешние по отношению к классу сущности, которые имеют доступ к приватной и защищенной частям класса.
  - Можно и функции и другие классы
 

#### Начало кода для `Array`

```cpp
template <typename T, std::size_t N>
struct Array {
    T data[N];

    T& operator[](std::size_t index) {
        return data[index];
    }

    const T& operator[](std::size_t index) const {
        return data[index];
    }

    std::size_t size() const { return N; }
};
```
**Спойлер**  
_Для корректного прохождения тестов ваш класс должен реализовывать следующие методы (подумайте, какие методы должны быть константными, какие - неконстантными, а какие должны иметь обе версии):_

 - _Операция [] для доступа к элементу массива по индексу;_
 - _Методы Front() и Back() для доступа к первому и последнему элементу соответственно;_
 - _Метод Data(), возвращающий указатель на начало массива;_
 - _Метод Size(), возвращающий размер массива;_
 - _Метод Empty(), возвращающий true, если массив пуст, и false в противном случае;_
 - _Метод Fill(const T& value), который заполняет массив значениями value;_

#### Начало кода для `Rational`

```cpp
#include <compare>

class Rational {
private:
    int numerator;
    int denominator;

public:
    Rational(int num = 0, int denom = 1) : numerator(num), denominator(denom) {        // Тут может быть логика нормализации дроби. Её стоит вывести в отдельный метод/функцию    }

    friend Rational operator+(const Rational& lhs, const Rational& rhs) {
        return Rational(lhs.numerator * rhs.denominator + rhs.numerator * lhs.denominator,
                        lhs.denominator * rhs.denominator);
    }

    auto operator<=>(const Rational& other) const = default;  // Читать негде, гуглите, если что тут [4] 

    // Оператор вывода в поток
    friend std::ostream& operator<<(std::ostream& os, const Rational& r) {
        os << r.numerator << '/' << r.denominator;
        return os;
    }
};
```

1. С оператором `<=>` при указании `= default` автоматически генерируются остальные операторы сравнения (`<`, `>`, `==` и т.д.).
2. Использование внешних функций позволяет обеспечить коммутативность операций, например, сложение целого числа и дроби `2 + Rational`.


**Спойлер**  
_Рациональное число представляется двумя **взаимно простыми** целыми числами - числителем и **положительным**
знаменателем. Этот инвариант необходимо поддерживать при выполнении любых операций над объектами класса `Rational`._
_Публичный интерфейс класса должен включать:_
* _Конструктор по умолчанию, который инициализирует число нулем;_
* _Неявный конструктор преобразования от целых чисел (должен работать следующий код `Rational x = 5;`). Не забудьте
добавить комментарий `// NOLINT` (см. замечания);_
* _Конструктор от двух целых чисел (числитель и знаменатель). При этом **не** гарантируется, что числа взаимно простые и
ненулевые (об этом далее);_
* _Методы `GetNumerator()` и `GetDenominator()`, возвращающие числитель и знаменатель соответственно;_
* _Методы `SetNumerator(int)` и `SetDenominator(int)`, устанавливающие числитель и знаменатель в требуемые значения;_
* _Бинарные арифметические операции (`+`, `-`, `/`, `*`) и их присваивающие версии (`+=`, `-=`, `/=`, `*=`);_
* _Унарные операции (`+`, `-`), а также префиксные и постфиксные инкременты и декременты (`++`, `--`);_
* _Операции сравнения;_
* _Операции ввода из потока и вывода в поток (`>>`, `<<`);_

## Полезные ссылки
- [0] Перегрузка =. [тут](https://www.geeksforgeeks.org/cpp-assignment-operator-overloading/)
- [1] Перегрузка приведения типов - [пример с пояснениями](https://www.geeksforgeeks.org/typecast-overloading-in-cpp/)
- [2] [тоже](https://www.learncpp.com/cpp-tutorial/overloading-typecasts/)
- [3] Оператор космического корабля, лучше гуглите, могу дать перевод статьи от Microsoft, но [тут](https://habr.com/ru/companies/microsoft/articles/458242/) чуть сложно.
 