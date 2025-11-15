#ifndef C__LEARNING_TASK2_4_H
#define C__LEARNING_TASK2_4_H

#include <string>
using namespace std;

class Task2_4 {
public:
    void run();

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
};

#endif //C__LEARNING_TASK2_4_H
