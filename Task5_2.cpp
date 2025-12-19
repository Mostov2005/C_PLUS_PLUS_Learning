#include <iostream>
#include <new>
#include <stdexcept>
#include <utility>
#include <string>

using namespace std;

template<typename T>
class Vector {
private:
    T *data_; // выделенная память (capacity)
    size_t size_; // size — количество реально созданных элементов
    size_t cap_; // capacity — сколько памяти выделено

    // Выделение сырой памяти, не создавая объекты
    static T *allocate_raw(size_t n) {
        if (n == 0) return nullptr;
        void *mem = ::operator new(n * sizeof(T));
        return static_cast<T *>(mem);
    }

    // Освобождение сырой памяти
    static void deallocate_raw(T *p) noexcept {
        ::operator delete(p);
    }

    // Явный вызов деструкторов
    static void destroy_range(T *from, T *to) noexcept {
        while (to != from) {
            --to;
            to->~T();
        }
    }

    // Геометрическое увеличение capacity (×2)
    void grow_if_needed() {
        size_t newCap = cap_ == 0 ? 1 : cap_ * 2;
        reserve(newCap);
    }

public:
    // Конструктор по умолчанию
    Vector() noexcept : data_(nullptr), size_(0), cap_(0) {
    }

    // Конструктор с размером и значением
    Vector(size_t n, const T &value) : data_(nullptr), size_(0), cap_(0) {
        if (n == 0) return;
        data_ = allocate_raw(n);
        size_t i = 0;
        try {
            for (; i < n; ++i)
                new(data_ + i) T(value);
        } catch (...) {
            destroy_range(data_, data_ + i);
            deallocate_raw(data_);
            throw;
        }
        size_ = cap_ = n;
    }

    // Конструктор копирования
    Vector(const Vector &other) : data_(nullptr), size_(0), cap_(0) {
        if (other.size_ == 0) return;
        data_ = allocate_raw(other.size_);
        size_t i = 0;
        try {
            for (; i < other.size_; ++i)
                new(data_ + i) T(other.data_[i]);
        } catch (...) {
            destroy_range(data_, data_ + i);
            deallocate_raw(data_);
            throw;
        }
        size_ = cap_ = other.size_;
    }

    // Деструктор
    ~Vector() {
        destroy_range(data_, data_ + size_);
        deallocate_raw(data_);
    }

    // Оператор присваивания
    Vector &operator=(Vector other) noexcept {
        swap(other);
        return *this;
    }

    // Доступ к элементам
    T &operator[](size_t idx) noexcept { return data_[idx]; }
    const T &operator[](size_t idx) const noexcept { return data_[idx]; }

    // at()
    T &at(size_t idx) {
        if (idx >= size_)
            throw out_of_range("Выход за гнаницы!");
        return data_[idx];
    }

    const T &at(size_t idx) const {
        if (idx >= size_)
            throw out_of_range("Выход за гнаницы!");
        return data_[idx];
    }

    // Доступ к элементам
    T *data() noexcept { return data_; }
    const T *data() const noexcept { return data_; }

    // front(), back()
    T &front() { return data_[0]; }
    T &back() { return data_[size_ - 1]; }

    // size(), capacity(), empty()
    size_t size() const noexcept { return size_; }
    size_t capacity() const noexcept { return cap_; }
    bool empty() const noexcept { return size_ == 0; }


    // push_back()
    void push_back(const T &value) {
        if (size_ == cap_) grow_if_needed();
        new(data_ + size_) T(value);
        ++size_;
    }

    // emplace_back()
    template<typename... Args>
    void emplace_back(Args &&... args) {
        if (size_ == cap_) grow_if_needed();
        new(data_ + size_) T(std::forward<Args>(args)...);
        ++size_;
    }

    // pop_back()
    void pop_back() {
        if (size_ == 0) return;
        data_[--size_].~T();
    }

    // clear()
    void clear() noexcept {
        destroy_range(data_, data_ + size_);
        size_ = 0;
    }

    // reserve()
    void reserve(size_t newCap) {
        if (newCap <= cap_) return;

        T *newData = allocate_raw(newCap);
        size_t i = 0;
        try {
            for (; i < size_; ++i)
                new(newData + i) T(std::move_if_noexcept(data_[i]));
        } catch (...) {
            destroy_range(newData, newData + i);
            deallocate_raw(newData);
            throw;
        }

        destroy_range(data_, data_ + size_);
        deallocate_raw(data_);
        data_ = newData;
        cap_ = newCap;
    }

    // swap()
    void swap(Vector &other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(cap_, other.cap_);
    }
};

class Task5_2 {
public:
    int run() {
        cout << "Задание 5.2 Свой вектор\n\n";

        // Конструктор по умолчанию
        // size = 0, capacity = 0, empty = true
        Vector<int> v;
        cout << "Конструктор по умолчанию:\n";
        cout << "size = " << v.size()
                << ", capacity = " << v.capacity()
                << ", empty = " << (v.empty() ? "true" : "false") << "\n\n";

        // push_back + геометрическое увеличение capacity (×2)
        cout << "push_back() и рост capacity:\n";
        for (int i = 1; i <= 6; ++i) {
            v.push_back(i * 10);
            cout << "Добавлен элемент " << i * 10
                    << " -> size = " << v.size()
                    << ", capacity = " << v.capacity() << "\n";
        }
        cout << "\n";

        // Доступ к элементам: operator[]
        cout << "Доступ к элементам через operator[]:\n";
        for (size_t i = 0; i < v.size(); ++i)
            cout << v[i] << " ";
        cout << "\n\n";

        // front() и back()
        cout << "front = " << v.front()
                << ", back = " << v.back() << "\n\n";

        // pop_back() — явный вызов деструктора элемента
        v.pop_back();
        cout << "После pop_back():\n";
        cout << "size = " << v.size()
                << ", back = " << v.back() << "\n\n";

        // emplace_back() — placement new
        v.emplace_back(777);
        cout << "После emplace_back(777):\n";
        cout << "back = " << v.back()
                << ", size = " << v.size() << "\n\n";

        // Конструктор с размером и значением
        Vector<int> a(3, 5);
        cout << "Конструктор Vector(3, 5):\n";
        for (size_t i = 0; i < a.size(); ++i)
            cout << a[i] << " ";
        cout << "\n";
        cout << "size = " << a.size()
                << ", capacity = " << a.capacity() << "\n\n";

        // reserve() — управление памятью
        a.reserve(10);
        cout << "После reserve(10):\n";
        cout << "size = " << a.size()
                << ", capacity = " << a.capacity() << "\n\n";

        // Конструктор копирования
        Vector<int> b = a;
        cout << "Конструктор копирования (b = a):\n";
        for (size_t i = 0; i < b.size(); ++i)
            cout << b[i] << " ";
        cout << "\n\n";

        // Работа с произвольным типом (std::string)
        Vector<string> strings;
        strings.emplace_back("Hello");
        strings.push_back("World");

        cout << "Vector<string>:\n";
        for (size_t i = 0; i < strings.size(); ++i)
            cout << strings[i] << " ";
        cout << "\n\n";

        // at() — проверка границ и исключение
        cout << "Проверка at(): обращение за границы\n";
        try {
            strings.at(5) = "!";
        } catch (const out_of_range &e) {
            cout << "Поймано исключение: " << e.what() << "\n";
        }
        cout << "\n";

        // clear() — удаление элементов без утечки памяти
        strings.clear();
        cout << "После clear():\n";
        cout << "size = " << strings.size()
                << ", capacity = " << strings.capacity() << "\n\n";

        return 0;
    }
};
