// #include "Task2_4.h"
// #include <iostream>
// #include <fstream>
// #include <iomanip>
// #include <cstdlib>
// #include <ctime>
// using namespace std;
//
// void Task2_4::run() {
//     cout << "Задание 2.4 Работа с таблицами, Вариант 4\n\n";
//
//     srand(time(nullptr)); // сид для рандома
//
//     int rows = 4, cols = 4;
//     int **mat = createTable<int>(rows, cols);
//
//     //  2a. Заполнение нулями
//     cout << "Заполнение нулями:\n";
//     fillZero(mat, rows, cols);
//     printTable(mat, rows, cols);
//
//     // 2b. Заполнение случайными числами
//     cout << "\nЗаполнение случайными числами:\n";
//     fillRandom(mat, rows, cols, 0, 10);
//     printTable(mat, rows, cols);
//
//     //  2c. Заполнение с клавиатуры
//     cout << "\nЗаполнение с клавиатуры:\n";
//     fillKeyboard(mat, rows, cols);
//     printTable(mat, rows, cols);
//
//     //  2d. Заполнение из файла
//     cout << "\nЗаполнение из файла:\n";
//     fillFromFile(mat, rows, cols, "Task2_4.txt");
//     printTable(mat, rows, cols);
//
//
//     //  3. Запись в файл
//     printTableToFile(mat, rows, cols, "output_table.txt");
//     cout << "\nМатрица записана в output_table.txt\n";
//
//     // 4. Среднее ниже побочной диагонали
//     double avg = averageBelowSecondaryDiagonal(mat, rows, cols);
//     cout << "\nСреднее арифметическое элементов ниже побочной диагонали: " << avg << "\n";
//
//     //  5. Освобождение памяти
//     freeTable(mat, rows);
// }
//
// // 1. Создание таблицы
// template<typename T>
// T **Task2_4::createTable(int rows, int cols) {
//     T **table = new T *[rows];
//     for (int i = 0; i < rows; i++)
//         table[i] = new T[cols];
//     return table;
// }
//
// // 2а. Заполнение нулями
// template<typename T>
// void Task2_4::fillZero(T **table, int rows, int cols) {
//     for (int i = 0; i < rows; i++)
//         for (int j = 0; j < cols; j++)
//             table[i][j] = 0;
// }
//
// // 2б. Заполнение случайными числами
// template<typename T>
// void Task2_4::fillRandom(T **table, int rows, int cols, T minVal, T maxVal) {
//     for (int i = 0; i < rows; i++)
//         for (int j = 0; j < cols; j++)
//             table[i][j] = minVal + rand() % (maxVal - minVal + 1);
// }
//
// // 2в. Заполнение с клавиатуры
// template<typename T>
// void Task2_4::fillKeyboard(T **table, int rows, int cols) {
//     for (int i = 0; i < rows; i++)
//         for (int j = 0; j < cols; j++) {
//             cout << "table[" << i << "][" << j << "] = ";
//             cin >> table[i][j];
//         }
// }
//
// // 2г. Заполнение из файла
// template<typename T>
// void Task2_4::fillFromFile(T **table, int rows, int cols, const string &filename) {
//     ifstream fin(filename);
//     if (!fin) {
//         cout << "Файл " << filename << " не найден!\n";
//         return;
//     }
//     for (int i = 0; i < rows; i++)
//         for (int j = 0; j < cols; j++)
//             fin >> table[i][j];
//     fin.close();
// }
//
// // 3а. Вывод в консоль
// template<typename T>
// void Task2_4::printTable(T **table, int rows, int cols) {
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++)
//             cout << setw(5) << table[i][j];
//         cout << "\n";
//     }
// }
//
// // 3б. Вывод в файл
// template<typename T>
// void Task2_4::printTableToFile(T **table, int rows, int cols, const string &filename) {
//     ofstream fout(filename);
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++)
//             fout << table[i][j] << " ";
//         fout << "\n";
//     }
//     fout.close();
// }
//
// // 4. Среднее арифметическое элементов, расположенных ниже побочной диагонали
// template<typename T>
// double Task2_4::averageBelowSecondaryDiagonal(T **table, int rows, int cols) {
//     double sum = 0;
//     int count = 0;
//     for (int i = 0; i < rows; i++)
//         for (int j = 0; j < cols; j++)
//             if (i + j > cols - 1) {
//                 sum += table[i][j];
//                 count++;
//             }
//     return count ? sum / count : 0;
// }
//
// // 5. Освобождение памяти
// template<typename T>
// void Task2_4::freeTable(T **table, int rows) {
//     for (int i = 0; i < rows; i++)
//         delete[] table[i];
//     delete[] table;
// }


