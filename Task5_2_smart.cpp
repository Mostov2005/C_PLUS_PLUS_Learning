#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <string>

using namespace std;

template<typename T>
class Vector_smart {
private:
    unique_ptr<T[]> data_; // умный указатель на массив
    size_t size_; // текущий размер
    size_t cap_; // вместимость

    // Увеличение capacity ×2
    void grow_if_needed() {
        size_t newCap = (cap_ == 0 ? 1 : cap_ * 2);
        reserve(newCap);
    }

public:
    // --- Конструкторы ---

    Vector_smart() : data_(nullptr), size_(0), cap_(0) {
    }

    explicit Vector_smart(size_t n) : data_(nullptr), size_(0), cap_(0) {
        if (n == 0) return;
        data_ = make_unique<T[]>(n);
        for (size_t i = 0; i < n; ++i)
            data_[i] = T(); // инициализация значением по умолчанию
        size_ = cap_ = n;
    }

    Vector_smart(size_t n, const T &value) {
        data_ = make_unique<T[]>(n);
        for (size_t i = 0; i < n; ++i)
            data_[i] = value;
        size_ = cap_ = n;
    }

    // Копирование
    Vector_smart(const Vector_smart &other) : size_(other.size_), cap_(other.cap_) {
        if (cap_ == 0) return;
        data_ = make_unique<T[]>(cap_);
        for (size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }

    // Перемещение
    Vector_smart(Vector_smart &&other) noexcept = default;

    // Присваивание (copy-and-swap)
    Vector_smart &operator=(Vector_smart other) noexcept {
        swap(other);
        return *this;
    }

    // --- Методы доступа ---

    T &operator[](size_t idx) noexcept { return data_[idx]; }
    const T &operator[](size_t idx) const noexcept { return data_[idx]; }

    T &at(size_t idx) {
        if (idx >= size_) throw out_of_range("Vector::at: index out of range");
        return data_[idx];
    }

    const T &at(size_t idx) const {
        if (idx >= size_) throw out_of_range("Vector::at: index out of range");
        return data_[idx];
    }

    size_t size() const noexcept { return size_; }
    size_t capacity() const noexcept { return cap_; }
    bool empty() const noexcept { return size_ == 0; }

    // --- Модификаторы ---

    void push_back(const T &value) {
        if (size_ == cap_) grow_if_needed();
        data_[size_++] = value;
    }

    void push_back(T &&value) {
        if (size_ == cap_) grow_if_needed();
        data_[size_++] = std::move(value);
    }

    template<typename... Args>
    void emplace_back(Args &&... args) {
        if (size_ == cap_) grow_if_needed();
        data_[size_] = T(std::forward<Args>(args)...);
        size_++;
    }

    void pop_back() {
        if (size_ > 0) size_--;
    }

    void clear() noexcept {
        size_ = 0;
    }

    void reserve(size_t newCap) {
        if (newCap <= cap_) return;

        unique_ptr<T[]> newData = make_unique<T[]>(newCap);

        for (size_t i = 0; i < size_; ++i)
            newData[i] = std::move_if_noexcept(data_[i]);

        data_ = std::move(newData);
        cap_ = newCap;
    }

    void swap(Vector_smart &other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(cap_, other.cap_);
    }
};


class Task5_2_smart {
public:
    int run() {
        cout << "Vector_smart<T> с умными указателями\n\n";

        Vector_smart<int> v;
        cout << "После default ctor: size=" << v.size() << " cap=" << v.capacity() << "\n";

        for (int i = 1; i <= 6; ++i) {
            v.push_back(i * 10);
            cout << "push_back(" << i * 10 << ") -> size=" << v.size() << " cap=" << v.capacity() << "\n";
        }

        cout << "Элементы v: ";
        for (size_t i = 0; i < v.size(); ++i) cout << v[i] << " ";
        cout << "\n\n";

        v.pop_back();
        cout << "После pop_back(): size=" << v.size() << " cap=" << v.capacity() << "\n\n";

        v.emplace_back(777);
        cout << "После emplace_back(777): back=" << v[v.size() - 1] << " size=" << v.size() << "\n\n";

        Vector_smart<int> a(3, 5);
        cout << "a: size=" << a.size() << " cap=" << a.capacity() << "\n";
        a.reserve(10);
        cout << "a после reserve(10): size=" << a.size() << " cap=" << a.capacity() << "\n";

        Vector_smart<int> b = a;
        cout << "b (копия a): size=" << b.size() << " cap=" << b.capacity() << "\n";

        Vector_smart<string> strings;
        strings.emplace_back("Hello");
        strings.push_back(string("World"));

        cout << "\nstrings: size=" << strings.size() << " cap=" << strings.capacity() << "\n";
        for (size_t i = 0; i < strings.size(); ++i) cout << strings[i] << " ";
        cout << "\n";

        cout << "Демонстрация at(): попытка вызвать index 5\n";
        try {
            strings.at(5) = "!";
        } catch (const out_of_range &e) {
            cout << "Поймано исключение: " << e.what() << "\n";
        }

        strings.clear();
        cout << "После clear(): size=" << strings.size() << " cap=" << strings.capacity() << "\n";

        return 0;
    }
};
