#include <iostream>
#include <stdexcept>
#include <cstddef>

using namespace std;


template<typename T>
class Deque {
private:
    T *data;
    size_t capacity;
    size_t count;
    size_t head; // индекс первого элемента

    // Увеличение ёмкости в 2 раза
    void resize() {
        size_t newCapacity = capacity * 2;
        T *newData = new T[newCapacity];

        for (size_t i = 0; i < count; ++i) {
            newData[i] = data[(head + i) % capacity];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
        head = 0;
    }

public:
    // Конструкторы
    Deque() : capacity(4), count(0), head(0) {
        data = new T[capacity];
    }

    // Конструктор копирования
    Deque(const Deque &other)
        : capacity(other.capacity), count(other.count), head(0) {
        data = new T[capacity];
        for (size_t i = 0; i < count; ++i) {
            data[i] = other[i];
        }
    }

    // Конструктор перемещения
    Deque(Deque &&other)
        : data(other.data), capacity(other.capacity),
          count(other.count), head(other.head) {
        other.data = nullptr;
        other.count = 0;
        other.capacity = 0;
        other.head = 0;
    }

    // Основные операции
    void push_back(const T &value) {
        if (count == capacity)
            resize();

        data[(head + count) % capacity] = value;
        ++count;
    }

    void push_front(const T &value) {
        if (count == capacity)
            resize();

        head = (head + capacity - 1) % capacity;
        data[head] = value;
        ++count;
    }

    void pop_back() {
        if (empty())
            throw out_of_range("Дек пуст");
        --count;
    }

    void pop_front() {
        if (empty())
            throw out_of_range("Дек пуст");
        head = (head + 1) % capacity;
        --count;
    }

    // Доступ к элементам
    T &front() {
        if (empty())
            throw out_of_range("Дек пуст");
        return data[head];
    }

    T &back() {
        if (empty())
            throw out_of_range("Дек пуст");
        return data[(head + count - 1) % capacity];
    }

    const T &front() const {
        if (empty())
            throw out_of_range("Дек пуст");
        return data[head];
    }

    const T &back() const {
        if (empty())
            throw out_of_range("Дек пуст");
        return data[(head + count - 1) % capacity];
    }

    // Доступ по индексу
    T &operator[](size_t index) {
        return data[(head + index) % capacity];
    }

    const T &operator[](size_t index) const {
        return data[(head + index) % capacity];
    }

    // Доступ с проверкой границ
    T &at(size_t index) {
        if (index >= count)
            throw out_of_range("Индекс вне диапазона");
        return (*this)[index];
    }

    const T &at(size_t index) const {
        if (index >= count)
            throw out_of_range("Индекс вне диапазона");
        return (*this)[index];
    }

    // Размеры
    size_t size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }

    // Деструктор
    ~Deque() {
        delete[] data;
    }

    // Вывод содержимого дека
    void print() const {
        cout << "[ ";
        for (size_t i = 0; i < count; ++i) {
            cout << data[(head + i) % capacity] << " ";
        }
        cout << "]\n";
    }
};


class Task5_4 {
public:
    int run() {
        cout << "Задание 5.4* Свой дек\n\n";

        Deque<int> d;

        cout << "Дек пуст? " << d.empty() << "\n";

        d.push_back(10);
        d.push_back(20);
        d.push_front(5);
        d.push_front(1);

        cout << "После добавления элементов:\n";
        d.print();

        cout << "Первый элемент: " << d.front() << "\n";
        cout << "Последний элемент: " << d.back() << "\n";

        cout << "Элемент с индексом 2: " << d[2] << "\n";
        cout << "Элемент с индексом 3 (at): " << d.at(3) << "\n";

        d.pop_front();
        d.pop_back();

        cout << "После удаления первого и последнего элементов:\n";
        d.print();

        cout << "Проверка автоматического расширения:\n";
        for (int i = 0; i < 10; ++i)
            d.push_back(i * 10);

        d.print();

        cout << "Размер дека: " << d.size() << "\n";
        cout << "Дек пуст? " << d.empty() << "\n";

        return 0;
    }
};
