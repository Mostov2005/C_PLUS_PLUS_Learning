#ifndef C__LEARNING_TASK2_4_H
#define C__LEARNING_TASK2_4_H

#include <string>
#include <memory>
using namespace std;

class Task2_4 {
public:
    void run();

    // ВЕРСИЯ СЫРЫХ УКАЗАТЕЛЕЙ
    /*
    // 1. Создание таблицы
    template<typename T>
    T **createTable(int rows, int cols);

    // 2а. Заполнение нулями
    template<typename T>
    void fillZero(T **table, int rows, int cols);

    // 2б. Заполнение случайными числами
    template<typename T>
    void fillRandom(T **table, int rows, int cols, T minVal, T maxVal);

    // 2в. Заполнение с клавиатуры
    template<typename T>
    void fillKeyboard(T **table, int rows, int cols);

    // 2г. Заполнение из файла
    template<typename T>
    void fillFromFile(T **table, int rows, int cols, const string &filename);

    // 3а. Вывод на консоль
    template<typename T>
    void printTable(T **table, int rows, int cols);

    // 3б. Вывод в файл
    template<typename T>
    void printTableToFile(T **table, int rows, int cols, const string &filename);

    // 4. Среднее арифметическое элементов ниже побочной диагонали
    template<typename T>
    double averageBelowSecondaryDiagonal(T **table, int rows, int cols);

    // 5. Освобождение памяти
    template<typename T>
    void freeTable(T **table, int rows);
    */

    // ВЕРСИЯ С УМНЫМИ УКАЗАТЕЛЯМИ (unique_ptr)

    // 1. Создание таблицы
    template<typename T>
    unique_ptr<unique_ptr<T[]>[]> createTable(int rows, int cols);

    // 2а. Заполнение нулями
    template<typename T>
    void fillZero(unique_ptr<unique_ptr<T[]>[]> &table, int rows, int cols);

    // 2б. Заполнение случайными числами
    template<typename T>
    void fillRandom(unique_ptr<unique_ptr<T[]>[]> &table, int rows, int cols, T minVal, T maxVal);

    // 2в. Заполнение с клавиатуры
    template<typename T>
    void fillKeyboard(unique_ptr<unique_ptr<T[]>[]> &table, int rows, int cols);

    // 2г. Заполнение из файла
    template<typename T>
    void fillFromFile(unique_ptr<unique_ptr<T[]>[]> &table, int rows, int cols, const string &filename);

    // 3а. Вывод на консоль
    template<typename T>
    void printTable(unique_ptr<unique_ptr<T[]>[]> &table, int rows, int cols);

    // 3б. Вывод в файл
    template<typename T>
    void printTableToFile(unique_ptr<unique_ptr<T[]>[]> &table, int rows, int cols, const string &filename);

    // 4. Среднее арифметическое элементов ниже побочной диагонали
    template<typename T>
    double averageBelowSecondaryDiagonal(unique_ptr<unique_ptr<T[]>[]> &table, int rows, int cols);

    // 5. Освобождение памяти — не требуется, unique_ptr всё сам очищает
};

#endif //C__LEARNING_TASK2_4_H
