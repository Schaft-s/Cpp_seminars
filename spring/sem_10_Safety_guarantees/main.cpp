#include <vector>
#include <chrono>
#include <iostream>
#include <random>

struct HeavyObject {
    int* data;
    std::string name;
    double value;

    HeavyObject() : data(new int[100]), value(0.0) {
        // Инициализация массива случайными значениями
        std::generate_n(data, 100, std::rand);
    }

    ~HeavyObject() {
        delete[] data;
    }

    // Перемещающий конструктор
    HeavyObject(HeavyObject&& other) noexcept : data(other.data), name(std::move(other.name)), value(other.value) {
        other.data = nullptr;
    }

    // Запрет копирования для упрощения
    HeavyObject(const HeavyObject&) = delete;
    HeavyObject& operator=(const HeavyObject&) = delete;

    // Оператор присваивания перемещением
    HeavyObject& operator=(HeavyObject&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            other.data = nullptr;
            name = std::move(other.name);
            value = other.value;
        }
        return *this;
    }
};

struct HeavyObject_without_npexcept {
    int* data;
    std::string name;
    double value;

    HeavyObject_without_npexcept() : data(new int[100]), value(0.0) {
        // Инициализация массива случайными значениями
        std::generate_n(data, 100, std::rand);
    }

    ~HeavyObject_without_npexcept() {
        delete[] data;
    }

    // Перемещающий конструктор
    HeavyObject_without_npexcept(HeavyObject_without_npexcept&& other) : data(other.data), name(std::move(other.name)), value(other.value) {
        other.data = nullptr;
    }

    // Запрет копирования для упрощения
    HeavyObject_without_npexcept(const HeavyObject_without_npexcept&) = delete;
    HeavyObject& operator=(const HeavyObject&) = delete;

    // Оператор присваивания перемещением
    HeavyObject_without_npexcept& operator=(HeavyObject_without_npexcept&& other) {
        if (this != &other) {
            delete[] data;
            data = other.data;
            other.data = nullptr;
            name = std::move(other.name);
            value = other.value;
        }
        return *this;
    }
};

void testPerformance1() {
    std::vector<HeavyObject> vec;
    vec.reserve(1000); // Изначальная вместимость

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 2000; ++i) {
        vec.emplace_back();
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Duration for HeavyObject vector: " << duration.count() << " ms" << std::endl;
}
void testPerformance2() {
    std::vector<HeavyObject_without_npexcept> vec;
    vec.reserve(1000); // Изначальная вместимость

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 2000; ++i) {
        vec.emplace_back();
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Duration for HeavyObject_without_npexcept vector: " << duration.count() << " ms" << std::endl;
}

int main() {
    testPerformance1();
    testPerformance2();

}
