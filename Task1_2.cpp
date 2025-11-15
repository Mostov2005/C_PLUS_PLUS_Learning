#include "Task1_2.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

void Task1_2::run() {
    cout << "Задание 1.2 Исследование массивов\n\n";

    const int n = 5, rows = 3, cols = 4;

    // 1. Создание без инициализации
    cout << "1. Создание без инициализации:\n";

    // Одномерный статический массив
    int static1D[n];
    cout << "Статический 1D: ";
    for (int i = 0; i < n; i++) cout << static1D[i] << " ";
    cout << "\nАдреса: ";
    for (int i = 0; i < n; i++) cout << &static1D[i] << " ";
    cout << "\n";

    // Одномерный динамический массив
    int *dynamic1D = new int[n];
    cout << "Динамический 1D: ";
    for (int i = 0; i < n; i++) cout << dynamic1D[i] << " ";
    cout << "\nАдреса: ";
    for (int i = 0; i < n; i++) cout << (dynamic1D + i) << " ";
    cout << "\n";

    // Двумерный как единый блок
    int *block2D = new int[rows * cols];
    cout << "2D блок памяти: ";
    for (int i = 0; i < rows * cols; i++) cout << block2D[i] << " ";
    cout << "\n";

    // Двумерный статический массив
    int static2D[rows][cols];
    cout << "Статический 2D: ";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) cout << static2D[i][j] << " ";
    }
    cout << "\n";

    // Двумерный динамический массив (массив указателей)
    int **dynamic2D = new int *[rows];
    for (int i = 0; i < rows; i++) dynamic2D[i] = new int[cols];
    cout << "Динамический 2D: ";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) cout << dynamic2D[i][j] << " ";
    }
    cout << "\n\n";

    // 2. Заполнение из файла
    cout << "2. Заполнение из файла:\n";
    ifstream fin("Task1_2.txt");
    if (fin.is_open()) {
        for (int i = 0; i < n; i++) {
            if (!(fin >> dynamic1D[i])) dynamic1D[i] = 0;
            cout << "dynamic1D[" << i << "] = " << dynamic1D[i] << "\n";
        }
        for (int i = 0; i < rows * cols; i++) fin >> block2D[i];
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) fin >> dynamic2D[i][j];
    }
    fin.close();

    cout << "Динамический 1D: ";
    for (int i = 0; i < n; i++) cout << dynamic1D[i] << " ";
    cout << "\n2D блок памяти: ";
    for (int i = 0; i < rows * cols; i++) cout << block2D[i] << " ";
    cout << "\nДинамический 2D: ";
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) cout << dynamic2D[i][j] << " ";
    cout << "\n\n";

    // 3. Вывод на консоль с адресами
    cout << "3. Вывод элементов с адресами:\n";
    cout << "Статический 1D: ";
    for (int i = 0; i < n; i++) cout << static1D[i] << " ";
    cout << "\nАдреса: ";
    for (int i = 0; i < n; i++) cout << &static1D[i] << " ";
    cout << "\n";

    cout << "Динамический 1D: ";
    for (int i = 0; i < n; i++) cout << dynamic1D[i] << " ";
    cout << "\nАдреса: ";
    for (int i = 0; i < n; i++) cout << (dynamic1D + i) << " ";

    cout << "\n\n";

    // 4. Операции
    cout << "4. Операции с массивами:\n";
    // получить элемент по индексу
    cout << "Элемент static1D[2]: " << static1D[2] << "\n";
    cout << "Элемент dynamic2D[1][2]: " << dynamic2D[1][2] << "\n";

    // обмен первого и последнего элементов/строк/столбцов
    swap(static1D[0], static1D[n - 1]);
    swap(dynamic1D[0], dynamic1D[n - 1]);
    for (int j = 0; j < cols; j++) swap(dynamic2D[0][j], dynamic2D[rows - 1][j]); // строки
    for (int i = 0; i < rows; i++) swap(dynamic2D[i][0], dynamic2D[i][cols - 1]); // столбцы

    cout << "После обмена:\n";
    cout << "static1D: ";
    for (int i = 0; i < n; i++) cout << static1D[i] << " ";
    cout << "\ndynamic1D: ";
    for (int i = 0; i < n; i++) cout << dynamic1D[i] << " ";
    cout << "\ndynamic2D: ";
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) cout << dynamic2D[i][j] << " ";
    cout << "\n";

    // 5. Завершение работы
    delete[] dynamic1D;
    delete[] block2D;
    for (int i = 0; i < rows; i++) delete[] dynamic2D[i];
    delete[] dynamic2D;
}
