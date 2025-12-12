// Task5_2.cpp
#include <iostream>
#include <new>
#include <stdexcept>
#include <utility>
#include <string>

using namespace std;

// ===================== Шаблонный Vector<T> =====================
template<typename T>
class Vector {
private:
    T* data_;          // указатель на блок памяти (не инициализированных объектов)
    size_t size_;      // количество инициализированных элементов
    size_t cap_;       // выделенная емкость (количество объектов, которые можно разместить)

    // allocate / deallocate
    static T* allocate_raw(size_t n) {
        if (n == 0) return nullptr;
        void* mem = ::operator new(n * sizeof(T)); // может бросить bad_alloc
        return static_cast<T*>(mem);
    }

    static void deallocate_raw(T* p) noexcept {
        ::operator delete(p);
    }

    // уничтожить диапазон [from, to)
    static void destroy_range(T* from, T* to) noexcept {
        while (to != from) {
            --to;
            to->~T();
        }
    }

    // Увеличить capacity геометрически (×2)
    void grow_if_needed() {
        size_t newCap = cap_ == 0 ? 1 : cap_ * 2;
        reserve(newCap);
    }

public:
    // --- Конструкторы / Деструктор ---

    Vector() noexcept : data_(nullptr), size_(0), cap_(0) {}

    explicit Vector(size_t n) : data_(nullptr), size_(0), cap_(0) {
        if (n == 0) return;
        data_ = allocate_raw(n);
        size_t i = 0;
        try {
            for (; i < n; ++i) new (data_ + i) T();
        } catch (...) {
            destroy_range(data_, data_ + i);
            deallocate_raw(data_);
            data_ = nullptr;
            throw;
        }
        size_ = cap_ = n;
    }

    Vector(size_t n, const T& value) : data_(nullptr), size_(0), cap_(0) {
        if (n == 0) return;
        data_ = allocate_raw(n);
        size_t i = 0;
        try {
            for (; i < n; ++i) new (data_ + i) T(value);
        } catch (...) {
            destroy_range(data_, data_ + i);
            deallocate_raw(data_);
            data_ = nullptr;
            throw;
        }
        size_ = cap_ = n;
    }

    // Конструктор копирования
    Vector(const Vector& other) : data_(nullptr), size_(0), cap_(0) {
        if (other.size_ == 0) return;
        data_ = allocate_raw(other.size_);
        size_t i = 0;
        try {
            for (; i < other.size_; ++i) new (data_ + i) T(other.data_[i]);
        } catch (...) {
            destroy_range(data_, data_ + i);
            deallocate_raw(data_);
            data_ = nullptr;
            throw;
        }
        size_ = cap_ = other.size_;
    }

    // Конструктор перемещения
    Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), cap_(other.cap_) {
        other.data_ = nullptr;
        other.size_ = other.cap_ = 0;
    }

    // Оператор присваивания (copy-and-swap)
    Vector& operator=(Vector other) noexcept {
        swap(other);
        return *this;
    }

    // Деструктор
    ~Vector() {
        if (data_) {
            destroy_range(data_, data_ + size_);
            deallocate_raw(data_);
        }
    }

    // --- Доступ к элементам ---
    T& operator[](size_t idx) noexcept { return data_[idx]; }
    const T& operator[](size_t idx) const noexcept { return data_[idx]; }

    T& at(size_t idx) {
        if (idx >= size_) throw out_of_range("Vector::at: index out of range");
        return data_[idx];
    }
    const T& at(size_t idx) const {
        if (idx >= size_) throw out_of_range("Vector::at: index out of range");
        return data_[idx];
    }

    T* data() noexcept { return data_; }
    const T* data() const noexcept { return data_; }

    T& front() { return data_[0]; }
    const T& front() const { return data_[0]; }

    T& back() { return data_[size_ - 1]; }
    const T& back() const { return data_[size_ - 1]; }

    // --- Информация ---
    size_t size() const noexcept { return size_; }
    size_t capacity() const noexcept { return cap_; }
    bool empty() const noexcept { return size_ == 0; }

    // --- Модификаторы ---
    void push_back(const T& value) {
        if (size_ == cap_) grow_if_needed();
        new (data_ + size_) T(value);
        ++size_;
    }

    void push_back(T&& value) {
        if (size_ == cap_) grow_if_needed();
        new (data_ + size_) T(std::move(value));
        ++size_;
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ == cap_) grow_if_needed();
        new (data_ + size_) T(std::forward<Args>(args)...);
        ++size_;
    }

    void pop_back() {
        if (size_ == 0) return;
        data_[size_-1].~T();
        --size_;
    }

    void clear() noexcept {
        destroy_range(data_, data_ + size_);
        size_ = 0;
    }

    // reserve: базовая гарантия — при исключении объект остается в прежнем состоянии
    void reserve(size_t newCap) {
        if (newCap <= cap_) return;

        T* newData = allocate_raw(newCap);
        size_t i = 0;
        try {
            for (; i < size_; ++i)
                new (newData + i) T(std::move_if_noexcept(data_[i]));
        } catch (...) {
            // если что-то упало во время копирования/перемещения — очистим и освободим
            destroy_range(newData, newData + i);
            deallocate_raw(newData);
            throw;
        }

        // успешно скопировали/переместили — можем уничтожить старые и заменить
        destroy_range(data_, data_ + size_);
        deallocate_raw(data_);
        data_ = newData;
        cap_ = newCap;
    }

    // swap
    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(cap_, other.cap_);
    }
};


class Task5_2 {
public:
    int run() {
        cout << "Задание 5.2 — демонстрация Vector<T>\n\n";

        // --- Демонстрация с int ---
        Vector<int> v;
        cout << "После default ctor: size=" << v.size() << " cap=" << v.capacity() << "\n";

        for (int i = 1; i <= 6; ++i) {
            v.push_back(i * 10);
            cout << "push_back(" << i*10 << ") -> size=" << v.size() << " cap=" << v.capacity() << "\n";
        }

        cout << "Элементы v: ";
        for (size_t i = 0; i < v.size(); ++i) cout << v[i] << " ";
        cout << "\n\n";

        v.pop_back();
        cout << "После pop_back(): size=" << v.size() << " cap=" << v.capacity() << "\n\n";

        v.emplace_back(777);
        cout << "После emplace_back(777): back=" << v.back() << " size=" << v.size() << "\n\n";

        // --- Демонстрация reserve и copy ---
        Vector<int> a(3, 5); // {5,5,5}
        cout << "a: size=" << a.size() << " cap=" << a.capacity() << "\n";
        a.reserve(10);
        cout << "a после reserve(10): size=" << a.size() << " cap=" << a.capacity() << "\n";

        Vector<int> b = a; // копирование
        cout << "b (копия a): size=" << b.size() << " cap=" << b.capacity() << "\n";

        // --- Демонстрация для std::string и at() ---
        Vector<string> strings;
        strings.emplace_back("Hello");
        strings.push_back(string("World"));

        cout << "\nstrings: size=" << strings.size() << " cap=" << strings.capacity() << "\n";
        for (size_t i = 0; i < strings.size(); ++i) cout << strings[i] << " ";
        cout << "\n";

        cout << "Демонстрация at(): попытка обратиться к индексу 5 (out_of_range expected)\n";
        try {
            strings.at(5) = "!"; // должен бросить std::out_of_range
        } catch (const out_of_range& e) {
            cout << "Поймано исключение: " << e.what() << "\n";
        }

        // --- clear и отсутствие утечек ---
        strings.clear();
        cout << "После clear(): strings.size=" << strings.size() << " cap=" << strings.capacity() << "\n";

        return 0;
    }
};