#include "Task3_3.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void Task3_3::run() {
    cout << "Задание 3.3 Точки на плоскости, Вариант 2\n\n";

    vector<pair<int, int> > points = {
        {1, 2}, {-3, 4},
        {5, -2}, {-1, -1}, {0, 0}, {2, 1}, {1, 5}
    };

    cout << "Исходные точки:\n";
    for (auto &p: points)
        cout << "(" << p.first << "," << p.second << ") ";
    cout << "\n\n";

    // a) удалить все точки из II четверти (x<0, y>0)
    points.erase(
        remove_if(points.begin(), points.end(),
                  [](const pair<int, int> &p) { return p.first < 0 && p.second > 0; }),
        points.end()
    );
    cout << "После удаления точек из II четверти:\n";
    for (auto &p: points)
        cout << "(" << p.first << "," << p.second << ") ";
    cout << "\n\n";

    // б) подсчитать количество точек, у которых x > y
    int count_x_gt_y = count_if(points.begin(), points.end(),
                                [](const pair<int, int> &p) { return p.first > p.second; });
    cout << "Количество точек, у которых x > y: " << count_x_gt_y << "\n\n";

    // в) найти наименее удалённую от начала координат точку
    auto closest = min_element(points.begin(), points.end(),
                               [](const pair<int, int> &a, const pair<int, int> &b) {
                                   return (a.first * a.first + a.second * a.second) <
                                          (b.first * b.first + b.second * b.second);
                               });
    if (closest != points.end())
        cout << "Наименее удалённая от начала координат точка: ("
                << closest->first << "," << closest->second << ")\n\n";

    // г) расположить в порядке возрастания координаты x, не меняя порядок точек с одинаковой x
    stable_sort(points.begin(), points.end(),
                [](const pair<int, int> &a, const pair<int, int> &b) { return a.first < b.first;});
    cout << "Точки, отсортированные по x:\n";
    for (auto &p: points)
        cout << "(" << p.first << "," << p.second << ") ";
    cout << "\n";
}
