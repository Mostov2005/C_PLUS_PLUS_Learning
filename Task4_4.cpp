#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

struct Patient {
    string surname;
    int age;
};

struct Film {
    string title;
    int year;
};

class Task4_4 {
public:
    int run() {
        cout << "Задание 4.4 Контейнеры и классы\n";
        cout << "18. Перечень пациентов поликлиники. Операции:\n"
                "а) Добавить пациента в начало списка, если ему больше N лет или в конец, если меньше.\n Поменять фамилию заданного пациента.\n"
                "б) Обменять заданного пациента местами с впереди стоящим. Добавить пациента в конец списка.\n";

        list<Patient> patients;
        int N = 40;

        // Добавление пациентов
        Patient p1{"Иванов", 45};
        Patient p2{"Петров", 30};
        Patient p3{"Владимирцев", 50};

        if (p1.age > N) patients.push_front(p1);
        else patients.push_back(p1);
        if (p2.age > N) patients.push_front(p2);
        else patients.push_back(p2);
        if (p3.age > N) patients.push_front(p3);
        else patients.push_back(p3);

        cout << "\nСписок пациентов:\n";
        for (const auto &p: patients)
            cout << p.surname << " " << p.age << "\n";

        // Изменение фамилии
        for (auto &p: patients) {
            if (p.surname == "Владимирцев") p.surname = "Смирнов";
        }

        // Обмен местами второго с первым
        auto it = ++patients.begin(); // второй элемент
        auto prev = it;
        --prev;
        iter_swap(it, prev);

        // Добавление нового пациента в конец
        patients.push_back({"Кузнецов", 35});

        // Вывод
        cout << "\nСписок пациентов:\n";
        for (const auto &p: patients)
            cout << p.surname << " " << p.age << "\n";


        cout << "Класс Каталог фильмов.\n"
                "Основное: по режиссёру получать список его фильмов.\n"
                "Дополнительное: добавлять и удалять режиссёров, добавлять фильм заданного режиссёра,\n"
                "удалять и изменять заданный фильм заданного режиссёра.\n"
                "6. Исправить ошибку в фамилии режиссёра. \n"
                "Найти фильмы всех режиссёров, выпущенные в прокат в заданном промежутке лет.\n\n";

        unordered_map<string, vector<Film> > catalog;

        catalog["Тарантино"] = {{"Криминальное чтиво", 1994}, {"Убить Билла", 2003}};
        catalog["Нолан"] = {{"Начало", 2010}, {"Интерстеллар", 2014}};

        // Добавление нового фильма к существующему режиссёру
        catalog["Нолан"].push_back({"Дюнкерк", 2017});

        // Исправление фамилии режиссёра
        catalog["Нолан_Исправлено"] = catalog["Нолан"];
        catalog.erase("Нолан"); // удаляем старый ключ

        // Вывод фильмов конкретного режиссёра
        cout << "Фильмы режиссёра Нолан_Исправлено:\n";
        for (const auto &film : catalog["Нолан_Исправлено"])
            cout << film.title << " (" << film.year << ")\n";

        // Поиск фильмов, выпущенных в заданном промежутке лет
        int year_start = 2000, year_end = 2015;
        cout << "\nФильмы, выпущенные с " << year_start << " по " << year_end << ":\n";
        for (const auto &[director, films] : catalog) {
            for (const auto &film : films) {
                if (film.year >= year_start && film.year <= year_end) {
                    cout << director << ": " << film.title << " (" << film.year << ")\n";
                }
            }
        }

    }
};