#include "Task2_4.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <memory> // для unique_ptr
using namespace std;

void Task2_4::run() {
    cout << "Задание 2.4 Работа с таблицами, Вариант 4\n\n";

    srand(time(nullptr)); // сид для рандома

    int rows = 4, cols = 4;
    auto mat = createTable<int>(rows, cols);

    // 2a. Заполнение нулями
    cout << "Заполнение нулями:\n";
    fillZero(mat, rows, cols);
    printTable(mat, rows, cols);

    // 2b. Заполнение случайными числами
    cout << "\nЗаполнение случайными числами:\n";
    fillRandom(mat, rows, cols, 0, 10);
    printTable(mat, rows, cols);

    // 2c. Заполнение с клавиатуры
    cout << "\nЗаполнение с клавиатуры:\n";
    fillKeyboard(mat, rows, cols);
    printTable(mat, rows, cols);

    // 2d. Заполнение из файла
    cout << "\nЗаполнение из файла:\n";
    fillFromFile(mat, rows, cols, "Task2_4.txt");
    printTable(mat, rows, cols);

    // 3. Запись в файл
    printTableToFile(mat, rows, cols, "output_table.txt");
    cout << "\nМатрица записана в output_table.txt\n";

    // 4. Среднее ниже побочной диагонали
    double avg = averageBelowSecondaryDiagonal(mat, rows, cols);
    cout << "\nСреднее арифметическое элементов ниже побочной диагонали: " << avg << "\n";

    // 5. Освобождение памяти — теперь не требуется!
}

// 1. Создание таблицы с unique_ptr
template<typename T>
unique_ptr<unique_ptr<T[]>[]> Task2_4::createTable(int rows, int cols) {
    auto table = make_unique<unique_ptr<T[]>[]>(rows);
    for (int i = 0; i < rows; i++)
        table[i] = make_unique<T[]>(cols);
    return table;
}


// 2a. Заполнение нулями
template<typename T>
void Task2_4::fillZero(unique_ptr<unique_ptr<T[]>[]> &table, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            table[i][j] = 0;
}

// 2b. Заполнение случайными числами
template<typename T>
void Task2_4::fillRandom(unique_ptr<unique_ptr<T[]>[]> &table, int rows, int cols, T minVal, T maxVal) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            table[i][j] = minVal + rand() % (maxVal - minVal + 1);
}

// 2c. Заполнение с клавиатуры
template<typename T>
void Task2_4::fillKeyboard(unique_ptr<unique_ptr<T[]>[]> &table, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            cout << "table[" << i << "][" << j << "] = ";
            cin >> table[i][j];
        }
}

// 2d. Заполнение из файла
template<typename T>
void Task2_4::fillFromFile(unique_ptr<unique_ptr<T[]>[]> &table, int rows, int cols, const string &filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Файл " << filename << " не найден!\n";
        return;
    }
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fin >> table[i][j];
    fin.close();
}

// 3a. Вывод в консоль
template<typename T>
void Task2_4::printTable(unique_ptr<unique_ptr<T[]>[]> &table, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            cout << setw(5) << table[i][j];
        cout << "\n";
    }
}

// 3b. Вывод в файл
template<typename T>
void Task2_4::printTableToFile(unique_ptr<unique_ptr<T[]>[]> &table, int rows, int cols, const string &filename) {
    ofstream fout(filename);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            fout << table[i][j] << " ";
        fout << "\n";
    }
    fout.close();
}

// 4. Среднее арифметическое элементов ниже побочной диагонали
template<typename T>
double Task2_4::averageBelowSecondaryDiagonal(unique_ptr<unique_ptr<T[]>[]> &table, int rows, int cols) {
    double sum = 0;
    int count = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (i + j > cols - 1) {
                sum += table[i][j];
                count++;
            }
    return count ? sum / count : 0;
}
