#include "Task4_1.h"
#include <iostream>
#include <utility>

using namespace std;


// Конструктор по умолчанию
Cargo::Cargo() : weight(0) {
    cout << "Конструктор по умолчанию\n";
}

// Параметризированный конструктор
Cargo::Cargo(double w) : weight(w >= 0 ? w : 0) {
    // если вес отрицательный, ставим 0
    cout << "Параметризированный конструктор\n";
}

// Конструктор копирования
Cargo::Cargo(const Cargo &other) : weight(other.weight) {
    cout << "Конструктор копирования\n";
}

// Конструктор перемещения
Cargo::Cargo(Cargo &&other) noexcept : weight(other.weight) {
    other.weight = 0; // "забираем" вес, у исходного объекта ставим 0
    cout << "Конструктор перемещения\n";
}

// Оператор копирующего присваивания
Cargo &Cargo::operator=(const Cargo &other) {
    cout << "Оператор копирующего присваивания\n";
    if (this != &other) {
        // проверка самоприсваивания
        weight = other.weight;
    }
    return *this;
}

// Оператор перемещения
Cargo &Cargo::operator=(Cargo &&other) noexcept {
    cout << "Оператор перемещающего присваивания\n";
    if (this != &other) {
        // проверка самоприсваивания
        weight = other.weight;
        other.weight = 0; // "забираем" вес, у исходного объекта ставим 0
    }
    return *this;
}

// Деструктор
Cargo::~Cargo() {
    cout << "Деструктор для объекта с весом = " << weight << "\n";
}

// Метод для получения веса (только для чтения)
double Cargo::getWeight() const {
    return weight;
}

void Task4_1::run() {
    cout << "Задание 4.1 Миникласс, Вариант 7\n\n";
    cout << "7. Груз с одним числовым полем - весом.\n"
            "Значение веса устанавливается при создании объекта и не может быть отрицательным.\n"
            "В дальнейшем можно только посмотреть значение веса методом getWeight().\n\n";
    Cargo o;
    cout << "Вес объекта o = " << o.getWeight() << "\n";

    Cargo a(12); // параметризированный конструктор
    cout << "Вес объекта a = " << a.getWeight() << "\n";

    Cargo b(-5); // параметризированный конструктор, но вес станет 0
    cout << "Вес объекта b = " << b.getWeight() << "\n";

    Cargo c = a; // конструктор копирования
    cout << "Вес объекта c = " << c.getWeight() << "\n";

    Cargo d = std::move(a); // конструктор перемещения
    cout << "Вес объекта d = " << d.getWeight() << "\n";
    cout << "Вес объекта a = " << a.getWeight() << "\n";

    cout << "\n" << endl;

    Cargo e;
    e = c; // копирующее присваивание
    cout << "Вес объекта e = " << e.getWeight() << "\n";

    Cargo f; // Создали, а потом мув
    f = std::move(d); // перемещающее присваивание
    cout << "Вес объекта f = " << f.getWeight() << "\n";

    cout << "\n" << endl;
}
