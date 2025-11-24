#ifndef C__LEARNING_TASK4_2_H
#define C__LEARNING_TASK4_2_H

#include <vector>

class Task4_2 {
public:
    void run();
};

// Класс для работы с одномерным массивом целых чисел
class IntArrayClass {
private:
    std::vector<int> IntArray;
    static int count; // количество объектов

public:
    // Конструкторы
    IntArrayClass();
    IntArrayClass(const std::vector<int>& arr);

    // Деструктор
    ~IntArrayClass();

    // Методы
    void input();       // ввод элементов
    void output() const; // вывод элементов
    void sortArray();   // сортировка по возрастанию
    size_t size() const; // размер массива
    int sum() const;     // сумма элементов

    // Перегрузка операторов
    IntArrayClass& operator++(); // ++
    IntArrayClass& operator--(); // --
    IntArrayClass operator*(int scalar) const; // *

    // Статический метод
    static int getCount();
};

#endif //C__LEARNING_TASK4_2_H
