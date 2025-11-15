#include "Task2_3.h"
#include <iostream>
using namespace std;

// f(x) из условия
float f(float x) {
    if (x > 0) return x;
    else if (x >= -1) return 0;
    else return x * x;
}

// Возвращает значение
float F(float x) {
    return f(x);
}

// Записывает результат в ссылку
void F(float x, float &y) {
    y = f(x);
}

void Task2_3::run() {
    cout << "Задание 2.3 Перегрузка функций, Вариант 16\n\n";

    float a = -2.0, b = 2.0, h = 0.5;

    cout << "y = F(x):\n";
    for (float x = a; x <= b; x += h) {
        float y = F(x);
        cout << "x = " << x << ": y = " << y << "\n";
    }

    cout << "\n" << endl;

    cout << "F(x, y):\n";
    for (float x = a; x <= b; x += h) {
        float y;
        F(x, y);
        cout << "x = " << x << ": y = " << y << "\n";
    }
}
