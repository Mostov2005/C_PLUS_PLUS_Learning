#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Sound {
    int height;
    double duration;

    void print() const {
        cout << "Нота: " << height << ", Длительность: " << duration << "\n";
    }
};

class Task4_5 {
public:
    int run() {
        cout << "Задание 4.5 Мелодия (+ алгоритмы)\n";
        cout << "Создать Мелодию - последовательный контейнер элементов класса Звук\n"
                "(поля: высота ноты, длительность звучания). \n"
                "Реализовать следующие возможности с использованием подходящих алгоритмов стандартной библиотеки:\n"
                "5. Изменить мелодию, сделав каждый звук на тон выше, а длительность в два раза меньше.\n"
                "10. Найти два идущих подряд звука, совпадающих по высоте. \n"
                "17. Узнать, какой звук звучал бы N-м по счёту (и какие звуки шли бы до него, а какие после), \n"
                "если бы звуки мелодии были расположены по длительности от самой длинной к самой короткой, \n"
                "а при равенстве длительности от самой высокой к самой низкой.\n\n";


        vector<Sound> melody = {
            {60, 1.0}, {62, 0.5}, {64, 0.5},
            {64, 0.5}, {65, 1.5}, {67, 1.0}
        };

        cout << "Исходная мелодия:\n";
        for (auto &s: melody) s.print();

        // 5. Изменить мелодию: высота +1, длительность /2
        for_each(melody.begin(), melody.end(), [](Sound &s) {
            s.height += 1;
            s.duration /= 2.0;
        });

        cout << "\nМелодия после изменения (высота+1, длительность/2):\n";
        for (auto &s: melody) s.print();

        // 10. Найти два подряд идущих звука с одинаковой высотой
        auto it = adjacent_find(melody.begin(), melody.end(), [](const Sound &a, const Sound &b) {
            return a.height == b.height;
        });

        if (it != melody.end() && (it + 1) != melody.end()) {
            cout << "\nДва подряд идущих звука с одинаковой высотой:\n";
            it->print();
            (it + 1)->print();
        } else {
            cout << "\nТаких подряд идущих звуков нет.\n";
        }

        // 17. N-й звук по длительности (убывание), при равенстве — по высоте (убывание)
        int N = 3;
        vector<Sound> sorted_melody = melody; // копия для сортировки

        sort(sorted_melody.begin(), sorted_melody.end(), [](const Sound &a, const Sound &b) {
            if (a.duration != b.duration) return a.duration > b.duration; // по длительности, убывание
            return a.height > b.height; // при равенстве — по высоте, убывание
        });

        if (N <= 0 || N > (int) sorted_melody.size()) {
            cout << "\nНекорректное N!";
        } else {
            cout << "\nN-й звук по отсортированной мелодии:\n";
            sorted_melody[N - 1].print();

            cout << "Звуки до него:\n";
            for (int i = 0; i < N - 1; ++i) sorted_melody[i].print();

            cout << "Звуки после него:\n";
            for (size_t i = N; i < sorted_melody.size(); ++i) sorted_melody[i].print();
        }

        return 0;
    }
};
